#ifndef MEMLAYOUT_HEADER
#define MEMLAYOUT_HEADER

#define KERNEL_STACK_SIZE 4096

#define IO_MAPPED_OFFSET 0x1000
#define KERNEL_BASE 0x80000000
#define KERNEL_LINK (KERNEL_BASE + IO_MAPPED_OFFSET)

#define V2P(a) ((uint32_t)a - KERNEL_BASE)
#define P2V(a) ((uint32_t)a + KERNEL_BASE)

#define V2P_WO(x) (x - KERNEL_BASE)
#define P2V_WO(x) (x + KERNEL_BASE)

#endif
