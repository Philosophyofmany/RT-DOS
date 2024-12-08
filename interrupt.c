#include "interrupt.h"
#include "io.h"  // For I/O operations
#include <stdint.h>

#define PIC1_CMD 0x20    // Command port for PIC1
#define PIC1_DATA 0x21   // Data port for PIC1
#define PIC2_CMD 0xA0    // Command port for PIC2
#define PIC2_DATA 0xA1   // Data port for PIC2

// IRQ vector table
void (*interrupt_handlers[256])();

// A simple implementation of enabling IRQ1 (keyboard) for example
void enable_irq(uint8_t irq) {
    if (irq < 8) {
        outb(PIC1_CMD, 0x20);  // Send End of Interrupt (EOI) to PIC1
    } else {
        outb(PIC2_CMD, 0x20);  // Send EOI to PIC2
    }
    // Unmask the IRQ in the appropriate PIC (PIC1 or PIC2)
    if (irq < 8) {
        outb(PIC1_DATA, ~(1 << irq));  // Unmask IRQ on PIC1
    } else {
        outb(PIC2_DATA, ~(1 << (irq - 8)));  // Unmask IRQ on PIC2
    }
}

// Register an interrupt handler
void register_interrupt_handler(uint8_t irq, void (*handler)()) {
    interrupt_handlers[irq] = handler;
}

// Example of handling interrupts (you'd typically use this with assembly to hook into the interrupt vector table)
void interrupt_handler(uint8_t irq) {
    if (interrupt_handlers[irq]) {
        interrupt_handlers[irq]();
    }
}
