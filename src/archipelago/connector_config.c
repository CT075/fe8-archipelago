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
      return 24;
    case Siegmund:
      return 25;
    case Gleipnir:
      return 26;
    case Garm:
      return 27;
    case Nidhogg:
      return 28;
    case Vidofnir:
      return 29;
    case Excalibur:
      return 30;
    case Audhulma:
      return 31;
    case Ivaldi:
      return 32;
    case Latona:
      return 33;
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
      dst->payload.weaponType = Anima;
      break;
    case 6:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Light;
      break;
    case 7:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Dark;
      break;
    case 8:
      dst->kind = ProgWLv;
      dst->payload.weaponType = Staff;
      break;
    case 9:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Sieglinde;
      break;
    case 10:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Siegmund;
      break;
    case 11:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Gleipnir;
      break;
    case 12:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Garm;
      break;
    case 13:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Nidhogg;
      break;
    case 14:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Vidofnir;
      break;
    case 15:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Excalibur;
      break;
    case 16:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Audhulma;
      break;
    case 17:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Ivaldi;
      break;
    case 18:
      dst->kind = HolyWeapon;
      dst->payload.holyWeapon = Latona;
      break;
  };
}
