#ifndef KERNEL_UTIL_HEADER
#define KERNEL_UTIL_HEADER

void util_memory_copy(char *src, char *dest, int bytes);
void util_int_to_ascii(int n, char *output);
void util_str_reverse(const char *str, char *output);

#define INT_STR_MAX_SIZE 12

#endif
