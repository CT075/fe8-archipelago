#include "global.h"

#include "agb_sram.h"

#include "ram_structures.h"

void saveConvoy(void *target, unsigned size) {
  WriteAndVerifySramFast((void *)newConvoyArray, target, size);
}

void loadConvoy(void *source, unsigned size) {
  ReadSramFast(source, (void *)newConvoyArray, size);
}
