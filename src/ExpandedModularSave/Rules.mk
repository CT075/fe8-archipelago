sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

dir := $(d)/Src
include $(dir)/Rules.mk

dir := $(d)/Modules
include $(dir)/Rules.mk

EVENTS_$(d) := \
	$(d)/ExModularSave.event \
	$(d)/ExModularSaveInternals.event \
	$(SAVE_CHUNKS_GEN_EVENT) \
	$(SUSP_CHUNKS_GEN_EVENT) \

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
