#include "util.h"
#include <stdint.h>

void util_memory_copy(uint8_t *src, uint8_t *dest, uint32_t bytes) {
  uint32_t index = 0;
  while (index < bytes) {
    *(dest + index) = *(src + index);
    index++;
  }
}

uint32_t util_str_length(const char *str) {
  uint32_t length = 0;
  while (str[length] != 0) {
    length++;
  }
  return length;
}

void util_str_reverse(const char *str, char *output) {
  if (str[0] == 0) {
    output[0] = 0;
    return;
  }

  uint32_t length = util_str_length(str);
  uint32_t index = length;

  while (index-- != 0) {
    output[length - index - 1] = str[index];
  }
  output[length - index - 1] = str[index];

  output[length] = 0;
}

void util_int_to_ascii(int n, char *output) {
  int sign = n;

  if (sign < 0) {
    n = -n;
  }

  char to_reverse[INT_STR_MAX_SIZE] = {};
  int index = 0;
  do {
    to_reverse[index++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) {
    to_reverse[index++] = '-';
  }
  to_reverse[index] = 0;

  util_str_reverse(to_reverse, output);
}

char util_char_uppercase(char c) {
  if (c < 0x61 || c > 0x7A) {
    return c;
  }

  return c - 32;
}
