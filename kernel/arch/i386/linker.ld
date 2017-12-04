/* Bootloader will start exectution at the designated symbol */
ENTRY(_start)

/* The various sections of the object files will be placed */
SECTIONS
{
  /* Begin at 1MiB */
  . = 1M;

  /* First place the multiboot header, then the .text section */
  .text BLOCK(4K) : ALIGN(4K)
  {
    *(.multiboot)
    *(.text)
  }

  /* Then place read-only data */
  .rodata BLOCK(4K) : ALIGN(4K)
  {
    *(.rodata)
  }

  /* Then place read-write data that is initialized */
  .data BLOCK(4K) : ALIGN(4K)
  {
    *(.data)
  }

  /* Then place read-write data that is unintialized */
  /* And place the stack */
  .bss BLOCK(4k) : ALIGN(4k)
  {
    *(COMMON)
    *(.bss)
  }
}
