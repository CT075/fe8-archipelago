#include "global.h"

#include "bmunit.h"

#include "bmsave.h"
#include "bmreliance.h"
#include "constants/classes.h"
#include "event.h"

#include "archipelago.h"
#include "ram_structures.h"

void deathlinkInvalidateSuspend(void) {
  InvalidateSuspendSave(SAVE_ID_SUSPEND);
}

void UnitKill(struct Unit* unit) {
  if (UNIT_FACTION(unit) == FACTION_BLUE) {
    if (UNIT_IS_PHANTOM(unit))
      unit->pCharacterData = NULL;
    else {
      unit->state |= US_DEAD | US_HIDDEN;
      if (archipelagoOptions.deathLinkKind == OnAnyDeath) {
        deathLinkInfo->pendingOut += 1;
      }
      InitUnitsupports(unit);
    }
  } else {
    unit->pCharacterData = NULL;
  }
}

void CallGameOverEvent(void) {
  deathLinkInfo->ready = false;
  if (archipelagoOptions.deathLinkKind >= OnGameOver) {
    deathLinkInfo->pendingOut += 1;
  }
  EventEngine_Create((u16 *)EventScr_GameOver, EV_EXEC_GAMEPLAY);
}

// If you receive a deathlink, that Game Over should not trigger another
// deathlink. A hacky way to deal with that is to decrement the outgoing
// deathlink counter *before* triggering the game over.
// CR cam: Come up with a more principled way to do this.
void deathlinkDebounceHack(struct EventEngineProc *_proc) {
  if (archipelagoOptions.deathLinkKind >= OnGameOver) {
    deathLinkInfo->pendingOut -= 1;
  }
}
