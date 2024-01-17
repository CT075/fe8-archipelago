sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/convoy200.lyn.event


EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(d)/convoy200.lyn.event

d := $(dirstack_$(sp))
sp := $(basename $(sp))
