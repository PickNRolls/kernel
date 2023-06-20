ENTRY(_start)

SECTIONS {
    . = 0x80001000;

    .text : {
        *(.text .text.*)
    }

    PROVIDE(etext = .);

    .rodata : {
        *(.rodata .rodata.*)
    }

    . = ALIGN(0x1000);

    PROVIDE(data = .);

    .data : {
        *(.data)
    }

    PROVIDE(edata = .);

    .bss : {
        *(.bss)
    }

    PROVIDE(end = .);
}

