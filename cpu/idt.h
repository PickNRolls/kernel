#ifndef CPU_IDT_HEADER
#define CPU_IDT_HEADER

#include <stdint.h>

#define KERNEL_CS 0x08

// https://wiki.osdev.org/Interrupt_Descriptor_Table
typedef struct {
  uint16_t low_offset;
  uint16_t segment_selector;
  uint8_t reserved_zeros;
  uint8_t flags;
  uint16_t high_offset;
} __attribute__((packed)) Idt_Entry;

typedef struct {
  uint16_t size;
  uint32_t offset;
} __attribute__((packed)) Idt_Register;

#define IDT_ENTRIES 256

void cpu_idt_set_entry(int n, uint32_t handler);
void cpu_idt_set();

#endif
