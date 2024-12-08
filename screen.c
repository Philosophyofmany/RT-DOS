#include "screen.h"

/* Base address for video memory in VGA text mode */
volatile unsigned char* video_memory = (volatile unsigned char*)0xB8000;

void put_char(int x, int y, char c, unsigned char color) {
    int index = (y * SCREEN_WIDTH + x) * 2;
    video_memory[index] = c;
    video_memory[index + 1] = color;
}

void draw_box(int x, int y, int width, int height, const char* message) {
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

    int msg_len = 0;
    while (message[msg_len] != '\0') msg_len++;
    int msg_start_x = x + (width - msg_len) / 2;
    int msg_start_y = y + height / 2;

    for (int i = 0; i < msg_len; i++) {
        put_char(msg_start_x + i, msg_start_y, message[i], DEFAULT_COLOR);
    }
}
