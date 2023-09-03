sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

# CR cam: should this live here?
CLIB_REFERENCE := FE8U-20190316
CLIB_LYN_REFERENCE_SYMS := $(VENDOR_DIR)/CLib/reference/$(CLIB_REFERENCE).s
CLIB_LYN_REFERENCE := $(BUILD_DIR)/$(CLIB_REFERENCE).o

MODULES_$(d) := MSCore MSSizeHook MSBWLHook MSaFuncs MSuFuncs

EVENTS_$(d) := $(foreach mod, $(MODULES_$(d)), $(d)/$(mod).lyn.event)

$(CLIB_LYN_REFERENCE): $(CLIB_LYN_REFERENCE_SYMS)
	$(ARM_AS) $(ASFLAGS) $(SDEPFLAGS) $< -o $@

$(d)/%.lyn.event: $(d)/%.o $(LYN) $(CLIB_LYN_REFERENCE)
	$(LYN) $< $(CLIB_LYN_REFERENCE) > $@

EVENTS := $(EVENTS) $(EVENTS_$(d))
CLEAN := $(CLEAN) $(d)/*.o

d := $(dirstack_$(sp))
sp := $(basename $(sp))
