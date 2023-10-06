sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

dir := $(d)/text
include $(dir)/Rules.mk

dir := $(d)/idleSprites
include $(dir)/Rules.mk

EVENTS_$(d) := $(d)/main.event $(d)/tweaks.event

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
