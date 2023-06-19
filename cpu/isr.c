#include "isr.h"
#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "../kernel/util.h"
#include "idt.h"

Isr *interrupt_handlers[256];

void cpu_isr_install() {
  cpu_idt_set_entry(0, (uint32_t)isr0);
  cpu_idt_set_entry(1, (uint32_t)isr1);
  cpu_idt_set_entry(2, (uint32_t)isr2);
  cpu_idt_set_entry(3, (uint32_t)isr3);
  cpu_idt_set_entry(4, (uint32_t)isr4);
  cpu_idt_set_entry(5, (uint32_t)isr5);
  cpu_idt_set_entry(6, (uint32_t)isr6);
  cpu_idt_set_entry(7, (uint32_t)isr7);
  cpu_idt_set_entry(8, (uint32_t)isr8);
  cpu_idt_set_entry(9, (uint32_t)isr9);
  cpu_idt_set_entry(10, (uint32_t)isr10);
  cpu_idt_set_entry(11, (uint32_t)isr11);
  cpu_idt_set_entry(12, (uint32_t)isr12);
  cpu_idt_set_entry(13, (uint32_t)isr13);
  cpu_idt_set_entry(14, (uint32_t)isr14);
  cpu_idt_set_entry(15, (uint32_t)isr15);
  cpu_idt_set_entry(16, (uint32_t)isr16);
  cpu_idt_set_entry(17, (uint32_t)isr17);
  cpu_idt_set_entry(18, (uint32_t)isr18);
  cpu_idt_set_entry(19, (uint32_t)isr19);
  cpu_idt_set_entry(20, (uint32_t)isr20);
  cpu_idt_set_entry(21, (uint32_t)isr21);
  cpu_idt_set_entry(22, (uint32_t)isr22);
  cpu_idt_set_entry(23, (uint32_t)isr23);
  cpu_idt_set_entry(24, (uint32_t)isr24);
  cpu_idt_set_entry(25, (uint32_t)isr25);
  cpu_idt_set_entry(26, (uint32_t)isr26);
  cpu_idt_set_entry(27, (uint32_t)isr27);
  cpu_idt_set_entry(28, (uint32_t)isr28);
  cpu_idt_set_entry(29, (uint32_t)isr29);
  cpu_idt_set_entry(30, (uint32_t)isr30);
  cpu_idt_set_entry(31, (uint32_t)isr31);

  port_byte_out(0x20, 0x11);
  port_byte_out(0xA0, 0x11);
  port_byte_out(0x21, 0x20);
  port_byte_out(0xA1, 0x28);
  port_byte_out(0x21, 0x04);
  port_byte_out(0xA1, 0x02);
  port_byte_out(0x21, 0x01);
  port_byte_out(0xA1, 0x01);
  port_byte_out(0x21, 0x0);
  port_byte_out(0xA1, 0x0);

  cpu_idt_set_entry(32, (uint32_t)irq0);
  cpu_idt_set_entry(33, (uint32_t)irq1);
  cpu_idt_set_entry(34, (uint32_t)irq2);
  cpu_idt_set_entry(35, (uint32_t)irq3);
  cpu_idt_set_entry(36, (uint32_t)irq4);
  cpu_idt_set_entry(37, (uint32_t)irq5);
  cpu_idt_set_entry(38, (uint32_t)irq6);
  cpu_idt_set_entry(39, (uint32_t)irq7);
  cpu_idt_set_entry(40, (uint32_t)irq8);
  cpu_idt_set_entry(41, (uint32_t)irq9);
  cpu_idt_set_entry(42, (uint32_t)irq10);
  cpu_idt_set_entry(43, (uint32_t)irq11);
  cpu_idt_set_entry(44, (uint32_t)irq12);
  cpu_idt_set_entry(45, (uint32_t)irq13);
  cpu_idt_set_entry(46, (uint32_t)irq14);
  cpu_idt_set_entry(47, (uint32_t)irq15);

  cpu_idt_set(); // Load with ASM
}

void cpu_isr_register_handler(uint32_t int_no, Isr *handler) {
  interrupt_handlers[int_no] = handler;
}

char *exception_messages[] = {"Division By Zero",
                              "Debug",
                              "Non Maskable Interrupt",
                              "Breakpoint",
                              "Into Detected Overflow",
                              "Out of Bounds",
                              "Invalid Opcode",
                              "No Coprocessor",

                              "Double Fault",
                              "Coprocessor Segment Overrun",
                              "Bad TSS",
                              "Segment Not Present",
                              "Stack Fault",
                              "General Protection Fault",
                              "Page Fault",
                              "Unknown Interrupt",

                              "Coprocessor Fault",
                              "Alignment Check",
                              "Machine Check",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",

                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved"};

void isr_handler(Registers *r) {
  if (interrupt_handlers[r->int_no] != 0) {
    Isr *handler = interrupt_handlers[r->int_no];
    handler(r);
  }
}

void irq_handler(Registers *r) {
  if (r->int_no >= 40) {
    port_byte_out(0xA0, 0x20); /* slave */
  }
  port_byte_out(0x20, 0x20); /* master */

  if (interrupt_handlers[r->int_no] != 0) {
    Isr *handler = interrupt_handlers[r->int_no];
    handler(r);
  }
}
