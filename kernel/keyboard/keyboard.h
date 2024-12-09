#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

// Function prototypes
void init_keyboard();
char get_key(); // Retrieves the last pressed key (blocking)
char try_get_key(); // Non-blocking, returns 0 if no key is pressed

#endif
