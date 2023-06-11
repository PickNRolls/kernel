#ifndef KERNEL_UTIL_HEADER
#define KERNEL_UTIL_HEADER

#include <stdint.h>

void util_memory_copy(uint8_t *src, uint8_t *dest, uint32_t bytes);
void util_int_to_ascii(int n, char *output);
void util_str_reverse(const char *str, char *output);
char util_char_uppercase(char c);

#define INT_STR_MAX_SIZE 12
#define INT8_STR_MAX_SIZE 5

#endif
