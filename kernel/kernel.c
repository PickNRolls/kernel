#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/screen.h"
#include "util.h"

int kernel_main() {
  screen_clear();
  cpu_isr_install();
  asm("sti");
  cpu_timer_init();

  return 0;
}
