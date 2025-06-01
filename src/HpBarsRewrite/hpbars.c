#include "global.h"

#include "bmitem.h"
#include "bmmap.h"
#include "bmtrick.h"
#include "bmunit.h"
#include "chapterdata.h"
#include "ctc.h"
#include "hardware.h"
#include "mu.h"
#include "unit_icon_data.h"
#include "worldmap.h"

#include "bmlib.h"
#include "bmphase.h"
#include "bmreliance.h"
#include "bmudisp.h"
#include "constants/event-flags.h"
#include "constants/terrains.h"
#include "constants/video-global.h"
#include "gba/syscall.h"

#include "hpbars.h"
#include "ram_structures.h"

// TODO: Un-magic these

const u16 EffectiveWarningTileData[] = {
  0x0001, 0x000f, // 8x8 sprite
  0x01ff, 0x0876, // the tile is 0x76
};

const u16 CritWarningTileData[] = {
  0x0001, 0x000f, 0x01ff, 0x0877 // tile #0x77
};

const u16 TalkBubbleTileData[] = {
  0x0001, 0x400f, // 16x8 sprite
  0x01ee, 0x0870  // tile #0x70
};

bool isEffectiveVs(struct Unit *attacker, struct Unit *defender) {
  for (int i = 0; i < UNIT_ITEM_COUNT; i += 1) {
    int item = ITEM_INDEX(attacker->items[i]);
    if (CanUnitUseWeapon(attacker, item) && IsItemEffectiveAgainst(item, defender)) {
      return TRUE;
    }
  }
  return FALSE;
}

bool isCritty(struct Unit *attacker) {
  for (int i = 0; i < UNIT_ITEM_COUNT; i += 1) {
    int item = ITEM_INDEX(attacker->items[i]);
    if (CanUnitUseWeapon(attacker, item) &&
        GetItemCrit(item) >= CRIT_WARNING_THRESHOLD) {
      return TRUE;
    }
  }
  return FALSE;
}

struct Unit *getSelectedUnit() {
  if (!UNIT_IS_VALID(gActiveUnit)) {
    return NULL;
  }

  if (UNIT_FACTION(gActiveUnit) != FACTION_BLUE) {
    return NULL;
  }

  if (!(gActiveUnit->state & 1)) {
    return NULL;
  }

  return gActiveUnit;
}

enum InfoKind getUnitInfoIcon(int i, struct Unit *unit, int x, int y) {
  struct Unit *activeUnit = getSelectedUnit();

  if (!activeUnit) {
    return NOTHING;
  }

  if (infoIconCache->valid) {
    return infoIconCache->entries[i];
  }

  enum InfoKind kd = NOTHING;

  // Regardless of allegiance: Can these two units talk?
  if (CheckForCharacterEvents(UNIT_CHAR_ID(unit), UNIT_CHAR_ID(activeUnit))) {
    kd = CAN_TALK;
  }
  // Otherwise, if units are allied, check support list
  else if (AreUnitsAllied(unit->index, gActiveUnit->index)) {
    int idx = GetUnitSupporterNum(activeUnit, UNIT_CHAR_ID(unit));

    if (idx != -1 && CanUnitSupportNow(activeUnit, idx)) {
      kd = CAN_TALK;
    }
  }
  // Otherwise, check effectiveness
  else if (isEffectiveVs(unit, activeUnit)) {
    kd = WARN_EFF;
  }
  // Finally, check crit
  else if (isCritty(unit)) {
    kd = WARN_CRIT;
  }

  infoIconCache->entries[i] = kd;

  return kd;
}

/*
void PutUnitSpriteIconsOam_(void) {
  u8 protectCharacterId;
  int i;
  int x;
  int y;
  s8 displayRescueIcon;

  u16 rescuePalLut[] = {
    0xC,
    0xE,
    0xD,
  };

  if (GetBattleMapKind() != 2) {
    protectCharacterId =
        GetROMChapterStruct(gPlaySt.chapterIndex)->protectCharacterIndex;
  }
  else {
    protectCharacterId = 0;
  }

  displayRescueIcon = (GetGameClock() % 32) < 20 ? 1 : 0;

  int poisonIconFrame = GetGameClock() / 8 % ARRAY_COUNT(sPoisonIconSprites);
  int sleepIconFrame = GetGameClock() / 16 % ARRAY_COUNT(sSleepIconSprites);
  int berserkIconFrame = GetGameClock() / 8 % ARRAY_COUNT(sBerserkIconSprites);
  int silenceIconFrame = GetGameClock() / 4 % ARRAY_COUNT(sSilenceIconSprites);

  if (CheckFlag(EVFLAG_HIDE_BLINKING_ICON) != 0)
    return;

  PutChapterMarkedTileIconOam();

  struct Unit *activeUnit = getSelectedUnit();

  if (!activeUnit) {
    infoIconCache->valid = FALSE;
  }

  for (i = 1; i < 0xc0; i++) {
    struct Unit *unit = GetUnit(i);

    if (!UNIT_IS_VALID(unit))
      continue;

    if (unit->state & US_HIDDEN)
      continue;

    if (GetUnitSpriteHideFlag(unit) != 0)
      continue;

    x = unit->xPos * 16 - gBmSt.camera.x;
    y = unit->yPos * 16 - gBmSt.camera.y;

    if (x < -16 || x > DISPLAY_WIDTH)
      continue;

    if (y < -16 || y > DISPLAY_HEIGHT)
      continue;

    switch (unit->statusIndex) {
    case UNIT_STATUS_POISON:
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x200 + x - 2), OAM0_Y(0x100 + y - 4),
          sPoisonIconSprites[poisonIconFrame], 0
      );
      break;
    case UNIT_STATUS_SILENCED:
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x200 + x - 2), OAM0_Y(0x100 + y - 4),
          sSilenceIconSprites[silenceIconFrame], 0
      );
      break;
    case UNIT_STATUS_SLEEP:
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x200 + x + 2), OAM0_Y(0x100 + y), sSleepIconSprites[sleepIconFrame], 0
      );
      break;
    case UNIT_STATUS_BERSERK:
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x200 + x + 1), OAM0_Y(0x100 + y - 5),
          sBerserkIconSprites[berserkIconFrame], 0
      );
      break;
    }

    // draw HP
    if (unit->curHP != 0 && unit->curHP != unit->maxHP) {
      int length = ((unit->maxHP - unit->curHP) * 11) / unit->maxHP;
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x201 + x), OAM0_Y(0x100 + y - 5), HPFramePointers[length], 0
      );
    }

    enum InfoKind kd = getUnitInfoIcon(i, unit, x, y);

    switch (kd) {
    case NOTHING:
      break;
    case WARN_EFF:
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x201 + x + 11), OAM0_Y(0x100 + y - 18), EffectiveWarningTileData, 0
      );
      break;
    case WARN_CRIT:
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x201 + x + 11), OAM0_Y(0x100 + y - 18), CritWarningTileData, 0
      );
      break;
    case CAN_TALK:
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x201 + x + 11), OAM0_Y(0x100 + y - 18), TalkBubbleTileData, 0
      );
      break;
    }

    if (!displayRescueIcon)
      continue;

    if (unit->state & US_RESCUING) {
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x200 + x + 9), OAM0_Y(0x100 + y + 7), gObject_8x8,
          (rescuePalLut[unit->rescue >> 6] & 0xf) * 0x1000 + 0x803
      );
    }
    else if ((UNIT_FACTION(unit) != FACTION_BLUE) &&
             (UNIT_CATTRIBUTES(unit) & CA_BOSS)) {
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x200 + x + 9), OAM0_Y(0x100 + y + 7), gObject_8x8, 0x810
      );
    }
    else if (protectCharacterId == unit->pCharacterData->number) {
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x200 + x + 9), OAM0_Y(0x100 + y + 7), gObject_8x8, 0x811
      );
    }
  }

  if (activeUnit) {
    infoIconCache->valid = TRUE;
    infoIconCache->lastActiveUnit = UNIT_CHAR_ID(activeUnit);
  }
}
*/

void PutUnitSpriteIconsOam(void) {
  s8 displayRescueIcon;
  u8 protectCharacterId;

  u16 rescuePalLut[] = {
    0xC,
    0xE,
    0xD,
  };

  if (GetBattleMapKind() != BATTLEMAP_KIND_SKIRMISH) {
    protectCharacterId =
        GetROMChapterStruct(gPlaySt.chapterIndex)->protectCharacterIndex;
  }
  else {
    protectCharacterId = 0;
  }

  displayRescueIcon = (GetGameClock() % 32) < 20 ? 1 : 0;

  u8 poisonIconFrame = (GetGameClock() / 8) % 12; // ARRAY_COUNT(sPoisonIconSprites);
  u8 sleepIconFrame = (GetGameClock() / 16) % 7; // ARRAY_COUNT(sSleepIconSprites);
  u8 berserkIconFrame = (GetGameClock() / 8) % 9; // ARRAY_COUNT(sBerserkIconSprites);
  u8 silenceIconFrame = (GetGameClock() / 4) % 18; // ARRAY_COUNT(sSilenceIconSprites);

  if (CheckFlag(EVFLAG_HIDE_BLINKING_ICON) != 0)
    return;

  PutChapterMarkedTileIconOam();

  for (int i = 1; i < 0xc0; i++) {
    struct Unit *unit = GetUnit(i);

    if (!UNIT_IS_VALID(unit))
      continue;

    if (unit->state & US_HIDDEN)
      continue;

    if (GetUnitSpriteHideFlag(unit) != 0)
      continue;

    int x = unit->xPos * 16 - gBmSt.camera.x;
    int y = unit->yPos * 16 - gBmSt.camera.y;

    if (x < -16 || x > DISPLAY_WIDTH)
      continue;

    if (y < -16 || y > DISPLAY_HEIGHT)
      continue;

    s8 xoffs = 0;
    s8 yoffs = 0;
    u16 *icon = NULL;

    switch (unit->statusIndex) {
    case UNIT_STATUS_POISON:
      xoffs = -2;
      yoffs = -4;
      icon = sPoisonIconSprites[poisonIconFrame];
      break;

    case UNIT_STATUS_SILENCED:
      xoffs = -2;
      yoffs = -4;
      icon = sSilenceIconSprites[silenceIconFrame];
      break;

    case UNIT_STATUS_SLEEP:
      xoffs = 2;
      yoffs = 0;
      icon = sSleepIconSprites[sleepIconFrame];
      break;

    case UNIT_STATUS_BERSERK:
      xoffs = 1;
      yoffs = -5;
      icon = sBerserkIconSprites[berserkIconFrame];
      break;

    case UNIT_STATUS_ATTACK:
    case UNIT_STATUS_DEFENSE:
    case UNIT_STATUS_CRIT:
    case UNIT_STATUS_AVOID:
      if (!displayRescueIcon)
        continue;
      xoffs = -1;
      yoffs = -5;
      icon = sSprite_0859B968;
      break;

    case UNIT_STATUS_SICK:
    case UNIT_STATUS_RECOVER:
      break;
    }

    if (icon != NULL) {
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x200 + x + xoffs), OAM0_Y(0x100 + y + yoffs), icon, 0
      );
    }

    if (!displayRescueIcon)
      continue;

    if (unit->state & US_RESCUING) {
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x200 + x + 9), OAM0_Y(0x100 + y + 7), gObject_8x8,
          (rescuePalLut[unit->rescue >> 6] & 0xf) * 0x1000 + 0x803
      );
    }
    else if ((UNIT_FACTION(unit) != FACTION_BLUE) &&
             (UNIT_CATTRIBUTES(unit) & CA_BOSS)) {
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x200 + x + 9), OAM0_Y(0x100 + y + 7), gObject_8x8, 0x810
      );
    }
    else if (protectCharacterId == unit->pCharacterData->number) {
      CallARM_PushToSecondaryOAM(
          OAM1_X(0x200 + x + 9), OAM0_Y(0x100 + y + 7), gObject_8x8, 0x811
      );
    }
  }
}
