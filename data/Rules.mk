sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

dir := $(d)/text
include $(dir)/Rules.mk

EVENTS_$(d) := $(d)/main.event

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
