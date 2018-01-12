#include <kernel/color_menu.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <kernel/keyboard.h>
#include <kernel/tty.h>

char first_option_list[20][20] = {"Black     ", "Blue      ", "Green     ",
                              "Cyan      ", "Red       ", "Magenta   ",
                              "Brown     ", "Light Grey", "Return    "};
char second_option_list[20][20] = {"Dark grey", "Light blue", "Light green",
                               "Light cyan", "Light red", "Light magenta",
                               "Light brown", "White", "Apply"};
void color_menu_loop(char fg_or_bg) {
  int y_position = 0;
  int x_position = 0;
  update_options(x_position, y_position);
  while(1) {
    char user_input = get_char();
    printf("%c", user_input);
    if(user_input == '8' && y_position > 0)
      --y_position;
    else if(user_input == '2' && y_position < 8)
      ++y_position;
    else if(user_input == '4' && x_position == 1)
      --x_position;
    else if(user_input == '6' && x_position == 0)
      ++x_position;
    if(user_input == '8' || user_input == '2' || user_input == '4' ||
       user_input == '6')
       update_options(x_position, y_position);
  }
}

void update_options(int x_pos, int y_pos) {
  terminal_clear();
  for(int y=0; y<9; ++y) {
    for(int x=0; x<2; ++x) {
      bool highlighted = false;
      if(x==x_pos && y==y_pos)
        highlighted = true;
      if(x==0) {
        print_option(first_option_list[y], highlighted);
        printf("   ");
      }
      else
        print_option(second_option_list[y], highlighted);
    }
    printf("\n");
  }
}

void print_option(char* name, bool highlighted) {
  if(highlighted)
    terminal_reverse_colors();
  printf(name);
  if(highlighted)
    terminal_reverse_colors();
}
