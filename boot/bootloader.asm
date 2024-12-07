; 32-bit Protected Mode Bootloader
global _start

section .multiboot
    ; Multiboot header for compatibility
    align 4
    dd 0x1BADB002              ; Multiboot magic number
    dd 0x00000003              ; Multiboot flags (page align + memory info)
    dd -(0x1BADB002 + 0x00000003)  ; Checksum

section .text
_start:
    cli                 ; Disable interrupts

    ; Set up Global Descriptor Table
    lgdt [gdt_descriptor]

    ; Set up segment registers
    mov ax, 0x10        ; Data segment selector
    mov ds, ax
    mov es, ax
    mov ss, ax

    ; Set up stack
    mov esp, 0x90000

    ; Jump to kernel entry point
    jmp 0x08:kernel_entry

; Global Descriptor Table
gdt_start:
    ; Null descriptor
    dd 0x0
    dd 0x0

    ; Code segment descriptor
    dw 0xFFFF           ; Limit low
    dw 0x0000           ; Base low
    db 0x00             ; Base middle
    db 10011010b        ; Access (executable, readable)
    db 11001111b        ; Granularity, 32-bit flag
    db 0x00             ; Base high

    ; Data segment descriptor
    dw 0xFFFF           ; Limit low
    dw 0x0000           ; Base low
    db 0x00             ; Base middle
    db 10010010b        ; Access (readable, writable)
    db 11001111b        ; Granularity, 32-bit flag
    db 0x00             ; Base high
gdt_end:

; GDT Descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; GDT size
    dd gdt_start                ; GDT address

; Kernel entry point (will be defined in kernel_entry.asm)
extern kernel_main
kernel_entry:
    ; Call kernel main function
    call kernel_main

    ; Halt if kernel returns
    cli
    hlt

; Pad to ensure correct size
times 510-($-$$) db 0
dw 0xAA55  ; Boot sector signature
