#ifndef RANDO_BASE_H
#define RANDO_BASE_H

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

#define PROG_CAPS_ADDR 0x02026E30

#define progCaps ((struct ProgressiveCaps *)PROG_CAPS_ADDR)

#define BLUE_UNIT_MAX 62
#define TRUE_LEVEL_CAP 20

#endif // RANDO_BASE_H
