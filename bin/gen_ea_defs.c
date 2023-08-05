#include <stdio.h>

#include "base.h"

// generate a .event file containing relevant C definitions
int main() {
  printf("#define PROGRESSIVE_CAPS_SIZE (%d)\n", sizeof(struct ProgressiveCaps));
  printf("#define PROGRESSIVE_CAPS_ADDR (0x%x)\n", PROG_CAPS_ADDR);
  return 0;
}
