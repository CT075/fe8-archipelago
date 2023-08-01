#ifndef RANDO_BASE_H
#define RANDO_BASE_H

#include "global.h"

struct ProgressiveCaps {
  int lvlCapStage;
  int swordLvlStage;
  int lanceLvlStage;
  int axeLvlStage;
  int bowLvlStage;
  int animaLvlStage;
  int lightLvlStage;
  int darkLvlStage;
  int staffLvlStage;
};

#define progCaps ((struct ProgressiveCaps *)0x0203EFC0)

#define BLUE_UNIT_MAX 62
#define TRUE_LEVEL_CAP 20

#endif // RANDO_BASE_H
