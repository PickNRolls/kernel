CR0_PAGING equ 0x80000000
CR0_WRITE_PROTECTION equ 0x00010000
CR4_PAGE_SIZE_EXT equ 0x00000010
KERNEL_BASE equ 0x80000000

global _start;
[bits 32]

_start:
  mov eax, cr4
  or eax, CR4_PAGE_SIZE_EXT
  mov cr4, eax
  ; Set page directory
  [extern kernel_entry_pgdir]
  ; Defined in cpu/paging.c
  mov eax, kernel_entry_pgdir - KERNEL_BASE
  mov cr3, eax
  ; Turn on paging.
  mov eax, cr0
  or eax, CR0_PAGING | CR0_WRITE_PROTECTION
  mov cr0, eax

  ; Set up the stack pointer.
  mov ebp, 0x80090000
  mov esp, ebp

  [extern kernel_main]
  mov eax, kernel_main
  call eax
  jmp $
