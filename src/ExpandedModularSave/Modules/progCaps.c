#include "global.h"

#include "bmsave.h"
#include "bmunit.h"

#include "base.h"

void saveProgCaps(void *target, unsigned size) {
  WriteAndVerifySramFast((void *)progCaps, target, size);
}

void loadProgCaps(void *source, unsigned size) {
  ReadSramFast(source, (void *)progCaps, size);
}
