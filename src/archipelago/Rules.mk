sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

LYN_EVENTS_$(d) := $(d)/archipelago.lyn.event $(d)/connector_config.lyn.event
REG_EVENTS_$(d) := $(d)/shims.event $(d)/ap_events.event $(d)/main.event
EVENTS_$(d) := $(LYN_EVENTS_$(d)) $(REG_EVENTS_$(d)) $(d)/connector_config_defs.event

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(LYN_EVENTS_$(d)) $(d)/*.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
