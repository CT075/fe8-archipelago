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

u8 Event37_GiveItem(struct EventEngineProc *proc) {
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
        handleHolyWeaponGet(proc, hw);
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
  }

  return 2;
}
