#include "global.h"

#include "agb_sram.h"

#include "ram_structures.h"

void saveSethDeployStage(void *target, unsigned size) {
  WriteAndVerifySramFast((void *)sethDeployStage, target, size);
}

void loadSethDeployStage(void *source, unsigned size) {
  ReadSramFast(source, (void *)sethDeployStage, size);
}
