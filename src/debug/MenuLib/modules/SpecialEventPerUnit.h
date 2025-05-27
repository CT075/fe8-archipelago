#include "eventinfo.h"
#include "uimenu.h"

struct SEPUAvailabilityConfig {
  u8 character;
  u8 class;
  u8 flag;
  u8 item;
};

u8 runEventFromMenu(struct MenuProc *owner, struct MenuItemProc *cmd, u16 *script);

u8 SEPUAvailableImpl(
    const struct MenuItemDef *self, int number,
    struct SEPUAvailabilityConfig *cfg
);
