#include "idt.h"
#include "types.h"

Idt_Entry idt[IDT_ENTRIES];
Idt_Register idt_reg;

void cpu_idt_set_entry(int n, uint32_t handler) {
  idt[n].low_offset = low_16(handler);
  idt[n].reserved_zeros = 0;
  idt[n].segment_selector = KERNEL_CS;
  idt[n].flags = 0x8E;
  idt[n].high_offset = high_16(handler);
}

void cpu_idt_set() {
  idt_reg.offset = (uint32_t)&idt;
  idt_reg.size = IDT_ENTRIES * sizeof(Idt_Entry) - 1;
  asm volatile("lidt (%0)" : : "r"(&idt_reg));
  asm volatile("sti");
}
