#include "global.h"

#include "bmmind.h"
#include "constants/event-flags.h"
#include "eventinfo.h"
#include "uimenu.h"

u8 debugEndMapEffect(struct MenuProc *menu, struct MenuItemProc *menuItem) {
  gActionData.unitActionType = UNIT_ACTION_WAIT;
  SetFlag(EVFLAG_DEFEAT_ALL);
  SetFlag(EVFLAG_WIN);
  return MENU_ACT_SKIPCURSOR | MENU_ACT_END | MENU_ACT_SND6A | MENU_ACT_CLEAR;
}
