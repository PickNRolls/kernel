#ifndef CPU_PAGING_HEADER
#define CPU_PAGING_HEADER

#include "../memlayout.h"
#include <stdint.h>

typedef uint32_t Pde;

#define PAGE_SIZE 4096
#define PDE_N 1024

#define PTE_PRESENT 0x1
#define PTE_WRITE 0x2
#define PTE_PAGE_SIZE 0x80
#define PDX_SHIFT 22

#endif
