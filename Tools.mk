# Build tools in bin/
# These can be called recursively because those tools are all self-contained

LYN_DIR := $(BIN_DIR)/lyn
LYN := $(LYN_DIR)/lyn

# ColorzCore needs to be run from the directory containing the `Language Raws`
# folder (it doesn't handle the `-raws` flag properly), so we simply copy
# everything into the root of the build dir.
COLORZCORE_DIR := $(BUILD_DIR)
$(shell mkdir -p $(COLORZCORE_DIR) > /dev/null)
COLORZCORE := $(COLORZCORE_DIR)/ColorzCore$(EXE)
COLORZCORE_BIN ?= $(error No ColorzCore binary; please set COLORZCORE_BIN and run `make ColorzCore`)
EA_STD_LIB_DIR := $(VENDOR_DIR)/EAStandardLibrary

$(LYN_DIR)/Makefile:
	cd bin/lyn && cmake .

$(LYN): $(LYN_DIR)/Makefile
	cd bin/lyn && $(MAKE)

GENDEFS_DIR := $(BIN_DIR)/gen_ea_defs
GENDEFS_SRC := $(GENDEFS_DIR)/gen_ea_defs.c
GENDEFS := $(BUILD_DIR)/gen_ea_defs

# CR cam: these should use `CDEPFLAGS` as well
$(GENDEFS): $(GENDEFS_SRC) include/*
	$(CC) $(GENDEFS_SRC) -o $(GENDEFS) $(INCFLAGS)

.PHONY: ColorzCore
ColorzCore: $(COLORZCORE)

# CR cam: Every time we change COLORZCORE_DIR we have to manually change the
# number of `..`s here.
$(COLORZCORE):
	ln -s $(COLORZCORE_BIN) $(COLORZCORE)
	ln -s '../$(EA_STD_LIB_DIR)/Language Raws' '$(COLORZCORE_DIR)/Language Raws'
	ln -s '../$(EA_STD_LIB_DIR)/EA Standard Library' '$(COLORZCORE_DIR)/EA Standard Library'
	ln -s '../$(EA_STD_LIB_DIR)/Extensions' '$(COLORZCORE_DIR)/Extensions'
	ln -s '..//$(EA_STD_LIB_DIR)/EAstdlib.event' '$(COLORZCORE_DIR)/EAstdlib.event'

.PHONY: tools
tools: $(LYN) $(COLORZCORE)
