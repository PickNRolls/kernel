#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../kernel/util.h"
#include "isr.h"
#include <stdint.h>

uint32_t tick = 0;

void handle_timer() { tick++; }

void cpu_timer_init() {
  cpu_isr_register_handler(IRQ0, handle_timer);

  /* Get the PIT value: hardware clock at 1193180 Hz */
  uint32_t divisor = 1193180 / 500;
  uint8_t low = (uint8_t)(divisor & 0xFF);
  uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);
  /* Send the command */
  port_byte_out(0x43, 0x36); /* Command port */
  port_byte_out(0x40, low);
  port_byte_out(0x40, high);
}
