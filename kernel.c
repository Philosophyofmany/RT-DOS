/* kernel.c - Simple kernel main function */

/* Basic video memory pointer for text mode */
volatile unsigned char* video_memory = (volatile unsigned char*)0xB8000;

/* Kernel main function */
void kernel_main() {
    // Write a simple message to screen
    const char* message = "Hello, im your kernel go fuck yourself!";
    unsigned int i = 0;

    // Write message to video memory
    while (message[i] != '\0') {
        video_memory[i * 2] = message[i];     // Character
        video_memory[i * 2 + 1] = 0x07;       // Color (white on black)
        i++;
    }

    // Infinite loop to prevent kernel from exiting
    while(1) {
        // You can add more kernel functionality here later
    }
}
