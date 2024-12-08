#ifndef SHELL_H
#define SHELL_H

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define DEFAULT_COLOR 0x07  // White text on black background

// Function declarations
void init_shell();
void shell_print(const char* str);
void shell_input();
void buffer_put_char(int x, int y, char c, unsigned char color);
void buffer_flush();
void buffer_clear();
void print_prompt();
void clear_line();

#endif
