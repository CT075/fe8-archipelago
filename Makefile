# With advice from http://sites.e-advies.nl/nonrecursive-make.html

VENDOR_DIR := vendor
BIN_DIR := bin

BUILD_DIR := _build

.DEFAULT_GOAL := all

ROOT := $(CURDIR)

dummy%:
	@:

### Standard parts

include Tools.mk
include Wizardry.mk
include Rules.mk
