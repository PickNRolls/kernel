#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/screen.h"
#include "util.h"

int kernel_main() {
  screen_clear();
  cpu_isr_install();
  cpu_timer_init();
  asm("sti");

  return 0;
}
