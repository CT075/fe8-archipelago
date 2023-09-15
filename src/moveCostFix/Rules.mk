sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/moveCosts.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(d)/moveCosts.lyn.event $(d)/*.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
