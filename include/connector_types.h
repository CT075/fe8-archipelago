// THIS FILE IS GENERATED, DO NOT EDIT DIRECTLY
// 
// To change this file, see `bin/connector_config/Generate.hs` at
// https://github.com/CT075/fe8-archipelago
// 

enum HolyWeapon {
  SIEGLINDE=0,
  SIEGMUND=1,
  GLEIPNIR=2,
  GARM=3,
  NIDHOGG=4,
  VIDOFNIR=5,
  EXCALIBUR=6,
  AUDHULMA=7,
  IVALDI=8,
  LATONA=9,
} __attribute__ ((__packed__));

enum WeaponKind {
  SWORD=0,
  LANCE=1,
  AXE=2,
  BOW=3,
  ANIMA=4,
  LIGHT=5,
  DARK=6,
  STAFF=7,
} __attribute__ ((__packed__));

union IncomingPayload {
  enum WeaponKind weaponKind;
  u8 itemID;
};

union OutgoingPayload {
  enum HolyWeapon holyWeaponID;
  u8 chapterID;
};

enum IncomingEventKind {
  PROGRESSIVELEVELCAP=0,
  PROGRESSIVEWEAPONLEVELCAP=1,
  GETITEM=2,
} __attribute__ ((__packed__));

enum OutgoingEventKind {
  GOTHOLYWEAPON=0,
  CLEAREDCHAPTER=1,
} __attribute__ ((__packed__));

struct OutEvent {
  enum OutEventKind kind;
  union OutPayload payload;
  bool seen;
};

struct InEvent {
  enum InEventKind kind;
  union InPayload payload;
  bool seen;
};

