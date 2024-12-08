#include "keyboard.h"
#include "io.h"
#include "interrupt.h"
#include <stdint.h>  // For uint8_t and uint16_t

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define BUFFER_SIZE 128
#define BACKSPACE 0x0E
#define ENTER 0x1C
#define IRQ1 33  // IRQ1 is usually associated with the keyboard interrupt

// ASCII mapping for scancodes
char keyboard_map[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static char input_buffer[BUFFER_SIZE];
static int buffer_index = 0;

void keyboard_handler() {
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);

    // Check if the key is released
    if (scancode & 0x80) {
        // Ignore key release events for now
    } else {
        char c = keyboard_map[scancode];
        if (c) {
            if (c == '\b' && buffer_index > 0) {
                buffer_index--;  // Handle backspace
            } else if (c == '\n') {
                input_buffer[buffer_index] = '\0';  // Null-terminate the input
                buffer_index = 0;  // Reset buffer for the next command
            } else if (buffer_index < BUFFER_SIZE - 1) {
                input_buffer[buffer_index++] = c;  // Add character to buffer
            }
        }
    }
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_handler);  // Register keyboard interrupt handler
    enable_irq(1);  // Enable keyboard interrupts
}

char kernel_getchar() {
    while (buffer_index == 0) {
        // Wait for input (busy wait)
    }
    return input_buffer[--buffer_index];  // Return the next character
}
