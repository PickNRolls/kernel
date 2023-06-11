#ifndef DRIVERS_KEYBOARD_HEADER
#define DRIVERS_KEYBOARD_HEADER

#include <stdint.h>

typedef struct Keyboard_Packet {
  uint8_t key_code;
  char ascii;

  // TODO: add is_meta_pressed
  // TODO: add is_alt_pressed
  uint8_t is_released;
  uint8_t is_shift_pressed;
  uint8_t is_caps_pressed;
  uint8_t is_ctrl_pressed;
  uint8_t is_caps_toggled;
  uint8_t is_repeat;
} Keyboard_Packet;

typedef void (*Keyboard_Handler)(Keyboard_Packet packet);

void keyboard_init();
void keyboard_register_handler(Keyboard_Handler handler);

/*
 * Key code is uint8_t number.
 * Higher 3 bits are keyboard row number, lower 5 bits are keyboard column
 * number. Row number count starts from the top, column number count starts from
 * the left.
 *
 * +-----------------------------+
 * |        |   Row 0   |        |
 * |--------+-----------+--------|
 * |--------+-----------+--------|
 * |Column 0|           |Column N|
 * |--------+-----------+--------|
 * |--------+-----------+--------|
 * |--------+-----------+--------|
 * |        |   Row 5   |        |
 * +-----------------------------+
 *
 * For now it has proper support for my hyperx alloy origins core keyboard,
 * excluding useless right side keys: scroll lock, pause break, print screen,
 * ins, home, pgup, del, end, pgdn.
 * And some "right fn key", "right document key", those are between right alt
 * and ctrl.
 * It may function wrong with any other keyboard, live with it.
 */

#define SCAN_CODE_RELEASE_OFFSET 0x80

#define KEY_CODE_ESC 0x01
#define KEY_CODE_F1 0x02
#define KEY_CODE_F2 0x03
#define KEY_CODE_F3 0x04
#define KEY_CODE_F4 0x05
#define KEY_CODE_F5 0x06
#define KEY_CODE_F6 0x07
#define KEY_CODE_F7 0x08
#define KEY_CODE_F8 0x09
#define KEY_CODE_F9 0x0A
#define KEY_CODE_F10 0x0B
#define KEY_CODE_F11 0x0C
#define KEY_CODE_F12 0x0D

#define KEY_CODE_BACKTICK 0x20
#define KEY_CODE_DIGIT1 0x21
#define KEY_CODE_DIGIT2 0x22
#define KEY_CODE_DIGIT3 0x23
#define KEY_CODE_DIGIT4 0x24
#define KEY_CODE_DIGIT5 0x25
#define KEY_CODE_DIGIT6 0x26
#define KEY_CODE_DIGIT7 0x27
#define KEY_CODE_DIGIT8 0x28
#define KEY_CODE_DIGIT9 0x29
#define KEY_CODE_DIGIT0 0x2A
#define KEY_CODE_DASH 0x2B
#define KEY_CODE_EQUAL 0x2C
#define KEY_CODE_BACKSPACE 0x2D

#define KEY_CODE_TAB 0x40
#define KEY_CODE_Q 0x41
#define KEY_CODE_W 0x42
#define KEY_CODE_E 0x43
#define KEY_CODE_R 0x44
#define KEY_CODE_T 0x45
#define KEY_CODE_Y 0x46
#define KEY_CODE_U 0x47
#define KEY_CODE_I 0x48
#define KEY_CODE_O 0x49
#define KEY_CODE_P 0x4A
#define KEY_CODE_LEFT_BRACE 0x4B
#define KEY_CODE_RIGHT_BRACE 0x4C
#define KEY_CODE_BACKSLASH 0x4D

#define KEY_CODE_CAPS 0x60
#define KEY_CODE_A 0x61
#define KEY_CODE_S 0x62
#define KEY_CODE_D 0x63
#define KEY_CODE_F 0x64
#define KEY_CODE_G 0x65
#define KEY_CODE_H 0x66
#define KEY_CODE_J 0x67
#define KEY_CODE_K 0x68
#define KEY_CODE_L 0x69
#define KEY_CODE_SEMICOLON 0x6A
#define KEY_CODE_APOSTROPHE 0x6B
#define KEY_CODE_ENTER 0x6C

#define KEY_CODE_LEFT_SHIFT 0x80
#define KEY_CODE_Z 0x81
#define KEY_CODE_X 0x82
#define KEY_CODE_C 0x83
#define KEY_CODE_V 0x84
#define KEY_CODE_B 0x85
#define KEY_CODE_N 0x86
#define KEY_CODE_M 0x87
#define KEY_CODE_COMMA 0x88
#define KEY_CODE_DOT 0x89
#define KEY_CODE_SLASH 0x8A
#define KEY_CODE_RIGHT_SHIFT 0x8B
#define KEY_CODE_ARROW_UP 0x8C

#define KEY_CODE_LEFT_CTRL 0xA0
#define KEY_CODE_LEFT_META 0xA1
#define KEY_CODE_LEFT_ALT 0xA2
#define KEY_CODE_SPACE 0xA3
#define KEY_CODE_RIGHT_ALT 0xA4
#define KEY_CODE_RIGHT_CTRL 0xA7
#define KEY_CODE_ARROW_LEFT 0xA8
#define KEY_CODE_ARROW_DOWN 0xA9
#define KEY_CODE_ARROW_RIGHT 0xAA

#define KEY_CODE_MAX (KEY_CODE_ARROW_RIGHT)

#endif
