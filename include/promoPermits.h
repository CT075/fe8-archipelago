#ifndef PROMO_PERMITS_H
#define PROMO_PERMITS_H

#include "connector_config.h"
#include "global.h"

int classIdToPromotedClass(u8 classId);
void setPromoPermit(enum PromotedClass cls);
bool canPromoteToClassId(u8 classId);

#endif // PROMO_PERMITS_H
