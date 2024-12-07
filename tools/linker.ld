ENTRY(_start)

SECTIONS
{
  . = 1M;
  .text : { *(.text) }
  .data : { *(.data) }
  .bss : { *(.bss) }

  /* Mark the stack segment as not executable */
  .stack (NOLOAD) : { *(.stack) }

  /* Other sections can go here */
}
