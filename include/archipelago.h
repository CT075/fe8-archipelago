#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

#include "global.h"
#include "proc.h"
#include "constants/items.h"

#include "connector_config.h"

#define SLOT_NAME_MAX 64

#define sizeof_round(ty) ((sizeof(ty) + sizeof(int)-1) & ~(sizeof(int)-1))

// CR cam: it would be nice to not need to do this address bumping manually
#define CHECKED_LOCATIONS_ADDR (PROG_CAPS_ADDR + sizeof_round(struct ProgressiveCaps))
#define checkedLocations ((struct Checks *)(CHECKED_LOCATIONS_ADDR))

struct APReceivedItem {
  u16 itemId;
  u8 filled;
};

#define RECEIVED_AP_ITEM_ADDR (CHECKED_LOCATIONS_ADDR + sizeof_round(struct Checks))
#define apReceivedItem ((struct APReceivedItem *)(RECEIVED_AP_ITEM_ADDR))

#define RECEIVED_ITEM_INDEX_ADDR (RECEIVED_AP_ITEM_ADDR + sizeof_round(struct APReceivedItem))
#define receivedItemIndex ((u32 *)(RECEIVED_ITEM_INDEX_ADDR))

void handleChapterClear(ProcPtr parent, int chapterNum);
void handleHolyWeaponGet(ProcPtr parent, enum HolyWeapon weap);

const u16 *receivedItemEvent(struct IncomingEvent *evt);

// CR cam: This should come from `Generate.hs` so we can ensure that this
// struct definition doesn't drift from the python code that sets it
struct ArchipelagoOptions {
  bool superDemonKing;
};

struct ArchipelagoInfo {
  u8 slotName[SLOT_NAME_MAX];
};

extern const struct ArchipelagoOptions archipelagoOptions;
extern const struct ArchipelagoInfo archipelagoInfo;

#endif // ARCHIPELAGO_H
