#include "global.h"
#include "bmbattle.h"
#include "bmunit.h"
#include "bmitem.h"
#include "constants/characters.h"

#include "archipelago.h"

bool hasDemonKingBuff(struct BattleUnit *bu) {
  return (
      archipelagoOptions.superDemonKing &&
      bu->unit.pCharacterData->number == CHARACTER_FOMORTIIS);
}

void ComputeBattleUnitAttack(struct BattleUnit *attacker, struct BattleUnit *defender) {
  if (GetItemIndex(attacker->weapon) == ITEM_MONSTER_STONE) {
    attacker->battleAttack = 0;
    return;
  }

  short weaponMight = GetItemMight(attacker->weapon) + attacker->wTriangleDmgBonus;
  bool usingHolyWeapon = false;
  short effectiveCoefficient = 1;

  if (IsUnitEffectiveAgainst(&attacker->unit, &defender->unit) == TRUE) {
    effectiveCoefficient = 3;
  }

  if (IsItemEffectiveAgainst(attacker->weapon, &defender->unit) == TRUE) {
    switch (GetItemIndex(attacker->weapon)) {
      case ITEM_SWORD_AUDHULMA:
      case ITEM_LANCE_VIDOFNIR:
      case ITEM_AXE_GARM:
      case ITEM_BOW_NIDHOGG:
      case ITEM_ANIMA_EXCALIBUR:
      case ITEM_LIGHT_IVALDI:
      case ITEM_DARK_GLEIPNIR:
      case ITEM_SWORD_SIEGLINDE:
      case ITEM_LANCE_SIEGMUND:
        usingHolyWeapon = true;
        // intentionally no break here

      default:
        effectiveCoefficient = 3;
        break;
    }
  }

  short attack = effectiveCoefficient * weaponMight + attacker->unit.pow;

  if (hasDemonKingBuff(defender) && !usingHolyWeapon) {
    attack /= 2;
  }

  attacker->battleAttack = attack;
}
