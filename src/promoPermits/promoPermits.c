#include "promoPermits.h"
#include "archipelago.h"
#include "bmarch.h"
#include "bmitem.h"
#include "bmsave.h"
#include "bmunit.h"
#include "classchg.h"
#include "connector_config.h"
#include "constants/characters.h"
#include "constants/classes.h"
#include "constants/items.h"
#include "fontgrp.h"
#include "functions.h"
#include "global.h"
#include "hardware.h"
#include "m4a.h"
#include "proc.h"
#include "ram_structures.h"
#include "uimenu.h"
#include "variables.h"

// Maps a class ID to its promotion permit bit. Both gender variants share a
// bit. Returns -1 for classes that are never gated (unpromoted classes,
// Great Lord, trainee (2) classes, monsters); promotion into those is always
// allowed.
int classIdToPromotedClass(u8 classId) {
  switch (classId) {
  case CLASS_PALADIN:
  case CLASS_PALADIN_F:
    return Paladin;
  case CLASS_GENERAL:
  case CLASS_GENERAL_F:
    return General;
  case CLASS_HERO:
  case CLASS_HERO_F:
    return Hero;
  case CLASS_SWORDMASTER:
  case CLASS_SWORDMASTER_F:
    return Swordmaster;
  case CLASS_ASSASSIN:
  case CLASS_ASSASSIN_F:
    return Assassin;
  case CLASS_SNIPER:
  case CLASS_SNIPER_F:
    return Sniper;
  case CLASS_RANGER:
  case CLASS_RANGER_F:
    return Ranger;
  case CLASS_WYVERN_LORD:
  case CLASS_WYVERN_LORD_F:
    return WyvernLord;
  case CLASS_WYVERN_KNIGHT:
  case CLASS_WYVERN_KNIGHT_F:
    return WyvernKnight;
  case CLASS_SAGE:
  case CLASS_SAGE_F:
    return Sage;
  case CLASS_MAGE_KNIGHT:
  case CLASS_MAGE_KNIGHT_F:
    return MageKnight;
  case CLASS_BISHOP:
  case CLASS_BISHOP_F:
    return Bishop;
  case CLASS_DRUID:
  case CLASS_DRUID_F:
    return Druid;
  case CLASS_SUMMONER:
  case CLASS_SUMMONER_F:
    return Summoner;
  case CLASS_ROGUE:
    return Rogue;
  case CLASS_GREAT_KNIGHT:
  case CLASS_GREAT_KNIGHT_F:
    return GreatKnight;
  case CLASS_WARRIOR:
    return Warrior;
  case CLASS_BERSERKER:
    return Berserker;
  case CLASS_FALCON_KNIGHT:
    return FalconKnight;
  case CLASS_VALKYRIE:
    return Valkyrie;
  // Tier-3 "super trainee" classes. Despite the decomp names, _T2 is the
  // third tier: Journeyman(1)=0x3D, Journeyman(2)=_T1=0x7E, Journeyman(3)=
  // _T2=0x38 (likewise for Pupil and Recruit).
  case CLASS_JOURNEYMAN_T2:
    return Journeyman;
  case CLASS_PUPIL_T2:
    return Pupil;
  case CLASS_RECRUIT_T2:
    return Recruit;
  default:
    return -1;
  }
}

void setPromoPermit(enum PromotedClass cls) { *promoPermits |= (1u << (int)cls); }

bool canPromoteToClassId(u8 classId) {
  int cls;
  if (!archipelagoOptions.promotionUnlocks)
    return true;
  cls = classIdToPromotedClass(classId);
  if (cls < 0)
    return true;
  return (*promoPermits >> cls) & 1;
}

static bool hasPermittedPromotionTarget(struct Unit *unit) {
  const u8 *targets = gPromoJidLut[unit->pClassData->number];
  int i;
  for (i = 0; i < 2; i++) {
    if (targets[i] && canPromoteToClassId(targets[i]))
      return true;
  }
  return false;
}

// Usability for the first two entries of gMenuItem_PromoSel (vanilla:
// MenuAlwaysEnabled); the pointers are repointed here in main.event. Grays
// out promotion choices whose permit has not been received.
u8 PromoSelMenuItemUsability(const struct MenuItemDef *def, int number) {
  struct ProcClassChgMenuSel *proc;
  struct ProcPromoSel *parent;
  struct ProcPromoMain *gparent;
  struct Unit *unit;
  u8 jid;

  if (!archipelagoOptions.promotionUnlocks)
    return MENU_ENABLED;

  proc = Proc_Find(ProcScr_ClassChgMenuSel);
  parent = proc->proc_parent;
  gparent = parent->proc_parent;
  unit = GetUnitFromCharId(gparent->pid);
  jid = gPromoJidLut[unit->pClassData->number][number];
  return canPromoteToClassId(jid) ? MENU_ENABLED : MENU_DISABLED;
}

// Replaces the vanilla promotion-select handler. The menu engine never
// blocks selecting MENU_DISABLED entries (it only draws them gray), and the
// vanilla handler assumes everything is selectable, so locked classes could
// still be promoted into. Re-check availability, then replicate the vanilla
// logic (decomp src/classchg-menuselect.c).
u8 ClassChgMenuItem_OnSelect(struct MenuProc *pmenu, struct MenuItemProc *pmitem) {
  struct ProcClassChgMenuSel *parent;
  struct ProcPromoSel *gparent;
  struct ProcPromoMain *ggparent;

  if (pmitem->availability != MENU_ENABLED) {
    m4aSongNumStart(0x6c);
    return 0;
  }

  parent = pmenu->proc_parent;
  gparent = parent->proc_parent;
  ggparent = gparent->proc_parent;
  if (gparent->stat == 0) {
    struct Unit *unit = GetUnitFromCharId(ggparent->pid);
    u8 classnumber = unit->pClassData->number;
    if (pmitem->itemNumber <= 1) {
      classnumber = gPromoJidLut[classnumber][pmitem->itemNumber];
      ggparent->jid = classnumber;
    }
    else if (pmitem->itemNumber == 2) {
      switch (classnumber) {
      case CLASS_JOURNEYMAN:
        ggparent->jid = CLASS_JOURNEYMAN_T1;
        break;
      case CLASS_PUPIL:
        ggparent->jid = CLASS_PUPIL_T1;
        break;
      case CLASS_RECRUIT:
        ggparent->jid = CLASS_RECRUIT_T1;
        break;
      default:
        ggparent->jid = classnumber;
        break;
      }
    }

    switch ((u8)ggparent->jid) {
    case CLASS_RANGER:
    case CLASS_RANGER_F:
      if (unit->state & US_IN_BALLISTA) {
        TryRemoveUnitFromBallista(unit);
      }
      break;
    }

    InitTextFont(&gFontClassChgMenu, (void *)BG_VRAM + 0x1000, 0x80, 0x5);
    TileMap_FillRect(TILEMAP_LOCATED(gBG0TilemapBuffer, 9, 4), 0xA, 0x6, 0);
    BG_EnableSyncByMask(BG0_SYNC_BIT);
    StartMenuExt(&Menu_PromoSubConfirm, 2, 0, 0, 0, pmenu);
  }

  return 0;
}

// Replaces the vanilla check (which requires having beaten both routes) so
// the super-trainee path is available from the start.
bool Check3rdTraineeEnabled(void) {
  return true;
}

// Replaces the vanilla usability check for promotion items (Hero Crest,
// Master Seal, ...). Replicates the vanilla logic, but a class-list match
// only counts if at least one of the unit's promotion targets is permitted.
s8 CanUnitUsePromotionItem(struct Unit *unit, int item) {
  const u8 *classList = NULL;
  const u8 *it;

  if (unit->pCharacterData->number == CHARACTER_EIRIKA ||
      unit->pCharacterData->number == CHARACTER_EPHRAIM) {
    switch (GetItemIndex(item)) {
    case ITEM_LUNARBRACE:
      classList = gItemUseJidList_LunarBrace;
      break;
    case ITEM_SOLARBRACE:
      classList = gItemUseJidList_SolarBrace;
      break;
    }

    if (classList) {
      for (it = classList; *it; it++) {
        if (unit->pClassData->number == *it)
          return hasPermittedPromotionTarget(unit);
      }
    }
  }

  if (unit->level < 10)
    return FALSE;

  switch (GetItemIndex(item)) {
  case ITEM_HEROCREST:
    classList = gItemUseJidList_HeroCrest;
    break;
  case ITEM_KNIGHTCREST:
    classList = gItemUseJidList_KnightCrest;
    break;
  case ITEM_ORIONSBOLT:
    classList = gItemUseJidList_OrionsBolt;
    break;
  case ITEM_ELYSIANWHIP:
    classList = gItemUseJidList_ElysianWhip;
    break;
  case ITEM_GUIDINGRING:
    classList = gItemUseJidList_GuidRing;
    break;
  case ITEM_MASTERSEAL:
    classList = gItemUseJidList_MasterSeal;
    break;
  case ITEM_LUNARBRACE:
    classList = gItemUseJidList_LunarBrace;
    break;
  case ITEM_SOLARBRACE:
    classList = gItemUseJidList_SolarBrace;
    break;
  case ITEM_HEAVENSEAL:
    classList = gItemUseJidList_HeavenSeal;
    break;
  case ITEM_UNK_C1:
    classList = gItemUseJidList_C1;
    break;
  case ITEM_OCEANSEAL:
    classList = gItemUseJidList_OceanSeal;
    break;
  }

  if (classList) {
    for (it = classList; *it; it++) {
      if (unit->pClassData->number == *it)
        return hasPermittedPromotionTarget(unit);
    }
  }

  return FALSE;
}
