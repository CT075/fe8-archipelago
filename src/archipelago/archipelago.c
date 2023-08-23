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

extern const u16 LevelUncapEvent[];
extern const u16 SwordRankUpEvent[];
extern const u16 LanceRankUpEvent[];
extern const u16 AxeRankUpEvent[];
extern const u16 BowRankUpEvent[];
extern const u16 AnimaRankUpEvent[];
extern const u16 LightRankUpEvent[];
extern const u16 DarkRankUpEvent[];
extern const u16 StaffRankUpEvent[];

const u16 *receivedItemEvent(struct IncomingEvent *evt) {
  switch (evt->kind) {
    case ProgLvlCap:
      return LevelUncapEvent;
    case ProgWLv:
      switch (evt->payload.weaponType) {
        case Sword:
          return SwordRankUpEvent;
        case Lance:
          return LanceRankUpEvent;
        case Axe:
          return AxeRankUpEvent;
        case Bow:
          return BowRankUpEvent;
        case Anima:
          return AnimaRankUpEvent;
        case Light:
          return LightRankUpEvent;
        case Dark:
          return DarkRankUpEvent;
        case Staff:
          return StaffRankUpEvent;
      };
    case HolyWeapon:
      // CR cam: .
      return LevelUncapEvent;
  };

  return LevelUncapEvent;
}

void giveAPEventReward(struct IncomingEvent *evt) {
  switch (evt->kind) {
    case ProgLvlCap:
      bumpLevelCap();
      break;
    case ProgWLv:
      bumpWeaponLevelCap(evt->payload.weaponType);
      break;
    case HolyWeapon:
      // CR cam: .
      break;
  };
}

void enqueueReceivedItemEvent() {
  if (!apReceivedItem->filled) {
    return;
  }

  struct IncomingEvent evt;

  u8 inWorldMap = Proc_Find((const struct ProcCmd *)0x08A3EE74) != NULL;
  unpackAPEventFromId(apReceivedItem->itemId, &evt);

  giveAPEventReward(&evt);

  const u16 *evtscr = receivedItemEvent(&evt);
  CallEvent(evtscr, inWorldMap ? EV_EXEC_WORLDMAP : EV_EXEC_GAMEPLAY);

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
