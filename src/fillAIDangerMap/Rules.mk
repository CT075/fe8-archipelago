sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/FillAIDangerMap.event

$(d)/FillAIDangerMap.event: $(d)/FillAIDangerMap.dmp

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
