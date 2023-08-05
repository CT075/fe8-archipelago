#include <stddef.h>

#include "proc.h"
#include "types.h"
#include "ap_event.h"
#include "unit.h"

struct EnqueuedEventCall {
  const u16* events;
  u8 execType;
  i8 used;
};

// Used for events that integration code specifically requests from the connector
// (for example, location check events)
volatile u32 ActiveEventType = 0;
volatile u32 ActiveEventRequest = 0;
volatile struct APQueuedEvent *ActiveEventResponse = NULL;

// Used for events that are queued to run during idle moments in player phase
// (for example, notifications for newly received items)
volatile struct APQueuedEvent *PPEventQueue = NULL;
volatile u8 PPEventActiveFlag = 0;

u8 triggeredGameOver = 0;
u8 shouldRefreshBmSprites = 0;

/* Extern items only used by this code */
extern struct EnqueuedEventCall gEventCallQueue[];

extern struct Vec2 gBmMapSize;

u16 ActiveEventCleanup[] CONST_DATA;
struct ProcCmd gUnknown_08A3EE74[] CONST_DATA;

void PlayerPhase_MainIdle(ProcPtr proc);
void StartMapSongBgm();
void ResetUnitSpriteHover();
void StartPlayerPhaseSideWindows();
void EndPlayerPhaseSideWindows();
void RefreshEntityBmMaps();
void RenderBmMap();
void RefreshUnitSprites();
void sub_8085374(ProcPtr proc);

struct ProcCmd ActiveEventProc[] CONST_DATA = {
  PROC_NAME("ActiveEventProc"),
  PROC_WHILE(RunActiveEventRequest),
  PROC_END
};

struct ProcCmd PlayerPhaseEventBlockProc[] CONST_DATA = {
  PROC_NAME("PlayerPhaseEventBlockProc"),
  PROC_WHILE(PPEventsRunning),
  // PROC_CALL(StartMapSongBgm),
  PROC_CALL(StartPlayerPhaseSideWindows),
  // PROC_CALL(ResetUnitSpriteHover),
  PROC_END
};

struct ProcCmd WMEventBlockProc[] CONST_DATA = {
  PROC_NAME("WMEventBlockProc"),
  PROC_WHILE(PPEventsRunning),
  PROC_END
};

void EnqueueWaitingPPEvents() {
  struct EnqueuedEventCall *callIt = gEventCallQueue;
  volatile struct APQueuedEvent *ppEventIt = PPEventQueue;
  u8 inWorldMap = Proc_Find(gUnknown_08A3EE74) != NULL;

  if (inWorldMap) {
    while ((ppEventIt != NULL) && !ppEventIt->runInWorldMap) {
      ppEventIt = ppEventIt->next;
    }
  }

  if (ppEventIt == NULL) {
    PPEventQueue = NULL;
    return;
  }

  /* Start the event engine with the first queued event if it doesn't exist already */
  if (!EventEngineExists()) {
    PPEventActiveFlag = 1;
    EventEngine_Create(ppEventIt->events, inWorldMap ? 0 : ppEventIt->execType);
    ppEventIt = ppEventIt->next;
  }

  /* Move events from AP queue to event engine queue */
  for (u8 i = 0; i < 0x0F; i++) {
    if (inWorldMap) {
      while ((ppEventIt != NULL) && !ppEventIt->runInWorldMap) {
        ppEventIt = ppEventIt->next;
      }
    }

    if (ppEventIt == NULL) {
      break;
    }

    if (!callIt->used) {
      callIt->events = ppEventIt->events;
      callIt->execType = inWorldMap ? 0 : ppEventIt->execType;
      callIt->used = 1;
      ppEventIt = ppEventIt->next;
      PPEventActiveFlag = 1;
    }
  }

  PPEventQueue = ppEventIt;
}

void PlayerPhase_MainIdleShim(ProcPtr proc) {
  if (PPEventQueue != NULL) {
    EndPlayerPhaseSideWindows();
    // RefreshEntityBmMaps();
    // RenderBmMap();
    // RefreshUnitSprites();

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

u8 InterceptWMInputHandling(ShimRegisters *regs) {
  if (PPEventQueue != NULL) {
    EnqueueWaitingPPEvents();
    Proc_StartBlocking(WMEventBlockProc, regs->r0);
    return 1;
  } else {
    PPEventActiveFlag = 0;
    return 0;
  }
}

u8 PPEventsRunning(ProcPtr proc) {
  if (EventEngineExists()) {
    return 1;
  } else if (PPEventQueue != NULL) {
    EnqueueWaitingPPEvents();
    return 1;
  } else {
    PPEventActiveFlag = 0;
    return 0;
  }
}

u8 RunActiveEventRequest(ProcPtr proc) {
  u8 inWorldMap = 0;
  struct APQueuedEvent *it = ActiveEventResponse;

  if (it == NULL) {
    return 1;
  } else {
    inWorldMap = Proc_Find(gUnknown_08A3EE74) != NULL;

    while (it != NULL) {
      if (inWorldMap) {
        while ((it != NULL) && !it->runInWorldMap) {
          it = it->next;
        }
      }

      if (it == NULL) {
        break;
      }

      if (it->events != NULL) {
        CallEvent(it->events, inWorldMap ? 0 : it->execType);
      }

      it = it->next;
    }
    CallEvent(ActiveEventCleanup, inWorldMap ? 0 : 3);
    return 0;
  }
}

void FinishActiveEvent(ProcPtr parent) {
  ActiveEventRequest = 0;
  ActiveEventType = 0;
  ActiveEventResponse = NULL;
}

ProcPtr RequestActiveEvent(ProcPtr parent, u32 type, u32 request) {
  ActiveEventType = type;
  ActiveEventRequest = request;
  return Proc_StartBlocking(ActiveEventProc, parent);
}

void ASMCOnUnitRecruited(ProcPtr parent) {
  u32 reqId = 0;
  u8 charId = 0;
  u8 slot = 0;

  /* On entry, slots 1-4 contain the IDs of characters that were just recruited. */
  for (i8 i = 3; i >= 0; i--) {
    slot = i + 1;
    charId = gEventSlots[slot] & 0xFF;
    reqId = (reqId << 8) | charId;
  }

  RequestActiveEvent(parent, 1, reqId);
}

void ASMCPrepareUnitDisappearEffect(ProcPtr parent) {
  u8 charId = 0;
  struct Unit* curUnit = NULL;
  u32 posVal = 0;

  /* On entry, slot 1 contains the ID of the unit we want to check. */
  charId = gEventSlots[1] & 0xFF;
  curUnit = GetUnitFromCharId(charId);
  gEventSlots[0xB] = 0;
  gEventSlots[1] = 0;
  if (curUnit != NULL) {
    if (!IsCharacterAvailable[charId]) {
      if ((curUnit->state & 0x0001000C) == 0) {
        posVal = (((u16)curUnit->yPos) << 16) | curUnit->xPos;
        gEventSlots[0xB] = posVal;
        gEventSlots[1] = 1;
      }

      /* Mark as hidden, undeployed, and out of party
       * (bits 0, 3, 16, 21, and 26)
       */
      curUnit->state |= 0x04210009;
    }
  }
}

int GetCurrentLordId() {
  u8 chapterIdx = *(u8*)(((u32)gRAMChapterData) + 0x0E);
  u8 chapterMode = *(u8*)(((u32)gRAMChapterData) + 0x1B);

  if (chapterIdx == 0x05 || chapterMode == 3) {
    return 0x0F; // Ephraim
  } else {
    return 0x01; // Eirika
  }
}

void GetUnitAppearPosition(struct Unit *unit, int *xOut, int *yOut) {
  int ix, iy, minDistance = 9999;
  const i8 *terrainLookup = GetUnitMovementCost(unit);
  struct Unit *lord = GetUnitFromCharId(GetCurrentLordId());

  // gBmMapUnit[gActiveUnit->yPos][gActiveUnit->xPos] = 0xFF;

  for (iy = gBmMapSize.y - 1; iy >= 0; --iy) {
    for (ix = gBmMapSize.x - 1; ix >= 0; --ix) {
      int distance;

      /* Is there already a unit here? */
      if (gBmMapUnit[iy][ix] != 0)
        continue;

      /* Is there a hidden unit here(?) */
      if (gBmMapHidden[iy][ix] & 1)
        continue;

      /* Can the unit move on this terrain? */
      if (terrainLookup[gBmMapTerrain[iy][ix]] <= 0)
        continue;

      distance = RECT_DISTANCE(ix, iy, lord->xPos, lord->yPos);
      if (minDistance >= distance) {
        minDistance = distance;
        *xOut = ix;
        *yOut = iy;
      }
    }
  }

  // gBmMapUnit[gActiveUnit->yPos][gActiveUnit->xPos] = 0;
}

void ASMCPrepareUnitAppearEffect(ProcPtr parent) {
  u8 charId = gEventSlots[1] & 0xFF;
  struct Unit* unit = GetUnitFromCharId(charId);
  int x, y = 0;
  u8 inWorldMap = 0;
  u32 state = unit->state;

  gEventSlots[1] = 0;
  if (unit == NULL) {
    return;
  }

  inWorldMap = Proc_Find(gUnknown_08A3EE74) != NULL;
  if (inWorldMap) {
    /* Check if unit was previously REMU'd */
    if ((unit->state & 0x04010000) == 0) {
        return;
    }

    unit->state &= ~0x04010009;
    gEventSlots[1] = 2;
    gEventSlots[2] = UnitReceivedTextIds[charId];
  } else {
    /* Check if unit was previously REMU'd */
    if ((unit->state & 0x04010000) == 0) {
      return;
    }

    GetUnitAppearPosition(unit, &x, &y);

    unit->xPos = x;
    unit->yPos = y;
    unit->state &= ~0x04010009;

    gEventSlots[0xB] = (y << 16) | x;
    gEventSlots[1] = 1;
    gEventSlots[2] = 0;

    RefreshEntityBmMaps();
    RenderBmMap();
    RefreshUnitSprites();
  }
}

void ASMCSendVictoryEvent(ProcPtr parent) {
  RequestActiveEvent(parent, 2, 1);
}

u8 OnGameOver(ShimRegisters *regs) {
  if (!triggeredGameOver) {
    RequestActiveEvent((ProcPtr)regs->r0, 3, 1);
  }
  return 0;
}

void ASMCTriggerGameOver(ProcPtr parent) {
  triggeredGameOver = 1;
  sub_8085374(parent);
  triggeredGameOver = 0;
}
