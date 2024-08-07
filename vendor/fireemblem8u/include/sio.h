#pragma once

#include "global.h"
#include "proc.h"
#include "mu.h"
#include "bmsave.h"

struct Proc085AAAC4 {
    PROC_HEADER;

    /* 29 */ STRUCT_PAD(0x29, 0x40);
    /* 40 */ int unk40;
};

struct ProcTactician {
    PROC_HEADER;

    /* 2C */ struct Proc085AAAC4 * child1;
    /* 30 */ u8 line_idx;
    /* 31 */ u8 text_idx;
    /* 32 */ u8 unk32;
    /* 33 */ u8 unk33;
    /* 34 */ s16 conf_idx;
    /* 36 */ s16 unk36;
    /* 38 */ u8 cur_len;                /* used tactician name string length */
    /* 39 */ u8 unk39;
    /* 3A */ u8 unk3A;
    /* 3A */ u8 unk3B;
    /* 3C */ u8 max_len;                /* pre-configured max string length */
    /* 3D */ char str[0x4C - 0x3D];
    /* 4C */ u16 unk4C[0x10];
};

struct TacticianTextConf {
    /* 00 */ u8 * str[0xC];
    /* 30 */ u16 xpos;
    /* 32 */ u16 unk32;
    /* 34 */ u8 unk34;
    /* 35 */ STRUCT_PAD(0x35, 0x36);
    /* 36 */ s16 unk36[4];
    /* 3E */ u8 unk3E;
};

extern const struct TacticianTextConf gTacticianTextConf[];
const struct TacticianTextConf * GetTacticianTextConf(s16);

enum sio_save_config_bitfile {
    SIO_SAVE_CONF_B3 = 1 << 3,
};

struct SioSaveConf {
    u8 _unk0_ : 1;
    u8 _unk1_ : 1;
    u8 _unk2_ : 1;
    u8 _unk3_ : 1;
    u8 _unk4_ : 4;
    u8 _unk8_;
} __attribute__((packed));
extern struct SioSaveConf gSioSaveConfig;

struct SioUnknown_0203DD90_Unk2C
{
    /* 00 */ u8 unitId;
    /* 04 */ int newScore;
};

struct SioUnknown_0203DD90
{
    u8 unk_00; // ?
    u8 unk_01; // current phase
    u8 unk_02; // current cursor unit idx
    u8 unk_03; // current cursor unit idx (again?)
    u8 unk_04; // current selected unit idx (attacker)
    u8 unk_05; // current selected combat target unit id
    u8 unk_06; // weapon index maybe?
    u8 unk_07; // ?
    u8 unk_08; // ?
    u8 unk_09; // ?
    /* 0A */ u8 unk_0A[4]; // num units alive per team?
    /* 0E */ u8 unk_0E; // ?
    /* 0F */ u8 unk_0F[4]; // player ids?
    /* 14 */ int currentScore[4]; // scores
    /* 24 */ u16 unk_24[4]; // leader face IDs
    /* 2C */ struct SioUnknown_0203DD90_Unk2C unk_2c[4];
};

extern struct SioUnknown_0203DD90 gUnk_Sio_0203DD90;

struct SioProc85A971C_Unk44
{
    /* 00 */ u8 playerId;
    /* 01 */ STRUCT_PAD(0x01, 0x04);
    /* 04 */ u32 points;
};

u32 SioStrCpy(u8 const * src, u8 * dst);
void SioDrawNumber(struct Text * text, int x, int color, int number);
void SioInit(void);
void SioPollingMsgAndAck(ProcPtr proc);
void SetBmStLinkArenaFlag(void);
void UnsetBmStLinkArenaFlag(void);
bool CheckInLinkArena(void);    // <!> This function is defined as different types by files, maybe a bug.
void sub_8042EA8(void);

struct Proc_Sio_085A93A0 {
    PROC_HEADER;

    STRUCT_PAD(0x29, 0x58);

    /* 38 */ u32 timer;
};

void sub_8042EB4(struct Proc_Sio_085A93A0 * proc);
void sub_8042EF0(struct Proc_Sio_085A93A0 * proc);
void sub_8042F44(void);
void sub_8042F58(ProcPtr proc);
void sub_8042F84(void);
void sub_8042F98(ProcPtr proc);

struct ProcSioHold {
    PROC_HEADER;

    int x;
    int y, y_min, y_max;
};

void SioHold_Loop(struct ProcSioHold * proc);
ProcPtr StartSioHold(ProcPtr parent, int x, int y, int y_max, int y_min);
// ??? EndSioHold(???);
void sub_804303C(ProcPtr proc, int num);
void ClearSioBG(void);
void sub_804309C(void);
void sub_8043100(int, int);
void sub_8043164(void);
void sub_80431B4(struct Unit * unit);
void SioPlaySoundEffect(int);
// ??? sub_8043244(???);
bool IsKeyInputSequenceComplete(const u16 * list);
// ??? sub_80432F4(???);

/* sio_teamlist.c */

struct SioProc85AAA78
{
    /* 00 */ PROC_HEADER;
    /* 2C */ int unk_2c;
    /* 30 */ s16 unk_30[5];
    /* 3A */ u8 unk_3a[5];
    /* 40 */ int unk_40;
    /* 44 */ s8 unk_44;
    /* 45 */ STRUCT_PAD(0x45, 0x48);
    /* 48 */ int unk_48;
};

struct SioTeamListProc
{
    /* 00 */ PROC_HEADER;
    /* 2C */ struct SioProc85AAA78 * unk_2c;
    /* 30 */ ProcPtr pSioHoldProc;
    /* 34 */ int numActiveOptions;
    /* 38 */ int unk_38;
    /* 3C */ int optionIdx;
    /* 40 */ int unk_40;
    /* 44 */ int unk_44;
    /* 48 */ u8 unk_48;
    /* 49 */ STRUCT_PAD(0x49, 0x4A);
    /* 4A */ u16 yBg1;
    /* 4C */ s8 unk_4c;
    /* 4D */ u8 validOptions[5];
    /* 52 */ u8 selectedOption;
    /* 53 */ u8 selectedTeam;
    /* 54 */ u8 unk_54;
    /* 55 */ u8 unk_55;
    /* 56 */ STRUCT_PAD(0x56, 0x58);
    /* 58 */ int unk_58;
    /* 5C */ s8 unk_5c;
};

// ??? StartLinkArenaTeamList(???);
// ??? SioTeamList_Init(???);
// ??? CanBuildNewLinkArenaTeam(???);
// ??? sub_8043394(???);
// ??? sub_80433C0(???);
// ??? DrawLinkArenaTeamName(???);
// ??? sub_804352C(???);
// ??? sub_8043548(???);
// ??? SioTeamList_EraseTeam(???);
// ??? SioTeamList_SwapTeams(???);
// ??? sub_80437C0(???);
// ??? GetLATeamListHelpTextId(???);
// ??? SioTeamList_SetupGfx(???);
// ??? SioTeamList_Main_HandleDPadInput(???);
// ??? SioTeamList_Loop_MainKeyHandler(???);
// ??? SioTeamList_StartUnitList(???);
// ??? SioTeamList_WaitForUnitListScreen(???);
// ??? sub_8043D5C(???);
// ??? SioTeamList_8043D8C(???);
// ??? sub_8044280(???);
// ??? SioTeamList_804429C(???);
// ??? SioTeamList_8044324(???);
// ??? SioTeamList_StartEraseTeamSubMenu(???);
// ??? SioTeamList_EraseTeam_KeyHandler(???);
// ??? SioTeamList_LoadTeam_Dummy(???);

void sub_8044560(struct ProcTactician * proc, u8 * str);
void sub_8044614(struct ProcTactician * proc);
void TacticianDrawCharacters(struct ProcTactician * proc);
int StrLen(u8 * buf);
void Tactician_InitScreen(struct ProcTactician * proc);
void SioUpdateTeam(char * str, int team);
void sub_80449E8(struct ProcTactician * proc, int idx, const struct TacticianTextConf * conf);
void TacticianTryAppendChar(struct ProcTactician * proc, const struct TacticianTextConf * conf);
void TacticianTryDeleteChar(struct ProcTactician * proc, const struct TacticianTextConf * conf);
void SaveTactician(struct ProcTactician * proc, const struct TacticianTextConf * conf);
// ??? sub_8044B78(???);
// ??? sub_8044C54(???);
// ??? Tactician_Loop(???);
// ??? sub_8044F84(???);
// ??? sub_8044FE4(???);
// ??? sub_8044FFC(???);
// ??? sub_804503C(???);
// ??? sub_8045068(???);
// ??? NameSelect_DrawName(???);
// ??? sub_8045108(???);
// ??? sub_80451F0(???);
// ??? SioPostBattleSprites_Init(???);
// ??? SioPostBattleSprites_Loop_DrawSlideIn(???);
// ??? SioPostBattleSprites_Loop_DrawStatic(???);
// ??? StartDrawLinkArenaRankSprites(???);
// ??? sub_80454E4(???);
// ??? sub_804556C(???);
// ??? SioPostBattle_StartMusicProc(???);
// ??? SioPostBattle_Init(???);
// ??? SioPostBattle_Loop_Main(???);
// ??? SioPostBattle_AwaitAPress(???);
// ??? SioPostBattleMusic_PlayFanfare(???);
// ??? SioPostBattleMusic_PlayStandardBgm(???);
// ??? sub_8045930(???);
// ??? sub_8045A64(???);
// ??? sub_8045AF4(???);
// ??? New6C_SIOMAIN2(???);
// ??? sub_8045C28(???);
// ??? sub_8045C68(???);
void sub_8045CBC(void);
void sub_8045CE0(void);
// ??? sub_8045CEC(???);
// ??? sub_8045DC0(???);
// ??? sub_8045F00(???);
// ??? sub_8045F48(???);
// ??? sub_804619C(???);
// ??? sub_8046234(???);
// ??? sub_80462D4(???);
// ??? sub_80463A8(???);
// ??? sub_804645C(???);
// ??? sub_8046478(???);
// ??? sub_80464B0(???);
// ??? sub_8046580(???);
// ??? sub_8046704(???);
// ??? sub_80467AC(???);
// ??? sub_8046838(???);
// ??? sub_80469AC(???);
// ??? sub_80469B8(???);
// ??? sub_80469C4(???);
// ??? sub_8046C64(???);
// ??? sub_8046CF0(???);
// ??? sub_8046D6C(???);
// ??? sub_8046DB4(???);
// ??? sub_8046DD0(???);
// ??? sub_8046DEC(???);
// ??? sub_8046E0C(???);
// ??? sub_8046E4C(???);
// ??? DrawLinkArenaRankIcon(???);
void DrawLinkArenaModeIcon(u16 *, u32);
// ??? DrawLinkArenaRankingRow(???);
// ??? DrawLinkArenaRankings(???);
// ??? SioResult_Init(???);
// ??? SioResult_Loop_Main(???);
// ??? sub_8047308(???);
// ??? SioResult_NewHS_Init(???);
// ??? SioResult_NewHS_LoopScroll(???);
// ??? SioResult_NewHS_AwaitAPress(???);

/* sio_rulesettings.c */

struct ProcSioRuleSettings
{
    /* 00 */ PROC_HEADER;
    /* 2C */ ProcPtr unk_2c;
    /* 30 */ int unk_30;
};

struct LinkArenaRuleInfo
{
    /* 00 */ int labelTextId;
    /* 04 */ int xPos[2];
    /* 0C */ int optionTextId[2];
};

extern const struct LinkArenaRuleInfo gLinkArenaRuleData[];

void StartSioResultNewHighScore(int value, ProcPtr parent);
void LoadLinkArenaRuleSettings(u8 * buf);
// ??? SaveLinkArenaRuleSettings(???);
void sub_80476CC(int idx, int state);
// ??? SioRuleSettings_Init(???);
// ??? SioRuleSettings_Loop_Main(???);

struct SioProc85AA9C0
{
    /* 00 */ PROC_HEADER;
    /* 2A */ s16 xBase;
    /* 2C */ s16 yBase;
    /* 2E */ u8 unk_2e;
    /* 2F */ u8 unk_2f;
    /* 30 */ u8 unk_30;
    /* 32 */ s16 unk_32;
    /* 34 */ s16 unk_34;
    /* 36 */ u16 unk_36;
    /* 38 */ u16 unk_38;
    /* 3A */ s16 unk_3a;
    /* 3C */ s16 unk_3c;
    /* 3E */ u8 unk_3e;
};

struct SioMenuProc
{
    /* 00 */ PROC_HEADER;
    /* 2C */ struct SioProc85AA9C0 * unk_2c[5];
    /* 40 */ u8 unk_40[4];
    /* 44 */ s8 unk_44;
    /* 48 */ int unk_48;
    /* 4C */ int unk_4c;
    /* 50 */ int unk_50;
    /* 54 */ int unk_54;
    /* 58 */ s8 unk_58;
    /* 59 */ s8 unk_59;
};

int sub_8047A54(struct SioMenuProc *, int);
// ??? CheckSomethingSaveRelated(???);
// ??? SioMenu_Init(???);
// ??? SioMenu_LoadGraphics(???);
// ??? SioMenu_8047C60(???);
// ??? sub_8047CF0(???);
// ??? SioMenu_RestartGraphicsMaybe(???);
// ??? SioMenu_HandleDPadInput(???);
// ??? SioMenu_Loop_HandleKeyInput(???);
// ??? SioMenu_80480B4(???);
// ??? SioMenu_End(???);
void StartLinkArenaMainMenu(ProcPtr);

void sub_8048260(ProcPtr); // StartNameSelect
// ??? StartTacticianNameSelect(???);

// ??? XMapTransfer_80482E0(???);
// ??? XMapTransfer_80483F8(???);
// ??? XMapTransfer_8048418(???);
// ??? XMapTransfer_8048460(???);
// ??? PutXMapProgressPercent(???);
// ??? DrawXMapSendProgress(???);
// ??? DrawXMapReceiveProgress(???);
// ??? StartXMapTransfer(???);
// ??? XMapTransfer_AwaitCompletion(???);
// ??? sub_80486D4(???);
// ??? sub_80486E8(???);
// ??? XMapTransfer_8048730(???);
// ??? sub_804879C(???);
// ??? sub_80487C0(???);
// ??? sub_804881C(???);
// ??? EraseSaveData(???);
void CallEraseSaveEvent(void);
// ??? sub_8048864(???);
void sub_8048884(struct SioProc85A971C_Unk44 *);
// ??? DrawLinkArenaPointsBox(???);
// ??? LAPointsBox_LoadBoxes(???);
// ??? LAPointsBox_Dummy(???);
void StartLinkArenaPointsBox(void);
void EndLinkArenaPointsBox(void);
// ??? PointsNumberMover_Init(???);
// ??? PointsNumberMover_LoopNumberEmerge(???);
// ??? PointsNumberMover_LoopMoveToPointsBox(???);
// ??? DrawLinkArenaScoreNumber(???);
// ??? PointsNumberMover_InitScoreChange(???);
// ??? PointsNumberMover_TickScore(???);
// ??? PointsNumberMover_AwaitEnd(???);
// ??? PointsSpriteText_Init(???);
// ??? PointsSpriteText_LoopIn(???);
// ??? PointsSpriteText_LoopOut(???);
// ??? sub_80490EC(???);
// ??? sub_8049238(???);
void sub_804926C(ProcPtr);
// ??? sub_8049298(???);
// ??? sub_80492B8(???);
// ??? sub_80492D8(???);
// ??? sub_80492E8(???);
// ??? sub_804933C(???);
// ??? sub_8049350(???);
// ??? sub_80493A8(???);
// ??? sub_80493D0(???);
// ??? sub_80494D4(???);
// ??? sub_80494F0(???);
void sub_8049594(void);
// ??? sub_80495F4(???);
void sub_80496A4(void);
// ??? sub_804970C(???);
// ??? sub_8049744(???);
void sub_8049788(void);
// ??? sub_80497A0(???);
void sub_80497CC(void);
// ??? sub_8049828(???);
// ??? sub_80498F4(???);
// ??? sub_8049940(???);
// ??? sub_8049964(???);
// ??? sub_80499D0(???);
int sub_8049A60(void);
// ??? sub_8049B04(???);
// ??? sub_8049B24(???);
// ??? sub_8049C18(???);
// ??? sub_8049C94(???);
// ??? sub_8049CD4(???);
// ??? sub_8049D0C(???);
// ??? sub_8049D24(???);
// ??? sub_8049F38(???);
// ??? sub_8049F44(???);
// ??? sub_804A108(???);
// ??? sub_804A158(???);
// ??? sub_804A1D0(???);
// ??? sub_804A298(???);
// ??? sub_804A3A8(???);
// ??? sub_804A430(???);
// ??? sub_804A44C(???);
// ??? sub_804A51C(???);
// ??? sub_804A5A4(???);
// ??? sub_804A614(???);
// ??? sub_804A6A4(???);
// ??? sub_804A7C0(???);
// ??? sub_804A914(???);
// ??? sub_804A9A4(???);
// ??? sub_804AA88(???);
// ??? sub_804AAA4(???);
// ??? sub_804AADC(???);
// ??? sub_804AAFC(???);
// ??? sub_804ABB4(???);
// ??? sub_804ABCC(???);
// ??? sub_804AC68(???);
// ??? sub_804ACAC(???);
// ??? sub_804ACC4(???);
// ??? sub_804ADA0(???);
// ??? sub_804AE08(???);
// ??? sub_804AE7C(???);
// ??? sub_804AEC4(???);
// ??? ITEMRANGEDONE_sub_804AF2C(???);
// ??? sub_804AF5C(???);
// ??? sub_804B190(???);
// ??? sub_804B1C0(???);
// ??? sub_804B250(???);
// ??? sub_804B278(???);
void sub_804B38C(void);
void sub_804B3A0(void);
// ??? sub_804B3B0(???);
// ??? sub_804B3D0(???);
// ??? sub_804B408(???);
// ??? sub_804B43C(???);
// ??? sub_804B480(???);
// ??? sub_804B518(???);
// ??? sub_804B554(???);
// ??? sub_804B5E0(???);
// ??? sub_804B604(???);
// ??? sub_804B624(???);
// ??? sub_804B6AC(???);
// ??? sub_804B6B8(???);
// ??? sub_804B6CC(???);
// ??? sub_804B6F4(???);
// ??? sub_804B708(???);
// ??? sub_804B71C(???);
// ??? sub_804B76C(???);
// ??? sub_804B7E4(???);
// ??? sub_804B800(???);
// ??? sub_804B850(???);
// ??? sub_804B8D0(???);
void Set_0203DDDC(void);
void Clear_0203DDDC(void);
// ??? sub_804B938(???);
// ??? sub_804B964(???);
// ??? sub_804B9A4(???);
// ??? sub_804B9BC(???);
// ??? sub_804B9E4(???);
// ??? sub_804BB54(???);
// ??? sub_804BBA0(???);
// ??? sub_804BC3C(???);
// ??? sub_804BC84(???);
// ??? sub_804BD2C(???);
// ??? sub_804BD3C(???);
// ??? sub_804BDD8(???);
// ??? sub_804BDFC(???);
// ??? sub_804BE88(???);
// ??? sub_804BE98(???);
// ??? sub_804BEB8(???);
// ??? sub_804BED8(???);
// ??? sub_804BF30(???);
void StartLinkArenaMUDeathFade(struct MuProc *);
// ??? sub_804BFAC(???);
// ??? sub_804BFF8(???);
// ??? SioWarp_Init(???);
// ??? SioWarp_Loop(???);
// ??? SioWarp_End(???);
// ??? SioWarpFx_StartSioWarp(???);
// ??? SioWarpFx_804C178(???);
// ??? SioWarpFx_HideMoveUnit(???);
// ??? SioWarpFx_SetMUPosition(???);
// ??? SioWarpFx_ShowMoveUnit(???);
// ??? SioWarpFx_804C1D8(???);
// ??? SioWarpFx_AwaitSioWarp(???);
ProcPtr StartSioWarpFx(struct Unit *, struct MuProc *, int, int, int, int, ProcPtr);
// ??? sub_804C260(???);
void PutLinkArenaButtonSpriteAt(int, int);
// ??? LAButtonSprites_Loop(???);
void StartLinkArenaButtonSpriteDraw(int, int, ProcPtr);
void EndLinkArenaButtonSpriteDraw(void);
void InitSioBG(void);
void sub_804C3A0(int, int);
void sub_804C3A4(int);
void nullsub_13(void);
// ??? sub_804C3AC(???);
// ??? LATitleBanner_Init(???);
// ??? LATitleBanner_Loop(???);
void StartLinkArenaTitleBanner(ProcPtr parent, int, int);
void sub_804C4F8(void);
void sub_804C508(void);
void sub_804C558(void);
void sub_804C590(void);
// ??? sub_804C5A4(???);
// ??? sub_804C5F8(???);
ProcPtr sub_804C758(ProcPtr, u8, u8, u8, u8);
void sub_804C7C8(struct SioProc85AA9C0 * proc, int, int, int, int);
void sub_804C7DC(struct SioProc85AA9C0 * proc, s16 x, s16 y);
// ??? sub_804C7E4(???);
// ??? sub_804C83C(???);
// ??? sub_804C894(???);
ProcPtr sub_804CAEC(struct SioTeamListProc * parent, int numActiveOptions, u8 * buf);
// ??? LATeamSpriteDraw_Loop(???);
void PutLinkArenaTeamSprites(int x, int y, int upperBound, int lowerBound, int count, ProcPtr parent);
void ScrollMultiArenaTeamSprites(int);;
// ??? UpdateNameEntrySpriteGlow(???);
// ??? NameEntrySpriteDraw_Loop(???);
ProcPtr StartNameEntrySpriteDraw(ProcPtr parent, int a, int b);
void UpdateNameEntrySpriteDraw(void *, int, int, int, int, int);
// ??? RuleSettingSprites_Interactive_Loop(???);
// ??? RuleSettingSprites_Static_Loop(???);
ProcPtr StartRuleSettingSpriteDrawInteractive(ProcPtr);
void StartRuleSettingSpriteDrawStatic(void);
void UpdateRuleSettingSprites(ProcPtr, s16, s16, s16);
// ??? UpdateSioMenuBurstGlow(???);
// ??? SioMenuBurstFx_Loop(???);
ProcPtr StartSioMenuBurstFx(ProcPtr, int, int);
// ??? LinkArenaMenuScroll_Init(???);
// ??? LinkArenaMenuScroll_Loop(???);
void StartLinkArenaMenuScrollBar(int, int, u8, u8, u8, ProcPtr);
void UpdateLinkArenaMenuScrollBar(u8, s16);
// ??? LAPhaseIntro_Init(???);
// ??? LAPhaseIntro_End(???);
// ??? LAPhaseIntro_StartBgm(???);
// ??? sub_804D3F0(???);
void sub_804D40C(struct Unit *);
// ??? sub_804D428(???);
// ??? LAVersusSpriteDraw_Loop(???);
ProcPtr StartLinkArenaVersusSpriteDraw(int x, int y, ProcPtr parent);
void EndLinkArenaVersusSpriteDraw(void);
// ??? GetLinkArenaVersusSpriteDraw(???);
void sub_804D6D4(void);
// ??? sub_804D724(???);
// ??? sub_804D778(???);
// ??? sub_804D7B0(???);
ProcPtr sub_804D7DC(int, int, ProcPtr);
void sub_804D80C(void);
void PutLinkArenaChoiceBannerSprite(int, int);
// ??? sub_804D858(???);
// ??? sub_804D8A4(???);
// ??? sub_804D8C8(???);
// ??? sub_804D8DC(???);
// ??? sub_804D940(???);
// ??? sub_804D950(???);
// ??? sub_804D9C4(???);
// ??? sub_804DA00(???);
// ??? sub_804DDF0(???);
// ??? sub_804DE3C(???);
// ??? sub_804DE60(???);
// ??? sub_804DF24(???);
// ??? sub_804DF38(???);
// ??? sub_804E024(???);
// ??? sub_804E03C(???);

// extern ??? gUnk_Sio_02000000

extern struct Font Font_Sio_02000C60;
// extern ??? gLinkArenaSt
// extern ??? gUnknown_0203DA30
// extern ??? gUnk_Sio_0203DA78
extern struct Text gUnk_Sio_0203DA88[];
extern struct Text Texts_0203DAB0;
// extern ??? gUnk_Sio_0203DAC0
extern char gUnk_Sio_0203DAC5[][15];

extern struct Text Texts_0203DB14[10];
extern struct Text gUnk_Sio_0203DB1C[];
extern struct Font Font_0203DB64;
// extern ??? gLinkArenaTeamList
extern struct MultiArenaRankingEnt gSioResultRankings[];
// extern ??? gUnk_Sio_0203DC48
extern struct Text gSioTexts[];
extern struct Text Text_0203DB14;
extern s8 gUnk_Sio_0203DD24;
// extern ??? gUnk_Sio_0203DD28
extern u16 gKeyInputSequenceBuffer[];
extern int gKeyInputSequenceTimer;
// extern ??? gUnk_Sio_0203DD50
extern int gUnk_Sio_0203DD8C;
// extern ??? gUnk_Sio_0203DD90
// extern ??? gUnk_Sio_0203DD94
// extern ??? gUnk_Sio_0203DD95
// extern ??? gUnk_Sio_0203DD9A
// extern ??? gUnk_Sio_0203DDB4
extern s8 gUnk_Sio_0203DDDC;

// extern ??? gUnknown_080D8714
extern s16 gUnknown_080D9C9E[];
// extern ??? gUnknown_080D9D34
// extern ??? gUnknown_080D9D4D
// extern ??? gUnknown_080D9D56
extern u8 const gUnknown_080D9D5E[];
extern s8 const gUnknown_080D9D61[];
extern u16 const Sprite_080D9D6E[];
extern u16 const Sprite_080D9D76[];
extern u16 const Sprite_080D9D7E[];
extern u16 const Sprite_080D9D86[];
extern u16 const Sprite_080D9D8E[];
extern u16 const Sprite_080D9DA2[];
extern u16 const Sprite_080D9DC2[];
extern u16 const Sprite_080D9DD6[];
extern u16 const Sprite_080D9DE4[];
extern u16 const Sprite_080D9DF2[];
extern u16 const Sprite_080D9E06[];
extern u16 const Sprite_080D9E0E[];
// extern ??? gUnknown_080D9E1C
// extern ??? gUnknown_080D9E44
// extern ??? gLinkArenaRuleData

// extern ??? gUnknown_080D9EC8
// extern ??? gUnknown_080D9EF0

// extern ??? gUnknown_080D9F18
// extern ??? gUnknown_080D9F20
// extern ??? gUnknown_080D9F28
// extern ??? gUnknown_080D9F38
// extern ??? gUnknown_080D9F48
// extern ??? gUnknown_080D9F98
// extern ??? gUnknown_080D9FA0
// extern ??? gUnknown_080D9FA8
// extern ??? gUnknown_080D9FB0
// extern ??? gUnknown_080D9FB5
// extern ??? gUnknown_080D9FB7
// extern ??? Sprite_LinkArenaBButton
// extern ??? SioDefaultBgConfig
// extern ??? gUnknown_080DA09C
// extern ??? gUnknown_080DA0DA
// extern ??? Sprite_LinkArena_PressStart
// extern ??? gUnknown_080DA102
// extern ??? Sprite_NameEntry_PositionIndicator
// extern ??? Sprite_SioMenuBurst_TopLeft
// extern ??? Sprite_SioMenuBurst_TopRight
// extern ??? Sprite_SioMenuBurst_BottomLeft
// extern ??? Sprite_SioMenuBurst_BottomRight
// extern ??? gUnknown_080DA1CA
// extern ??? gUnknown_080DA20C
// extern ??? gUnknown_080DA21C
// extern ??? gUnknown_080DA22C
// extern ??? Sprite_080DA25C
// extern ??? Sprite_080DA26A
// extern ??? Sprite_080DA27E
// extern ??? Sprite_LinkArena_ChoiceBanner

extern CONST_DATA struct ProcCmd ProcScr_SIOCON[];
extern CONST_DATA struct ProcCmd ProcScr_SIOVSYNC[];
extern CONST_DATA struct ProcCmd ProcScr_SIOMAIN[];
extern CONST_DATA u8 * gpSioUnkBuffer;
extern CONST_DATA struct ProcCmd gUnknown_085A93A0[];
extern CONST_DATA struct ProcCmd ProcScr_HOLD[];
extern CONST_DATA u16 gSioList_085A93E0[];
extern CONST_DATA u16 gSioList_085A93F0[];
// extern ??? gSioTeamListConfigLut
extern CONST_DATA struct ProcCmd ProcScr_SioTeamList[];
// extern ??? ProcScr_TacticianNameSelection
// extern ??? SpriteArray_085A96D4
extern struct ProcCmd ProcScr_DebugMonitor[];
extern struct ProcCmd ProcScr_SIOTERM[];
extern struct ProcCmd ProcScr_SIOPRA[];
extern struct ProcCmd ProcScr_SIOBAT[];
extern struct ProcCmd ProcScr_SIORESULT[];
extern struct ProcCmd ProcScr_SIO_RuleSettings[];

extern int gCurrentKeyInSeqIndex;
extern int gTargetKeyInSeqIndex;
// extern ??? gUnknown_03001810
// extern ??? gUnknown_03001818
// extern ??? gUnknown_0300182C
// extern ??? gUnknown_03001830
// extern ??? gUnknown_03001834
// extern ??? gUnknown_03001838
// extern ??? gUnknown_03001840
// extern ??? gUnknown_03001850
extern int gUnknown_03001860;
// extern ??? gUnknown_03001864
