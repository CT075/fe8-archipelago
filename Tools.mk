# Build tools in bin/
# These can be called recursively because those tools are all self-contained

LYN_DIR := $(BIN_DIR)/lyn
LYN := $(LYN_DIR)/lyn$(EXE)

$(LYN_DIR)/Makefile:
	cd bin/lyn && cmake .

$(LYN): $(LYN_DIR)/Makefile
	cd bin/lyn && $(MAKE)

tools: $(LYN)
