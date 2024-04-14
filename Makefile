
# Target platform 
PLATFORM = NUCLEO_G431KB

TARGET = main
MCU = NUCLEO_G431KB

BUILD_DIR ?= Debug
SRC_DIRS ?= Source

# General flags
GFLAGS = -Wall \
        -Werror \
        -g \
        -O0 \
        -std=c89
		
# Architectures Specific Flags
ifeq ($(PLATFORM),NUCLEO_G431KB)
    CPU = cortex-m4
    ARCH = armv7e-m
    SPECS = nosys.specs
    FLOAT = hard
    FPU = fpv4-sp-d16
endif

# Platform Specific Flags
ifeq ($(PLATFORM),NUCLEO_G431KB)
    LINKER_FILE = STM32G431KBTX_FLASH.ld
else
endif

# Compiler Flags and Defines
ifeq ($(PLATFORM),NUCLEO_G431KB)
    CC = arm-none-eabi-gcc
    LD = arm-none-eabi-ld
    LDFLAGS = -Wl,-Map=$(BUILD_DIR)/$(TARGET).map -T $(LINKER_FILE)
    CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 $(GFLAGS)
    CPPFLAGS = -I/Include
    #CFLAGS = -mcpu=$(CPU) -march=$(ARCH) -mthumb --specs=$(SPECS) $(GFLAGS)
else
    CC = gcc
    LD ?=
    LDFLAGS ?=
    CFLAGS = $(GFLAGS)
endif

SOURCES = Source/main.c

OBJS := $(patsubst $(SRC_DIRS)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
OBJS_CLEAN := $(subst /,\,$(OBJS))


$(BUILD_DIR)/%.i: $(SRC_DIRS)/%.c
	$(CC) -I$(INCLUDE) -E $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/startup_stm32g431kbtx.o: $(SRC_DIRS)/startup_stm32g431kbtx.s
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: compile-all
compile-all: $(OBJS)

.PHONY: build
build: all

.PHONY: all
all: $(BUILD_DIR)/$(TARGET).out

.PHONY: clean
clean:
	del /Q $(OBJS_CLEAN) $(BUILD_DIR)\$(TARGET).out

$(BUILD_DIR)/$(TARGET).out: $(OBJS) Source/startup_stm32g431kbtx.o
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@
