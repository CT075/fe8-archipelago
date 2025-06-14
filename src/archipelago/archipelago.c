// TODO: cleanup
// CR-soon cam: We could actually merge the handling of filler items and holy
// weapons.

#include "global.h"

#include "event.h"
#include "proc.h"
#include "playerphase.h"
#include "player_interface.h"
#include "fontgrp.h"
#include "popup.h"
#include "bmunit.h"
#include "bmitem.h"
#include "bmcontainer.h"
#include "constants/characters.h"
#include "constants/items.h"

#include "constants.h"
#include "archipelago.h"
#include "progressiveCaps.h"
#include "ram_structures.h"
#include "ParseDefinitions.event.h"

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

const struct PopupInstruction Popup_LevelCapIncreased[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(0x0D5),                   /* Level cap */
  POPUP_SPACE(1),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(0x0D4),                   /* increased! */
  POPUP_END
};

const struct PopupInstruction Popup_WRankUp[] = {
  POPUP_SOUND(0x5A),
  POPUP_MSG(0x001),                   /* [.] */
  POPUP_WTYPE_ICON,
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(0x0D6),                   /* Weapon rank */
  POPUP_SPACE(1),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(0x0D4),                   /* increased! */
  POPUP_END
};

const struct PopupInstruction Popup_DeathLink[] = {
  POPUP_SOUND(0x5C),
  POPUP_MSG(0x008),                   /* Got */
  POPUP_SPACE(1),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(DeathLinkText),           /* DeathLink! */
  POPUP_END
};

// Incoming items

u8 eventsRunning(ProcPtr);

const struct ProcCmd PlayerPhaseEventBlockProc[] = {
  PROC_NAME("PlayerPhaseEventBlockProc"),
  PROC_WHILE(eventsRunning),
  PROC_CALL(StartPlayerPhaseSideWindows),
  PROC_END
};

extern const u16 receiveAPItemEvent[];
extern const u16 activateDeathLinkEvent[];

u16 holyWeaponTrueValue(enum HolyWeapon hw) {
  switch (hw) {
    case Sieglinde:
      return ITEM_SWORD_SIEGLINDE;
    case Siegmund:
      return ITEM_LANCE_SIEGMUND;
    case Gleipnir:
      return ITEM_DARK_GLEIPNIR;
    case Garm:
      return ITEM_AXE_GARM;
    case Nidhogg:
      return ITEM_BOW_NIDHOGG;
    case Vidofnir:
      return ITEM_LANCE_VIDOFNIR;
    case Excalibur:
      return ITEM_ANIMA_EXCALIBUR;
    case Audhulma:
      return ITEM_SWORD_AUDHULMA;
    case Ivaldi:
      return ITEM_LIGHT_IVALDI;
    case Latona:
      return ITEM_STAFF_LATONA;
  }
  return -1;
}

u16 fillerItemTrueValue(enum FillerItem f) {
  switch (f) {
    case AngelicRobe:
      return ITEM_BOOSTER_HP;
    case EnergyRing:
      return ITEM_BOOSTER_POW;
    case SecretBook:
      return ITEM_BOOSTER_SKL;
    case Speedwings:
      return ITEM_BOOSTER_SPD;
    case GoddessIcon:
      return ITEM_BOOSTER_LCK;
    case DragonShield:
      return ITEM_BOOSTER_DEF;
    case Talisman:
      return ITEM_BOOSTER_RES;
    case BodyRing:
      return ITEM_BOOSTER_CON;
    case Boots:
      return ITEM_BOOSTER_MOV;
    case KnightCrest:
      return ITEM_KNIGHTCREST;
    case HeroCrest:
      return ITEM_HEROCREST;
    case OrionsBolt:
      return ITEM_ORIONSBOLT;
    case GuidingRing:
      return ITEM_GUIDINGRING;
    case ElysianWhip:
      return ITEM_ELYSIANWHIP;
    case OceanSeal:
      return ITEM_OCEANSEAL;
    case MasterSeal:
      return ITEM_MASTERSEAL;
  }
  return -1;
}

void giveAPEventReward(ProcPtr parent, struct IncomingEvent *evt) {
  struct Unit *target;
  switch (evt->kind) {
    case ProgLvlCap:
      bumpLevelCap();
      NewPopup_Simple(Popup_LevelCapIncreased, 0x60, 0, parent);
      break;
    case ProgWLv:
      bumpWeaponLevelCap(evt->payload.weaponType);
      switch (evt->payload.weaponType) {
        case Sword:
          SetPopupItem(ITYPE_SWORD);
          break;
        case Lance:
          SetPopupItem(ITYPE_LANCE);
          break;
        case Axe:
          SetPopupItem(ITYPE_AXE);
          break;
        case Bow:
          SetPopupItem(ITYPE_BOW);
          break;
        case Anima:
          SetPopupItem(ITYPE_ANIMA);
          break;
        case Light:
          SetPopupItem(ITYPE_LIGHT);
          break;
        case Dark:
          SetPopupItem(ITYPE_DARK);
          break;
        case Staff:
          SetPopupItem(ITYPE_STAFF);
          break;
      }
      NewPopup_Simple(Popup_WRankUp, 0x60, 0x0, parent);
      break;
    case HolyWeapon:
      switch (gPlaySt.chapterModeIndex) {
        case CHAPTER_MODE_EIRIKA:
          target = GetUnitFromCharId(CHARACTER_EIRIKA);
          break;
        case CHAPTER_MODE_EPHRAIM:
          target = GetUnitFromCharId(CHARACTER_EPHRAIM);
          break;
        default:
          target = GetUnitFromCharId(CHARACTER_EIRIKA);
          break;
      }
      u16 item = holyWeaponTrueValue(evt->payload.holyWeapon);
      NewPopup_ItemGot(parent, target, item);
      break;
    case FillerItem:
      switch (gPlaySt.chapterModeIndex) {
        case CHAPTER_MODE_EIRIKA:
          target = GetUnitFromCharId(CHARACTER_EIRIKA);
          break;
        case CHAPTER_MODE_EPHRAIM:
          target = GetUnitFromCharId(CHARACTER_EPHRAIM);
          break;
        default:
          target = GetUnitFromCharId(CHARACTER_EIRIKA);
          break;
      }
      u16 itemfiller = fillerItemTrueValue(evt->payload.fillerItem);
      NewPopup_ItemGot(parent, target, itemfiller);
      break;
  };
}

void receiveAPItem(struct EventEngineProc *proc) {
  struct IncomingEvent evt;
  unpackAPEventFromId(receivedAPItem->itemId, &evt);

  giveAPEventReward(proc, &evt);
}

void activateDeathLink(struct EventEngineProc *proc) {
  NewPopup_Simple(Popup_DeathLink, 0x60, 0, (ProcPtr *)proc);
}

// CR-someday cam: Dedup these two events into a generic "network event" handler

void enqueueReceivedItemEvent() {
  if (!receivedAPItem->filled) {
    return;
  }

  u8 inWorldMap = Proc_Find((const struct ProcCmd *)0x08A3EE74) != NULL;

  CallEvent(receiveAPItemEvent, inWorldMap ? EV_EXEC_WORLDMAP : EV_EXEC_GAMEPLAY);

  receivedAPItem->filled = 0;
  *receivedItemIndex += 1;
}

void triggerDeathLink() {
  if (!deathLinkInfo->pendingIn) {
    return;
  }

  deathLinkInfo->pendingIn = 0;

  u8 inWorldMap = Proc_Find((const struct ProcCmd *)0x08A3EE74) != NULL;

  CallEvent(activateDeathLinkEvent, inWorldMap ? EV_EXEC_WORLDMAP : EV_EXEC_GAMEPLAY);
}

bool8 HasConvoyAccess() {
  return true;
}

void PlayerPhase_MainIdleShim(ProcPtr proc) {
  deathLinkInfo->ready = true;
  if (deathLinkInfo->pendingIn) {
    EndPlayerPhaseSideWindows();
    triggerDeathLink();
    Proc_StartBlocking(PlayerPhaseEventBlockProc, proc);
  }
  else if (receivedAPItem->filled) {
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
  }
  else if (deathLinkInfo->pendingIn) {
    triggerDeathLink();
    return 1;
  }
  else if (receivedAPItem->filled) {
    enqueueReceivedItemEvent();
    return 1;
  }
  else {
    return 0;
  }
}

const struct LocationItem locItems[NUM_CHECKS] = {
  [0 ... NUM_CHECKS-1] = { .kind = Empty, .id = 0 }
};

void handleLocationGet(ProcPtr parent, int index) {
  int byteIndex = index / 8;
  int bitIndex = index % 8;

  checkedLocations->found[byteIndex] |= (1 << bitIndex);

  const struct LocationItem *item = &locItems[index];

  switch (item->kind) {
    case Empty:
      return;
    case APItem:
      NewPopup_Simple(Popup_GotAPItem, 0x60, 0x0, parent);
      break;
    case SelfItem:
      struct IncomingEvent evt;
      unpackAPEventFromId(item->id, &evt);
      giveAPEventReward(parent, &evt);
  }
}

void handleChapterClear(ProcPtr parent, int chapterId) {
  handleLocationGet(parent, chapterClearFlagIndex(chapterId));
}

void handleHolyWeaponGet(ProcPtr parent, enum HolyWeapon hw) {
  handleLocationGet(parent, holyWeaponFlagIndex(hw));
}

const struct ArchipelagoOptions archipelagoOptions = {0};
const struct ArchipelagoInfo archipelagoInfo = {0};
