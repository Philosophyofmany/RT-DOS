#include <stddef.h>
#include <stdint.h>
#include "../inout/io.h"
#include "screen.h"

#define VIDEO_MEMORY 0xB8000  // VGA text mode video memory address
#define SCREEN_WIDTH 80       // Number of columns
#define SCREEN_HEIGHT 25      // Number of rows
#define WHITE_ON_BLACK 0x0F   // White text on black background

static uint16_t* const video_memory = (uint16_t*)VIDEO_MEMORY;
static size_t cursor_row = 0;
static size_t cursor_col = 0;
static char *vidptr = (char *)VIDEO_MEMORY;  // Pointer to video memory
static unsigned int current_loc = 0;         // Current cursor location

// Function to update the hardware cursor position
static void update_cursor() {
    uint16_t position = cursor_row * SCREEN_WIDTH + cursor_col;
    outb(0x3D4, 0x0F);          // Set the high byte of the cursor
    outb(0x3D5, (uint8_t)(position & 0xFF));
    outb(0x3D4, 0x0E);          // Set the low byte of the cursor
    outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
}

// Function to clear the screen
// void clear_screen() {
//     for (size_t row = 0; row < SCREEN_HEIGHT; ++row) {
//         for (size_t col = 0; col < SCREEN_WIDTH; ++col) {
//             video_memory[row * SCREEN_WIDTH + col] = ' ' | (WHITE_ON_BLACK << 8);
//         }
//     }
//     cursor_row = 0;
//     cursor_col = 0;
//     update_cursor();
// }

// Function to print a single character to the screen
static void print_char(char c) {
    if (c == '\n') {
        cursor_col = 0;
        ++cursor_row;
    } else {
        video_memory[cursor_row * SCREEN_WIDTH + cursor_col] = c | (WHITE_ON_BLACK << 8);
        ++cursor_col;
        if (cursor_col >= SCREEN_WIDTH) {
            cursor_col = 0;
            ++cursor_row;
        }
    }

    // Scroll the screen if necessary
    if (cursor_row >= SCREEN_HEIGHT) {
        for (size_t row = 1; row < SCREEN_HEIGHT; ++row) {
            for (size_t col = 0; col < SCREEN_WIDTH; ++col) {
                video_memory[(row - 1) * SCREEN_WIDTH + col] = video_memory[row * SCREEN_WIDTH + col];
            }
        }
        // Clear the last row after scrolling
        for (size_t col = 0; col < SCREEN_WIDTH; ++col) {
            video_memory[(SCREEN_HEIGHT - 1) * SCREEN_WIDTH + col] = ' ' | (WHITE_ON_BLACK << 8);
        }
        --cursor_row; // Keep the cursor at the last row after scrolling
    }

    update_cursor();
}

// Function to print a string to the screen
void print_string(const char* str) {
    unsigned short* video_memory = (unsigned short*)VIDEO_MEMORY;

    while (*str != '\0') {
        *video_memory = (unsigned short)(*str | 0x0F00);  // Write character with light gray color
        video_memory++;  // Move to the next screen position
        str++;
    }
}

/* Prints a string to the screen */
// void kprint(const char *str) {
//     while (*str) {
//         if (*str == '\n') {
//             kprint_newline();
//         } else {
//             vidptr[current_loc++] = *str;    // Write character
//             vidptr[current_loc++] = 0x07;   // Default attribute
//         }
//         str++;
//     }
// }

// /* Moves the cursor to the next line */
// void kprint_newline(void) {
//     current_loc = (current_loc / (SCREEN_WIDTH * 2) + 1) * (SCREEN_WIDTH * 2);
// }
