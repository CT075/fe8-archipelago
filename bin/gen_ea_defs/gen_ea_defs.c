#include <stdio.h>

#include "progressiveCaps.h"
#include "archipelago.h"
#include "ram_structures.h"

// CR cam: Instead of generating this, we should instead generate the EMS adds
// directly.
//
// generate a .event file containing relevant C definitions
int main() {
  printf("#define PROGRESSIVE_CAPS_SIZE (%d)\n", sizeof(struct ProgressiveCaps));
  printf("#define PROGRESSIVE_CAPS_ADDR (0x%x)\n", PROGRESSIVE_CAPS_ADDR);
  printf("#define CHECKED_LOCATION_SIZE (%d)\n", sizeof(struct Checks));
  printf("#define CHECKED_LOCATION_ADDR (0x%x)\n", CHECKED_LOCATIONS_ADDR);
  printf("#define AP_RECEIVED_ITEM_SIZE (%d)\n", sizeof(struct APReceivedItem));
  printf("#define AP_RECEIVED_ITEM_ADDR (0x%x)\n", RECEIVED_AP_ITEM_ADDR);
  printf("#define RECEIVED_ITEM_IX_ADDR (0x%x)\n", RECEIVED_ITEM_INDEX_ADDR);
  return 0;
}
