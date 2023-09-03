BASEROM := fe8.gba

TARGET := fe8_ap.gba

BASEPATCH := fe8_ap_base.bsdiff

EVENT_MAIN := main.event
EAFLAGS := -werr -output:../$(TARGET) -input:../$(EVENT_MAIN) --nocash-sym

ARCHIPELAGO_DEFS := _build/archipelagoDefs.event

$(ARCHIPELAGO_DEFS): $(GENDEFS) include/progressiveCaps.h include/archipelago.h
	$(GENDEFS) > $(ARCHIPELAGO_DEFS)

include/connector_config.h: $(BIN_DIR)/connector_config/Generate.hs
	runhaskell -Wall $< H > $@

src/archipelago/connector_config.c: $(BIN_DIR)/connector_config/Generate.hs
	runhaskell -Wall $< C > $@

connector/py/data_init.py: $(BIN_DIR)/connector_config/Generate.hs
	runhaskell -Wall $< Py > $@

src/archipelago/connector_config_defs.event: $(BIN_DIR)/connector_config/Generate.hs
	runhaskell -Wall $< Event > $@

SYMBOLS := $(TARGET:.gba=.sym)

EVENTS := $(EVENT_MAIN) $(ARCHIPELAGO_DEFS)

hack: $(BASEPATCH)

# All subdirectories
dir := src
include $(dir)/Rules.mk

dir := data
include $(dir)/Rules.mk

# The variables `EVENTS` and `CLEAN` are populated by subdirectory makefiles.

$(BASEROM):
	$(error no $(BASEROM) found at build root)

$(TARGET) $(SYMBOLS): $(BASEROM) $(COLORZCORE) $(EVENTS) $(PARSEFILE)
	cd $(BUILD_DIR) && \
		cp ../$(BASEROM) ../$(TARGET) && \
		./ColorzCore A FE8 $(EAFLAGS) \
	|| (rm -f ../$(TARGET) $(SYMBOLS) && false)

$(BASEPATCH): $(TARGET)
	python -c "from bsdiff4 import file_diff; file_diff('$(BASEROM)', '$<', '$@')"

CLEAN := $(CLEAN) $(BUILD_DIR) $(BASEPATCH)

.PHONY: clean
clean: clean-tools
	rm -rf $(CLEAN)

.SECONDARY: $(CLEAN)
