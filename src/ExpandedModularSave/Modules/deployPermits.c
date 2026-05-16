#include "global.h"

#include "agb_sram.h"

#include "deployPermits.h"
#include "ram_structures.h"

void saveDeployPermits(void *target, unsigned size) {
  WriteAndVerifySramFast((void *)deployPermits, target, size);
}

void loadDeployPermits(void *source, unsigned size) {
  ReadSramFast(source, (void *)deployPermits, size);
}
