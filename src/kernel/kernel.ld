ENTRY(_start)

SECTIONS {
    . = 0x10000;  /* Kernel will be loaded at 0x10000 */
    .text : {
        *(.text)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
    }
}
