sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

EVENTS_$(d) := $(d)/main.event
PARSE_DEFNS := $(BUILD_DIR)/ParseDefinitions.event
PARSE_DEFNS_H := $(BUILD_INCLUDE)/ParseDefinitions.event.h

$(d)/main.event $(PARSE_DEFNS): $(d)/alltext.txt $(PARSEFILE) $(BIN_DIR)/text-process-classic.py
	python $(BIN_DIR)/text-process-classic.py $< \
		--installer $@ \
		--definitions $(PARSE_DEFNS) \
		--parser-exe $(PARSEFILE)

$(PARSE_DEFNS_H): $(PARSE_DEFNS)
	sed "s/\\$$/0x/g" $< > $@

EVENTS := $(EVENTS) $(EVENTS_$(d))

CLEAN := $(CLEAN) .TextEntries

d := $(dirstack_$(sp))
sp := $(basename $(sp))
