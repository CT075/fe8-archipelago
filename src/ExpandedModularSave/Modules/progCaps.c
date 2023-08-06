#include "global.h"

#include "agb_sram.h"

#include "progressiveCaps.h"

void saveProgCaps(void *target, unsigned size) {
  WriteAndVerifySramFast((void *)progCaps, target, size);
}

void loadProgCaps(void *source, unsigned size) {
  ReadSramFast(source, (void *)progCaps, size);
}
