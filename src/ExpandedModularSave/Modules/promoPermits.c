#include "global.h"

#include "agb_sram.h"

#include "promoPermits.h"
#include "ram_structures.h"

void savePromoPermits(void *target, unsigned size) {
  WriteAndVerifySramFast((void *)promoPermits, target, size);
}

void loadPromoPermits(void *source, unsigned size) {
  ReadSramFast(source, (void *)promoPermits, size);
}
