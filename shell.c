#include "shell.h"

// Forward declaration of process_command
void process_command(char* command);

#define MAX_INPUT_LENGTH 128
#define DEFAULT_COLOR 0x07
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

unsigned char text_buffer[SCREEN_WIDTH * SCREEN_HEIGHT * 2];
int cursor_x = 0;
int cursor_y = 0;

char input_buffer[MAX_INPUT_LENGTH];
int input_index = 0;

void init_shell() {
    buffer_clear();
    cursor_x = 0;
    cursor_y = 0;
    print_prompt();
}

void shell_print(const char* str) {
    while (*str) {
        buffer_put_char(cursor_x, cursor_y, *str, DEFAULT_COLOR);
        str++;

        cursor_x++;
        if (cursor_x >= SCREEN_WIDTH) {
            cursor_x = 0;
            cursor_y++;
            if (cursor_y >= SCREEN_HEIGHT) {
                cursor_y = 0;  // Wrap around
            }
        }
    }
    buffer_flush();
}

// Mock function to simulate character input
char mock_getchar() {
    static const char* test_input = "hello\nclear\nexit\n";
    static int test_index = 0;

    char c = test_input[test_index];
    if (c != '\0') {
        test_index++;
    } else {
        c = '\0'; // Simulate end of input
    }
    return c;
}

void shell_input() {
    char c;
    while (1) {
        c = mock_getchar();  // Temporarily replace kernel_getchar with mock_getchar

        if (c == '\0') {
            break;  // Exit simulation
        }

        if (c == '\n' || c == '\r') {
            input_buffer[input_index] = '\0';
            process_command(input_buffer);
            input_index = 0;
            print_prompt();
        } else if (c == 0x08) { // Backspace
            if (input_index > 0) {
                input_index--;
                clear_line();
                print_prompt();
                shell_print(input_buffer);
            }
        } else if (c >= 32 && c <= 126) { // Printable characters
            if (input_index < MAX_INPUT_LENGTH - 1) {
                input_buffer[input_index] = c;
                input_index++;
                shell_print(&c);
            }
        }
    }
}

void clear_line() {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        buffer_put_char(i, cursor_y, ' ', DEFAULT_COLOR);
    }
}

void print_prompt() {
    char* prompt = "root@RT-DOS:/ ";
    shell_print(prompt);
}

void buffer_put_char(int x, int y, char c, unsigned char color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        int index = (y * SCREEN_WIDTH + x) * 2;
        text_buffer[index] = c;
        text_buffer[index + 1] = color;
    }
}

void buffer_flush() {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * 2; i++) {
        ((volatile unsigned char*)0xB8000)[i] = text_buffer[i];
    }
}

void buffer_clear() {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        text_buffer[i * 2] = ' ';
        text_buffer[i * 2 + 1] = DEFAULT_COLOR;
    }
    buffer_flush();
}

// Simple string comparison function
int my_strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

void process_command(char* command) {
    if (my_strcmp(command, "clear") == 0) {
        buffer_clear();
        print_prompt();
    } else if (my_strcmp(command, "hello") == 0) {
        shell_print("Hello, world!\n");
    } else {
        shell_print("Unknown command: ");
        shell_print(command);
        shell_print("\n");
    }
}
