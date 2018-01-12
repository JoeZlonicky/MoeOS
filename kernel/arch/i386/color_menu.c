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
char second_option_list[20][20] = {"Dark Grey    ", "Light Blue   ", "Light Green  ",
                                   "Light Cyan   ", "Light Red    ", "Light Magenta",
                                   "Yellow       ", "White        "};

void color_menu_loop(char fg_or_bg) {
  int y_position = 0;
  int x_position = 0;
  update_color_menu_options(x_position, y_position);
  while(1) {
    char user_input = get_char();
    if((user_input == 'w') && y_position > 0)
      --y_position;
    else if(user_input == 's' && y_position < 8) {
      ++y_position;
      if(x_position == 1 && y_position == 8)
        --x_position;
    }
    else if(user_input == 'a' && x_position == 1)
      --x_position;
    else if(user_input == 'd' && x_position == 0 && y_position < 8)
      ++x_position;
    if(user_input == 'w' || user_input == 's' || user_input == 'a' ||
       user_input == 'd') {
       update_color_menu_options(x_position, y_position);
    }
    if(user_input == '\n') {
      int index = y_position;
      if(x_position == 1)
        index += 8;
      if(index == 8) {
        terminal_clear();
        break;
      }
      else {
        if(fg_or_bg == 'b')
          terminal_set_bg_color(index);
        else
          terminal_set_fg_color(index);
        update_color_menu_options(x_position, y_position);
      }

    }
  }
}

void update_color_menu_options(int x_pos, int y_pos) {
  terminal_clear();
  printf(" Choose a color: \n");
  for(int y=0; y<9; ++y) {
    for(int x=0; x<2; ++x) {
      bool highlighted = false;
      if(x==x_pos && y==y_pos)
        highlighted = true;
      if(x==0) {
        printf(" ");
        print_option(first_option_list[y], highlighted);
        printf("   ");
      }
      else
        print_option(second_option_list[y], highlighted);
    }
    printf("\n");
    if(y==7)
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
