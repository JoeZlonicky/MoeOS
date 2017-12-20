#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/kerboard.h>


void kernel_main(void) {
  terminal_initialize();
  printf("Hello from the kernel!\n");
  printf(get_char())
}
