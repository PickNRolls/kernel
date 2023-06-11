; Defined in isr.c
[extern isr_handler]
[extern irq_handler]

isr_common_handler:
	pusha
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	push esp

    cld
	call isr_handler
	
	pop eax 
	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	popa
	add esp, 8
	iret

irq_common_handler:
	pusha
	mov ax, ds
	push eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	push esp

    cld
	call irq_handler
	
	pop ebx 
	pop ebx
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx
	popa
	add esp, 8
	iret

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; 0: Divide By Zero Exception
isr0:
    push byte 0
    push byte 0
    jmp isr_common_handler

; 1: Debug Exception
isr1:
    push byte 0
    push byte 1
    jmp isr_common_handler

; 2: Non Maskable Interrupt Exception
isr2:
    push byte 0
    push byte 2
    jmp isr_common_handler

; 3: Int 3 Exception
isr3:
    push byte 0
    push byte 3
    jmp isr_common_handler

; 4: INTO Exception
isr4:
    push byte 0
    push byte 4
    jmp isr_common_handler

; 5: Out of Bounds Exception
isr5:
    push byte 0
    push byte 5
    jmp isr_common_handler

; 6: Invalid Opcode Exception
isr6:
    push byte 0
    push byte 6
    jmp isr_common_handler

; 7: Coprocessor Not Available Exception
isr7:
    push byte 0
    push byte 7
    jmp isr_common_handler

; 8: Double Fault Exception (With Error Code!)
isr8:
    push byte 8
    jmp isr_common_handler

; 9: Coprocessor Segment Overrun Exception
isr9:
    push byte 0
    push byte 9
    jmp isr_common_handler

; 10: Bad TSS Exception (With Error Code!)
isr10:
    push byte 10
    jmp isr_common_handler

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    push byte 11
    jmp isr_common_handler

; 12: Stack Fault Exception (With Error Code!)
isr12:
    push byte 12
    jmp isr_common_handler

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    push byte 13
    jmp isr_common_handler

; 14: Page Fault Exception (With Error Code!)
isr14:
    push byte 14
    jmp isr_common_handler

; 15: Reserved Exception
isr15:
    push byte 0
    push byte 15
    jmp isr_common_handler

; 16: Floating Point Exception
isr16:
    push byte 0
    push byte 16
    jmp isr_common_handler

; 17: Alignment Check Exception
isr17:
    push byte 0
    push byte 17
    jmp isr_common_handler

; 18: Machine Check Exception
isr18:
    push byte 0
    push byte 18
    jmp isr_common_handler

; 19: Reserved
isr19:
    push byte 0
    push byte 19
    jmp isr_common_handler

; 20: Reserved
isr20:
    push byte 0
    push byte 20
    jmp isr_common_handler

; 21: Reserved
isr21:
    push byte 0
    push byte 21
    jmp isr_common_handler

; 22: Reserved
isr22:
    push byte 0
    push byte 22
    jmp isr_common_handler

; 23: Reserved
isr23:
    push byte 0
    push byte 23
    jmp isr_common_handler

; 24: Reserved
isr24:
    push byte 0
    push byte 24
    jmp isr_common_handler

; 25: Reserved
isr25:
    push byte 0
    push byte 25
    jmp isr_common_handler

; 26: Reserved
isr26:
    push byte 0
    push byte 26
    jmp isr_common_handler

; 27: Reserved
isr27:
    push byte 0
    push byte 27
    jmp isr_common_handler

; 28: Reserved
isr28:
    push byte 0
    push byte 28
    jmp isr_common_handler

; 29: Reserved
isr29:
    push byte 0
    push byte 29
    jmp isr_common_handler

; 30: Reserved
isr30:
    push byte 0
    push byte 30
    jmp isr_common_handler

; 31: Reserved
isr31:
    push byte 0
    push byte 31
    jmp isr_common_handler


irq0:
    push byte 0
    push byte 32
    jmp irq_common_handler

irq1:
    push byte 1
    push byte 33
    jmp irq_common_handler

irq2:
    push byte 2
    push byte 34
    jmp irq_common_handler

irq3:
    push byte 3
    push byte 35
    jmp irq_common_handler

irq4:
    push byte 4
    push byte 36
    jmp irq_common_handler

irq5:
    push byte 5
    push byte 37
    jmp irq_common_handler

irq6:
    push byte 6
    push byte 38
    jmp irq_common_handler

irq7:
    push byte 7
    push byte 39
    jmp irq_common_handler

irq8:
    push byte 8
    push byte 40
    jmp irq_common_handler

irq9:
    push byte 9
    push byte 41
    jmp irq_common_handler

irq10:
    push byte 10
    push byte 42
    jmp irq_common_handler

irq11:
    push byte 11
    push byte 43
    jmp irq_common_handler

irq12:
    push byte 12
    push byte 44
    jmp irq_common_handler

irq13:
    push byte 13
    push byte 45
    jmp irq_common_handler

irq14:
    push byte 14
    push byte 46
    jmp irq_common_handler

irq15:
    push byte 15
    push byte 47
    jmp irq_common_handler

