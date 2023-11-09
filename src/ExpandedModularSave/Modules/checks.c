#include "global.h"

#include "agb_sram.h"

#include "progressiveCaps.h"
#include "archipelago.h"
#include "ram_structures.h"

void saveChecks(void *target, unsigned size) {
  WriteAndVerifySramFast((void *)checkedLocations, target, size);
}

void loadChecks(void *source, unsigned size) {
  ReadSramFast(source, (void *)checkedLocations, size);
}
