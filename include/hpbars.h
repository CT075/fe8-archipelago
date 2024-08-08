#ifndef HPBARS_H
#define HPBARS_H

extern u16 *HPFramePointers[];

#define CRIT_WARNING_THRESHOLD 25

enum InfoKind {
  NOTHING,
  WARN_EFF,
  WARN_CRIT,
  CAN_TALK,
};

struct InfoCache {
  bool valid;
  u8 lastActiveUnit;
  enum InfoKind entries[62+50+20];
};

#endif
