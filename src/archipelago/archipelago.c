// TODO: cleanup

#include "global.h"

#include "event.h"
#include "proc.h"
#include "playerphase.h"
#include "player_interface.h"

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

// Incoming items

u8 eventsRunning(ProcPtr);

const struct ProcCmd PlayerPhaseEventBlockProc[] = {
  PROC_NAME("PlayerPhaseEventBlockProc"),
  PROC_WHILE(eventsRunning),
  PROC_CALL(StartPlayerPhaseSideWindows),
  PROC_END
};

// TODO: make this non-constant
extern const u16 ReceiveItemEvent[];

const u16 *receivedItemEvent(u8 itemId) {
  return ReceiveItemEvent;
}

void enqueueReceivedItemEvent() {
  if (!apReceivedItem->filled) {
    return;
  }

  u8 inWorldMap = Proc_Find((const struct ProcCmd *)0x08A3EE74) != NULL;
  const u16 *evt = receivedItemEvent(apReceivedItem->itemId);
  CallEvent(evt, inWorldMap ? EV_EXEC_WORLDMAP : EV_EXEC_GAMEPLAY);

  *lastReceivedEventIndex = apReceivedItem->eventIndex;
  apReceivedItem->filled = 0;
}

void PlayerPhase_MainIdleShim(ProcPtr proc) {
  if (apReceivedItem->filled) {
    EndPlayerPhaseSideWindows();
    enqueueReceivedItemEvent();
    Proc_StartBlocking(PlayerPhaseEventBlockProc, proc);
  }
  else {
    PlayerPhase_MainIdle(proc);
  }
}

u8 eventsRunning(ProcPtr proc) {
  if (EventEngineExists()) {
    return 1;
  } else if (apReceivedItem->filled) {
    enqueueReceivedItemEvent();
    return 1;
  } else {
    return 0;
  }
}
