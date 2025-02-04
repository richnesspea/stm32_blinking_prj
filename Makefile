# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
GDB = gdb-multiarch
OPENOCD = openocd
STFLASH = /usr/bin/st-flash  # Dùng đường dẫn tuyệt đối
RM = rm -rf

# Ensure Make runs in Bash
SHELL := /bin/bash

# Directories
INCLUDE_DIRS = Core/Inc \
               Drivers/Inc

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Files
TARGET = $(BIN_DIR)/stm32_blinking

# Source files
SOURCES = Core/Src/main.c \
          Drivers/Src/GPIO.c \
          Startup/stm32_startup.c

OBJECT_NAMES = $(SOURCES:.c=.o)
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECT_NAMES))

# Flags
MCU = cortex-m4
WFLAGS = -Wall -Wextra -Werror -Wshadow
CFLAGS = -mcpu=$(MCU) -mthumb $(WFLAGS) $(addprefix -I,$(INCLUDE_DIRS)) -O0 -g3 -std=gnu11
LDFLAGS = -mcpu=$(MCU) -mthumb -T Linker/stm_ls.ld -specs=nosys.specs -specs=nano.specs -Wl,--gc-sections -lm

# Build
## Linking
$(TARGET).elf: $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

## Compiling
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

## Generate binary file
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Show size
size: $(TARGET).elf
	$(SIZE) $<

# Phonies
.PHONY: all clean flash debug openocd gdb

all: $(TARGET).bin

clean:
	$(RM) $(BUILD_DIR)

flash: $(TARGET).bin
	@echo "Checking for st-flash..."
	@if ! which st-flash > /dev/null; then \
		echo "Error: st-flash not found! Install with: sudo apt install stlink-tools"; \
		exit 1; \
	fi
	@echo "Using st-flash from: $$(${STFLASH} --version)"
	@echo "Flashing firmware..."
	$(STFLASH) write $< 0x08000000

# Debugging
debug: $(TARGET).elf openocd gdb

openocd:
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f4x.cfg &

gdb:
	$(GDB) $(TARGET).elf -ex "target remote :3333"
