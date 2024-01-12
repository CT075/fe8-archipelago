#include "global.h"
#include "proc.h"
#include "event.h"

#include "connector_config.h"
#include "archipelago.h"

// TODO: In theory, we could generate this from [connector_config]. However, by
// doing the division here, it's a lot easier to transition to adding more
// chapter-specific archipelago stuff.

void markCh1Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch1Id);
}

void markCh2Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch2Id);
}

void markCh3Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch3Id);
}

void markCh4Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch4Id);
}

void markCh5Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch5Id);
}

void markCh5xClear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch5xId);
}

void markCh6Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch6Id);
}

void markCh7Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch7Id);
}

void markCh8Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch8Id);
}

void markCh9Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch9Id);
}

void markCh10Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch10Id);
}

void markCh11Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch11Id);
}

void markCh12Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch12Id);
}

void markCh13Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch13Id);
}

void markCh14Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch14Id);
}

void markCh15Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch15Id);
}

void markCh16Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch16Id);
}

void markCh17Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch17Id);
}

void markCh18Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch18Id);
}

void markCh19Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch19Id);
}

void markCh20Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ch20Id);
}

void markEndgameClear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Endgame1Id);
}

void markFormortiisClear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Endgame2Id);
}

void markPrologueClear(struct EventEngineProc *proc) {
  handleChapterClear(proc, PrologueId);
}

void markTower1Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Tower1Id);
}

void markTower2Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Tower2Id);
}

void markTower3Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Tower3Id);
}

void markTower4Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Tower4Id);
}

void markTower5Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Tower5Id);
}

void markTower6Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Tower6Id);
}

void markTower7Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Tower7Id);
}

void markTower8Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Tower8Id);
}

void markRuins1Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ruins1Id);
}

void markRuins2Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ruins2Id);
}

void markRuins3Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ruins3Id);
}

void markRuins4Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ruins4Id);
}

void markRuins5Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ruins5Id);
}

void markRuins6Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ruins6Id);
}

void markRuins7Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ruins7Id);
}

void markRuins8Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ruins8Id);
}

void markRuins9Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ruins9Id);
}

void markRuins10Clear(struct EventEngineProc *proc) {
  handleChapterClear(proc, Ruins10Id);
}
