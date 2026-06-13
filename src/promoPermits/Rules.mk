sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/promoPermits.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(d)/promoPermits.lyn.event $(d)/promoPermits.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
