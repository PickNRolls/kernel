#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "util.h"

int kernel_main() {
  screen_clear();
  cpu_isr_install();

  asm volatile("int $0");
  asm volatile("int $1");
  asm volatile("int $2");

  asm volatile("int $32");

  return 0;
}
