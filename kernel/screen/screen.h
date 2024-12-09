#ifndef SCREEN_H
#define SCREEN_H

// void clear_screen();               // To clear the screen
void print_string(const char* str); // To print a string
static void update_cursor();              // Declare this if needed outside screen.c
static void print_char(char c);           // Declare this if needed outside screen.c
// void kprint(const char *str);
// void kprint_newline(void);

#endif
