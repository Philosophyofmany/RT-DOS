[bits 32]                ; 32-bit code (kernel is 32-bit)
[global _start]          ; Export _start to indicate entry point for linker

section .text
_start:
    ; Kernel initialization (e.g., printing a message)
    mov edx, hello_message
    call print_string
    jmp $

print_string:
    ; Print string using BIOS interrupt (just for demonstration)
    mov ecx, [edx]
print_loop:
    mov al, [ecx]
    cmp al, 0
    je print_done
    mov ah, 0x0E         ; BIOS teletype output function (print character)
    int 0x10             ; Call BIOS interrupt
    inc ecx              ; Move to next character
    jmp print_loop       ; Repeat

print_done:
    ret

hello_message db 'Hello from the Kernel!', 0  ; Null-terminated string
