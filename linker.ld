
SECTIONS {
    /* Kernel starts at 1MB memory location */
    . = 0x100000;

    /* Multiboot header must be at the start */
    .multiboot : {
        *(.multiboot)
    }

    /* Text section (code) */
    .text ALIGN(4K) : {
        *(.text)
    }

    /* Read-only data section */
    .rodata ALIGN(4K) : {
        *(.rodata)
    }

    /* Data section */
    .data ALIGN(4K) : {
        *(.data)
    }

    /* BSS section */
    .bss ALIGN(4K) : {
        *(COMMON)
        *(.bss)
    }

    /* End of kernel */
    end = .;
}
