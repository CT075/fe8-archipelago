#include "global.h"

#include "bmmind.h"
#include "constants/event-flags.h"
#include "event.h"
#include "eventinfo.h"
#include "promoPermits.h"
#include "ram_structures.h"
#include "uimenu.h"

u8 debugEndMapEffect(struct MenuProc *menu, struct MenuItemProc *menuItem) {
  gActionData.unitActionType = UNIT_ACTION_WAIT;
  SetFlag(EVFLAG_DEFEAT_ALL);
  SetFlag(EVFLAG_WIN);
  return MENU_ACT_SKIPCURSOR | MENU_ACT_END | MENU_ACT_SND6A | MENU_ACT_CLEAR;
}

// Called from the testing-only prologue ending (DEBUG_PROMO_QUICKSTART).
// Grants every deploy permit so units can be fielded at prep screens without
// a connected client, plus exactly the Paladin promo permit: Franz's Knight
// Crest should be usable with only Paladin selectable, while Gilliam's
// (General/Great Knight, both locked) stays greyed out.
void debugPromoQuickstart(struct EventEngineProc *proc) {
  *deployPermits = ~0u;
  setPromoPermit(Paladin);
}
