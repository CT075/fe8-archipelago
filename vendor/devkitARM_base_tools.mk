#---------------------------------------------------------------------------------
# make sure we have bash shell
#---------------------------------------------------------------------------------
export SHELL := /usr/bin/env bash
#---------------------------------------------------------------------------------
# path to tools
#---------------------------------------------------------------------------------
DEVKITPATH=$(shell echo "$(DEVKITPRO)" | sed -e 's/^\([a-zA-Z]\):/\/\1/')

export PATH	:=	$(DEVKITPATH)/tools/bin:$(DEVKITPATH)/devkitARM/bin:$(PATH)

#---------------------------------------------------------------------------------
# the prefix on the compiler executables
#---------------------------------------------------------------------------------
PREFIX		:=	arm-none-eabi-

export ARM_CC	:=	$(PREFIX)gcc
export ARM_CXX	:=	$(PREFIX)g++
export ARM_AS	:=	$(PREFIX)as
export ARM_AR	:=	$(PREFIX)gcc-ar
export ARM_OBJCOPY	:=	$(PREFIX)objcopy
export ARM_STRIP	:=	$(PREFIX)strip
export ARM_NM	:=	$(PREFIX)gcc-nm
export ARM_RANLIB	:=	$(PREFIX)gcc-ranlib

ISVC=$(or $(VCBUILDHELPER_COMMAND),$(MSBUILDEXTENSIONSPATH32),$(MSBUILDEXTENSIONSPATH))

ifneq (,$(ISVC))
	ERROR_FILTER	:=	2>&1 | sed -e 's/\(.[a-zA-Z]\+\):\([0-9]\+\):/\1(\2):/g'
endif

#---------------------------------------------------------------------------------
# allow seeing compiler command lines with make V=1 (similar to autotools' silent)
#---------------------------------------------------------------------------------
ifeq ($(V),1)
    SILENTMSG := @true
    SILENTCMD :=
else
    SILENTMSG := @echo
    SILENTCMD := @
endif

#---------------------------------------------------------------------------------
# canned command sequence for binary data
#---------------------------------------------------------------------------------
define bin2o
    $(SILENTCMD)mkdir -p $(dir $@)
    $(SILENTCMD)bin2s -a 4 -H $(dir $@)`(echo $(<F) | tr . _)`.h $< > $(@D)/$(<F).s
	$(SILENTCMD)$(CC) -x assembler-with-cpp $(CPPFLAGS) $(ASFLAGS) -c $(@D)/$(<F).s -o $(@D)/$(<F).o
endef


