#include "../drivers/screen.h"
#include "util.h"

int kernel_main() {
  screen_clear();

  int i = 0;
  for (i = 0; i < 24; i++) {
    char str[255];
    util_int_to_ascii(i, str);
    screen_print_at(str, i, 0);
  }

  return 0;
}
