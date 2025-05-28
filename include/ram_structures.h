// THIS FILE IS GENERATED
//
// To change this file, see `bin/ram_alloc.py` and `data/ram_structures.csv`.

#ifndef RAM_STRUCTURES_H
#define RAM_STRUCTURES_H

#include "global.h"

#include "constants.h"
#include "archipelago.h"
#include "progressiveCaps.h"
#include "hpbars.h"

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
#define INFO_ICON_CACHE_ADDR (NEW_CONVOY_ARRAY_ADDR + sizeof_round(u16[200]))
#define infoIconCache ((struct InfoCache *)(INFO_ICON_CACHE_ADDR))
#define DEATH_LINK_INFO_ADDR (INFO_ICON_CACHE_ADDR + sizeof_round(struct InfoCache))
#define deathLinkInfo ((struct DeathLinkState *)(DEATH_LINK_INFO_ADDR))

#endif // RAM_STRUCTURES_H

