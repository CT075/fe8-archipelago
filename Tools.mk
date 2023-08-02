# Build tools in bin/
# These can be called recursively because those tools are all self-contained

LYN_DIR := $(BIN_DIR)/lyn
LYN := $(LYN_DIR)/lyn$(EXE)

COLORZCORE_DIR := $(BIN_DIR)/tools_cache
$(shell mkdir -p $(COLORZCORE_DIR) > /dev/null)
COLORZCORE := $(COLORZCORE_DIR)/ColorzCore$(EXE)

$(LYN_DIR)/Makefile:
	cd bin/lyn && cmake .

$(LYN): $(LYN_DIR)/Makefile
	cd bin/lyn && $(MAKE)

.PHONY: tools
tools: $(LYN)
