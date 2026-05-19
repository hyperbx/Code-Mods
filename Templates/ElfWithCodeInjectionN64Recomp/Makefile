TARGET_NAME    := mod
TARGET_DIR     := bin
TARGET_PATH    := $(TARGET_DIR)/$(TARGET_NAME).elf
TARGET_INFO    := $(TARGET_NAME).toml

INT_DIR        := obj

DECOMP_DIR     := ../../Dependencies/mm
TEMPLATE_DIR   := ../../Dependencies/MMRecompModTemplate
RECOMP_DIR     := ../../Dependencies/N64Recomp
TOOLS_ROOT_DIR := ../../Tools

ENV_SETUP_PATH := $(TOOLS_ROOT_DIR)/Setup.py
ENV_PLATFORM   := Windows
ENV_ARCH       := x64

SOURCES  := *.c

INCLUDES := $(TEMPLATE_DIR)/include \
			$(TEMPLATE_DIR)/include/dummy_headers \
			$(DECOMP_DIR)/include \
			$(DECOMP_DIR)/src \
			$(DECOMP_DIR)/extracted/n64-us

INCLUDES_AFTER := include/libc $(DECOMP_DIR)/include/libc

ifeq ($(OS), Windows_NT)
	ENV_PLATFORM := Windows
else ifeq ($(shell uname), Darwin)
	ENV_PLATFORM := macOS
else
	ENV_PLATFORM := Linux
endif

ifeq ($(OS), Windows_NT)
    ifeq ($(PROCESSOR_ARCHITECTURE), ARM64)
        ENV_ARCH := arm64
	else
        ENV_ARCH := x64
    endif
else
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P), x86_64)
        ENV_ARCH := x64
    else ifneq ($(filter arm%,$(UNAME_P)),)
        ENV_ARCH := arm64
    endif
endif

TOOLS_DIR := $(TOOLS_ROOT_DIR)/$(ENV_PLATFORM)/$(ENV_ARCH)
CC := $(TOOLS_DIR)/nrs_bin/clang
LD := $(TOOLS_DIR)/nrs_bin/ld.lld

LD_SCRIPT  := $(TARGET_NAME).ld
ARCH_FLAGS := -target mips -mips2 -mabi=32 -O2 -G0 -mno-abicalls -mno-odd-spreg -mno-check-zero-division \
              -fomit-frame-pointer -ffast-math -fno-unsafe-math-optimizations -fno-builtin-memset
WARN_FLAGS := -Wall -Wextra -Wno-incompatible-library-redeclaration -Wno-unused-parameter -Wno-unknown-pragmas -Wno-unused-variable \
              -Wno-missing-braces -Wno-unsupported-floating-point-opt -Werror=section
C_FLAGS    := $(ARCH_FLAGS) $(WARN_FLAGS) -D_LANGUAGE_C -nostdinc -ffunction-sections
CPP_FLAGS  := -DMIPS -DF3DEX_GBI_2 -DF3DEX_GBI_PL -DGBI_DOWHILE $(foreach dir,$(INCLUDES),-I $(dir)) $(foreach dir,$(INCLUDES_AFTER),-idirafter $(dir))
LD_FLAGS   := -nostdlib -T $(LD_SCRIPT) -Map $(TARGET_DIR)/$(TARGET_NAME).map --unresolved-symbols=ignore-all --emit-relocs -e 0 --no-nmagic -gc-sections

C_SRCS := $(foreach src,$(SOURCES),$(wildcard $(src)))
C_OBJS := $(addprefix $(INT_DIR)/,$(C_SRCS:.c=.o))
C_DEPS := $(addprefix $(INT_DIR)/,$(C_SRCS:.c=.d))

ALL_OBJS := $(C_OBJS)
ALL_DEPS := $(C_DEPS)
INT_DIRS := $(sort $(dir $(ALL_OBJS)))

all: setup $(TARGET_PATH) package

setup:
	python $(TOOLS_ROOT_DIR)/Setup.py $(ENV_PLATFORM) $(ENV_ARCH)

$(TARGET_PATH): $(ALL_OBJS) $(LD_SCRIPT) | $(INT_DIR)
	$(LD) $(ALL_OBJS) $(LD_FLAGS) -o $@

$(INT_DIR) $(INT_DIRS):
ifeq ($(OS), Windows_NT)
	if not exist "$(subst /,\,$(TARGET_DIR))" mkdir "$(subst /,\,$(TARGET_DIR))"
	if not exist "$(subst /,\,$@)" mkdir "$(subst /,\,$@)"
else
	mkdir -p $(TARGET_DIR)
	mkdir -p $@
endif

$(C_OBJS): $(INT_DIR)/%.o : %.c | $(INT_DIRS)
	$(CC) $(C_FLAGS) $(CPP_FLAGS) $< -MMD -MF $(@:.o=.d) -c -o $@

clean:
ifeq ($(OS), Windows_NT)
	if exist $(TARGET_DIR) rmdir /S /Q $(TARGET_DIR)
	if exist $(INT_DIR) rmdir /S /Q $(INT_DIR)
else
	rm -rf $(TARGET_DIR)
	rm -rf $(INT_DIR)
endif

-include $(ALL_DEPS)

.PHONY: clean all

package:
	$(TOOLS_DIR)/nrs_bin/RecompModTool $(TARGET_INFO) $(TARGET_DIR)