// TODO: cleanup
// CR-soon cam: We could actually merge the handling of filler items and holy
// weapons.

#include "global.h"

#include "bmcontainer.h"
#include "bmitem.h"
#include "bmunit.h"
#include "constants/characters.h"
#include "constants/items.h"
#include "event.h"
#include "fontgrp.h"
#include "player_interface.h"
#include "playerphase.h"
#include "popup.h"
#include "proc.h"

#include "ParseDefinitions.event.h"
#include "archipelago.h"
#include "constants.h"
#include "deployPermits.h"
#include "progressiveCaps.h"
#include "ram_structures.h"

const struct PopupInstruction Popup_GotAPItem[] = {
  POPUP_SOUND(0x5A), POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(0x008), /* Got */
  POPUP_SPACE(1),    POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(0x0DD), /* an Archipelago Item */
  POPUP_SPACE(1),    POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(0x022), /* .[.] */
  POPUP_END
};

const struct PopupInstruction Popup_LevelCapIncreased[] = {
  POPUP_SOUND(0x5A), POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(0x0D5), /* Level cap */
  POPUP_SPACE(1),    POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(0x0D4), /* increased! */
  POPUP_END
};

const struct PopupInstruction Popup_WRankUp[] = {
  POPUP_SOUND(0x5A), POPUP_MSG(0x001), /* [.] */
  POPUP_WTYPE_ICON,  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(0x0D6), /* Weapon rank */
  POPUP_SPACE(1),    POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(0x0D4), /* increased! */
  POPUP_END
};

const struct PopupInstruction Popup_DeathLink[] = {
  POPUP_SOUND(0x5C),
  POPUP_MSG(0x008), /* Got */
  POPUP_SPACE(1),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(DeathLinkText), /* DeathLink! */
  POPUP_END
};

static const struct PopupInstruction Popup_SethCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(SethNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_FranzCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(FranzNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_GilliamCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(GilliamNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_VanessaCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(VanessaNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_MoulderCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(MoulderNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_RossCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(RossNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_GarciaCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(GarciaNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_NeimiCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(NeimiNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_ColmCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(ColmNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_ArturCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(ArturNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_LuteCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(LuteNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_NatashaCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(NatashaNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_JoshuaCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(JoshuaNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_FordeCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(FordeNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_KyleCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(KyleNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_TanaCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(TanaNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_AmeliaCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(AmeliaNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_InnesCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(InnesNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_GerikCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(GerikNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_TethysCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(TethysNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_MarisaCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(MarisaNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_LArachelCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(LArachelNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_DozlaCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(DozlaNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_SalehCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(SalehNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_EwanCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(EwanNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_CormagCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(CormagNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_RennacCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(RennacNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_DuesselCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(DuesselNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_KnollCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(KnollNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_MyrrhCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(MyrrhNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};
static const struct PopupInstruction Popup_SyreneCanDeploy[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(SyreneNameText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};

static const struct PopupInstruction *const kUnitDeployPopups[] = {
  Popup_SethCanDeploy,     /* Seth=0 */
  Popup_FranzCanDeploy,    /* Franz=1 */
  Popup_GilliamCanDeploy,  /* Gilliam=2 */
  Popup_VanessaCanDeploy,  /* Vanessa=3 */
  Popup_MoulderCanDeploy,  /* Moulder=4 */
  Popup_RossCanDeploy,     /* Ross=5 */
  Popup_GarciaCanDeploy,   /* Garcia=6 */
  Popup_NeimiCanDeploy,    /* Neimi=7 */
  Popup_ColmCanDeploy,     /* Colm=8 */
  Popup_ArturCanDeploy,    /* Artur=9 */
  Popup_LuteCanDeploy,     /* Lute=10 */
  Popup_NatashaCanDeploy,  /* Natasha=11 */
  Popup_JoshuaCanDeploy,   /* Joshua=12 */
  Popup_FordeCanDeploy,    /* Forde=13 */
  Popup_KyleCanDeploy,     /* Kyle=14 */
  Popup_TanaCanDeploy,     /* Tana=15 */
  Popup_AmeliaCanDeploy,   /* Amelia=16 */
  Popup_InnesCanDeploy,    /* Innes=17 */
  Popup_GerikCanDeploy,    /* Gerik=18 */
  Popup_TethysCanDeploy,   /* Tethys=19 */
  Popup_MarisaCanDeploy,   /* Marisa=20 */
  Popup_LArachelCanDeploy, /* LArachel=21 */
  Popup_DozlaCanDeploy,    /* Dozla=22 */
  Popup_SalehCanDeploy,    /* Saleh=23 */
  Popup_EwanCanDeploy,     /* Ewan=24 */
  Popup_CormagCanDeploy,   /* Cormag=25 */
  Popup_RennacCanDeploy,   /* Rennac=26 */
  Popup_DuesselCanDeploy,  /* Duessel=27 */
  Popup_KnollCanDeploy,    /* Knoll=28 */
  Popup_MyrrhCanDeploy,    /* Myrrh=29 */
  Popup_SyreneCanDeploy,   /* Syrene=30 */
};

const struct PopupInstruction Popup_SethDeployStage1[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(SethDeployStage1OpenText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_GRAY),
  POPUP_MSG(SethDeployStage1LockedText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};

const struct PopupInstruction Popup_SethDeployStage2[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(SethDeployStage2OpenText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_GRAY),
  POPUP_MSG(SethDeployStage2LockedText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};

const struct PopupInstruction Popup_SethDeployStage3[] = {
  POPUP_SOUND(0x5A),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_BLUE),
  POPUP_MSG(SethDeployStage3OpenText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_GRAY),
  POPUP_MSG(SethDeployStage3LockedText),
  POPUP_COLOR(TEXT_COLOR_SYSTEM_WHITE),
  POPUP_MSG(CanDeploySuffixText),
  POPUP_END
};

// Incoming items

u8 eventsRunning(ProcPtr);

const struct ProcCmd PlayerPhaseEventBlockProc[] = {
  PROC_NAME("PlayerPhaseEventBlockProc"), PROC_WHILE(eventsRunning),
  PROC_CALL(StartPlayerPhaseSideWindows), PROC_END
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
  case UnitDeploy:
    setDeployPermit(evt->payload.recruitedUnit);
    NewPopup_Simple(kUnitDeployPopups[evt->payload.recruitedUnit], 0x60, 0, parent);
    break;
  case ProgSethDeploy: {
    u8 stage = *sethDeployStage;
    if (stage < 4) {
      stage += 1;
      *sethDeployStage = stage;
    }
    const struct PopupInstruction *popup;
    switch (stage) {
    case 1:
      popup = Popup_SethDeployStage1;
      break;
    case 2:
      popup = Popup_SethDeployStage2;
      break;
    case 3:
      popup = Popup_SethDeployStage3;
      break;
    default:
      popup = Popup_SethCanDeploy;
      setDeployPermit(Seth);
      break;
    }
    NewPopup_Simple(popup, 0x60, 0, parent);
    break;
  }
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

bool8 HasConvoyAccess() { return true; }

void PlayerPhase_MainIdleShim(ProcPtr proc) {
  deathLinkInfo->ready = true;
  checkAllPlayerUnitsRecruited(proc);
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

const struct LocationItem locItems[NUM_CHECKS] = { [0 ... NUM_CHECKS -
                                                    1] = { .kind = Empty, .id = 0 } };

void handleLocationGet(ProcPtr parent, int index) {
  int byteIndex = index / 8;
  int bitIndex = index % 8;

  if (checkedLocations->found[byteIndex] & (1 << bitIndex)) {
    return;
  }

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

void handleUnitRecruited(ProcPtr parent, enum RecruitedUnit unit) {
  handleLocationGet(parent, recruitedUnitFlagIndex(unit));
}

static const struct {
  int charId;
  enum RecruitedUnit unit;
} kTrackedChars[] = {
  { CHARACTER_SETH, Seth },       { CHARACTER_FRANZ, Franz },
  { CHARACTER_GILLIAM, Gilliam }, { CHARACTER_VANESSA, Vanessa },
  { CHARACTER_MOULDER, Moulder }, { CHARACTER_ROSS, Ross },
  { CHARACTER_GARCIA, Garcia },   { CHARACTER_NEIMI, Neimi },
  { CHARACTER_COLM, Colm },       { CHARACTER_ARTUR, Artur },
  { CHARACTER_LUTE, Lute },       { CHARACTER_NATASHA, Natasha },
  { CHARACTER_JOSHUA, Joshua },   { CHARACTER_FORDE, Forde },
  { CHARACTER_KYLE, Kyle },       { CHARACTER_TANA, Tana },
  { CHARACTER_AMELIA, Amelia },   { CHARACTER_INNES, Innes },
  { CHARACTER_GERIK, Gerik },     { CHARACTER_TETHYS, Tethys },
  { CHARACTER_MARISA, Marisa },   { CHARACTER_LARACHEL, LArachel },
  { CHARACTER_DOZLA, Dozla },     { CHARACTER_SALEH, Saleh },
  { CHARACTER_EWAN, Ewan },       { CHARACTER_CORMAG, Cormag },
  { CHARACTER_RENNAC, Rennac },   { CHARACTER_DUESSEL, Duessel },
  { CHARACTER_KNOLL, Knoll },     { CHARACTER_MYRRH, Myrrh },
  { CHARACTER_SYRENE, Syrene },
};

void checkAllPlayerUnitsRecruited(ProcPtr proc) {
  if (gPlaySt.chapterStateBits & PLAY_FLAG_EXTRA_MAP) {
    return;
  }
  for (int i = 0; i < (int)(sizeof(kTrackedChars) / sizeof(kTrackedChars[0])); i++) {
    if (GetUnitFromCharIdAndFaction(kTrackedChars[i].charId, FACTION_ID_BLUE)) {
      handleUnitRecruited(proc, kTrackedChars[i].unit);
    }
  }
}

const struct ArchipelagoOptions archipelagoOptions = { 0 };
const struct ArchipelagoInfo archipelagoInfo = { 0 };
