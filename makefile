# Directory structure
BUILD_DIR = src/build
SRC_DIR = src

# Tools
NASM = nasm
GCC = gcc
LD = ld
MKFS_FAT = mkfs.fat
DD = dd

# File names
BOOTLOADER_SRC = $(SRC_DIR)/boot/bootloader.asm
KERNEL_SRC = $(SRC_DIR)/kernel/kernel.asm
KERNEL_C_SRC = $(SRC_DIR)/kernel/kernel.c
KERNEL_OBJ = $(BUILD_DIR)/kernel.o
KERNEL_C_OBJ = $(BUILD_DIR)/kernel_c.o
BOOTLOADER_BIN = $(BUILD_DIR)/bootloader.bin
KERNEL_BIN = $(BUILD_DIR)/kernel.bin
FLP_IMG = $(BUILD_DIR)/main_floppy.img

# Build bootloader and kernel
all: $(FLP_IMG)

$(BOOTLOADER_BIN): $(BOOTLOADER_SRC)
	$(NASM) -f bin -o $(BOOTLOADER_BIN) $(BOOTLOADER_SRC)

$(KERNEL_OBJ): $(KERNEL_SRC)
	$(NASM) -f elf32 -o $(KERNEL_OBJ) $(KERNEL_SRC)

$(KERNEL_C_OBJ): $(KERNEL_C_SRC)
	$(GCC) -ffreestanding -nostdlib -m32 -Wall -Wextra -c $(KERNEL_C_SRC) -o $(KERNEL_C_OBJ)

$(KERNEL_BIN): $(KERNEL_OBJ) $(KERNEL_C_OBJ)
	$(LD) -m elf_i386 -T $(SRC_DIR)/kernel/kernel.ld -o $(KERNEL_BIN) $(KERNEL_OBJ) $(KERNEL_C_OBJ)

$(FLP_IMG): $(BOOTLOADER_BIN) $(KERNEL_BIN)
	# Remove old floppy image if it exists
	rm -f $(FLP_IMG)

	# Create an empty floppy image with 2880 sectors (1.44MB floppy)
	$(DD) if=/dev/zero of=$(FLP_IMG) bs=512 count=2880

	# Format the image as FAT12
	$(MKFS_FAT) -F 12 -n "NBOS" $(FLP_IMG)

	# Copy the bootloader and kernel into the floppy image
	$(DD) if=$(BOOTLOADER_BIN) of=$(FLP_IMG) conv=notrunc bs=512 seek=0
	$(DD) if=$(KERNEL_BIN) of=$(FLP_IMG) conv=notrunc bs=512 seek=4

clean:
	rm -f $(BOOTLOADER_BIN) $(KERNEL_BIN) $(KERNEL_OBJ) $(KERNEL_C_OBJ) $(FLP_IMG)
