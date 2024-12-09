
#define VIDEO_MEMORY 0xB8000  // VGA video memory address for text mode
#define SCREEN_WIDTH 80       // 80 columns in text mode
#define SCREEN_HEIGHT 25      // 25 rows in text mode

// Function to print a string directly to the screen at the current position
void print_string(const char* str) {
    unsigned short* video_memory = (unsigned short*)VIDEO_MEMORY;

    // Loop through the string and write each character to the screen
    while (*str != '\0') {
        *video_memory = (unsigned short)(*str | 0x0F00);  // Write character with light gray color
        video_memory++;  // Move to the next screen position
        str++;
    }
}

void kernel_main() {
    // Step 1: Print "I'm your kernel" directly to the screen
    print_string("I'm your kernel");

    // Step 2: Infinite loop to keep the kernel running
    while (1) {
        // You can add more functionality here if needed
    }
}