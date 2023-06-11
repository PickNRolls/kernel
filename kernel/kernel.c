#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "util.h"

void kernel_handle_keyboard(Keyboard_Packet packet) {
  if (!packet.is_released) {
    char s[] = {packet.ascii, 0};
    screen_print(s);

    if (packet.is_shift_pressed) {
      screen_print("\nShift is pressed\n");
    }

    if (packet.is_ctrl_pressed) {
      screen_print("\nCtrl is pressed\n");
    }

    if (packet.is_caps_pressed) {
      screen_print("\nCaps is pressed\n");
    }

    if (packet.is_caps_toggled) {
      screen_print("\nCaps is toggled\n");
    }
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
