sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/deathlink.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(d)/deathlink.lyn.event $(d)/*.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
