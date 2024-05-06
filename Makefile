
# Target platform 
PLATFORM = NUCLEO_G431KB

TARGET = main
MCU = NUCLEO_G431KB

BUILD_DIR ?= Debug
SRC_DIRS ?= Source

# General flags
GFLAGS = -std=c99 -O0 -g

# Warning flags
WFLAGS = -ansi -pedantic -fsigned-char -ffunction-sections -fdata-sections -fstrict-flex-arrays=3 -WNSObject-attribute -Wabsolute-value -Waddress-of-packed-member -Waggregate-return -Waggressive-loop-optimizations -Wall -Walloc-zero -Walloca -Wanalyzer-allocation-size -Wanalyzer-deref-before-check -Wanalyzer-double-fclose -Wanalyzer-double-free -Wanalyzer-exposure-through-output-file -Wanalyzer-exposure-through-uninit-copy -Wanalyzer-fd-access-mode-mismatch -Wanalyzer-fd-double-close -Wanalyzer-fd-leak -Wanalyzer-fd-phase-mismatch -Wanalyzer-fd-type-mismatch -Wanalyzer-fd-use-after-close -Wanalyzer-fd-use-without-check -Wanalyzer-file-leak -Wanalyzer-free-of-non-heap -Wanalyzer-imprecise-fp-arithmetic -Wanalyzer-infinite-recursion -Wanalyzer-jump-through-null -Wanalyzer-malloc-leak -Wanalyzer-mismatching-deallocation -Wanalyzer-null-argument -Wanalyzer-null-dereference -Wanalyzer-out-of-bounds -Wanalyzer-possible-null-argument -Wanalyzer-possible-null-dereference -Wanalyzer-putenv-of-auto-var -Wanalyzer-shift-count-negative -Wanalyzer-shift-count-overflow -Wanalyzer-stale-setjmp-buffer -Wanalyzer-tainted-allocation-size -Wanalyzer-tainted-array-index -Wanalyzer-tainted-assertion -Wanalyzer-tainted-divisor -Wanalyzer-tainted-offset -Wanalyzer-tainted-size -Wanalyzer-too-complex -Wanalyzer-unsafe-call-within-signal-handler -Wanalyzer-use-after-free -Wanalyzer-use-of-pointer-in-stale-stack-frame -Wanalyzer-use-of-uninitialized-value -Wanalyzer-va-arg-type-mismatch -Wanalyzer-va-list-exhausted -Wanalyzer-va-list-leak -Wanalyzer-va-list-use-after-va-end -Wanalyzer-write-to-const -Wanalyzer-write-to-string-literal -Warith-conversion -Wattribute-warning -Wattributes -Wbad-function-cast -Wbuiltin-declaration-mismatch -Wbuiltin-macro-redefined -Wc++-compat -Wc11-c2x-compat -Wc90-c99-compat -Wc99-c11-compat -Wcannot-profile -Wcast-qual -Wcomplain-wrong-lang -Wconversion -Wcoverage-invalid-line-number -Wcoverage-mismatch -Wcpp -Wdangling-else -Wdate-time -Wdeclaration-after-statement -Wdesignated-init -Wdisabled-optimization -Wdiscarded-array-qualifiers -Wdiscarded-qualifiers -Wdiv-by-zero -Wdouble-promotion -Wduplicated-branches -Wduplicated-cond -Wendif-labels -Wexpansion-to-defined -Wextra -Wfloat-conversion -Wfloat-equal -Wformat-contains-nul -Wformat-diag -Wformat-extra-args -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat-y2k -Wformat-zero-length -Wframe-address -Wfree-nonheap-object -Whsa -Wif-not-aligned -Wignored-attributes -Wincompatible-pointer-types -Winfinite-recursion -Winline -Wint-conversion -Wint-to-pointer-cast -Winvalid-memory-model -Winvalid-pch -Winvalid-utf8 -Wjump-misses-init -Wlogical-op -Wlong-long -Wlto-type-mismatch -Wmissing-declarations -Wmissing-include-dirs -Wmissing-profile -Wmissing-prototypes -Wmultichar -Wnested-externs -Wnull-dereference -Wodr -Wold-style-definition -Wopenacc-parallelism -Woverflow -Woverlength-strings -Woverride-init-side-effects -Wpacked -Wpacked-bitfield-compat -Wpacked-not-aligned -Wpadded -Wpedantic -Wpointer-arith -Wpointer-compare -Wpointer-to-int-cast -Wpragmas -Wprio-ctor-dtor -Wredundant-decls -Wreturn-local-addr -Wscalar-storage-order -Wshift-count-negative -Wshift-count-overflow -Wsign-conversion -Wsizeof-array-argument -Wstack-protector -Wstrict-flex-arrays -Wstrict-prototypes -Wstringop-overread -Wstringop-truncation -Wsuggest-final-methods -Wsuggest-final-types -Wswitch-bool -Wswitch-default -Wswitch-enum -Wswitch-outside-range -Wswitch-unreachable -Wsync-nand -Wtrampolines -Wtrivial-auto-var-init -Wtsan -Wundef -Wunicode -Wunreachable-code -Wunsafe-loop-optimizations -Wunsuffixed-float-constants -Wunused -Wunused-but-set-variable -Wunused-local-typedefs -Wunused-macros -Wunused-result -Wvarargs -Wvariadic-macros -Wvector-operation-performance -Wvla -Wxor-used-as-pow -Warray-bounds=2 -Warray-parameter=2 -Wattribute-alias=2 -Wbidi-chars -Wcast-align=strict -Wcomments -Wdangling-pointer=2 -Wdeprecated -Wdeprecated-declarations -Werror-implicit-function-declaration -Wformat-overflow=2 -Wformat-truncation=2 -Wformat=2 -Wimplicit-fallthrough=4 -Wnormalized=nfkc -Wshadow-compatible-local -Wshadow-local -Wshadow=compatible-local -Wshadow=global -Wshadow=local -Wshift-overflow=2 -Wstrict-aliasing=3 -Wstrict-overflow=5 -Wstringop-overflow=4 -Wunused-const-variable=2 -Wuse-after-free=3 -Wwrite-strings
		
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

SOURCES := Source/main.c \
           Source/GPIO.c \
           Source/Test.c

DEPS := $(patsubst $(SRC_DIRS)/%.c,$(BUILD_DIR)/%.d,$(SOURCES))

OBJS := $(patsubst $(SRC_DIRS)/%.c,$(BUILD_DIR)/%.o,$(SOURCES)) \
        Debug/startup_stm32g431xx.o \
        Debug/system_stm32g4xx.o

CLEAN_FILES := $(subst /,\,$(OBJS)) $(subst /,\,$(DEPS))

$(BUILD_DIR)/%.d: $(SRC_DIRS)/%.c
	$(CC) -MM -MT $(patsubst %.d,%.o,$@) -MT $@ $(CPPFLAGS) $< > $@
    

$(BUILD_DIR)/%.i: $(SRC_DIRS)/%.c
	$(CC) -I$(INCLUDE) -E $< -o $@

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/startup_stm32g431xx.o: STM32G431/Src/startup_stm32g431xx.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/system_stm32g4xx.o: STM32G431/Src/system_stm32g4xx.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

EXTLISTCREATOR ?= arm-none-eabi-objdump

.PHONY: rebuild
ReBuild: clean build rebuild_message

.PHONY: build
build: $(BUILD_DIR)/$(TARGET).elf build_message

.PHONY: build_message
build_message:
	@echo Build Done!

.PHONY: rebuild_message
rebuild_message:
	@echo ReBuild Done!

.PHONY: clean_message
clean_message:
	@echo Clean Done!

.PHONY: clean
clean: clean_all clean_message

.PHONY: clean_all
clean_all:
	@del /F /Q $(CLEAN_FILES) $(BUILD_DIR)\$(TARGET).elf $(BUILD_DIR)\$(TARGET).lst

#$(BUILD_DIR)\$(TARGET).map

$(BUILD_DIR)/$(TARGET).elf: $(DEPS) $(OBJS)
	$(CC) -T$(LINKER_FILE) $(OBJS) $(LDFLAGS) -o $@
	$(EXTLISTCREATOR) --source --all-headers --demangle --disassemble --line-numbers --reloc --syms --wide $@ > $(BUILD_DIR)/$(TARGET).lst