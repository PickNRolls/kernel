#include "screen.h"
#include "../kernel/util.h"
#include "ports.h"

int internal_get_offset(int row, int col) { return 2 * (row * MAX_COLS + col); }
int internal_get_offset_row(int offset) { return offset / 2 / MAX_COLS; }
int internal_get_offset_col(int offset) { return offset / 2 % MAX_COLS; }
void internal_set_cursor_offset(int offset) {
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, offset >> 8);
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, offset & 0xff);
}
uint32_t internal_get_cursor_offset() {
  port_byte_out(REG_SCREEN_CTRL, 14);
  uint32_t offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);
  return offset * 2;
}
/**
 * returns offset for next internal_print_char
 * */
int internal_print_char(char c, int row, int col, unsigned char attribute) {
  uint8_t *video = (uint8_t *)VIDEO_ADDRESS;
  int offset;

  if (row >= MAX_ROWS || col >= MAX_COLS) {
    offset = 2 * MAX_ROWS * MAX_COLS - 10;
    char *error_message = "Error";
    int i = 0;
    while (i < 5) {
      video[offset] = error_message[i];
      video[offset + 1] = RED_ON_WHITE;
      i++;
      offset += 2;
    }
    return offset;
  }

  if (row < 0 && col < 0) {
    offset = internal_get_cursor_offset();
  } else {
    offset = internal_get_offset(row, col);
  }

  if (c == '\n') {
    row = internal_get_offset_row(offset);
    offset = internal_get_offset(row + 1, 0);
  } else if (c == '\b') {
    if (offset != 0) {
      offset -= 2;
      video[offset] = ' ';
    }
  } else {
    video[offset] = c;
    video[offset + 1] = attribute;
    offset += 2;
  }

  if (offset >= MAX_OFFSET) {
    util_memory_copy(video + BYTES_IN_ROW, video, MAX_OFFSET - BYTES_IN_ROW);
    for (int i = 0; i < MAX_COLS; i++) {
      video[MAX_OFFSET - BYTES_IN_ROW + i] = 0;
    }
    offset -= BYTES_IN_ROW;
  }

  internal_set_cursor_offset(offset);
  return offset;
}

void screen_clear() {
  char *video = (char *)VIDEO_ADDRESS;

  int i = 0;
  while (i < MAX_OFFSET) {
    video[i * 2] = ' ';
    video[i * 2 + 1] = WHITE_ON_BLACK;
    i++;
  }

  internal_set_cursor_offset(0);
}

void screen_print_at_offset(char *message, uint32_t offset) {
  uint32_t row = internal_get_offset_row(offset);
  uint32_t col = internal_get_offset_col(offset);

  int i = 0;
  while (message[i] != 0) {
    offset = internal_print_char(message[i], row, col, WHITE_ON_BLACK);
    row = internal_get_offset_row(offset);
    col = internal_get_offset_col(offset);
    i++;
  }
}

void screen_print_at(char *message, int row, int col) {
  uint32_t offset;
  if (col >= 0 && row >= 0) {
    offset = internal_get_offset(row, col);
  } else {
    offset = internal_get_cursor_offset();
  }

  return screen_print_at_offset(message, offset);
}

void screen_print(char *message) { screen_print_at(message, -1, -1); }

void screen_backspace() { screen_print("\b"); }
