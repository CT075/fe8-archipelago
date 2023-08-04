BASEROM := fe8.gba

TARGET := fe8_ap.gba

EVENT_MAIN := main.event
EAFLAGS := -werr -output:../$(TARGET) -input:../$(EVENT_MAIN) --nocash-sym

SYMBOLS := $(BUILD_DIR)/$(TARGET:.gba=.sym)

EVENTS := $(EVENT_MAIN)

hack: $(TARGET)

# All subdirectories
dir := src
include $(dir)/Rules.mk

# The variables `EVENTS` and `CLEAN` gets added to by subdirectory makefiles.

$(BASEROM):
	$(error no $(BASEROM) found at build root)

$(TARGET) $(SYMBOLS): $(BASEROM) $(COLORZCORE) $(EVENTS)
	cd $(BUILD_DIR) && \
		cp ../$(BASEROM) ../$(TARGET) && \
		./ColorzCore A FE8 $(EAFLAGS) \
	|| rm -f ../$(TARGET) $(SYMBOLS)

CLEAN := $(BUILD_DIR) $(CACHE_DIR) $(OBJ_DIR)

.PHONY: clean
clean:
	rm -f $(CLEAN)
	cd $(BIN_DIR)/lyn && make clean

.SECONDARY: $(CLEAN)
