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

// Dummy game-save chunk loader (see gGameSaveChunks). Any game-save load
// (including "Restart Chapter" after a suspend) re-enters the chapter from the
// start, so the next PrepScreenReset must run a full deploy reset even if this
// chapter already reset earlier in the same play session. Deliberately not in
// gSuspendSaveChunks: resuming a suspend mid-prep must keep the player's
// chosen deployment.
void clearLastResetChapter(void *source, unsigned size) { *lastResetChapter = 0; }
