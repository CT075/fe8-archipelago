#include "global.h"

#include "uimenu.h"

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

s8 CanUnitUseLockpickItem(struct Unit *unit) {
  if (archipelagoOptions.lockpickUsability < GlobalLockpicks &&
      !(UNIT_CATTRIBUTES(unit) & CA_THIEF))
    return FALSE;

  if (!CanUnitUseChestKeyItem(unit) && !CanUnitUseDoorKeyItem(unit) &&
      !CanUnitOpenBridge(unit))
    return FALSE;

  return TRUE;
}
