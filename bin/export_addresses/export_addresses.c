#include <stdio.h>
#include <string.h>

#include "progressiveCaps.h"
#include "archipelago.h"
#include "ram_structures.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("usage: ./export_addresses [Event/Sym]");
    return 1;
  }

  // CR-someday cam: Right now, we manually decide which symbols to export, but
  // we could in theory figure it out from `ram_structures.csv`. However, that
  // would mean doing CSV/string processing in C, which is not really worth the
  // effort.
  if (strcmp(argv[1], "Event") == 0) {
    printf("#ifndef ARCHIPELAGO_DEFS_EVENT\n");
    printf("#define ARCHIPELAGO_DEFS_EVENT\n");
    printf("#define PROGRESSIVE_CAPS_SIZE (%d)\n", sizeof(struct ProgressiveCaps));
    printf("#define PROGRESSIVE_CAPS_ADDR (0x%x)\n", PROGRESSIVE_CAPS_ADDR);
    printf("#define CHECKED_LOCATION_SIZE (%d)\n", sizeof(struct Checks));
    printf("#define CHECKED_LOCATION_ADDR (0x%x)\n", CHECKED_LOCATIONS_ADDR);
    printf("#define AP_RECEIVED_ITEM_SIZE (%d)\n", sizeof(struct APReceivedItem));
    printf("#define AP_RECEIVED_ITEM_ADDR (0x%x)\n", RECEIVED_AP_ITEM_ADDR);
    printf("#define RECEIVED_ITEM_IX_ADDR (0x%x)\n", RECEIVED_ITEM_INDEX_ADDR);
    printf("#define NEW_CONVOY_ARRAY_ADDR (0x%x)\n", NEW_CONVOY_ARRAY_ADDR);
    printf("#endif\n");
  }
  else if (strcmp(argv[1], "Sym") == 0) {
    printf("%08X receivedAPItem\n", RECEIVED_AP_ITEM_ADDR);
    printf("%08X receivedItemIndex\n", RECEIVED_ITEM_INDEX_ADDR);
    printf("%08X checkedLocations\n", CHECKED_LOCATIONS_ADDR);
    // Fake symbols are a hack to reuse [populate_with_symbols] infrastructure
    // to export the necessary [sizeof] data.
    //
    // arm-none-eabi-gcc and modern gcc handle enum sizes differently, so this
    // doesn't work properly anyway.
    //printf("%08X fake_locItemSize\n", sizeof_round(struct LocationItem));
  }
  else {
    printf("usage: ./export_addresses [Event/Sym]");
    return 1;
  }

  return 0;
}
