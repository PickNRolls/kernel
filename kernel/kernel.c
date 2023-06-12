#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "util.h"

void kernel_handle_keyboard(Keyboard_Packet packet) {
  if (!packet.is_released) {
    char s[] = {packet.ascii, 0};
    screen_print(s);
  }
}

int kernel_main() {
  screen_clear();

  cpu_isr_install();
  cpu_timer_init();

  keyboard_init();
  keyboard_register_handler(kernel_handle_keyboard);

  return 0;
}
