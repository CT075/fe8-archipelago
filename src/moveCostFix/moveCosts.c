#include "global.h"

#include "bmunit.h"
#include "bmmap.h"
#include "bmidoten.h"
#include "variables.h"

#include "constants/terrains.h"

#define MOV_SENTINEL 31

// Code adapted from circleseverywhere

int getTerrain(int x, int y) {
  if (x >= gBmMapSize.x || y >= gBmMapSize.y || x < 0 || y < 0) {
    return 255;
  }

  return gBmMapTerrain[y][x];
};

// Returns 0 or unit's max mov
int checkUnitStuck(struct Unit *unit, const s8 costs[]) {
  int x = unit->xPos;
  int y = unit->yPos;

  // If any adjacent tile is passable, we're not stuck.

  if (costs[getTerrain(x+1, y)] < MOV_SENTINEL) {
    return 0;
  }

  if (costs[getTerrain(x-1, y)] < MOV_SENTINEL) {
    return 0;
  }

  if (costs[getTerrain(x, y+1)] < MOV_SENTINEL) {
    return 0;
  }

  if (costs[getTerrain(x, y-1)] < MOV_SENTINEL) {
    return 0;
  }

  return UNIT_MOV(unit);
}

void SetWorkingMoveCosts(const s8 costs[TERRAIN_COUNT]) {
  struct Unit *unit = gActiveUnit;

  int stuck = checkUnitStuck(unit, costs);

  for (int i = 0; i < TERRAIN_COUNT; i += 1) {
    u8 cost = costs[i];

    if (stuck && cost == 31) {
      cost = stuck;
    }

    gWorkingTerrainMoveCosts[i] = cost;
  }
}
