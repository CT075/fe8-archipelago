// THIS FILE IS GENERATED, DO NOT EDIT DIRECTLY
// 
// To change this file, see `bin/connector_config/Generate.hs` at
// https://github.com/CT075/fe8-archipelago

#ifndef CONNECTOR_CONFIG_H
#define CONNECTOR_CONFIG_H

#include "global.h"

enum HolyWeapon {
  Sieglinde=0,
  Siegmund=1,
  Gleipnir=2,
  Garm=3,
  Nidhogg=4,
  Vidofnir=5,
  Excalibur=6,
  Audhulma=7,
  Ivaldi=8,
  Latona=9,
};

struct Checks {
  u8 found[8];
};

int chapterClearFlagIndex(int chapter);
int holyWeaponFlagIndex(enum HolyWeapon weapon);

#define Ch1Id (1)
#define Ch2Id (2)
#define Ch3Id (3)
#define Ch4Id (4)
#define Ch5Id (5)
#define Ch6Id (7)
#define Ch7Id (8)
#define Ch8Id (9)
#define Ch9Id (10)
#define Ch10Id (11)
#define Ch11Id (12)
#define Ch12Id (13)
#define Ch13Id (14)
#define Ch14Id (15)
#define Ch15Id (16)
#define Ch16Id (17)
#define Ch17Id (18)
#define Ch18Id (19)
#define Ch19Id (20)
#define Ch20Id (21)
#define Ch5xId (6)
#define PrologueId (0)
#define EndgameId (22)

const u16 *receivedItemEvent(u8 itemId);

#endif // CONNECTOR_CONFIG_H
