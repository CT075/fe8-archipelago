#include "global.h"

#include "proc.h"

#include "progressiveCaps.h"
#include "constants.h"
#include "archipelago.h"

// Outgoing items

void markLocation(int index) {
  int byteIndex = index / 8;
  int bitIndex = index % 8;

  checkedLocations->found[byteIndex] |= (1 << bitIndex);
}

void markChapterCleared(int chapterId) {
  markLocation(chapterClearFlagIndex(chapterId));
}

void markHolyWeaponGet(enum HolyWeapon weap) {
  markLocation(holyWeaponFlagIndex(weap));
}

/*
void PlayerPhase_MainIdleShim(ProcPtr proc) {
  if (PPEventQueue != NULL) {
    EndPlayerPhaseSideWindows();

    EnqueueWaitingPPEvents();

    Proc_StartBlocking(PlayerPhaseEventBlockProc, proc);
  } else {
    PPEventActiveFlag = 0;
    if (shouldRefreshBmSprites) {
      shouldRefreshBmSprites = 0;
      RefreshEntityBmMaps();
      RenderBmMap();
      RefreshUnitSprites();
    }

    return PlayerPhase_MainIdle(proc);
  }
}
*/
