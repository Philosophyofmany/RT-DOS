#include "isr.h"
#define IDT_ENTRIES 256

isr_t interrupt_handlers[IDT_ENTRIES];

// Registers an interrupt handler
void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

// Called from the assembly ISR stub
void isr_handler(registers_t* regs) {
    if (interrupt_handlers[regs->int_no]) {
        isr_t handler = interrupt_handlers[regs->int_no];
        handler(regs);
    }
}
