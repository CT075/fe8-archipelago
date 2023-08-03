
all: targets

# All subdirectories
dir := src
#include $(dir)/Rules.mk

# The variables `TGT_*` and `CLEAN` get added to by subdirectory makefiles.

.PHONY: targets
targets: $(TGT_EVENTS)
