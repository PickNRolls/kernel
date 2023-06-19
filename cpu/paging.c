#include "paging.h"

__attribute__((__aligned__(PAGE_SIZE))) Pde kernel_entry_pgdir[PDE_N] = {
    [0] = (0) | PTE_PRESENT | PTE_WRITE | PTE_PAGE_SIZE,
    [KERNEL_BASE >> PDX_SHIFT] = (0) | PTE_PRESENT | PTE_WRITE | PTE_PAGE_SIZE};
