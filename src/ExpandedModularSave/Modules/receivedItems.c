#include "global.h"

#include "agb_sram.h"

#include "progressiveCaps.h"
#include "archipelago.h"
#include "ram_structures.h"

void saveReceivedItemIndex(void *target, unsigned size) {
  WriteAndVerifySramFast((void *)receivedItemIndex, target, size);
}

void loadReceivedItemIndex(void *source, unsigned size) {
  ReadSramFast(source, (void *)receivedItemIndex, size);
}
