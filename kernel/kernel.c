#include "../cpu/isr.h"
#include "../cpu/paging.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../memlayout.h"
#include "util.h"

void kernel_handle_keyboard(Keyboard_Packet packet) {
  if (!packet.is_released) {
    char s[] = {packet.ascii, 0};
    screen_print(s);
  }
}

void handle_page_fault(Registers *r) { screen_print("Page fault\n"); }

int kernel_main() {
  cpu_isr_install();
  cpu_isr_register_handler(14, handle_page_fault);

  screen_clear();
  cpu_timer_init();
  keyboard_init();
  keyboard_register_handler(kernel_handle_keyboard);

  while (1) {
  }

  return 0;
}
