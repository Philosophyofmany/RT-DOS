# Compiler and assembler
CC = gcc
AS = nasm
LD = ld

# Directories
OBJDIR = build
SRCDIR = src
INCDIR = include
BOOTDIR = boot
KERNELDIR = kernel
OUTPUTDIR = .

# Files
BOOTLOADER = $(BOOTDIR)/bootloader.asm
KERNEL_ENTRY = $(BOOTDIR)/kernel_entry.asm
KERNEL_C = $(KERNELDIR)/kernel.c

# Output
OUTPUT = $(OUTPUTDIR)/os_image
BOOT_IMG = $(BOOTDIR)/boot.img

# Linker flags to disable executable stack
LD_FLAGS = -z noexecstack

# Compile and link the bootloader
$(OBJDIR)/bootloader.o: $(BOOTLOADER)
	$(AS) -f elf32 $(BOOTLOADER) -o $(OBJDIR)/bootloader.o

$(OBJDIR)/kernel_entry.o: $(KERNEL_ENTRY)
	$(AS) -f elf32 $(KERNEL_ENTRY) -o $(OBJDIR)/kernel_entry.o

$(OBJDIR)/kernel.o: $(KERNEL_C)
	$(CC) -m32 -ffreestanding -c $(KERNEL_C) -o $(OBJDIR)/kernel.o

# Link the kernel and bootloader
$(OUTPUT): $(OBJDIR)/bootloader.o $(OBJDIR)/kernel_entry.o $(OBJDIR)/kernel.o
	$(LD) $(LD_FLAGS) -m elf_i386 -o $(OUTPUT) $(OBJDIR)/bootloader.o $(OBJDIR)/kernel_entry.o $(OBJDIR)/kernel.o -T tools/linker.ld

# Build the bootable image
build: $(OUTPUT)
	# Ensure the boot.img file is clean or created
	@echo "Creating bootable image..."
	dd if=$(OUTPUT) of=$(BOOT_IMG) bs=512 seek=4

# Clean up
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJDIR)/*.o $(OUTPUT) $(BOOT_IMG)

.PHONY: build clean
