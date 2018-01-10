#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <../arch/i386/vga.h>

void print_option(char* name, bool highlighted);
const char* get_input();
void welcome_screen();

void kernel_main(void) {
  terminal_initialize();
  welcome_screen();
  print_option("Option 1", false);
  print_option("Option 2", true);
  print_option("Option 3", false);
  while (1) {
    char* user_input = get_input();
    printf("\nYou entered: %s\n", user_input);
    if(user_input == "clear") terminal_clear();
  }
}

void print_option(char* name, bool highlighted) {
  if(highlighted)
    terminal_set_color(VGA_COLOR_BLACK | VGA_COLOR_LIGHT_GREY << 4);
  printf("%s", name);
  if(highlighted)
    terminal_set_color(VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4);
  printf("\n");
}

const char* get_input() {
  char* command = "";
  int position = 0;
  while(1) {
    char* user_input = get_char();
    if(user_input == "\n") {
      return command;
    } else {
      command[position] = user_input[0];
      ++position;
      printf(user_input);
    }
  }
}
    
    
    
void welcome_screen() {
  printf("88b           d88    ,ad8888ba,    88888888888      ,ad8888ba,     ad88888ba\n");  
  printf("888b         d888   d8''    `'8b   88              d8''    `'8b   d8'     '8b\n");  
  printf("88`8b       d8'88  d8'        `8b  88             d8'        `8b  Y8,        \n");  
  printf("88 `8b     d8' 88  88          88  88aaaaa        88          88  `Y8aaaaa,  \n");  
  printf("88  `8b   d8'  88  88          88  88'''''        88          88    `'''''8b,\n");  
  printf("88   `8b d8'   88  Y8,        ,8P  88             Y8,        ,8P          `8b\n");  
  printf("88    `888'    88   Y8a.    .a8P   88              Y8a.    .a8P   Y8a     a8P\n");  
  printf("88     `8'     88    `Y8888Y''     88888888888      `'Y8888Y''     'Y88888P' \n");
  printf("88888888888888888888888888888888888888888888888888888888888888888888888888888\n");
  printf("                        8  PRESS ENTER TO CONTINUE  8                        \n");
  printf("                        88888888888888888888888888888                        \n");
  get_char();
  terminal_clear();
}
