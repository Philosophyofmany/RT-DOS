[global kernel_start]

section .text
kernel_start:
    ; Initialize the stack
    mov esp, 0x90000   ; Set up stack pointer (ensure this doesn't overlap with other regions)

    ; Call the kernel entry function (written in C)
    extern kernel_main  ; Declare the kernel_main function, written in C
    call kernel_main    ; Call the kernel entry function in C

    ; Infinite loop to prevent returning (this should never be reached)
    hlt                 ; Halt the CPU if kernel_main returns (this is a safety measure)

section .note.GNU-stack
    ; Mark the stack as non-executable
    ; This section is required to prevent the warning about executable stack.
    ; It tells the linker not to make the stack executable.
