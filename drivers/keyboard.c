#include "keyboard.h"
#include "../cpu/isr.h"
#include "../kernel/util.h"
#include "ports.h"
#include "screen.h"

Keyboard_Handler registered_handlers[32] = {0};
uint8_t registered_handlers_count = 0;
uint8_t is_caps_toggled = 0;
uint8_t key_codes_pressed[KEY_CODE_MAX] = {0};

uint8_t scan_to_key[] = {
    [0x01] = KEY_CODE_ESC,
    KEY_CODE_DIGIT1,
    KEY_CODE_DIGIT2,
    KEY_CODE_DIGIT3,
    KEY_CODE_DIGIT4,
    KEY_CODE_DIGIT5,
    KEY_CODE_DIGIT6,
    KEY_CODE_DIGIT7,
    KEY_CODE_DIGIT8,
    KEY_CODE_DIGIT9,
    KEY_CODE_DIGIT0,
    KEY_CODE_DASH,
    KEY_CODE_EQUAL,
    KEY_CODE_BACKSPACE,
    KEY_CODE_TAB,
    KEY_CODE_Q,
    KEY_CODE_W,
    KEY_CODE_E,
    KEY_CODE_R,
    KEY_CODE_T,
    KEY_CODE_Y,
    KEY_CODE_U,
    KEY_CODE_I,
    KEY_CODE_O,
    KEY_CODE_P,
    KEY_CODE_LEFT_BRACE,
    KEY_CODE_RIGHT_BRACE,
    KEY_CODE_ENTER,
    KEY_CODE_LEFT_CTRL,
    KEY_CODE_A,
    KEY_CODE_S,
    KEY_CODE_D,
    KEY_CODE_F,
    KEY_CODE_G,
    KEY_CODE_H,
    KEY_CODE_J,
    KEY_CODE_K,
    KEY_CODE_L,
    KEY_CODE_SEMICOLON,
    KEY_CODE_APOSTROPHE,
    KEY_CODE_BACKTICK,
    KEY_CODE_LEFT_SHIFT,
    KEY_CODE_BACKSLASH,
    KEY_CODE_Z,
    KEY_CODE_X,
    KEY_CODE_C,
    KEY_CODE_V,
    KEY_CODE_B,
    KEY_CODE_N,
    KEY_CODE_M,
    KEY_CODE_COMMA,
    KEY_CODE_DOT,
    KEY_CODE_SLASH,
    KEY_CODE_RIGHT_SHIFT,
    [0x38] = KEY_CODE_LEFT_ALT,
    KEY_CODE_SPACE,
    KEY_CODE_CAPS,
    KEY_CODE_F1,
    KEY_CODE_F2,
    KEY_CODE_F3,
    KEY_CODE_F4,
    KEY_CODE_F5,
    KEY_CODE_F6,
    KEY_CODE_F7,
    KEY_CODE_F8,
    KEY_CODE_F9,
    KEY_CODE_F10,
};

char key_to_char[KEY_CODE_MAX] = {
    [KEY_CODE_DIGIT1] = '1',     [KEY_CODE_DIGIT2] = '2',
    [KEY_CODE_DIGIT3] = '3',     [KEY_CODE_DIGIT4] = '4',
    [KEY_CODE_DIGIT5] = '5',     [KEY_CODE_DIGIT6] = '6',
    [KEY_CODE_DIGIT7] = '7',     [KEY_CODE_DIGIT8] = '8',
    [KEY_CODE_DIGIT9] = '9',     [KEY_CODE_DIGIT0] = '0',
    [KEY_CODE_DASH] = '-',       [KEY_CODE_EQUAL] = '=',
    [KEY_CODE_Q] = 'q',          [KEY_CODE_W] = 'w',
    [KEY_CODE_E] = 'e',          [KEY_CODE_R] = 'r',
    [KEY_CODE_T] = 't',          [KEY_CODE_Y] = 'y',
    [KEY_CODE_U] = 'u',          [KEY_CODE_I] = 'i',
    [KEY_CODE_O] = 'o',          [KEY_CODE_P] = 'p',
    [KEY_CODE_LEFT_BRACE] = '[', [KEY_CODE_RIGHT_BRACE] = ']',
    [KEY_CODE_BACKSLASH] = '\\', [KEY_CODE_A] = 'a',
    [KEY_CODE_S] = 's',          [KEY_CODE_D] = 'd',
    [KEY_CODE_F] = 'f',          [KEY_CODE_G] = 'g',
    [KEY_CODE_H] = 'h',          [KEY_CODE_J] = 'j',
    [KEY_CODE_K] = 'k',          [KEY_CODE_L] = 'l',
    [KEY_CODE_SEMICOLON] = ';',  [KEY_CODE_APOSTROPHE] = '\'',
    [KEY_CODE_ENTER] = '\n',     [KEY_CODE_BACKSPACE] = '\b',
    [KEY_CODE_Z] = 'z',          [KEY_CODE_X] = 'x',
    [KEY_CODE_C] = 'c',          [KEY_CODE_V] = 'v',
    [KEY_CODE_B] = 'b',          [KEY_CODE_N] = 'n',
    [KEY_CODE_M] = 'm',          [KEY_CODE_COMMA] = ',',
    [KEY_CODE_DOT] = '.',        [KEY_CODE_SLASH] = '/',
    [KEY_CODE_SPACE] = ' ',      [KEY_CODE_BACKTICK] = '`'};

char keyboard_get_key_code_char(uint8_t key_code) {
  uint8_t is_shift_pressed = key_codes_pressed[KEY_CODE_LEFT_SHIFT] ||
                             key_codes_pressed[KEY_CODE_RIGHT_SHIFT];

  char c = key_to_char[key_code];
  if (c != 0 && is_caps_toggled ^ is_shift_pressed) {
    c = util_char_uppercase(c);
  }

  if (!is_shift_pressed) {
    return c;
  }

  switch (key_code) {
  case KEY_CODE_BACKTICK:
    return '~';
  case KEY_CODE_DIGIT1:
    return '!';
  case KEY_CODE_DIGIT2:
    return '@';
  case KEY_CODE_DIGIT3:
    return '#';
  case KEY_CODE_DIGIT4:
    return '$';
  case KEY_CODE_DIGIT5:
    return '%';
  case KEY_CODE_DIGIT6:
    return '^';
  case KEY_CODE_DIGIT7:
    return '&';
  case KEY_CODE_DIGIT8:
    return '*';
  case KEY_CODE_DIGIT9:
    return '(';
  case KEY_CODE_DIGIT0:
    return ')';
  case KEY_CODE_DASH:
    return '_';
  case KEY_CODE_EQUAL:
    return '+';
  case KEY_CODE_COMMA:
    return '<';
  case KEY_CODE_DOT:
    return '>';
  case KEY_CODE_LEFT_BRACE:
    return '{';
  case KEY_CODE_RIGHT_BRACE:
    return '}';
  case KEY_CODE_SLASH:
    return '?';
  case KEY_CODE_BACKSLASH:
    return '|';
  case KEY_CODE_SEMICOLON:
    return ':';
  case KEY_CODE_APOSTROPHE:
    return '"';
  default:
    return c;
  }
}

void keyboard_call_key(uint8_t key_code, uint8_t is_released) {
  char ascii = keyboard_get_key_code_char(key_code);

  if (key_code == KEY_CODE_CAPS && !is_released) {
    is_caps_toggled = !is_caps_toggled;
  }

  Keyboard_Packet packet = {
      .key_code = key_code,
      .ascii = ascii,

      .is_released = is_released,
      .is_caps_toggled = is_caps_toggled,
      .is_caps_pressed = key_codes_pressed[KEY_CODE_CAPS],
      .is_ctrl_pressed = key_codes_pressed[KEY_CODE_LEFT_CTRL] ||
                         key_codes_pressed[KEY_CODE_RIGHT_CTRL],
      .is_shift_pressed = key_codes_pressed[KEY_CODE_LEFT_SHIFT] ||
                          key_codes_pressed[KEY_CODE_RIGHT_SHIFT],
      .is_repeat = 0, // TODO: create proper is_repeat
  };

  uint32_t index = 0;
  while (index < registered_handlers_count) {
    registered_handlers[index](packet);
    index++;
  }

  key_codes_pressed[key_code] = !is_released;
}

void keyboard_call_key_down(uint8_t key_code) {
  uint8_t is_released = 0;
  return keyboard_call_key(key_code, is_released);
}

void keyboard_call_key_release(uint8_t key_code) {
  uint8_t is_released = 1;
  return keyboard_call_key(key_code, is_released);
}

void handle_keyboard() {
  uint8_t scan_code = port_byte_in(0x60);
  if (scan_code == 0) {
    return;
  }

  uint8_t is_releasing_now = scan_code > SCAN_CODE_RELEASE_OFFSET;
  if (is_releasing_now) {
    uint8_t pressed_scan_code = scan_code - SCAN_CODE_RELEASE_OFFSET;
    uint8_t pressed_key_code = scan_to_key[pressed_scan_code];
    keyboard_call_key_release(pressed_key_code);
    return;
  }

  uint8_t key_code = scan_to_key[scan_code];
  keyboard_call_key_down(key_code);
}

void keyboard_register_handler(Keyboard_Handler handler) {
  registered_handlers[registered_handlers_count] = handler;
  registered_handlers_count++;
}

void keyboard_init() { cpu_isr_register_handler(IRQ1, handle_keyboard); }
