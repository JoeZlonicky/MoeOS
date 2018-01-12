#include <kernel/tty.h>
#include <kernel/welcome_screen.h>
#include <kernel/color_menu.h>
#include <kernel/command_terminal.h>
#include <kernel/menu_features.h>
#include <kernel/shutdown.h>
#include <stdio.h>
#include <stdint.h>


void update_main_menu_options(int y_pos);

char option_list[5][40] = {"TicTacToe(Not Implemented)", "Terminal",
                           "Change Font Color", "Change Background Color",
                           "Shutdown(Not Implemented)"};

void kernel_main(void) {
  terminal_initialize();
  welcome_screen();

  int y_position = 0;
  update_main_menu_options(y_position);
  while(1) {
    char user_input = get_menu_input();
    if(user_input == 'w' && y_position > 0)
      --y_position;
    else if(user_input == 's' && y_position < 4)
      ++y_position;
    if(user_input == 'w' || user_input == 's')
      update_main_menu_options(y_position);

    if(user_input == '\n') {
      switch(y_position) {
        case 0:
          printf("Playing tic tac toe");
          break;
        case 1:
          terminal_clear();
          command_terminal_loop();
          break;
        case 2:
          color_menu_loop('f');
          break;
        case 3:
          color_menu_loop('b');
          break;
        case 4:
          printf("Shutting down");
          shutdown();
          break;
        default:
          break;
      }
      //update_main_menu_options(y_position);
    }

  }
}

void update_main_menu_options(int y_pos){
  terminal_clear();
  for(int y=0; y < 5; ++y) {
    bool highlighted = false;
    if(y==y_pos)
      highlighted = true;
    printf(" ");
    print_option(option_list[y], highlighted);
    printf("\n");
  }
}
