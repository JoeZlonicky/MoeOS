#include <stdio.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>


void kernel_main(void) {
  terminal_initialize();
  printf("Keyboard input: ");
  printf(itoa(get_char(), 2));
}
