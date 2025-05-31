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

void deathlinkGameOver(void) {
  EventEngine_Create((u16 *)EventScr_GameOver, EV_EXEC_GAMEPLAY);
}
