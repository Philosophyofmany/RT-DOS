#include "screen.h"

/* Base address for video memory in VGA text mode */
volatile unsigned char* video_memory = (volatile unsigned char*)0xB8000;

/* Define constants for screen size */
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define DEFAULT_COLOR 0x0F // White text on black background

void put_char(int x, int y, char c, unsigned char color) {
    // Ensure x and y are within bounds of the screen
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return; // Don't write outside the screen
    }

    // Calculate the index in video memory
    int index = (y * SCREEN_WIDTH + x) * 2;

    // Write character and color to video memory
    video_memory[index] = c;
    video_memory[index + 1] = color;
}

void draw_box(int x, int y, int width, int height, const char* message) {
    // Draw the box border
    for (int i = 0; i < width; i++) {
        put_char(x + i, y, '-', DEFAULT_COLOR);
        put_char(x + i, y + height - 1, '-', DEFAULT_COLOR);
    }
    for (int i = 0; i < height; i++) {
        put_char(x, y + i, '|', DEFAULT_COLOR);
        put_char(x + width - 1, y + i, '|', DEFAULT_COLOR);
    }
    put_char(x, y, '+', DEFAULT_COLOR);
    put_char(x + width - 1, y, '+', DEFAULT_COLOR);
    put_char(x, y + height - 1, '+', DEFAULT_COLOR);
    put_char(x + width - 1, y + height - 1, '+', DEFAULT_COLOR);

    // Center the message inside the box
    int msg_len = 0;
    while (message[msg_len] != '\0') msg_len++;
    int msg_start_x = x + (width - msg_len) / 2;
    int msg_start_y = y + height / 2;

    // Draw the message inside the box
    for (int i = 0; i < msg_len; i++) {
        put_char(msg_start_x + i, msg_start_y, message[i], DEFAULT_COLOR);
    }
}
