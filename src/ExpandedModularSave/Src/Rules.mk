sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/MSCore.lyn.event $(d)/MSSizeHook.lyn.event $(d)/MSBWLHook.lyn.event
EVENTS_$(d) := $(EVENTS_$(d)) $(d)/MSaFuncs.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
