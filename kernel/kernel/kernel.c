#include <stdio.h>
#include <stdbool.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <../arch/i386/vga.h>

void kernel_main(void) {
  terminal_initialize();
  print_option("Option 1", false);
  print_option("Option 2", true);
  print_option("Option 3", false);
  while (1) {
    printf(get_char());
  }
}

void print_option(char* name, bool highlighted) {
  if(highlighted)
    terminal_set_color(VGA_COLOR_BLACK | VGA_COLOR_LIGHT_GREY << 4);
  printf("%s\n", name);
  if(highlighted)
    terminal_set_color(VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4);
}
    
    
