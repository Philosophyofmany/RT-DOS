; bootloader.asm
[global _start]

section .text
_start:
    ; Disable interrupts
    cli

    ; Set up the GDT (Global Descriptor Table)
    ; Set up a simple 32-bit protected mode

    ; Load the kernel into memory
    ; Assuming the kernel is located at 0x10000
    mov si, 0x10000  ; Kernel load address

    ; Read the kernel from disk (BIOS interrupt)
    ; (This is a simple example, use BIOS services to load sectors)
    mov ah, 0x02      ; BIOS read sector function
    mov al, 1         ; Number of sectors to read
    mov ch, 0         ; Cylinder 0
    mov cl, 2         ; Read from sector 2
    mov dh, 0         ; Head 0
    mov dl, 0x80      ; Disk 0x80 (first hard disk)
    int 0x13          ; Call BIOS interrupt

    ; Jump to kernel entry
    jmp 0x10000       ; Jump to the kernel entry point (adjust for your setup)
