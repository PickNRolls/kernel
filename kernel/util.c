#include "util.h"
#include <stdint.h>

void util_memory_copy(char *src, char *dest, int bytes) {
  int i = 0;
  while (i < bytes) {
    *(dest + i) = *(src + i);
    i++;
  }
}

uint32_t util_str_length(const char *str) {
  uint32_t length = 0;
  while (str[length] != 0) {
    length++;
  }
  return length;
}

void util_str_reverse(char const *str, char *output) {
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
