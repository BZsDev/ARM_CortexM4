
# Target platform 
PLATFORM = NUCLEO_G431KB

TARGET = main
MCU = NUCLEO_G431KB

BUILD_DIR ?= Debug
SRC_DIRS ?= Source

# General flags
GFLAGS = -std=c99 -O0 -g

# Warning flags
WFLAGS = -Wall -Wextra -Wpedantic
		
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
    LINKER_FILE = STM32G431/Ld/STM32G431KBTX_FLASH.ld
else
endif

# Compiler Flags and Defines
ifeq ($(PLATFORM),NUCLEO_G431KB)
    CC = arm-none-eabi-gcc
    LDFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nano.specs -Xlinker --gc-sections -Wl,--no-warn-rwx-segments
    CFLAGS =  --specs=nano.specs -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 $(GFLAGS) $(WFLAGS)
    #CFLAGS = -mcpu=$(CPU) -march=$(ARCH) -mthumb --specs=$(SPECS) $(GFLAGS)
else
    CC = gcc
    LD ?=
    LDFLAGS ?=
    CFLAGS =  $(GFLAGS) $(WFLAGS)
endif

CPPFLAGS = -IInclude -ISTM32G431/Inc -DSTM32G431xx

SOURCES = Source/main.c

OBJS := $(patsubst $(SRC_DIRS)/%.c,$(BUILD_DIR)/%.o,$(SOURCES)) \
        Debug/startup_stm32g431xx.o \
        Debug/system_stm32g4xx.o

OBJS_CLEAN := $(subst /,\,$(OBJS))


$(BUILD_DIR)/%.i: $(SRC_DIRS)/%.c
	$(CC) -I$(INCLUDE) -E $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/startup_stm32g431xx.o: STM32G431/Src/startup_stm32g431xx.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/system_stm32g4xx.o: STM32G431/Src/system_stm32g4xx.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: compile-all
compile-all: $(  )

.PHONY: build
build: all

.PHONY: all
all: $(BUILD_DIR)/$(TARGET).elf

.PHONY: clean
clean:
	rm -f $(OBJS) $(BUILD_DIR)\$(TARGET).elf

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) -T$(LINKER_FILE) $(OBJS) $(LDFLAGS) -o $@
