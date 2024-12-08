#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

// Function prototypes
void register_interrupt_handler(uint8_t irq, void (*handler)());
void enable_irq(uint8_t irq);

#endif
