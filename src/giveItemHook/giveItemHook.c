#include "global.h"

#include "variables.h"
#include "functions.h"
#include "event.h"
#include "proc.h"
#include "bmunit.h"
#include "popup.h"
#include "constants/characters.h"
#include "constants/items.h"

#include "archipelago.h"

int checkHolyWeapon(u16 item, enum HolyWeapon *dst) {
  switch (item) {
    case ITEM_SWORD_SIEGLINDE:
      *dst = Sieglinde;
      return 1;
    case ITEM_LANCE_SIEGMUND:
      *dst = Siegmund;
      return 1;
    case ITEM_DARK_GLEIPNIR:
      *dst = Gleipnir;
      return 1;
    case ITEM_AXE_GARM:
      *dst = Garm;
      return 1;
    case ITEM_BOW_NIDHOGG:
      *dst = Nidhogg;
      return 1;
    case ITEM_LANCE_VIDOFNIR:
      *dst = Vidofnir;
      return 1;
    case ITEM_ANIMA_EXCALIBUR:
      *dst = Excalibur;
      return 1;
    case ITEM_SWORD_AUDHULMA:
      *dst = Audhulma;
      return 1;
    case ITEM_LIGHT_IVALDI:
      *dst = Ivaldi;
      return 1;
    case ITEM_STAFF_LATONA:
      *dst = Latona;
      return 1;
  }

  return 0;
}

u16 holyWeaponTrueValue(enum HolyWeapon hw) {
  switch (hw) {
    case Sieglinde:
      return ITEM_SWORD_SIEGLINDE;
    case Siegmund:
      return ITEM_LANCE_SIEGMUND;
    case Gleipnir:
      return ITEM_DARK_GLEIPNIR;
    case Garm:
      return ITEM_AXE_GARM;
    case Nidhogg:
      return ITEM_BOW_NIDHOGG;
    case Vidofnir:
      return ITEM_LANCE_VIDOFNIR;
    case Excalibur:
      return ITEM_ANIMA_EXCALIBUR;
    case Audhulma:
      return ITEM_SWORD_AUDHULMA;
    case Ivaldi:
      return ITEM_LIGHT_IVALDI;
    case Latona:
      return ITEM_STAFF_LATONA;
  }
  return -1;
}

void handleHolyWeaponGet(enum HolyWeapon hw) {
  markHolyWeaponGet(hw);
  // TODO: "got an archipelago item!"
}

int Event37_GiveItem(struct EventEngineProc *proc) {
  u8 subcmd = EVT_SUB_CMD(proc->pEventCurrent);

  struct Unit *target = GetUnitStructFromEventParameter(proc->pEventCurrent[1]);

  if (!target) {
    return 6;
  }

  u16 item;

  switch (subcmd) {
    case 0:
      item = gEventSlots[3];
      enum HolyWeapon hw;
      // If the GIVEITEM event gives a holy weapon, intercept it and run the
      // Archipelago routine instead.
      if (checkHolyWeapon(item, &hw)) {
        handleHolyWeaponGet(hw);
      }
      else {
        NewPopup_ItemGot(proc, target, item);
      }
      break;
    case 1:
      NewPopup_GoldGot(proc, target, gEventSlots[3]);
      break;
    case 2:
      s32 gold = GetPartyGoldAmount() - gEventSlots[3];
      if (gold < 0) {
        gold = 0;
      }
      SetPartyGoldAmount(gold);
      break;
    case 3:
      switch (gPlaySt.chapterModeIndex) {
        case CHAPTER_MODE_EIRIKA:
          target = GetUnitFromCharId(CHARACTER_EIRIKA);
          break;
        case CHAPTER_MODE_EPHRAIM:
          target = GetUnitFromCharId(CHARACTER_EPHRAIM);
          break;
      }
      item = holyWeaponTrueValue(gEventSlots[3]);
      NewPopup_ItemGot(proc, target, item);
      break;
  }

  return 2;
}
