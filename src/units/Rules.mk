sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

dir := $(d)/data
include $(dir)/Rules.mk

EVENTS_$(d) := $(d)/deployPermits.lyn.event

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(d)/deployPermits.lyn.event $(d)/deployPermits.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
