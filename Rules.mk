BASEROM := fe8.gba

TARGET := fe8_ap.gba

BASEPATCH := fe8_ap_base.bsdiff4

EVENT_MAIN := main.event
EAFLAGS := -werr -output:$(TARGET) -input:$(EVENT_MAIN) --nocash-sym \
					 -raws:'$(EA_STD_LIB_DIR)/Language Raws' \
					 -I:'$(EA_STD_LIB_DIR)/EA Standard Library' \
					 -I:'$(EA_STD_LIB_DIR)/Extensions' \
					 -I:'$(EA_STD_LIB_DIR)'

ARCHIPELAGO_DEFS := $(BUILD_DIR)/archipelagoDefs.event

RAM_STRUCTURES_H := include/ram_structures.h
RAM_SYMS := $(BUILD_DIR)/ram_syms.sym

SAVE_CHUNKS_GEN_EVENT := $(BUILD_DIR)/save_chunks.gen.event
SUSP_CHUNKS_GEN_EVENT := $(BUILD_DIR)/suspend_chunks.gen.event

POSTPROCESS := $(BIN_DIR)/postprocess.py

POPULATED_CONNECTOR_CONFIG := $(BUILD_DIR)/connector_config.py

BLANK_WEAPON_RANKS_HS := $(BIN_DIR)/blank_weapon_ranks/BlankWeaponRanks.hs
BLANK_WEAPON_RANKS := $(BUILD_DIR)/blank_weapon_ranks.event

$(ARCHIPELAGO_DEFS): $(GENDEFS) $(RAM_STRUCTURES_H)
	$(GENDEFS) Event > $@

$(RAM_SYMS): $(GENDEFS) $(RAM_STRUCTURES_H)
	$(GENDEFS) Sym > $@

$(BLANK_WEAPON_RANKS): $(BLANK_WEAPON_RANKS_HS)
	runhaskell -Wall $< > $@

include/connector_config.h: $(BIN_DIR)/connector_config/Generate.hs
	runhaskell -Wall $< H > $@

src/archipelago/connector_config.c: $(BIN_DIR)/connector_config/Generate.hs
	runhaskell -Wall $< C > $@

CONNECTOR_CONFIG_PY := connector/py/connector_config.py

$(CONNECTOR_CONFIG_PY): $(BIN_DIR)/connector_config/Generate.hs
	runhaskell -Wall $< Py > $@

src/archipelago/connector_config_defs.event: $(BIN_DIR)/connector_config/Generate.hs
	runhaskell -Wall $< Event > $@

$(RAM_STRUCTURES_H): $(BIN_DIR)/ram_alloc.py data/ram_structures.csv
	python $< --items_file $(word 2,$^) > $@

$(SAVE_CHUNKS_GEN_EVENT): $(BIN_DIR)/save_alloc.py data/save_chunks.csv
	python $< --items_file $(word 2,$^) --which save > $@

$(SUSP_CHUNKS_GEN_EVENT): $(BIN_DIR)/save_alloc.py data/save_chunks.csv
	python $< --items_file $(word 2,$^) --which suspend > $@

SYMBOLS := $(TARGET:.gba=.sym)

EVENTS := $(EVENT_MAIN) $(ARCHIPELAGO_DEFS) $(BLANK_WEAPON_RANKS)

hack: $(BASEPATCH)

# All subdirectories
dir := src
include $(dir)/Rules.mk

dir := data
include $(dir)/Rules.mk

# The variables `EVENTS` and `CLEAN` are populated by subdirectory makefiles.

$(BASEROM):
	$(error no $(BASEROM) found at build root)

# CR cam: split out the postprocess step somehow
$(TARGET) $(SYMBOLS) $(POPULATED_CONNECTOR_CONFIG): \
		$(BASEROM) $(COLORZCORE) $(EVENTS) $(PARSEFILE) $(RAM_SYMS) \
		$(CONNECTOR_CONFIG_PY) $(POSTPROCESS)
	cp $(BASEROM) $(TARGET)
	$(COLORZCORE) A FE8 $(EAFLAGS) || (rm -f $(TARGET) $(SYMBOLS) && false)
	cat $(RAM_SYMS) >> $(SYMBOLS)
	python $(POSTPROCESS) \
		--sym_file $(SYMBOLS) \
		--connector_config_in $(CONNECTOR_CONFIG_PY) \
		--connector_config_out $(POPULATED_CONNECTOR_CONFIG) \
		--target $(TARGET)

$(BASEPATCH): $(TARGET)
	# CR cam: install bsdiff4 if not already present
	python -c "from bsdiff4 import file_diff; file_diff('$(BASEROM)', '$<', '$@')"

CLEAN := $(CLEAN) $(BUILD_DIR) $(BASEPATCH)

.PHONY: clean
clean: clean-tools
	rm -rf $(CLEAN)

.SECONDARY: $(CLEAN)

all: hack $(CONNECTOR_CONFIG_PY)

debug: EAFLAGS := $(EAFLAGS) -D:'DEBUG=1' -debug
debug: $(TARGET)
