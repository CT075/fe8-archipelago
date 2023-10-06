sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

$(d)/gfx/%.dmp: $(d)/gfx/%.png
	$(PNG2DMP) $< --lz77 > $@

$(d)/main.event: $(d)/gfx/*.dmp

EVENTS_$(d) := $(d)/main.event

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
