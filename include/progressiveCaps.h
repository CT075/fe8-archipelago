#ifndef PROGRESSIVE_CAPS_H
#define PROGRESSIVE_CAPS_H

#include "archipelago.h"
#include "constants.h"
#include "global.h"

struct ProgressiveCaps {
  u8 lvlCapStage;
  u8 swordLvlCapStage;
  u8 lanceLvlCapStage;
  u8 axeLvlCapStage;
  u8 bowLvlCapStage;
  u8 animaLvlCapStage;
  u8 lightLvlCapStage;
  u8 darkLvlCapStage;
  u8 staffLvlCapStage;
};

#define TRUE_LEVEL_CAP 20

int GetLevelCap();
void bumpLevelCap();
void bumpWeaponLevelCap(enum WeaponType wtype);

#endif // PROGRESSIVE_CAPS_H
