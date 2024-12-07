; kernel_entry.asm
[global kernel_start]

section .text
_start:
    ; Initialize the stack
    mov esp, 0x90000   ; Set up stack pointer

    ; Call the kernel entry function (written in C)
    extern kernel_main
    call kernel_main
