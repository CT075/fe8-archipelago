# With advice from http://sites.e-advies.nl/nonrecursive-make.html

DEVKITARM ?= $(error You don't seem to have devkitARM installed, or at least $$DEVKITARM is unset)
VENDOR_DIR := vendor
BIN_DIR := bin

TOOL_CACHE := $(BIN_DIR)/tool_cache

.PHONY: devkit_check

devkit_check:
	echo $(DEVKITARM) > /dev/null

### Standard parts

include Tools.mk
include Wizardry.mk
#include Rules.mk

# CR cam: populate this
clean:
	cd $(BIN_DIR)/lyn && make clean
	rm -rf $(TOOL_CACHE)
	rm -rf $(CACHE_DIR)
	rm -rf $(OBJ_DIR)
