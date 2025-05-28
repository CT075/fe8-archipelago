#ifndef HPBARS_H
#define HPBARS_H

extern u16 *HPFramePointers[];

#define CRIT_WARNING_THRESHOLD 25

enum __attribute__ ((__packed__)) InfoKind {
  NOTHING=0,
  WARN_EFF=1,
  WARN_CRIT=2,
  CAN_TALK=3,
};

struct InfoCache {
  bool valid;
  u8 lastActiveUnit;
  enum InfoKind entries[62+50+20];
};

#endif
