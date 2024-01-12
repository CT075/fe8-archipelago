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
#define Endgame1Id (22)
#define Endgame2Id (23)
#define Tower1Id (24)
#define Tower2Id (25)
#define Tower3Id (26)
#define Tower4Id (27)
#define Tower5Id (28)
#define Tower6Id (29)
#define Tower7Id (30)
#define Tower8Id (31)
#define Ruins1Id (32)
#define Ruins2Id (33)
#define Ruins3Id (34)
#define Ruins4Id (35)
#define Ruins5Id (36)
#define Ruins6Id (37)
#define Ruins7Id (38)
#define Ruins8Id (39)
#define Ruins9Id (40)
#define Ruins10Id (41)

enum WeaponType {
  Sword=0,
  Lance=1,
  Axe=2,
  Bow=3,
  Staff=4,
  Anima=5,
  Light=6,
  Dark=7,
};

enum FillerItem {
  AngelicRobe=0,
  EnergyRing=1,
  SecretBook=2,
  Speedwings=3,
  GoddessIcon=4,
  DragonShield=5,
  Talisman=6,
  BodyRing=7,
  Boots=8,
  KnightCrest=9,
  HeroCrest=10,
  OrionsBolt=11,
  GuidingRing=12,
  ElysianWhip=13,
  OceanSeal=14,
  MasterSeal=15,
};

#define NUM_CHECKS (52)

enum ItemKind {
  ProgLvlCap=0,
  ProgWLv=1,
  HolyWeapon=2,
  FillerItem=3,
};

union Payload {
  // progressive levelcap has no payload
  enum WeaponType weaponType;
  enum HolyWeapon holyWeapon;
  enum FillerItem fillerItem;
};

struct IncomingEvent {
  enum ItemKind kind;
  union Payload payload;
};

void unpackAPEventFromId(u16 id, struct IncomingEvent *dst);

#endif // CONNECTOR_CONFIG_H
