sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/skirmishSpawn.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(d)/skirmishSpawn.lyn.event $(d)/*.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
