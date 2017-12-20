#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>


void kernel_main(void) {
  terminal_initialize();
  printf(get_char());
}
