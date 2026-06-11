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

int recruitedUnitFlagIndex(enum RecruitedUnit unit) {
  switch (unit) {
    case Seth:
      return 52;
    case Franz:
      return 53;
    case Gilliam:
      return 54;
    case Vanessa:
      return 55;
    case Moulder:
      return 56;
    case Ross:
      return 57;
    case Garcia:
      return 58;
    case Neimi:
      return 59;
    case Colm:
      return 60;
    case Artur:
      return 61;
    case Lute:
      return 62;
    case Natasha:
      return 63;
    case Joshua:
      return 64;
    case Forde:
      return 65;
    case Kyle:
      return 66;
    case Tana:
      return 67;
    case Amelia:
      return 68;
    case Innes:
      return 69;
    case Gerik:
      return 70;
    case Tethys:
      return 71;
    case Marisa:
      return 72;
    case LArachel:
      return 73;
    case Dozla:
      return 74;
    case Saleh:
      return 75;
    case Ewan:
      return 76;
    case Cormag:
      return 77;
    case Rennac:
      return 78;
    case Duessel:
      return 79;
    case Knoll:
      return 80;
    case Myrrh:
      return 81;
    case Syrene:
      return 82;
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
    case 19:
      dst->kind = FillerItem;
      dst->payload.fillerItem = AngelicRobe;
      break;
    case 20:
      dst->kind = FillerItem;
      dst->payload.fillerItem = EnergyRing;
      break;
    case 21:
      dst->kind = FillerItem;
      dst->payload.fillerItem = SecretBook;
      break;
    case 22:
      dst->kind = FillerItem;
      dst->payload.fillerItem = Speedwings;
      break;
    case 23:
      dst->kind = FillerItem;
      dst->payload.fillerItem = GoddessIcon;
      break;
    case 24:
      dst->kind = FillerItem;
      dst->payload.fillerItem = DragonShield;
      break;
    case 25:
      dst->kind = FillerItem;
      dst->payload.fillerItem = Talisman;
      break;
    case 26:
      dst->kind = FillerItem;
      dst->payload.fillerItem = BodyRing;
      break;
    case 27:
      dst->kind = FillerItem;
      dst->payload.fillerItem = Boots;
      break;
    case 28:
      dst->kind = FillerItem;
      dst->payload.fillerItem = KnightCrest;
      break;
    case 29:
      dst->kind = FillerItem;
      dst->payload.fillerItem = HeroCrest;
      break;
    case 30:
      dst->kind = FillerItem;
      dst->payload.fillerItem = OrionsBolt;
      break;
    case 31:
      dst->kind = FillerItem;
      dst->payload.fillerItem = GuidingRing;
      break;
    case 32:
      dst->kind = FillerItem;
      dst->payload.fillerItem = ElysianWhip;
      break;
    case 33:
      dst->kind = FillerItem;
      dst->payload.fillerItem = OceanSeal;
      break;
    case 34:
      dst->kind = FillerItem;
      dst->payload.fillerItem = MasterSeal;
      break;
    case 35:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Seth;
      break;
    case 36:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Franz;
      break;
    case 37:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Gilliam;
      break;
    case 38:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Vanessa;
      break;
    case 39:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Moulder;
      break;
    case 40:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Ross;
      break;
    case 41:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Garcia;
      break;
    case 42:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Neimi;
      break;
    case 43:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Colm;
      break;
    case 44:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Artur;
      break;
    case 45:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Lute;
      break;
    case 46:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Natasha;
      break;
    case 47:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Joshua;
      break;
    case 48:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Forde;
      break;
    case 49:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Kyle;
      break;
    case 50:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Tana;
      break;
    case 51:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Amelia;
      break;
    case 52:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Innes;
      break;
    case 53:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Gerik;
      break;
    case 54:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Tethys;
      break;
    case 55:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Marisa;
      break;
    case 56:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = LArachel;
      break;
    case 57:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Dozla;
      break;
    case 58:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Saleh;
      break;
    case 59:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Ewan;
      break;
    case 60:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Cormag;
      break;
    case 61:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Rennac;
      break;
    case 62:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Duessel;
      break;
    case 63:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Knoll;
      break;
    case 64:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Myrrh;
      break;
    case 65:
      dst->kind = UnitDeploy;
      dst->payload.recruitedUnit = Syrene;
      break;
    case 66:
      dst->kind = ProgSethDeploy;
      break;
  };
}
