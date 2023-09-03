sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/progCaps.lyn.event $(d)/checks.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(d)/progCaps.lyn.event $(d)/checks.lyn.event $(d)/*.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
