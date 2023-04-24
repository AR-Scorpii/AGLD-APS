################################################################################
# makefile script to compile the STC8H project with SDCC compiler
# 
# available parameters: 
# target  - name of the main (master, origin, etc.) c file, as well as the 
#			final output. "main" is taken by default. 
# v		  - terminal output level (0 - quiet, 1 - default, 2 - all). 
# 
# This file is modified from: 
# https://github.com/latelee/Makefile_templet/blob/master/stm32_project/Makefile
# which is licensed by Apache License 2.0 (available at: 
# http://www.apache.org/licenses/LICENSE-2.0)
################################################################################

## user controlled variables
target := main
v := 1
mode := release

## definitions
# destination
BUILD_DIR = build

# command
CC	:= sdcc
HEX	:= packihx
CFLAGS += --iram-size 256 --xram-size 4096 --code-size 65536
CFLAGS += -mmcs51 --model-medium
# CFLAGS += -mmcs51 --model-large

ifeq ($(mode), debug)
	CFLAGS += -D _DEBUG
endif

Q	:= @
E	:= @echo
ifeq ($(v), 0)
	Q	:= @
	E	:= @true
else 
	ifeq ($(v), 2)
		Q	:= 
		E	:= @echo
	endif
endif

# source files
# C_SOURCES =  $(shell find .\ -name '*.c')
# C_SOURCES = $(wildcard *.c)
SUBDIR = * */* */*/* */*/*/*
C_SOURCES = $(wildcard *.c $(foreach folder, $(SUBDIR), $(folder)/*.c))
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.rel)))
vpath %.c $(sort $(dir $(C_SOURCES)))

.PHONY: all cleanhex clean test

## default action: build all
all: $(target).hex
	$(E) "================ ALL DONE! ================"

## create dir
$(BUILD_DIR):
	$(Q)mkdir -p $@

## compiling
# compile and assemble (but not link) to rel file
$(BUILD_DIR)/%.rel: %.c Makefile | $(BUILD_DIR)
	$(E) "Compiling:" $(basename $(notdir $@)).c
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

# link to ihx file
$(BUILD_DIR)/$(target).ihx: $(OBJECTS) Makefile
	$(E) "Generating:" $(notdir $@)
	$(Q)$(CC) $(CFLAGS) $(OBJECTS) -o $@

# pack to hex file
$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.ihx | $(BUILD_DIR)
	$(E) "Generating:" $(notdir $@)
	$(Q)$(HEX) $< > $@

# move generated hex file to root dir
$(target).hex: $(BUILD_DIR)/$(target).hex
	$(Q)mv $< .

## clean
# remove hex file only
cleanhex: 
	-$(Q)rm -rf $(target).hex

# remove all
clean: cleanhex
	-$(Q)rm -rf $(BUILD_DIR)

test:
	$(E) "Files:" $(C_SOURCES)