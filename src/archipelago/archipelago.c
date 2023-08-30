// TODO: cleanup

#include "global.h"

#include "event.h"
#include "proc.h"
#include "playerphase.h"
#include "player_interface.h"
#include "fontgrp.h"
#include "popup.h"

#include "progressiveCaps.h"
#include "constants.h"
#include "archipelago.h"

const struct PopupInstruction Popup_GotAPItem[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(0x008),                   /* Got */
  POPUP_SPACE(1),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(0x0DD),                   /* an Archipelago Item */
  POPUP_SPACE(1),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(0x022),                   /* .[.] */
  POPUP_END
};

// Outgoing items

void markLocation(int index) {
  int byteIndex = index / 8;
  int bitIndex = index % 8;

  checkedLocations->found[byteIndex] |= (1 << bitIndex);
}

// CR cam: extract common logic between these two `handle` functions.
// CR cam: Check whether the item is within our own ROM first

void handleChapterClear(ProcPtr parent, int chapterId) {
  markLocation(chapterClearFlagIndex(chapterId));
  NewPopup_Simple(Popup_GotAPItem, 0x60, 0x0, parent);
}

void handleHolyWeaponGet(ProcPtr parent, enum HolyWeapon hw) {
  markLocation(holyWeaponFlagIndex(hw));
  NewPopup_Simple(Popup_GotAPItem, 0x60, 0x0, parent);
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
extern const u16 GiveSieglindeEvent[];
extern const u16 GiveSiegmundEvent[];
extern const u16 GiveGleipnirEvent[];
extern const u16 GiveGarmEvent[];
extern const u16 GiveNidhoggEvent[];
extern const u16 GiveVidofnirEvent[];
extern const u16 GiveExcaliburEvent[];
extern const u16 GiveAudhulmaEvent[];
extern const u16 GiveIvaldiEvent[];
extern const u16 GiveLatonaEvent[];

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
      }
    case HolyWeapon:
      switch (evt->payload.holyWeapon) {
        case Sieglinde:
          return GiveSieglindeEvent;
        case Siegmund:
          return GiveSiegmundEvent;
        case Gleipnir:
          return GiveGleipnirEvent;
        case Garm:
          return GiveGarmEvent;
        case Nidhogg:
          return GiveNidhoggEvent;
        case Vidofnir:
          return GiveVidofnirEvent;
        case Excalibur:
          return GiveExcaliburEvent;
        case Audhulma:
          return GiveAudhulmaEvent;
        case Ivaldi:
          return GiveIvaldiEvent;
        case Latona:
          return GiveLatonaEvent;
      }
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
