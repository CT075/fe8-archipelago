sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

dir := $(d)/data
include $(dir)/Rules.mk

MAIN_$(d) := $(d)/main.event

EVENTS_$(d) := MAIN_$(d) $(d)/markRecruits.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(d)/markRecruits.lyn.event $(d)/markRecruits.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
