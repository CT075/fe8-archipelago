# We need $(CC) to build things in bin/, so we use a modified version of the
# devkitARM includefile to export a different set of compiler variables.
#
# CR cam: fix this
include $(VENDOR_DIR)/devkitARM_base_tools.mk

CACHE_DIR := .cache
$(shell mkdir -p $(CACHE_DIR) > /dev/null)
OBJ_DIR := obj
$(shell mkdir -p $(OBJ_DIR) > /dev/null)

# CR cam: we could generate this instead of vendoring it
FE8_SYMBOLS := $(VENDOR_DIR)/fe8-symbols.s

LYN_REFERENCE := $(OBJ_DIR)/fe8-reference.o

%.lyn.event: %.o $(LYN_REFERENCE) $(LYN)
	$(LYN) $< $(LYN_REFERENCE) > $@

%.dmp: %.o
	$(OBJCOPY) -S $< -O binary $@

INCLUDE_DIRS := include $(FIREEMBLEM8U)/include
INCFLAGS := $(foreach dir, $(INCLUDE_DIRS), -I "$(dir)")

ARCH := -mcpu=arm7tdmi -mthumb -mthumb-interwork
CFLAGS := $(ARCH) $(INCFLAGS) -Wall -Os -mtune=arm7tdmi -ffreestanding -mlong-calls
ASFLAGS := $(ARCH) $(INCFLAGS)

CDEPFLAGS = -MMD -MT "$*.o" -MT "$*.asm" -MF "$(CACHE_DIR)/$(notdir $*).d" -MP
SDEPFLAGS = --MD "$(CACHE_DIR)/$(notdir $*).d"

$(LYN_REFERENCE): vendor/fe8-symbols.s
	$(ARM_AS) $(ASFLAGS) $(SDEPFLAGS) $< -o $@

%.o: %.s
	$(ARM_AS) $(ASFLAGS) $(SDEPFLAGS) -I $(dir $<) $< -o $@

%.o: %.c
	$(ARM_CC) $(CFLAGS) $(CDEPFLAGS) -g -c $< -o $@

%.asm: %.c
	$(ARM_CC) $(CFLAGS) $(CDEPFLAGS) -S $< -o $@ -fverbose-asm

.PRECIOUS: %.o;

-include $(wildcard $(CACHE_DIR)/*.d)
