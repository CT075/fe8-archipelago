#include "global.h"

#include "uimenu.h"

#include "bmitem.h"
#include "bmitemuse.h"
#include "bmmenu.h"
#include "bmtarget.h"
#include "bmunit.h"
#include "constants/classes.h"
#include "uiselecttarget.h"

#include "archipelago.h"

u8 PickCommandUsability(const struct MenuItemDef *def, int number) {

  if (gActiveUnit->state & US_HAS_MOVED) {
    return MENU_NOTSHOWN;
  }

  if (archipelagoOptions.lockpickUsability < GlobalRoguePick &&
      gActiveUnit->pClassData->number != CLASS_ROGUE) {
    return MENU_NOTSHOWN;
  }

  MakeTargetListForPick(gActiveUnit);

  return GetSelectTargetCount() ? MENU_ENABLED : MENU_NOTSHOWN;
}

u8 canUseLockpick(struct Unit *unit) {
  return (archipelagoOptions.lockpickUsability >= GlobalLockpicks
      || (UNIT_CATTRIBUTES(unit) & CA_THIEF));
}

s8 IsItemDisplayUsable(struct Unit *unit, int item) {
  if (GetItemAttributes(item) & IA_WEAPON) {
    return CanUnitUseWeapon(unit, item);
  }

  if (GetItemAttributes(item) & IA_STAFF) {
    return CanUnitUseStaff(unit, item);
  }

  if (GetItemUseEffect(item)) {
    if (unit->statusIndex == UNIT_STATUS_SLEEP) {
      return FALSE;
    }

    if (unit->statusIndex == UNIT_STATUS_BERSERK) {
      return FALSE;
    }

    if (!(canUseLockpick(unit)) && GetItemIndex(item) == ITEM_LOCKPICK) {
      return FALSE;
    }

    if (!(UNIT_CATTRIBUTES(unit) & CA_REFRESHER) && IsItemDanceRing(item)) {
      return FALSE;
    }
  }

  return TRUE;
}

s8 CanUnitUseLockpickItem(struct Unit *unit) {
  if (!canUseLockpick(unit)) {
    return FALSE;
  }

  if (!CanUnitUseChestKeyItem(unit) && !CanUnitUseDoorKeyItem(unit) &&
      !CanUnitOpenBridge(unit)) {
    return FALSE;
  }

  return TRUE;
}
