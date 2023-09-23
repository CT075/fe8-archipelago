ARCHIPELAGO_LOC ?= $(error rerun with ARCHIPELAGO_LOC set)

SYMBOL_POPULATOR := bin/populate_with_symbols/populate_with_symbols.py

WORLD_LOC := worlds/fe8
AP_CONFIG_NAME := connector_config.py
AP_CONNECTOR_NAME := connector_fe8.lua
BASEPATCH_NAME := base_patch.bsdiff4

CONNECTOR := connector/lua/$(AP_CONNECTOR_NAME)

.PHONY: install_to_archipelago

install_to_archipelago: $(BASEPATCH) $(SYMBOL_POPULATOR_BIN) $(CONNECTOR_CONFIG_PY) $(CONNECTOR)
	python $(SYMBOL_POPULATOR) --sym_file $(SYMBOLS) --input $(CONNECTOR_CONFIG_PY) \
		> $(ARCHIPELAGO_LOC)/$(WORLD_LOC)/$(AP_CONFIG_NAME)
	python $(SYMBOL_POPULATOR) --sym_file $(SYMBOLS) --input $(CONNECTOR) \
		> $(ARCHIPELAGO_LOC)/$(WORLD_LOC)/data/$(AP_CONNECTOR_NAME)
	python $(SYMBOL_POPULATOR) --sym_file $(SYMBOLS) --input $(CONNECTOR) \
		> $(ARCHIPELAGO_LOC)/data/lua/$(AP_CONNECTOR_NAME)
	cp $(BASEPATCH) $(ARCHIPELAGO_LOC)/$(WORLD_LOC)/data/$(BASEPATCH_NAME)
