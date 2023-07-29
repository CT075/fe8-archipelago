#include "bmunit.h"

int (*GetStatIncrase)(int growth) = &GET_STAT_INCREASE;

void CheckBattleUnitLevelUp(struct BattleUnit* bu) {
    if (CanBattleUnitGainLevels(bu) && bu->unit.exp >= 100) {
        int growthBonus, statGainTotal;

        bu->unit.exp -= 100;
        bu->unit.level++;

        if (UNIT_CATTRIBUTES(&bu->unit) & CA_MAXLEVEL10) {
            if (bu->unit.level == 10) {
                bu->expGain -= bu->unit.exp;
                bu->unit.exp = UNIT_EXP_DISABLED;
            }
        } else if (bu->unit.level == 20) {
            bu->expGain -= bu->unit.exp;
            bu->unit.exp = UNIT_EXP_DISABLED;
        }

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
