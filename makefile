# Makefile

# Compiler and assembler
CC = gcc
AS = nasm
LD = ld

# Directories
OBJDIR = build
SRCDIR = src
INCDIR = include

# Files
BOOTLOADER = boot/bootloader.asm
KERNEL_ENTRY = boot/kernel_entry.asm
KERNEL_C = kernel/kernel.c

# Output
OUTPUT = os_image

# Compile and link the bootloader
$(OBJDIR)/bootloader.o: $(BOOTLOADER)
	$(AS) -f elf32 $(BOOTLOADER) -o $(OBJDIR)/bootloader.o

$(OBJDIR)/kernel_entry.o: $(KERNEL_ENTRY)
	$(AS) -f elf32 $(KERNEL_ENTRY) -o $(OBJDIR)/kernel_entry.o

$(OBJDIR)/kernel.o: $(KERNEL_C)
	$(CC) -m32 -ffreestanding -c $(KERNEL_C) -o $(OBJDIR)/kernel.o

# Link the kernel and bootloader
$(OUTPUT): $(OBJDIR)/bootloader.o $(OBJDIR)/kernel_entry.o $(OBJDIR)/kernel.o
	$(LD) -m elf_i386 -o $(OUTPUT) $(OBJDIR)/bootloader.o $(OBJDIR)/kernel_entry.o $(OBJDIR)/kernel.o -T tools/linker.ld

# Build the bootable image (optional)
build: $(OUTPUT)
	dd if=$(OUTPUT) of=boot/boot.img bs=512 seek=4

# Clean up
clean:
	rm -rf $(OBJDIR)/*.o $(OUTPUT)
