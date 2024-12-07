// kernel.c
#include "../include/kernel.h"

void kernel_main(void) {
    // Simple video output to the screen
    init_video();

    // Print a message to the screen
    char *video = (char *)VIDEO_MEMORY;
    const char *message = "Hello, Kernel!";

    while (*message) {
        *video = *message;  // Write char to video memory
        video += 2;         // Move to next position (2 bytes per character)
        message++;
    }

    // Halt the system (infinite loop)
    while (1) {
        __asm__ volatile("hlt");  // Halt instruction to stop CPU
    }
}

void init_video() {
    // Initialize the video memory (basic VGA text mode)
    // You could set up color attributes or other settings here
}
