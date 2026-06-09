#ifndef DEPLOY_PERMITS_H
#define DEPLOY_PERMITS_H

#include "global.h"
#include "connector_config.h"
#include "bmunit.h"

enum RecruitedUnit charIdToRecruitedUnit(u8 charId);
void setDeployPermit(enum RecruitedUnit unit);
bool canDeployUnit(enum RecruitedUnit unit);

#endif // DEPLOY_PERMITS_H
