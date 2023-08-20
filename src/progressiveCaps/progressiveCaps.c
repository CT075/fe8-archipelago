#include "global.h"

#include "bmbattle.h"
#include "bmunit.h"
#include "bmitem.h"

#include "constants.h"
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

int GetItemAwardedExp(int item) {
  return 0;
}
