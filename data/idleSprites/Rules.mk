sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

$(d)/gfx/%.dmp: $(d)/gfx/%.png
	$(PNG2DMP) $< --lz77 > $@

MAP_SPRITE_PNGS := $(shell find $(d)/gfx -name '*.png')

$(d)/main.event: $(foreach t,$(MAP_SPRITE_PNGS),$(t:.png=.dmp))

EVENTS_$(d) := $(d)/main.event

EVENTS := $(EVENTS) $(EVENTS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
