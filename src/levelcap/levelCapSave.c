#include "global.h"

#include "bmsave.h"
#include "bmunit.h"

#include "base.h"

void (* ReadSramFast)(void const * src, void * dest, u32 size);
u32 WriteAndVerifySramFast(void const * src, void * dest, u32 size);

u32 packProgCaps() {
    u32 result = 0;
    result |= progCaps->lvlCapStage;
    result |= progCaps->swordLvlStage << 3;
    result |= progCaps->lanceLvlStage << (3+2*1);
    result |= progCaps->axeLvlStage << (3+2*2);
    result |= progCaps->bowLvlStage << (3+2*3);
    result |= progCaps->animaLvlStage << (3+2*4);
    result |= progCaps->lightLvlStage << (3+2*5);
    result |= progCaps->darkLvlStage << (3+2*6);
    result |= progCaps->staffLvlStage << (3+2*7);
    return result;
}

void unpackProgCaps(u32 bonusFlags) {
    progCaps->lvlCapStage = bonusFlags & 3;
    progCaps->swordLvlStage = (bonusFlags >> 3) & 2;
    progCaps->lanceLvlStage = (bonusFlags >> (3+2*1)) & 2;
    progCaps->axeLvlStage = (bonusFlags >> (3+2*2)) & 2;
    progCaps->bowLvlStage = (bonusFlags >> (3+2*3)) & 2;
    progCaps->animaLvlStage = (bonusFlags >> (3+2*4)) & 2;
    progCaps->lightLvlStage = (bonusFlags >> (3+2*5)) & 2;
    progCaps->darkLvlStage = (bonusFlags >> (3+2*6)) & 2;
    progCaps->staffLvlStage = (bonusFlags >> (3+2*7)) & 2;
}

void WriteGameSave(int slot)
{
    int i;
    struct SaveBlockInfo chunk;
    struct GlobalSaveInfo info;
    struct Dungeon dungeon[2];

    struct GameSaveBlock *dest = GetSaveWriteAddr(slot);
    InvalidateSuspendSave(SAVE_ID_SUSPEND);
    gPlaySt.gameSaveSlot = slot;
    gPlaySt.time_saved = GetGameClock();
    WriteAndVerifySramFast(&gPlaySt, &dest->playSt, sizeof(gPlaySt));

    for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
        WriteGameSavePackedUnit(&gUnitArrayBlue[i], &dest->units[i]);

    ReadGlobalSaveInfo(&info);

    for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
        SGM_SetCharacterKnown(UNIT_CHAR_ID(&gUnitArrayBlue[i]), &info);

    WriteGlobalSaveInfo(&info);
    WriteGMMonsterRnState(&dest->gmUnit);
    WriteSupplyItems(dest->supplyItems);
    WritePidStats(dest->pidStats);
    WriteChapterStats(dest->chapterStats);
    dest->bonusClaimFlags = packProgCaps();
    WriteBonusContentClaimFlags(dest);
    WritePermanentFlags(dest->permanentFlags);
    WriteWorldMapStuff(&dest->wmStuff, &gGMData);
    SaveDungeonRecords(dungeon);
    WriteAndVerifySramFast(dungeon, dest->dungeons, sizeof(dungeon));

    chunk.magic32 = SAVEMAGIC32;
    chunk.kind = SAVEBLOCK_KIND_GAME;
    WriteSaveBlockInfo(&chunk, slot);
    WriteLastGameSaveId(slot);
}

void ReadGameSave(int slot)
{
    int i;
    struct Dungeon dungeon[2];
    struct GameSaveBlock *src = GetSaveReadAddr(slot);

    if (!(PLAY_FLAG_HARD & gBmSt.gameStateBits))
        InvalidateSuspendSave(SAVE_ID_SUSPEND);

    ReadSramFast(src, &gPlaySt, sizeof(gPlaySt));
    SetGameTime(gPlaySt.time_saved);
    gPlaySt.gameSaveSlot = slot;

    InitUnits();

    for (i = 0; i < UNIT_SAVE_AMOUNT_BLUE; i++)
        LoadSavedUnit(src->units + i, &gUnitArrayBlue[i]);

    ReadGMMonsterRnState(&src->gmUnit);
    ReadSupplyItems(src->supplyItems);
    ReadPermanentFlags(src->permanentFlags);
    ReadPidStats(src->pidStats);
    ReadChapterStats(src->chapterStats);
    ReadBonusContentClaimFlags(src);
    unpackProgCaps(src->bonusClaimFlags);
    ReadWorldMapStuff(&src->wmStuff, &gGMData);
    ReadSramFast(src->dungeons, dungeon, sizeof(dungeon));
    LoadDungeonRecords(dungeon);
    WriteLastGameSaveId(slot);
}
