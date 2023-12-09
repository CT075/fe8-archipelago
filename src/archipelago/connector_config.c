// THIS FILE IS GENERATED, DO NOT EDIT DIRECTLY
// 
// To change this file, see `bin/connector_config/Generate.hs` at
// https://github.com/CT075/fe8-archipelago

#include "connector_config.h"

int chapterClearFlagIndex(int chapterId) {
  return 0+chapterId;
}

int holyWeaponFlagIndex(enum HolyWeapon weapon) {
  switch (weapon) {
    case Sieglinde:
      return 42;
    case Siegmund:
      return 43;
    case Gleipnir:
      return 44;
    case Garm:
      return 45;
    case Nidhogg:
      return 46;
    case Vidofnir:
      return 47;
    case Excalibur:
      return 48;
    case Audhulma:
      return 49;
    case Ivaldi:
      return 50;
    case Latona:
      return 51;
    default:
      return -1;
  }
}

void unpackAPEventFromId(u16 id, struct IncomingEvent *dst) {
  switch (id) {
    case 0:
      dst->kind = ProgLvlCap;
      break;
    case 1:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Sword;
      break;
    case 2:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Lance;
      break;
    case 3:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Axe;
      break;
    case 4:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Bow;
      break;
    case 5:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Staff;
      break;
    case 6:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Anima;
      break;
    case 7:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Light;
      break;
    case 8:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Dark;
      break;
    case 16:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Audhulma;
      break;
    case 16:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Audhulma;
      break;
    case 11:
      dst->kind = FillerItem;
      dst->payload.fillerItem = AngelicRobe;
      break;
    case 12:
      dst->kind = FillerItem;
      dst->payload.fillerItem = EnergyRing;
      break;
    case 13:
      dst->kind = FillerItem;
      dst->payload.fillerItem = SecretBook;
      break;
    case 14:
      dst->kind = FillerItem;
      dst->payload.fillerItem = Speedwings;
      break;
    case 15:
      dst->kind = FillerItem;
      dst->payload.fillerItem = GoddessIcon;
      break;
    case 16:
      dst->kind = FillerItem;
      dst->payload.fillerItem = DragonShield;
      break;
    case 17:
      dst->kind = FillerItem;
      dst->payload.fillerItem = Talisman;
      break;
    case 18:
      dst->kind = FillerItem;
      dst->payload.fillerItem = BodyRing;
      break;
    case 19:
      dst->kind = FillerItem;
      dst->payload.fillerItem = Boots;
      break;
    case 20:
      dst->kind = FillerItem;
      dst->payload.fillerItem = KnightCrest;
      break;
    case 21:
      dst->kind = FillerItem;
      dst->payload.fillerItem = HeroCrest;
      break;
    case 22:
      dst->kind = FillerItem;
      dst->payload.fillerItem = OrionsBolt;
      break;
    case 23:
      dst->kind = FillerItem;
      dst->payload.fillerItem = GuidingRing;
      break;
    case 24:
      dst->kind = FillerItem;
      dst->payload.fillerItem = ElysianWhip;
      break;
    case 25:
      dst->kind = FillerItem;
      dst->payload.fillerItem = OceanSeal;
      break;
    case 26:
      dst->kind = FillerItem;
      dst->payload.fillerItem = MasterSeal;
      break;
  };
}
