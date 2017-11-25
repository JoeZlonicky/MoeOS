/* Declare constants */
.set ALIGN,    1<<0             # Bitwise shift left 0 (equals 1)
.set MEMINFO,  1<<1             # Bitwise shift left 1 (equals 2)
.set FLAGS,    ALIGN | MEMINFO  #
.set MAGIC,    0x1BADB002       # 'Magic number' that lets bootloader find the header
.set CHECKSUM, -(MAGIC +FLAGS)  # Proves we are in multiboot

/* Declare multiboot header which marks the program as a kernal */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Allocate stack */
.section .bss  #
.align 16      # Allocate a small stack
stack_bottom:  #
.skip 16384    # Allocate 16KiB
stack_top:     #

/* Entry point of kernal */
.section .text
.global _start
.type _start, @function

_start:
    mov $stack_top, %esp  # Set esp register to top of stack

    call kernel_main      # Enter the kernel

    /* If nothing else to do, enter infinate loop */
    cli     # Disable interrupts
1:  hlt     # Wait for next interrupt (which shouldn't happen)
    jmp 1b  # Jump to hlt intruction if it ever wakes up

/* Set suze if _start symbol to current location '.' minus its start */
.size _start, . - _start
