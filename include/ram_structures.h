// THIS FILE IS GENERATED
//
// To change this file, see `bin/ram_alloc.py` and `data/ram_structures.csv`.

#ifndef RAM_STRUCTURES_H
#define RAM_STRUCTURES_H

#include "global.h"

#include "constants.h"
#include "archipelago.h"
#include "progressiveCaps.h"

#define sizeof_round(ty) ((sizeof(ty) + sizeof(int)-1) & ~(sizeof(int)-1))

#define CHECKED_LOCATIONS_ADDR (FREE_RAM_START + 0)
#define checkedLocations ((struct Checks *)(CHECKED_LOCATIONS_ADDR))
#define RECEIVED_AP_ITEM_ADDR (CHECKED_LOCATIONS_ADDR + sizeof_round(struct Checks))
#define receivedAPItem ((struct APReceivedItem *)(RECEIVED_AP_ITEM_ADDR))
#define RECEIVED_ITEM_INDEX_ADDR (RECEIVED_AP_ITEM_ADDR + sizeof_round(struct APReceivedItem))
#define receivedItemIndex ((u32 *)(RECEIVED_ITEM_INDEX_ADDR))
#define PROGRESSIVE_CAPS_ADDR (RECEIVED_ITEM_INDEX_ADDR + sizeof_round(u32))
#define progressiveCaps ((struct ProgressiveCaps *)(PROGRESSIVE_CAPS_ADDR))
#define NEW_CONVOY_ARRAY_ADDR (PROGRESSIVE_CAPS_ADDR + sizeof_round(struct ProgressiveCaps))
#define newConvoyArray ((u16 *)(NEW_CONVOY_ARRAY_ADDR))

#endif // RAM_STRUCTURES_H

