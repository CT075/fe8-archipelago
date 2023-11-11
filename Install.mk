ARCHIPELAGO_LOC ?= $(error rerun with ARCHIPELAGO_LOC set)

WORLD_LOC := worlds/fe8
AP_CONFIG_NAME := connector_config.py
BASEPATCH_NAME := base_patch.bsdiff4

.PHONY: install_to_archipelago

install_to_archipelago: $(BASEPATCH)
	cp $(POPULATED_CONNECTOR_CONFIG) $(ARCHIPELAGO_LOC)/$(WORLD_LOC)/$(AP_CONFIG_NAME)
	cp $(BASEPATCH) $(ARCHIPELAGO_LOC)/$(WORLD_LOC)/data/$(BASEPATCH_NAME)
