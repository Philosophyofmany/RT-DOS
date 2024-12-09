#ifndef ISR_H
#define ISR_H

#include <stdint.h>

// Interrupt handler function type
typedef struct registers {
    uint32_t ds;                 // Data segment selector
    uint32_t edi, esi, ebp, esp; // Pushed by pusha
    uint32_t ebx, edx, ecx, eax; // Pushed by pusha
    uint32_t int_no, err_code;   // Interrupt number and error code
    uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor
} registers_t;

// Register an interrupt handler
typedef void (*isr_t)(registers_t*);
void register_interrupt_handler(uint8_t n, isr_t handler);

#endif
