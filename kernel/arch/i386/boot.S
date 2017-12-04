/* Declare constants for multiboot header */
.set ALIGN,    1<<0              # Align loaded modules on page boundaries
.set MEMINFO,  1<<1              # Provide memory map
.set FLAGS,    ALIGN | MEMINFO   # Multiboot flag field
.set MAGIC,    0x1BADB002        # 'Magic number' for finding the header
.set CHECKSUM, -(MAGIC + FLAGS)  # Proves we are in multiboot

/* Declare multiboot header which marks the program as a kernel */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Allocate stack */
.section .bss  #
.align 16      # Allocate a small stack
stack_bottom:  #
.skip 16384    # Skip 16KiB
stack_top:     #

/* Entry point of the kernel */
.section .text
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp  # Set esp register to top of the stack

    /* Call the global constructors */
    call _init

    /* Enter the kernel */
    call kernel_main

    /* If returns for whatever reason, enter infinite loop to hang */
    cli     # Disable interrupts
1:  hlt     # Wait for next interrupt (which shouldn't occur)
    jmp 1b  # Jump to hlt instruction if it ever wakes up

/* Set size of _start symbol to current location '.', minus the start */
.size _start, . - _start
