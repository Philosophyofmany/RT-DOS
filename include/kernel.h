// kernel.h
#ifndef KERNEL_H
#define KERNEL_H

// Function prototypes
void kernel_main(void);

// Hardware interaction functions
void write_char(char c);
void init_video();

// Macros and constants
#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#endif
