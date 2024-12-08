; boot.s - Multiboot compliant assembly entry point

; Multiboot header constants
MBALIGN     equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO     equ  1 << 1            ; provide memory map
FLAGS       equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

; Declare a multiboot header that marks the program as a kernel
section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; Provide a stack for the kernel
section .bss
align 4
stack_bottom:
    resb 16384   ; 16 KB of stack space
stack_top:

; Kernel entry point
section .text
global _start
_start:
    ; Set up stack
    mov esp, stack_top

    ; Call the kernel's main function
    extern kernel_main
    call kernel_main

    ; If kernel_main returns, halt the system
.hang:
    cli         ; Clear interrupt flag
    hlt         ; Halt the processor
    jmp .hang   ; If somehow we wake up, loop forever
