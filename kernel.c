#include "screen.h"

void kernel_main() {
    // Clear the screen
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            put_char(x, y, ' ', DEFAULT_COLOR);
        }
    }

    // Draw a box at the top of the screen
    draw_box(25, 1, 30, 3, "RT-DOS Experimental Kernel");

    // Infinite loop to keep the kernel running
    while (1) {}
}
