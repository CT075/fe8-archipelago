#ifndef ARCHIPELAGO_H
#define ARCHIPELAGO_H

#include "connector_config.h"

// CR cam: it would be nice to not need to do this manually
#define CHECKED_LOCATIONS_ADDR (0x02026E30 + sizeof(struct ProgressiveCaps))
#define checkedLocations ((struct Checks *)(CHECKED_LOCATIONS_ADDR))

void markChapterCleared(int chapterNum);
void markHolyWeaponGet(enum HolyWeapon weap);

#endif // ARCHIPELAGO_H
