sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/progCaps.lyn.event \
	$(d)/checks.lyn.event \
	$(d)/receivedItems.lyn.event \
	$(d)/convoy200.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(EVENTS_$(d)) $(d)/*.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
