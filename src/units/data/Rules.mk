sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)

d := $(dirstack_$(sp))
sp := $(basename $(sp))
