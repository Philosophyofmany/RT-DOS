#include "keyboard.h"
#include "../inout/io.h"
#include "../interrupts/isr.h"
#include "../screen/screen.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IRQ1 33

// Circular buffer for keyboard input
#define KEY_BUFFER_SIZE 256
static char key_buffer[KEY_BUFFER_SIZE];
static int buffer_start = 0;
static int buffer_end = 0;

// Modifier key states
static uint8_t shift_pressed = 0;
static uint8_t caps_lock = 0;

// US QWERTY keyboard scancode table (unshifted)
static const char scancode_to_char_unshifted[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// US QWERTY keyboard scancode table (shifted)
static const char scancode_to_char_shifted[128] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// Keyboard interrupt handler
static void keyboard_callback(registers_t* regs) {
    (void)regs;
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);

    // Handle key press and release events
    if (scancode < 128) {
        // Key press events
        switch (scancode) {
            case 0x2A: // Left Shift press
            case 0x36: // Right Shift press
                shift_pressed = 1;
                return;
            case 0x3A: // Caps Lock
                caps_lock = !caps_lock;
                return;
        }

        // Translate scancode to character
        char key;
        if (shift_pressed ^ caps_lock) {
            key = scancode_to_char_shifted[scancode];
        } else {
            key = scancode_to_char_unshifted[scancode];
        }

        // Add to buffer if valid key
        if (key) {
            key_buffer[buffer_end] = key;
            buffer_end = (buffer_end + 1) % KEY_BUFFER_SIZE;

            // Prevent buffer overflow
            if (buffer_end == buffer_start) {
                buffer_start = (buffer_start + 1) % KEY_BUFFER_SIZE;
            }

            // Optional: Echo key to screen
            char str[2] = {key, '\0'};
            print_string(str);
        }
    } else {
        // Key release events
        switch (scancode) {
            case 0xAA: // Left Shift release
            case 0xB6: // Right Shift release
                shift_pressed = 0;
                break;
        }
    }
}

// Initialize keyboard driver
void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}

// Blocking key read
char get_key() {
    while (buffer_start == buffer_end) {
        asm volatile("hlt"); // Wait for interrupt
    }

    char key = key_buffer[buffer_start];
    buffer_start = (buffer_start + 1) % KEY_BUFFER_SIZE;
    return key;
}

// Non-blocking key read
char try_get_key() {
    if (buffer_start == buffer_end) {
        return 0; // No key available
    }

    char key = key_buffer[buffer_start];
    buffer_start = (buffer_start + 1) % KEY_BUFFER_SIZE;
    return key;
}

// Check if a key is available
int is_key_available() {
    return buffer_start != buffer_end;
}

// Clear the keyboard buffer
void clear_keyboard_buffer() {
    buffer_start = 0;
    buffer_end = 0;
}
