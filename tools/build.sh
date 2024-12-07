#!/bin/bash

# Compile bootloader
nasm -f bin -o build/bootloader.bin boot/bootloader.asm

# Compile kernel
gcc -ffreestanding -c kernel/kernel.c -o build/kernel.o
gcc -ffreestanding -c kernel/kernel_entry.asm -o build/kernel_entry.o

# Link kernel and bootloader
ld -T tools/linker.ld -o build/bootloader_kernel.bin build/bootloader.bin build/kernel.o build/kernel_entry.o

# Create bootable ISO
grub-mkrescue -o build/os_image.iso --config=tools/grub.cfg build/

# Optional: Run in QEMU
# qemu-system-i386 -cdrom build/os_image.iso
