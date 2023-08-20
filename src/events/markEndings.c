#include "global.h"
#include "event.h"

#include "connector_config.h"
#include "archipelago.h"

// TODO: In theory, we could generate this from [connector_config]. However, by
// doing the division here, it's a lot easier to transition to adding more
// chapter-specific archipelago stuff.

void markCh1Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch1Id);
}

void markCh2Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch2Id);
}

void markCh3Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch3Id);
}

void markCh4Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch4Id);
}

void markCh5Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch5Id);
}

void markCh5xClear(struct EventEngineProc *engine) {
  markChapterCleared(Ch5xId);
}

void markCh6Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch6Id);
}

void markCh7Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch7Id);
}

void markCh8Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch8Id);
}

void markCh9Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch9Id);
}

void markCh10Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch10Id);
}

void markCh11Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch11Id);
}

void markCh12Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch12Id);
}

void markCh13Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch13Id);
}

void markCh14Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch14Id);
}

void markCh15Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch15Id);
}

void markCh16Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch16Id);
}

void markCh17Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch17Id);
}

void markCh18Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch18Id);
}

void markCh19Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch19Id);
}

void markCh20Clear(struct EventEngineProc *engine) {
  markChapterCleared(Ch20Id);
}

void markEndgameClear(struct EventEngineProc *engine) {
  markChapterCleared(EndgameId);
}

void markFormortiisClear(struct EventEngineProc *engine) {
  markChapterCleared(VictoryId);
}

void markPrologueClear(struct EventEngineProc *engine) {
  markChapterCleared(PrologueId);
}
