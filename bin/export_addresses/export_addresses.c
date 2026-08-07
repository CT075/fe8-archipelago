#include <stdio.h>
#include <string.h>

#include "archipelago.h"
#include "progressiveCaps.h"
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
    printf(
        "%08X deathLinkIn\n",
        DEATH_LINK_INFO_ADDR + offsetof(struct DeathLinkState, pendingIn)
    );
    printf(
        "%08X deathLinkOut\n",
        DEATH_LINK_INFO_ADDR + offsetof(struct DeathLinkState, pendingOut)
    );
    printf(
        "%08X deathLinkReady\n",
        DEATH_LINK_INFO_ADDR + offsetof(struct DeathLinkState, ready)
    );
    // Fake symbols are a hack to reuse [populate_with_symbols] infrastructure
    // to export the necessary [offsetof]/[sizeof] data.
    //
    // arm-none-eabi-gcc and modern gcc handle enum sizes differently, so this
    // is only safe for structs whose fields have a fixed size on both
    // compilers (e.g. [__packed__] enums), which [ArchipelagoOptions] does.
    printf(
        "%08X fake_superDemonKingOffs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, superDemonKing)
    );
    printf(
        "%08X fake_lockpickUsabilityOffs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, lockpickUsability)
    );
    printf(
        "%08X fake_deathLinkKindOffs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, deathLinkKind)
    );
    printf(
        "%08X fake_enableLevelCapsOffs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, enableLevelCaps)
    );
    printf(
        "%08X fake_enableWeaponLevelCapsOffs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, enableWeaponLevelCaps)
    );
    printf(
        "%08X fake_promotionUnlocksOffs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, promotionUnlocks)
    );
    printf(
        "%08X fake_recruitChecksEnabledOffs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, recruitChecksEnabled)
    );
    printf(
        "%08X fake_free\"Seth\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeSeth)
    );
    printf(
        "%08X fake_free\"Franz\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeFranz)
    );
    printf(
        "%08X fake_free\"Gilliam\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeGilliam)
    );
    printf(
        "%08X fake_free\"Vanessa\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeVanessa)
    );
    printf(
        "%08X fake_free\"Moulder\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeMoulder)
    );
    printf(
        "%08X fake_free\"Ross\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeRoss)
    );
    printf(
        "%08X fake_free\"Garcia\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeGarcia)
    );
    printf(
        "%08X fake_free\"Neimi\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeNeimi)
    );
    printf(
        "%08X fake_free\"Colm\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeColm)
    );
    printf(
        "%08X fake_free\"Artur\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeArtur)
    );
    printf(
        "%08X fake_free\"Lute\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeLute)
    );
    printf(
        "%08X fake_free\"Natasha\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeNatasha)
    );
    printf(
        "%08X fake_free\"Joshua\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeJoshua)
    );
    printf(
        "%08X fake_free\"Forde\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeForde)
    );
    printf(
        "%08X fake_free\"Kyle\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeKyle)
    );
    printf(
        "%08X fake_free\"Tana\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeTana)
    );
    printf(
        "%08X fake_free\"Amelia\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeAmelia)
    );
    printf(
        "%08X fake_free\"Innes\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeInnes)
    );
    printf(
        "%08X fake_free\"Gerik\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeGerik)
    );
    printf(
        "%08X fake_free\"Tethys\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeTethys)
    );
    printf(
        "%08X fake_free\"Marisa\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeMarisa)
    );
    printf(
        "%08X fake_free\"L\'Arachel\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeLArachel)
    );
    printf(
        "%08X fake_free\"Dozla\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeDozla)
    );
    printf(
        "%08X fake_free\"Saleh\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeSaleh)
    );
    printf(
        "%08X fake_free\"Ewan\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeEwan)
    );
    printf(
        "%08X fake_free\"Cormag\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeCormag)
    );
    printf(
        "%08X fake_free\"Rennac\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeRennac)
    );
    printf(
        "%08X fake_free\"Duessel\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeDuessel)
    );
    printf(
        "%08X fake_free\"Knoll\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeKnoll)
    );
    printf(
        "%08X fake_free\"Myrrh\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeMyrrh)
    );
    printf(
        "%08X fake_free\"Syrene\"Offs\n",
        (unsigned)offsetof(struct ArchipelagoOptions, freeSyrene)
    );
    // printf("%08X fake_locItemSize\n", sizeof_round(struct LocationItem));
  }
  else {
    printf("usage: ./export_addresses [Event/Sym]");
    return 1;
  }

  return 0;
}
