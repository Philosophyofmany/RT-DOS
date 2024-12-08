# Compiler and linker settings
CC = gcc
LD = ld
NASM = nasm

# Compiler flags
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra
LDFLAGS = -m elf_i386

# Output files
KERNEL_BIN = kernel.bin
ISO = mykernel.iso

# Source files
SOURCES = boot.o kernel.o screen.o

# Default target
all: $(ISO)

# Link the kernel
$(KERNEL_BIN): $(SOURCES) linker.ld
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $(SOURCES)

# Compile assembly file
boot.o: boot.s
	$(NASM) -f elf32 $< -o $@

# Compile kernel.c
kernel.o: kernel.c screen.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile screen.c
screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c $< -o $@

# Create bootable ISO
$(ISO): $(KERNEL_BIN) grub.cfg
	mkdir -p iso/boot/grub
	cp $(KERNEL_BIN) iso/boot/
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) iso

# Clean up
clean:
	rm -rf *.o $(KERNEL_BIN) $(ISO) iso

# QEMU run target
run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)
