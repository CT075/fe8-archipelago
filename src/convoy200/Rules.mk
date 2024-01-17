sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/main.event


EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN)

d := $(dirstack_$(sp))
sp := $(basename $(sp))
