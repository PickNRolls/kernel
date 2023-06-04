#ifndef DRIVERS_SCREEN_HEADER
#define DRIVERS_SCREEN_HEADER

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define MAX_OFFSET (MAX_ROWS * MAX_COLS * 2)
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void screen_clear();
void screen_print_at(char *message, int col, int row);
void screen_print(char *message);

#endif
