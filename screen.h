#ifndef SCREEN_H
#define SCREEN_H

/* Screen dimensions */
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

/* Default text color */
#define DEFAULT_COLOR 0x07

/* Declare video memory pointer as extern */
extern volatile unsigned char* video_memory;

/* Function prototypes */
void put_char(int x, int y, char c, unsigned char color);
void draw_box(int x, int y, int width, int height, const char* message);

#endif
