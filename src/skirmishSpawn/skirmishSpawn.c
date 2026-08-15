// Replaces the vanilla world map skirmish placement roll so that skirmishes
// prefer sites whose Archipelago check hasn't been collected yet.
//
// lyn rewrites `GenerateRandomonsterMergeNode` in place because the name
// matches a vanilla symbol; see `src/giveItemHook` for the same trick.

#include "global.h"

#include "rng.h"

#include "archipelago.h"
#include "connector_config.h"
#include "ram_structures.h"

// Length of `gWMMonsterSpawnLocations`.
#define NUM_SPAWN_NODES 9

// Location flag for each entry of `gWMMonsterSpawnLocations`, in that order.
static const u8 kSpawnNodeLocation[NUM_SPAWN_NODES] = {
  SkirmishZahaWoodsId,    SkirmishAdlasPlainsId, SkirmishTerasPlateauId,
  SkirmishHamillCanyonId, SkirmishBethroenId,    SkirmishZaalbulMarshId,
  SkirmishNarubeRiverId,  SkirmishNelerasPeakId, SkirmishMelkaenCoastId,
};

// Vanilla behaviour: weighted random index, or -1 if every weight is zero.
static int pickWeighted(const u8 *weights, int count) {
  int total = 0;

  for (int i = 0; i < count; i++) {
    total += weights[i];
  }

  if (total == 0) {
    return -1;
  }

  int roll = NextRN_N(total);
  int acc = 0;

  for (int i = 0; i < count; i++) {
    acc += weights[i];
    if (roll < acc) {
      return i;
    }
  }

  return count - 1;
}

int GenerateRandomonsterMergeNode(const u8 *weights, int count) {
  if (count == NUM_SPAWN_NODES) {
    u8 uncollected[NUM_SPAWN_NODES];
    int any = 0;

    for (int i = 0; i < NUM_SPAWN_NODES; i++) {
      int loc = kSpawnNodeLocation[i];
      int enabled = locItems[loc].kind != Empty;
      int collected = checkedLocations->found[loc / 8] & (1 << (loc % 8));

      // Zeroing rather than flattening keeps the vanilla weighting, so a site
      // that can't spawn this chapter still can't.
      uncollected[i] = (enabled && !collected) ? weights[i] : 0;
      any |= uncollected[i];
    }

    if (any) {
      return pickWeighted(uncollected, NUM_SPAWN_NODES);
    }
  }

  // Nothing left to check here, so fall back to the vanilla spread.
  return pickWeighted(weights, count);
}
