#include <stdio.h>

#include "progressiveCaps.h"
#include "archipelago.h"

// generate a .event file containing relevant C definitions
int main() {
  printf("#define PROGRESSIVE_CAPS_SIZE (%d)\n", sizeof(struct ProgressiveCaps));
  printf("#define PROGRESSIVE_CAPS_ADDR (0x%x)\n", PROG_CAPS_ADDR);
  printf("#define CHECKED_LOCATION_SIZE (%d)\n", sizeof(struct Checks));
  printf("#define CHECKED_LOCATION_ADDR (0x%x)\n", CHECKED_LOCATIONS_ADDR);
  return 0;
}
