BASEROM := fe8.gba

TARGET := fe8_ap.gba

EVENT_MAIN := main.event
EAFLAGS := -werr -output:../$(TARGET) -input:../$(EVENT_MAIN) --nocash-sym

ARCHIPELAGO_DEFS := _build/archipelagoDefs.event

$(ARCHIPELAGO_DEFS): $(GENDEFS)
	$(GENDEFS) > $(ARCHIPELAGO_DEFS)

include/connector_config.h: $(BIN_DIR)/connector_config/Generate.hs
	runhaskell -Wall $< H > $@

src/archipelago/connector_config.c: $(BIN_DIR)/connector_config/Generate.hs
	runhaskell -Wall $< C > $@

py/data_init.py: $(BIN_DIR)/connector_config/Generate.hs
	runhaskell -Wall $< Py > $@

SYMBOLS := $(BUILD_DIR)/$(TARGET:.gba=.sym)

EVENTS := $(EVENT_MAIN) $(ARCHIPELAGO_DEFS)

hack: $(TARGET)

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

CLEAN := $(BUILD_DIR)

.PHONY: clean
clean:
	rm -f $(CLEAN)
	cd $(BIN_DIR)/lyn && make clean

.SECONDARY: $(CLEAN)
