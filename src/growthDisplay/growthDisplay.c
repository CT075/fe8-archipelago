#include "global.h"

#include "bmbattle.h"
#include "bmitem.h"
#include "bmreliance.h"
#include "bmunit.h"
#include "hardware.h"
#include "icon.h"
#include "statscreen.h"

typedef enum text_colors TextColor;

const struct SSTextDispInfo sPage0TextInfo[] = {
  /*
  { gStatScreen.text + STATSCREEN_TEXT_SKLLABEL, gUiTmScratchA + TILEMAP_INDEX(1, 3),
    TEXT_COLOR_0123, 0, &gMid_Skl },
  { gStatScreen.text + STATSCREEN_TEXT_SPDLABEL, gUiTmScratchA + TILEMAP_INDEX(1, 5),
    TEXT_COLOR_0456, 0, &gMid_Spd },
  { gStatScreen.text + STATSCREEN_TEXT_LCKLABEL, gUiTmScratchA + TILEMAP_INDEX(1, 7),
    TEXT_COLOR_0789, 0, &gMid_Lck },
  { gStatScreen.text + STATSCREEN_TEXT_DEFLABEL, gUiTmScratchA + TILEMAP_INDEX(1, 9),
    TEXT_COLOR_0ABC, 0, &gMid_Def },
  { gStatScreen.text + STATSCREEN_TEXT_RESLABEL, gUiTmScratchA + TILEMAP_INDEX(1, 11),
    TEXT_COLOR_0DEF, 0, &gMid_Res },
  */
  { gStatScreen.text + STATSCREEN_TEXT_MOVLABEL, gUiTmScratchA + TILEMAP_INDEX(9, 1),
    TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Mov },
  { gStatScreen.text + STATSCREEN_TEXT_CONLABEL, gUiTmScratchA + TILEMAP_INDEX(9, 3),
    TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Con },
  { gStatScreen.text + STATSCREEN_TEXT_AIDLABEL, gUiTmScratchA + TILEMAP_INDEX(9, 5),
    TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Aid },
  { gStatScreen.text + STATSCREEN_TEXT_RESCUENAME, gUiTmScratchA + TILEMAP_INDEX(9, 7),
    TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Trv },
  { gStatScreen.text + STATSCREEN_TEXT_AFFINLABEL, gUiTmScratchA + TILEMAP_INDEX(9, 9),
    TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Affin },
  { gStatScreen.text + STATSCREEN_TEXT_STATUS, gUiTmScratchA + TILEMAP_INDEX(9, 11),
    TEXT_COLOR_SYSTEM_GOLD, 0, &gMid_Cnd },
  {}, // end
};

TextColor selectGrowthColor(u8 growth) {
  if ((gStatScreen.unit->index & 0xC0) != FACTION_BLUE) {
    return TEXT_COLOR_SYSTEM_GOLD;
  }

  if (growth < 30) {
    return TEXT_COLOR_SYSTEM_GRAY;
  }

  if (growth < 45) {
    return TEXT_COLOR_SYSTEM_WHITE;
  }

  if (growth < 60) {
    return TEXT_COLOR_SYSTEM_BLUE;
  }

  return TEXT_COLOR_SYSTEM_GREEN;
}

#define SELECT_GROWTH_COLOR(stat) \
  selectGrowthColor(gStatScreen.unit->pCharacterData->growth ## stat)

void DisplayPage0(void) {
  DisplayTexts(sPage0TextInfo);

  TextColor powColor = SELECT_GROWTH_COLOR(Pow);

  // Displaying str/mag label
  if (UnitHasMagicRank(gStatScreen.unit)) {
    // mag
    PutDrawText(
        &gStatScreen.text[STATSCREEN_TEXT_POWLABEL],
        gUiTmScratchA + TILEMAP_INDEX(1, 1), powColor, 0, 0,
        GetStringFromIndex(0x4FF)
    ); // Mag
  }
  else {
    // str
    PutDrawText(
        &gStatScreen.text[STATSCREEN_TEXT_POWLABEL],
        gUiTmScratchA + TILEMAP_INDEX(1, 1), powColor, 0, 0,
        GetStringFromIndex(0x4FE)
    ); // Str
  }

  // displaying str/mag stat value
  DrawStatWithBar(
      0, 5, 1, gStatScreen.unit->pow, GetUnitPower(gStatScreen.unit),
      UNIT_POW_MAX(gStatScreen.unit)
  );

  PutDrawText(
      &gStatScreen.text[STATSCREEN_TEXT_SKLLABEL], gUiTmScratchA + TILEMAP_INDEX(1, 3),
      SELECT_GROWTH_COLOR(Skl), 0, 0, GetStringFromIndex(gMid_Skl)
  );

  // displaying skl stat value
  DrawStatWithBar(
      1, 5, 3,
      gStatScreen.unit->state & US_RESCUING ? gStatScreen.unit->skl / 2
                                            : gStatScreen.unit->skl,
      GetUnitSkill(gStatScreen.unit),
      gStatScreen.unit->state & US_RESCUING ? UNIT_SKL_MAX(gStatScreen.unit) / 2
                                            : UNIT_SKL_MAX(gStatScreen.unit)
  );

  PutDrawText(
      &gStatScreen.text[STATSCREEN_TEXT_SPDLABEL], gUiTmScratchA + TILEMAP_INDEX(1, 5),
      SELECT_GROWTH_COLOR(Spd), 0, 0, GetStringFromIndex(gMid_Spd)
  );

  // displaying spd stat value
  DrawStatWithBar(
      2, 5, 5,
      gStatScreen.unit->state & US_RESCUING ? gStatScreen.unit->spd / 2
                                            : gStatScreen.unit->spd,
      GetUnitSpeed(gStatScreen.unit),
      gStatScreen.unit->state & US_RESCUING ? UNIT_SPD_MAX(gStatScreen.unit) / 2
                                            : UNIT_SPD_MAX(gStatScreen.unit)
  );

  PutDrawText(
      &gStatScreen.text[STATSCREEN_TEXT_LCKLABEL], gUiTmScratchA + TILEMAP_INDEX(1, 7),
      SELECT_GROWTH_COLOR(Lck), 0, 0, GetStringFromIndex(gMid_Lck)
  );

  // displaying lck stat value
  DrawStatWithBar(
      3, 5, 7, gStatScreen.unit->lck, GetUnitLuck(gStatScreen.unit),
      UNIT_LCK_MAX(gStatScreen.unit)
  );

  PutDrawText(
      &gStatScreen.text[STATSCREEN_TEXT_DEFLABEL], gUiTmScratchA + TILEMAP_INDEX(1, 9),
      SELECT_GROWTH_COLOR(Def), 0, 0, GetStringFromIndex(gMid_Def)
  );

  // displaying def stat value
  DrawStatWithBar(
      4, 5, 9, gStatScreen.unit->def, GetUnitDefense(gStatScreen.unit),
      UNIT_DEF_MAX(gStatScreen.unit)
  );

  PutDrawText(
      &gStatScreen.text[STATSCREEN_TEXT_RESLABEL], gUiTmScratchA + TILEMAP_INDEX(1, 11),
      SELECT_GROWTH_COLOR(Res), 0, 0, GetStringFromIndex(gMid_Res)
  );

  // displaying res stat value
  DrawStatWithBar(
      5, 5, 11, gStatScreen.unit->res, GetUnitResistance(gStatScreen.unit),
      UNIT_RES_MAX(gStatScreen.unit)
  );

  // displaying mov stat value
  DrawStatWithBar(
      6, 13, 1, UNIT_MOV_BASE(gStatScreen.unit), UNIT_MOV(gStatScreen.unit),
      UNIT_MOV_MAX(gStatScreen.unit)
  );

  // displaying con stat value
  DrawStatWithBar(
      7, 13, 3, UNIT_CON_BASE(gStatScreen.unit), UNIT_CON(gStatScreen.unit),
      UNIT_CON_MAX(gStatScreen.unit)
  );

  // displaying unit aid
  PutNumberOrBlank(
      gUiTmScratchA + TILEMAP_INDEX(13, 5), TEXT_COLOR_SYSTEM_BLUE,
      GetUnitAid(gStatScreen.unit)
  );

  // displaying unit aid icon
  DrawIcon(
      gUiTmScratchA + TILEMAP_INDEX(14, 5),
      GetUnitAidIconId(UNIT_CATTRIBUTES(gStatScreen.unit)),
      TILEREF(0, STATSCREEN_BGPAL_EXTICONS)
  );

  // displaying unit rescue name
  Text_InsertDrawString(
      &gStatScreen.text[STATSCREEN_TEXT_RESCUENAME], 24, TEXT_COLOR_SYSTEM_BLUE,
      GetUnitRescueName(gStatScreen.unit)
  );

  // displaying unit status name and turns

  if (gStatScreen.unit->statusIndex != UNIT_STATUS_RECOVER) {
    // display name

    if (gStatScreen.unit->statusIndex == UNIT_STATUS_NONE) {
      Text_InsertDrawString(
          &gStatScreen.text[STATSCREEN_TEXT_STATUS], 24, TEXT_COLOR_SYSTEM_BLUE,
          GetUnitStatusName(gStatScreen.unit)
      );
    }
    else {
      Text_InsertDrawString(
          &gStatScreen.text[STATSCREEN_TEXT_STATUS], 22, TEXT_COLOR_SYSTEM_BLUE,
          GetUnitStatusName(gStatScreen.unit)
      );
    }

    // display turns

    if (gStatScreen.unit->statusIndex != UNIT_STATUS_NONE) {
      PutNumberSmall(
          gUiTmScratchA + TILEMAP_INDEX(16, 11), 0, gStatScreen.unit->statusDuration
      );
    }
  }
  else {
    // I do not understand what this is for

    struct Unit tmp = *gStatScreen.unit;

    tmp.statusIndex = 0;

    if (gStatScreen.unit->statusIndex == UNIT_STATUS_NONE) {
      Text_InsertDrawString(
          &gStatScreen.text[STATSCREEN_TEXT_STATUS], 24, TEXT_COLOR_SYSTEM_BLUE,
          GetUnitStatusName(&tmp)
      );
    }
    else {
      Text_InsertDrawString(
          &gStatScreen.text[STATSCREEN_TEXT_STATUS], 22, TEXT_COLOR_SYSTEM_BLUE,
          GetUnitStatusName(&tmp)
      );
    }
  }

  // display affininity icon

  DrawIcon(
      gUiTmScratchA + TILEMAP_INDEX(12, 9), GetUnitAffinityIcon(gStatScreen.unit),
      TILEREF(0, STATSCREEN_BGPAL_EXTICONS)
  );

  DisplayBwl();
}

void DisplayLeftPanel(void) {
  const char *namestr = GetStringFromIndex(UNIT_NAME_ID(gStatScreen.unit));
  unsigned namexoff = GetStringTextCenteredPos(0x30, namestr);

  BG_Fill(gBG0TilemapBuffer, 0);

  // Generate battle stats for unit for display later
  BattleGenerateUiStats(gStatScreen.unit, GetUnitEquippedWeaponSlot(gStatScreen.unit));

  // Display character name
  PutDrawText(
      &gStatScreen.text[STATSCREEN_TEXT_CHARANAME],
      gBG0TilemapBuffer + TILEMAP_INDEX(3, 10), TEXT_COLOR_SYSTEM_WHITE, namexoff, 0,
      namestr
  );

  // Display class name
  PutDrawText(
      &gStatScreen.text[STATSCREEN_TEXT_CLASSNAME],
      gBG0TilemapBuffer + TILEMAP_INDEX(1, 13), TEXT_COLOR_SYSTEM_WHITE, 0, 0,
      GetStringFromIndex(gStatScreen.unit->pClassData->nameTextId)
  );

  // Display Lv/E labels
  PutTwoSpecialChar(
      gBG0TilemapBuffer + TILEMAP_INDEX(1, 15), TEXT_COLOR_SYSTEM_GOLD,
      TEXT_SPECIAL_LV_A, TEXT_SPECIAL_LV_B
  );
  PutSpecialChar(
      gBG0TilemapBuffer + TILEMAP_INDEX(5, 15), TEXT_COLOR_SYSTEM_GOLD, TEXT_SPECIAL_E
  );

  // Display Hp/'/' labels
  PutTwoSpecialChar(
      gBG0TilemapBuffer + TILEMAP_INDEX(1, 17), SELECT_GROWTH_COLOR(HP),
      TEXT_SPECIAL_HP_A, TEXT_SPECIAL_HP_B
  );
  PutSpecialChar(
      gBG0TilemapBuffer + TILEMAP_INDEX(5, 17), TEXT_COLOR_SYSTEM_GOLD,
      TEXT_SPECIAL_SLASH
  );

  // Display level
  PutNumberOrBlank(
      gBG0TilemapBuffer + TILEMAP_INDEX(4, 15), TEXT_COLOR_SYSTEM_BLUE,
      gStatScreen.unit->level
  );

  // Display exp
  PutNumberOrBlank(
      gBG0TilemapBuffer + TILEMAP_INDEX(7, 15), TEXT_COLOR_SYSTEM_BLUE,
      gStatScreen.unit->exp
  );

  // Display current hp

  if (GetUnitCurrentHp(gStatScreen.unit) > 99) {
    // Display '--' if current hp > 99
    PutTwoSpecialChar(
        gBG0TilemapBuffer + TILEMAP_INDEX(3, 17), TEXT_COLOR_SYSTEM_BLUE,
        TEXT_SPECIAL_DASH, TEXT_SPECIAL_DASH
    );
  }
  else {
    // Display current hp
    PutNumberOrBlank(
        gBG0TilemapBuffer + TILEMAP_INDEX(4, 17), TEXT_COLOR_SYSTEM_BLUE,
        GetUnitCurrentHp(gStatScreen.unit)
    );
  }

  // Display max hp

  if (GetUnitMaxHp(gStatScreen.unit) > 99) {
    // Display '--' if max hp > 99
    PutTwoSpecialChar(
        gBG0TilemapBuffer + TILEMAP_INDEX(6, 17), TEXT_COLOR_SYSTEM_BLUE,
        TEXT_SPECIAL_DASH, TEXT_SPECIAL_DASH
    );
  }
  else {
    // Display max hp
    PutNumberOrBlank(
        gBG0TilemapBuffer + TILEMAP_INDEX(7, 17), TEXT_COLOR_SYSTEM_BLUE,
        GetUnitMaxHp(gStatScreen.unit)
    );
  }
}
