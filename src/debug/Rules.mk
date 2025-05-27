sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

dir := $(d)/MenuLib
include $(dir)/Rules.mk

EVENTS_$(d) := $(d)/main.event $(d)/debug.lyn.event

# We could try to rebuild the code in `asm/`, but I wasn't able to get it to
# work, so let's just commit the pre-built asset.

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
