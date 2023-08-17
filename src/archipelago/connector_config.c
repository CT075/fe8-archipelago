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
      return 23;
    case Siegmund:
      return 24;
    case Gleipnir:
      return 25;
    case Garm:
      return 26;
    case Nidhogg:
      return 27;
    case Vidofnir:
      return 28;
    case Excalibur:
      return 29;
    case Audhulma:
      return 30;
    case Ivaldi:
      return 31;
    case Latona:
      return 32;
    default:
      return -1;
  }
}

void itemIdToEvent(u16 id, struct IncomingEvent *dst) {
  switch (id) {
    case 0:
      dst->kind = ProgLvlCap;
    case 1:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Sword;
    case 2:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Lance;
    case 3:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Axe;
    case 4:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Bow;
    case 5:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Anima;
    case 6:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Light;
    case 7:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Dark;
    case 8:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Staff;
    case 9:
      dst->kind = HolyWeapon;
      dst->payload.weaponType = Sieglinde;
    case 10:
      dst->kind = HolyWeapon;
      dst->payload.weaponType = Siegmund;
    case 11:
      dst->kind = HolyWeapon;
      dst->payload.weaponType = Gleipnir;
    case 12:
      dst->kind = HolyWeapon;
      dst->payload.weaponType = Garm;
    case 13:
      dst->kind = HolyWeapon;
      dst->payload.weaponType = Nidhogg;
    case 14:
      dst->kind = HolyWeapon;
      dst->payload.weaponType = Vidofnir;
    case 15:
      dst->kind = HolyWeapon;
      dst->payload.weaponType = Excalibur;
    case 16:
      dst->kind = HolyWeapon;
      dst->payload.weaponType = Audhulma;
    case 17:
      dst->kind = HolyWeapon;
      dst->payload.weaponType = Ivaldi;
    case 18:
      dst->kind = HolyWeapon;
      dst->payload.weaponType = Latona;
  };
}
