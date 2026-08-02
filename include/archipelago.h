#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

#include "constants/items.h"
#include "global.h"
#include "proc.h"

#include "connector_config.h"

#define SLOT_NAME_MAX 64

enum LocationItemKind {
  Empty = 0,
  APItem = 1,
  SelfItem = 2,
};

struct LocationItem {
  enum LocationItemKind kind;
  u16 id;
};

struct APReceivedItem {
  u16 itemId;
  u8 filled;
};

void handleChapterClear(ProcPtr parent, int chapterNum);
void handleHolyWeaponGet(ProcPtr parent, enum HolyWeapon weap);
void handleUnitRecruited(ProcPtr parent, enum RecruitedUnit unit);
void checkAllPlayerUnitsRecruited(ProcPtr proc);

const u16 *receivedItemEvent(struct IncomingEvent *evt);

struct DeathLinkState {
  u8 pendingIn;
  s8 pendingOut;
  u8 ready;
};

// CR cam: This should come from `Generate.hs` so we can ensure that this
// struct definition doesn't drift from the python code that sets it
enum __attribute__((__packed__)) LockpickUsability {
  Vanilla = 0,
  GlobalLockpicks = 1,
  GlobalRoguePick = 2,
};

enum __attribute__((__packed__)) DeathLinkKind {
  None = 0,
  OnGameOver = 1,
  OnAnyDeath = 2,
};

struct ArchipelagoOptions {
  bool superDemonKing;
  enum LockpickUsability lockpickUsability;
  enum DeathLinkKind deathLinkKind;
  bool enableLevelCaps;
  bool enableWeaponLevelCaps;
  bool promotionUnlocks;
  bool recruitChecksEnabled;
  bool freeSeth;
  bool freeFranz;
  bool freeGilliam;
  bool freeVanessa;
  bool freeMoulder;
  bool freeRoss;
  bool freeGarcia;
  bool freeNeimi;
  bool freeColm;
  bool freeArtur;
  bool freeLute;
  bool freeNatasha;
  bool freeJoshua;
  bool freeForde;
  bool freeKyle;
  bool freeTana;
  bool freeAmelia;
  bool freeInnes;
  bool freeGerik;
  bool freeTethys;
  bool freeMarisa;
  bool freeLArachel;
  bool freeDozla;
  bool freeEwan;
  bool freeCormag;
  bool freeRennac;
  bool freeDuessel;
  bool freeKnoll;
  bool freeMyrrh;
  bool freeSyrene;
  bool freeSaleh;
};

struct ArchipelagoInfo {
  u8 slotName[SLOT_NAME_MAX];
};

extern const struct ArchipelagoOptions archipelagoOptions;
extern const struct ArchipelagoInfo archipelagoInfo;

#endif // ARCHIPELAGO_H
