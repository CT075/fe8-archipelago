// CR cam: Split this into weapon-level and regular-level files.

#include "global.h"

#include "bmbattle.h"
#include "bmunit.h"
#include "bmitem.h"
#include "variables.h"
#include "statscreen.h"
#include "icon.h"
#include "hardware.h"
#include "constants/items.h"

#include "constants.h"
#include "archipelago.h"
#include "progressiveCaps.h"

int GetStatIncrease(int growth);
int GetUnitExpLevel(struct Unit*);

int GetLevelCap() {
  return 10 + progCaps->lvlCapStage*5;
}

void bumpLevelCap() {
  progCaps->lvlCapStage += 1;

  for (int i = 0 ; i < BLUE_UNIT_MAX ; i += 1) {
    struct Unit *unit = &gUnitArrayBlue[i];
    if (unit->exp == UNIT_EXP_DISABLED && unit->level < TRUE_LEVEL_CAP) {
      unit->exp = 0;
    }
  }
}

s8 CanBattleUnitGainLevels(struct BattleUnit *bu) {
  if (gBmSt.gameStateBits & 0x40)
    return TRUE;

  if (bu->unit.level >= TRUE_LEVEL_CAP)
    return FALSE;

  if (GetUnitExpLevel(&bu->unit) >= GetLevelCap())
    return FALSE;

  if (bu->unit.exp == UNIT_EXP_DISABLED)
    return FALSE;

  if (UNIT_FACTION(&bu->unit) != FACTION_BLUE)
    return FALSE;

  return TRUE;
}

void EnforceLevelCap(struct BattleUnit *bu) {
  if (UNIT_CATTRIBUTES(&bu->unit) & CA_MAXLEVEL10) {
    if (bu->unit.level == 10) {
      bu->expGain -= bu->unit.exp;
      bu->unit.exp = UNIT_EXP_DISABLED;
    }
  } else if (GetUnitExpLevel(&bu->unit) >= GetLevelCap()) {
    bu->expGain -= bu->unit.exp;
    bu->unit.exp = UNIT_EXP_DISABLED;
  }
}

void CheckBattleUnitLevelUp(struct BattleUnit *bu) {
  if (CanBattleUnitGainLevels(bu) && bu->unit.exp >= 100) {
    int growthBonus, statGainTotal;

    bu->unit.exp -= 100;
    bu->unit.level++;

    EnforceLevelCap(bu);

    growthBonus = (bu->unit.state & US_GROWTH_BOOST) ? 5: 0;
    statGainTotal = 0;

    bu->changeHP  = GetStatIncrease(bu->unit.pCharacterData->growthHP + growthBonus);
    statGainTotal += bu->changeHP;

    bu->changePow = GetStatIncrease(bu->unit.pCharacterData->growthPow + growthBonus);
    statGainTotal += bu->changePow;

    bu->changeSkl = GetStatIncrease(bu->unit.pCharacterData->growthSkl + growthBonus);
    statGainTotal += bu->changeSkl;

    bu->changeSpd = GetStatIncrease(bu->unit.pCharacterData->growthSpd + growthBonus);
    statGainTotal += bu->changeSpd;

    bu->changeDef = GetStatIncrease(bu->unit.pCharacterData->growthDef + growthBonus);
    statGainTotal += bu->changeDef;

    bu->changeRes = GetStatIncrease(bu->unit.pCharacterData->growthRes + growthBonus);
    statGainTotal += bu->changeRes;

    bu->changeLck = GetStatIncrease(bu->unit.pCharacterData->growthLck + growthBonus);
    statGainTotal += bu->changeLck;

    if (statGainTotal == 0) {
      for (statGainTotal = 0; statGainTotal < 2; ++statGainTotal) {
        bu->changeHP = GetStatIncrease(bu->unit.pCharacterData->growthHP);

        if (bu->changeHP)
          break;

        bu->changePow = GetStatIncrease(bu->unit.pCharacterData->growthPow);

        if (bu->changePow)
          break;

        bu->changeSkl = GetStatIncrease(bu->unit.pCharacterData->growthSkl);

        if (bu->changeSkl)
          break;

        bu->changeSpd = GetStatIncrease(bu->unit.pCharacterData->growthSpd);

        if (bu->changeSpd)
          break;

        bu->changeDef = GetStatIncrease(bu->unit.pCharacterData->growthDef);

        if (bu->changeDef)
          break;

        bu->changeRes = GetStatIncrease(bu->unit.pCharacterData->growthRes);

        if (bu->changeRes)
          break;

        bu->changeLck = GetStatIncrease(bu->unit.pCharacterData->growthLck);

        if (bu->changeLck)
          break;
      }
    }

    CheckBattleUnitStatCaps(GetUnit(bu->unit.index), bu);
  }
}

u8 *weaponLvlStage(int wType) {
  switch (wType) {
    case ITYPE_SWORD:
      return &progCaps->swordLvlCapStage;
    case ITYPE_LANCE:
      return &progCaps->lanceLvlCapStage;
    case ITYPE_AXE:
      return &progCaps->axeLvlCapStage;
    case ITYPE_BOW:
      return &progCaps->bowLvlCapStage;
    case ITYPE_ANIMA:
      return &progCaps->animaLvlCapStage;
    case ITYPE_LIGHT:
      return &progCaps->lightLvlCapStage;
    case ITYPE_DARK:
      return &progCaps->darkLvlCapStage;
    case ITYPE_STAFF:
      return &progCaps->staffLvlCapStage;
  }
  return &progCaps->swordLvlCapStage;
}

void bumpWeaponLevelCap(enum WeaponType wtype) {
  // CR-someday cam: This cast takes advantage of the specific ordering of the
  // weapon type listing in `Generate.hs`, which is not strictly a good idea,
  // but is unlikely to actually cause issues.
  u8 *stage = weaponLvlStage((int) wtype);
  *stage += 1;
}

int weaponLvlStageToWExp(u8 stage) {
  switch (stage) {
    case 0:
      return WPN_EXP_C;
    case 1:
      return WPN_EXP_B;
    case 2:
      return WPN_EXP_A;
    default:
      return WPN_EXP_S;
  }
}

int partyWeaponLevel(int wType) {
  return weaponLvlStageToWExp(*weaponLvlStage(wType));
}

int GetItemAwardedExp(int item) {
  return 0;
}

int getPlayerUnitWeaponRank(struct Unit *unit, int wType) {
  // !!x = 0 for x = 0 and 1 otherwise, so a weapon is usable iff the given
  // unit has any rank for that weapon at all and the slot's weapon rank is
  // high enough.
  return (!!unit->pClassData->baseRanks[wType]) * partyWeaponLevel(wType);
}

int getUnitWeaponRank(struct Unit *unit, int wType) {
  switch (UNIT_FACTION(unit)) {
    case FACTION_BLUE:
      return getPlayerUnitWeaponRank(unit, wType);

    case FACTION_RED:
    case FACTION_GREEN:
      return unit->ranks[wType];
  }

  return unit->ranks[wType];
}

// CR cam: set this by class
//int GetUnitBestWRankType(struct Unit *unit);

void ComputeBattleUnitWeaponRankBonuses(struct BattleUnit *bu) {
  if (bu->weapon) {
    int wType = GetItemType(bu->weapon);

    switch (UNIT_FACTION(&(bu->unit))) {
      case FACTION_BLUE:
        if (wType < 8 && partyWeaponLevel(wType) >= WPN_EXP_S) {
          bu->battleHitRate += 10;
          bu->battleCritRate += 15;
        }
        break;
      default:
    }
  }
}

s8 CanUnitUseWeapon(struct Unit *unit, int item) {
  if (item == 0)
    return FALSE;

  if (!(GetItemAttributes(item) & IA_WEAPON))
    return FALSE;

  bool isEirika = false;
  bool isEphraim = false;

  if (GetItemAttributes(item) & IA_LOCK_ANY) {
    // Check for item locks

    if ((GetItemAttributes(item) & IA_LOCK_1) && !(UNIT_CATTRIBUTES(unit) & CA_LOCK_1))
      return FALSE;

    // CR-someday cam: In order to allow the Sieg twins to be used by anyone,
    // we can't check the Eirika and Ephraim locks here. However, a far simpler
    // solution is to just remove the locks from Sieglinde and Siegmund and
    // keep the hardcoded Eirika/Ephraim check below.

    // Eirika lock
    if (UNIT_CATTRIBUTES(unit) & CA_LOCK_4) {
      isEirika = true;
    }

    // Ephraim lock
    if (UNIT_CATTRIBUTES(unit) & CA_LOCK_5) {
      isEphraim = true;
    }

    if ((GetItemAttributes(item) & IA_LOCK_6) && !(UNIT_CATTRIBUTES(unit) & CA_LOCK_6))
      return FALSE;

    if ((GetItemAttributes(item) & IA_LOCK_7) && !(UNIT_CATTRIBUTES(unit) & CA_LOCK_7))
      return FALSE;

    if ((GetItemAttributes(item) & IA_LOCK_2) && !(UNIT_CATTRIBUTES(unit) & CA_LOCK_2))
      return FALSE;

    // Monster lock is special
    if (GetItemAttributes(item) & IA_LOCK_3) {
      if (!(UNIT_CATTRIBUTES(unit) & CA_LOCK_3))
        return FALSE;

      return TRUE;
    }

    if (GetItemAttributes(item) & IA_UNUSABLE)
      if (!(IsItemUnsealedForUnit(unit, item)))
        return FALSE;
  }

  if ((unit->statusIndex == UNIT_STATUS_SILENCED) && (GetItemAttributes(item) & IA_MAGIC))
    return FALSE;

  int wRank = GetItemRequiredExp(item);

  if ((isEirika && item == ITEM_SWORD_SIEGLINDE) || (isEphraim && item == ITEM_LANCE_SIEGMUND)) {
    wRank = WPN_EXP_E;
  }
  else if (
    ((GetItemAttributes(item) & IA_LOCK_4) && !isEirika) ||
    ((GetItemAttributes(item) & IA_LOCK_5) && !isEphraim)
  ) {
    return FALSE;
  }

  int uRank = getUnitWeaponRank(unit, GetItemType(item));

  return (uRank >= wRank) ? TRUE : FALSE;
}

s8 CanUnitUseStaff(struct Unit* unit, int item) {
  if (item == 0)
    return FALSE;

  if (!(GetItemAttributes(item) & IA_STAFF))
    return FALSE;

  if (unit->statusIndex == UNIT_STATUS_SLEEP)
    return FALSE;

  if (unit->statusIndex == UNIT_STATUS_BERSERK)
    return FALSE;

  if (unit->statusIndex == UNIT_STATUS_SILENCED)
    return FALSE;

  int wRank = GetItemRequiredExp(item);
  int uRank = getUnitWeaponRank(unit, GetItemType(item));

  return (uRank >= wRank) ? TRUE : FALSE;
}

void DisplayWeaponExp(int num, int x, int y, int wtype) {
  int color;

  int wexp = getUnitWeaponRank(gStatScreen.unit, wtype);

  // Display weapon type icon
  DrawIcon(gBmFrameTmap0 + TILEMAP_INDEX(x, y),
    0x70 + wtype, // TODO: icon id definitions
    TILEREF(0, STATSCREEN_BGPAL_EXTICONS));

  color = wexp >= WPN_EXP_S
    ? TEXT_COLOR_SYSTEM_GREEN
    : TEXT_COLOR_SYSTEM_BLUE;

  // Display rank letter
  PutSpecialChar(gBmFrameTmap0 + TILEMAP_INDEX(x + 4, y),
    color,
    GetDisplayRankStringFromExp(wexp));

  DrawStatBarGfx(0x401 + num*6, 5,
    gBmFrameTmap1 + TILEMAP_INDEX(x + 2, y + 1), TILEREF(0, STATSCREEN_BGPAL_6),
    0x22, 0, 0);
}
