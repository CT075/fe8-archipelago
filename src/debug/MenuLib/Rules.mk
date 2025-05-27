sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/Kernel.event $(d)/Macros.event $(d)/ManualInstall.event \
							 $(d)/modules/SpecialEventPerUnit.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
