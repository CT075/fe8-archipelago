#include "global.h"

#include "agb_sram.h"

#include "archipelago.h"
#include "progressiveCaps.h"
#include "ram_structures.h"

void saveProgCaps(void *target, unsigned size) {
  WriteAndVerifySramFast((void *)progressiveCaps, target, size);
}

void loadProgCaps(void *source, unsigned size) {
  ReadSramFast(source, (void *)progressiveCaps, size);
}
