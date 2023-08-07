// THIS FILE IS GENERATED, DO NOT EDIT DIRECTLY
// 
// To change this file, see `bin/connector_config/Generate.hs` at
// https://github.com/CT075/fe8-archipelago

#include "connector_config.h"

int chapterClearFlagIndex(int chapter) {
  return 0+chapter;
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
  }
}
