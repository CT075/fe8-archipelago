sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/main.event $(d)/progressiveCaps.lyn.event $(d)/displayLvlCap.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(d)/progressiveCaps.lyn.event $(d)/*.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
