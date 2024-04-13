
# Target platform 
PLATFORM = HOST

TARGET = main
MCU = STM32F103C8T6

BUILD_DIR ?= Debug
SRC_DIRS ?= Source

# General flags
GFLAGS = -Wall \
        -Werror \
        -g \
        -O0 \
        -std=c89
		
# Architectures Specific Flags
ifeq ($(PLATFORM),STM32F103C8T6)
    CPU = cortex-m3
    ARCH = armv7e-m
    SPECS = nosys.specs
    FLOAT = hard
    FPU = fpv4-sp-d16
endif

# Platform Specific Flags
ifeq ($(PLATFORM),MSP432)
    LINKER_FILE = msp432p401r.lds
else
endif

# Compiler Flags and Defines
ifeq ($(PLATFORM),STM32F103C8T6)
    CC = arm-none-eabi-gcc
    LD = arm-none-eabi-ld
    LDFLAGS = -Wl,-Map=$(BUILD_DIR)/$(TARGET).map -T $(LINKER_FILE)
    CFLAGS = -mcpu=$(CPU) -march=$(ARCH) -mthumb --specs=$(SPECS) $(GFLAGS)
else
    CC = gcc
    LD ?=
    LDFLAGS ?=
    CFLAGS = $(GFLAGS)
endif

SOURCES = Source\main.c

OBJS := $(patsubst $(SRC_DIRS)\\%.c,$(BUILD_DIR)\\%.o,$(SOURCES))

$(BUILD_DIR)\\%.o: $(SRC_DIRS)\\%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


.PHONY: compile-all
compile-all: $(OBJS)

.PHONY: build
build: all

.PHONY: all
all: $(BUILD_DIR)\$(TARGET).out

.PHONY: clean
clean:
	del /Q $(OBJS) $(BUILD_DIR)\$(TARGET).out

$(BUILD_DIR)\$(TARGET).out: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@