#include<kernel/menu_features.h>

#include<stdbool.h>
#include<kernel/tty.h>
#include<kernel/keyboard.h>
#include<stdio.h>
#include<string.h>


void print_option(char* name, bool highlighted) {
  if(highlighted)
    terminal_reverse_colors();
  printf(name);
  if(highlighted)
    terminal_reverse_colors();
}

char get_menu_input() {
  int old_fg_color = get_terminal_fg_color();
  terminal_set_fg_color(get_terminal_bg_color());
  printf(" ");
  backspace();
  char user_input = get_char();
  terminal_set_fg_color(old_fg_color);
  return user_input;
}
