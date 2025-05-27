#include "bmunit.h"
#include "bmitem.h"
#include "event.h"
#include "eventinfo.h"
#include "uimenu.h"

#include "SpecialEventPerUnit.h"

u8 runEventFromMenu(struct MenuProc *owner, struct MenuItemProc *cmd, u16 *script) {
  CallEvent(script, EV_EXEC_CUTSCENE);

  return MENU_ACT_SKIPCURSOR | MENU_ACT_END | MENU_ACT_SND6A | MENU_ACT_CLEAR;
}

// Special Event Per Unit compat

u8 SEPUAvailableImpl(
    const struct MenuItemDef *self, int number,
    struct SEPUAvailabilityConfig *cfg
) {
  if (cfg->character != 0 && cfg->character != UNIT_CHAR_ID(gActiveUnit)) {
    return MENU_NOTSHOWN;
  }

  if (cfg->class != 0 && (cfg->class != UNIT_CLASS_ID(gActiveUnit))) {
    return MENU_NOTSHOWN;
  }

  if (cfg->flag != 0 && !CheckFlag(cfg->flag)) {
    return MENU_NOTSHOWN;
  }

  if (cfg->item != 0) {
    u8 found = 0;
    for (int i = 0 ; i < UNIT_ITEM_COUNT ; i += 1) {
      if (ITEM_INDEX(gActiveUnit->items[i]) == cfg->item) {
        // We could `return 1` immediately, but this is more obviously correct.
        found = 1;
      }
    }
    if (!found) {
      return MENU_NOTSHOWN;
    }
  }

  return MENU_ENABLED;
}
