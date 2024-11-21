# Compiler and Toolchain Settings
CC = i686-elf-gcc
AS = i686-elf-as
LD = i686-elf-ld
GRUB_MKRESCUE = grub2-mkrescue

# These are directories
SRC_DIR = src
BUILD_DIR = build
ISO_DIR = isodir
GRUB_DIR = $(ISO_DIR)/boot/grub

# source files and object files.
BOOT_SRC = $(SRC_DIR)/boot/boot.s
KERNEL_SRC = $(SRC_DIR)/kernel/kernel.c
BOOT_OBJ = $(BUILD_DIR)/boot.o
KERNEL_OBJ = $(BUILD_DIR)/kernel.o
BIN = $(BUILD_DIR)/noviceOS.bin
ISO = $(BUILD_DIR)/noviceOS.iso

# Other Files
GRUB_CFG = grub.cfg  # Main GRUB configuration file
LINKER_SCRIPT = $(SRC_DIR)/boot/linker.ld

# Default target (build the ISO)
all: $(ISO)

# Create the boot object file
$(BOOT_OBJ): $(BOOT_SRC)
	$(AS) -o $@ $<

# Create the kernel object file
$(KERNEL_OBJ): $(KERNEL_SRC)
	$(CC) -ffreestanding -c -o $@ $<

# Link the boot and kernel object files to create the OS binary
$(BIN): $(BOOT_OBJ) $(KERNEL_OBJ)
	$(LD) -T $(LINKER_SCRIPT) -o $@ $^

# Create the ISO image from the binary and GRUB configuration
$(ISO): $(BIN) $(GRUB_CFG)
	mkdir -p $(GRUB_DIR) $(ISO_DIR)/boot
	cp $(BIN) $(ISO_DIR)/boot/noviceOS.bin
	cp $(GRUB_CFG) $(GRUB_DIR)  # Copy the GRUB config
	$(GRUB_MKRESCUE) -o $@ $(ISO_DIR)

# Clean up build and ISO directories
clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR)

# Rebuild the entire project
rebuild: clean all

