# Build tools in bin/
# These can be called recursively because those tools are all self-contained

LYN_DIR := $(BIN_DIR)/lyn
LYN := $(LYN_DIR)/lyn

# ColorzCore needs to be run from the directory containing the `Language Raws`
# folder (it doesn't handle the `-raws` flag properly), so we simply copy
# everything into the root of the build dir.
COLORZCORE_DIR := $(BIN_DIR)/ColorzCore
$(shell mkdir -p $(COLORZCORE_DIR) > /dev/null)
COLORZCORE := $(BUILD_DIR)/ColorzCore$(EXE)
EA_STD_LIB_DIR := $(VENDOR_DIR)/EAStandardLibrary

$(LYN_DIR)/Makefile:
	cd $(LYN_DIR) && cmake .

$(LYN): $(LYN_DIR)/Makefile
	cd $(LYN_DIR) && $(MAKE)

PARSEFILE_DIR := $(BIN_DIR)/ParseFile
PARSEFILE := $(BUILD_DIR)/ParseFile

$(PARSEFILE): $(PARSEFILE_DIR)/ParseFile.hs $(PARSEFILE_DIR)/FlagUtilities.hs \
		$(PARSEFILE_DIR)/GBAUtilities.hs $(PARSEFILE_DIR)/FEParser.hs
	ghc $< -i$(PARSEFILE_DIR) -o $@

PNG2DMP_DIR := $(BIN_DIR)/Png2Dmp
PNG2DMP := $(PNG2DMP_DIR)/Png2Dmp

# XXX: We should properly be checking every .hs file here, but this is
# vendored, so they're not likely to change often enough.
$(PNG2DMP): $(PNG2DMP_DIR)/Png2Dmp.hs $(PNG2DMP_DIR)/Png2Dmp.cabal
	cd $(PNG2DMP_DIR) && \
		cabal build && \
		cp $(shell cd $(PNG2DMP_DIR) && cabal list-bin Png2Dmp) Png2Dmp

GENDEFS_DIR := $(BIN_DIR)/export_addresses
GENDEFS_SRC := $(GENDEFS_DIR)/export_addresses.c
GENDEFS := $(BUILD_DIR)/export_addresses

# CR cam: these should use `CDEPFLAGS` as well
$(GENDEFS): $(GENDEFS_SRC) include/*
	$(CC) $(GENDEFS_SRC) -o $(GENDEFS) $(INCFLAGS) -m32

.PHONY: ColorzCore
ColorzCore: $(COLORZCORE)

# CR cam: Every time we change COLORZCORE_DIR we have to manually change the
# number of `..`s here.
$(COLORZCORE):
	dotnet publish -o $(BUILD_DIR) $(COLORZCORE_DIR)/ColorzCore/ColorzCore.csproj
	ln -s '../$(EA_STD_LIB_DIR)/Language Raws' '$(BUILD_DIR)/Language Raws'
	ln -s '../$(EA_STD_LIB_DIR)/EA Standard Library' '$(BUILD_DIR)/EA Standard Library'
	ln -s '../$(EA_STD_LIB_DIR)/Extensions' '$(BUILD_DIR)/Extensions'
	ln -s '..//$(EA_STD_LIB_DIR)/EAstdlib.event' '$(BUILD_DIR)/EAstdlib.event'

.PHONY: tools
tools: $(LYN) $(COLORZCORE)

.PHONY: clean-tools
clean-tools:
	cd $(BIN_DIR)/lyn && make clean
	cd $(BIN_DIR)/ParseFile && rm -rf *.o
