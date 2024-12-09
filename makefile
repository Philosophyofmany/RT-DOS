# Set cross-compiler toolchain paths
CC = /home/lman/x86_64-elf/bin/x86_64-elf-gcc          # Cross-compiler for 64-bit x86 target
LD = /home/lman/x86_64-elf/bin/x86_64-elf-ld            # Cross-linker for 64-bit x86 target
NASM = nasm                                           # Assembly compiler

# Paths to the Newlib and include directories
NEWLIB_DIR = /home/lman/x86_64-elf/newlib-install
LIBRARY_PATH = $(NEWLIB_DIR)/x86_64-elf/lib
INCLUDE_PATH = $(NEWLIB_DIR)/include

# Compiler flags for 64-bit target
CFLAGS = -m64 -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -I$(INCLUDE_PATH)

# Linker flags for 64-bit target
LDFLAGS = -m elf_x86_64 -L$(LIBRARY_PATH) -lc -T linker.ld

# Output files
KERNEL_BIN = kernel.bin
ISO = mykernel.iso

# Source files
SOURCES = bootloader/boot.o kernel/kernel.o kernel/screen/screen.o kernel/shell/shell.o kernel/keyboard/keyboard.o kernel/interrupts/interrupt.o kernel/interrupts/isr.o newlib/syscalls.o

# Default target
all: $(ISO)

# Link the kernel
$(KERNEL_BIN): $(SOURCES) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(SOURCES)

# Compile assembly files
bootloader/boot.o: bootloader/boot.s
	$(NASM) -f elf64 $< -o $@

# Compile C kernel files
kernel/kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C screen
kernel/screen/screen.o: kernel/screen/screen.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C shell
kernel/shell/shell.o: kernel/shell/shell.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C keyboard
kernel/keyboard/keyboard.o: kernel/keyboard/keyboard.c kernel/keyboard_map.h
	$(CC) $(CFLAGS) -c $< -o $@

# Compile interrupt handling functions
kernel/interrupts/interrupt.o: kernel/interrupts/interrupt.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile ISR functions
kernel/interrupts/isr.o: kernel/interrupts/isr.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile syscalls for newlib
newlib/syscalls.o: newlib/syscalls.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create bootable ISO
$(ISO): $(KERNEL_BIN) bootloader/grub.cfg
	mkdir -p iso/boot/grub
	cp $(KERNEL_BIN) iso/boot/
	cp bootloader/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) iso

# Clean up
clean:
	rm -rf *.o $(KERNEL_BIN) $(ISO) iso

# QEMU run target
run: $(ISO)
	qemu-system-x86_64 -cdrom $(ISO) -m 512M -boot d -enable-kvm
