#include "global.h"
#include "bmunit.h"
#include "bmmap.h"
#include "bmudisp.h"
#include "connector_config.h"
#include "ram_structures.h"
#include "unitlistscreen.h"
#include "prepscreen.h"
#include "constants/characters.h"
#include "deployPermits.h"
#include "m4a.h"
#include "types.h"
#include "variables.h"
#include "functions.h"

extern void PrepUnit_DrawUnitListNames(struct ProcPrepUnit *proc);

static int charIdToRecruitedUnit(u8 charId) {
    switch (charId) {
        case CHARACTER_SETH:     return Seth;
        case CHARACTER_FRANZ:    return Franz;
        case CHARACTER_GILLIAM:  return Gilliam;
        case CHARACTER_VANESSA:  return Vanessa;
        case CHARACTER_MOULDER:  return Moulder;
        case CHARACTER_ROSS:     return Ross;
        case CHARACTER_GARCIA:   return Garcia;
        case CHARACTER_NEIMI:    return Neimi;
        case CHARACTER_COLM:     return Colm;
        case CHARACTER_ARTUR:    return Artur;
        case CHARACTER_LUTE:     return Lute;
        case CHARACTER_NATASHA:  return Natasha;
        case CHARACTER_JOSHUA:   return Joshua;
        case CHARACTER_FORDE:    return Forde;
        case CHARACTER_KYLE:     return Kyle;
        case CHARACTER_TANA:     return Tana;
        case CHARACTER_AMELIA:   return Amelia;
        case CHARACTER_INNES:    return Innes;
        case CHARACTER_GERIK:    return Gerik;
        case CHARACTER_TETHYS:   return Tethys;
        case CHARACTER_MARISA:   return Marisa;
        case CHARACTER_LARACHEL: return LArachel;
        case CHARACTER_DOZLA:    return Dozla;
        case CHARACTER_SALEH:    return Saleh;
        case CHARACTER_EWAN:     return Ewan;
        case CHARACTER_CORMAG:   return Cormag;
        case CHARACTER_RENNAC:   return Rennac;
        case CHARACTER_DUESSEL:  return Duessel;
        case CHARACTER_KNOLL:    return Knoll;
        case CHARACTER_MYRRH:    return Myrrh;
        case CHARACTER_SYRENE:   return Syrene;
        default: return -1;
    }
}

void setDeployPermit(enum RecruitedUnit unit) {
    *deployPermits |= (1u << (int)unit);
}

bool canDeployUnit(enum RecruitedUnit unit) {
    return (*deployPermits >> (int)unit) & 1;
}

// Iterates all player units and resets recruitable ones to undeployed.
// Non-recruitable units (lords, etc.) keep their deploy state.
static void resetPrepDeployment(void) {
    for (int i = 0; i < 62; i++) {
        struct Unit *unit = &gUnitArrayBlue[i];
        if (!unit->pCharacterData) continue;
        if (unit->state & US_DEAD) continue;
        int charId = UNIT_CHAR_ID(unit);
        int ru = charIdToRecruitedUnit((u8)charId);
        if (ru == -1) continue;
        if (IsCharacterForceDeployed(charId)) continue;
        unit->state &= ~US_BIT25;
        unit->state |= US_NOT_DEPLOYED;
        if (!canDeployUnit((enum RecruitedUnit)ru)) {
            unit->state |= US_UNSELECTABLE;
        }
    }
}

// Replaces UnitList_TogglePrepDeployState (0x0809132C).
// - Resets deployment to required-only on first browser open each chapter.
// - Allows undeploying any unit freely.
// - Blocks deploying units that lack a permit; plays error sound when blocked.
void myUnitListToggle(struct UnitListScreenProc *proc) {
    int cursor = proc->unk_30;
    struct SortedUnitEnt *ent = gSortedUnits[cursor];
    if (!ent || !ent->unit) return;
    struct Unit *unit = ent->unit;

    if (!(unit->state & US_NOT_DEPLOYED)) {
        // Already deployed — always allow undeploying.
        UnitList_UndeployUnit(unit, proc);
        return;
    }

    // Not deployed — check permit before allowing deploy.
    int charId = UNIT_CHAR_ID(unit);
    int ru = charIdToRecruitedUnit((u8)charId);
    if (ru != -1 && !canDeployUnit((enum RecruitedUnit)ru)) {
        m4aSongNumStart(0x6c);
        return;
    }
    UnitList_DeployUnit(unit, proc);
}

// Replaces CanCharacterBePrepMoved (0x0803374C).
// Blocks map-placement of recruitable units that lack a deploy permit.
bool myCanCharPrepMoved(int charId) {
    int ru = charIdToRecruitedUnit((u8)charId);
    if (ru != -1 && !canDeployUnit((enum RecruitedUnit)ru)) {
        return false;
    }
    return !IsCharacterForceDeployed(charId);
}

// Replaces PrepScreenProc_InitMapMenu (0x080334BC).
void myPrepInitMapMenu(struct ProcPrepSallyCursor *proc) {
    proc->unk_58 = 1;
    PrepScreenProc_StartMapMenu(proc);
}

// If a deploy permit item was written by the Python client while on the world map,
// apply it now so it takes effect before the prep screen is shown. Other item types
// wait for player phase where they show proper popups.
static void applyPendingDeployPermit(void) {
    if (!receivedAPItem->filled) {
        return;
    }
    struct IncomingEvent evt;
    unpackAPEventFromId(receivedAPItem->itemId, &evt);
    if (evt.kind == UnitDeploy) {
        setDeployPermit(evt.payload.recruitedUnit);
        receivedAPItem->filled = 0;
        *receivedItemIndex += 1;
    } else if (evt.kind == ProgSethDeploy) {
        u8 stage = *sethDeployStage;
        if (stage < 4) {
            stage += 1;
            *sethDeployStage = stage;
            if (stage == 4) {
                setDeployPermit(Seth);
            }
        }
        receivedAPItem->filled = 0;
        *receivedItemIndex += 1;
    }
}

// Hooks the EnablePrepScreenMenu proc call at 0x0859DD14 (pointer at 0x0859DD18).
// Called on EVERY path that makes the prep screen visible — both initial chapter
// entry and returns from the unit-list browser — so the guard distinguishes them.
void myPrepRevealReset(void *unused_proc) {
    applyPendingDeployPermit();
    u8 chapterTag = (u8)(gPlaySt.chapterIndex) | 0x80;
    if (*lastResetChapter != chapterTag) {
        resetPrepDeployment();
        RefreshEntityBmMaps();
        RefreshUnitSprites();
        *lastResetChapter = chapterTag;
    }
    EnablePrepScreenMenu();
}

// Replaces PrepCheckCanSelectUnit (0x0809ABD0).
// Blocks deploying units that lack a permit; otherwise replicates original logic.
int myPrepCheckCanSelectUnit(struct ProcPrepUnit *proc, struct Unit *unit) {
    int charId = UNIT_CHAR_ID(unit);
    int ru = charIdToRecruitedUnit((u8)charId);
    if (ru != -1 && !canDeployUnit((enum RecruitedUnit)ru)) {
        m4aSongNumStart(0x6c);
        return 0;
    }
    if (proc->cur_counter >= proc->max_counter) {
        m4aSongNumStart(0x6c);
        return 0;
    }
    proc->cur_counter++;
    unit->state &= ~(u32)(US_UNSELECTABLE | US_NOT_DEPLOYED);
    RegisterSioPid((u8)charId);
    m4aSongNumStart(0x6a);
    PrepUnit_DrawUnitListNames(proc);
    return 1;
}
