ENTRY(_start)

MEMORY {
    CODE (rx) : ORIGIN = 0x100000, LENGTH = 16M  /* Read/Execute region for code */
    DATA (rw) : ORIGIN = 0x2000000, LENGTH = 8M  /* Read/Write region for data */
    BSS  (rw) : ORIGIN = 0x3000000, LENGTH = 4M  /* Read/Write region for uninitialized data */
    STACK (rw) : ORIGIN = 0x4000000, LENGTH = 2M /* Read/Write region for stack */
}

SECTIONS {
    /* Set the base address of the program */
    . = 1M;

    /* .text section contains the executable code, marked as executable */
    .text : {
        *(.text)         /* All text (code) sections */
    } > CODE            /* Place this section in the 'CODE' memory region */

    /* .data section contains initialized data, marked as read-write but not executable */
    .data : {
        *(.data)         /* All data sections */
    } > DATA            /* Place this section in the 'DATA' memory region */

    /* .bss section contains uninitialized data, also read-write but not executable */
    .bss : {
        *(.bss)          /* All bss sections */
    } > BSS             /* Place this section in the 'BSS' memory region */

    /* Mark the stack segment as not executable */
    .stack (NOLOAD) : {
        *(.stack)        /* All stack sections */
    } > STACK           /* Ensure the stack is placed in the 'STACK' memory region */

    /* Ensure the stack has no execution permissions */
    .note.GNU-stack : { }

    /* .rodata section contains read-only data (like constants, strings) */
    .rodata : {
        *(.rodata)       /* All read-only data sections */
    } > CODE            /* Place this section in the 'CODE' memory region */

    /* Optional custom section for kernel entry code */
    .kernel : {
        *(.kernel_entry)  /* Ensure kernel entry code is placed in its own section */
    } > CODE
}
