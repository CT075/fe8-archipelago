#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

#include "connector_config.h"

#define sizeof_round(ty) ((sizeof(ty) + sizeof(int)-1) & ~(sizeof(int)-1))

// CR cam: it would be nice to not need to do this address bumping manually
#define CHECKED_LOCATIONS_ADDR (FREE_RAM_START + sizeof_round(struct ProgressiveCaps))
#define checkedLocations ((struct Checks *)(CHECKED_LOCATIONS_ADDR))

struct APReceivedItem {
  u16 itemId;
  u8 filled;
};

#define RECEIVED_AP_ITEM_ADDR (CHECKED_LOCATIONS_ADDR + sizeof_round(struct Checks *))
#define apReceivedItem ((struct APReceivedItem *)(RECEIVED_AP_ITEM_ADDR))

void markChapterCleared(int chapterNum);
void markHolyWeaponGet(enum HolyWeapon weap);

#endif // ARCHIPELAGO_H
