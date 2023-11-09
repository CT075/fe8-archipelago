#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

#include "global.h"
#include "proc.h"
#include "constants/items.h"

#include "connector_config.h"

#define SLOT_NAME_MAX 64

enum LocationItemKind {
  Empty=0,
  APItem=1,
  SelfItem=2,
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

const u16 *receivedItemEvent(struct IncomingEvent *evt);

// CR cam: This should come from `Generate.hs` so we can ensure that this
// struct definition doesn't drift from the python code that sets it
struct ArchipelagoOptions {
  bool superDemonKing;
};

struct ArchipelagoInfo {
  u8 slotName[SLOT_NAME_MAX];
};

extern const struct ArchipelagoOptions archipelagoOptions;
extern const struct ArchipelagoInfo archipelagoInfo;

#endif // ARCHIPELAGO_H
