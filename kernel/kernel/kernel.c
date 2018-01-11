#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <../arch/i386/vga.h>

void print_option(char* name, bool highlighted);
void get_input(char command_array[80]);
void welcome_screen();

void kernel_main(void) {
  terminal_initialize();
  welcome_screen();
  while (1) {
    char user_input[80];
    char hello_command[80] = "hello";
    get_input(user_input);
    if(memcmp(user_input, hello_command, 80) == 0) {
      printf("\nHello, world");
    }
    printf("\n");
  }
}

void print_option(char* name, bool highlighted) {
  if(highlighted)
    terminal_set_color(VGA_COLOR_BLACK | VGA_COLOR_LIGHT_GREY << 4);
  printf("%s\n", name);
  if(highlighted)
    terminal_set_color(VGA_COLOR_LIGHT_GREY | VGA_COLOR_BLACK << 4);
}

void get_input(char command_array[80]) {
  for(int x=0; x < 79; ++x) {
    command_array[x] = '\0';
  }
  int position = 0;
  printf(">");
  while(1) {
    char user_input = get_char();
    if(user_input == '\n') {
      break;
    }
    else if(user_input == '\b') {
      if(position > 0) {
        --position;
        command_array[position] = '\0';
        backspace();
      }
    }
    else {
      command_array[position] = user_input;
      printf("%c", user_input);
      ++position;
    }
  }
}

void welcome_screen() {
  printf("  88b           d88    ,ad8888ba,    88888888888     ,ad8888ba,     ad88888ba  \n");
  printf("  888b         d888   d8''    `'8b   88             d8''    `'8b   d8'     '8b \n");
  printf("  88`8b       d8'88  d8'        `8b  88            d8'        `8b  Y8,         \n");
  printf("  88 `8b     d8' 88  88          88  88aaaaa       88          88  `Y8aaaaa,   \n");
  printf("  88  `8b   d8'  88  88          88  88'''''       88          88    `'''''8b, \n");
  printf("  88   `8b d8'   88  Y8,        ,8P  88            Y8,        ,8P          `8b \n");
  printf("  88    `888'    88   Y8a.    .a8P   88             Y8a.    .a8P   Y8a     a8P \n");
  printf("  88     `8'     88    `Y8888Y''     88888888888     `'Y8888Y''     'Y88888P'  \n");
  printf(" 888888888888888888888888888888888888888888888888888888888888888888888888888888\n");
  printf("             8888888888888  PRESS ANYTHING TO START  8888888888888             \n");
  printf("                      88888888888888888888888888888888888                      \n");
  get_char();
  terminal_clear();
}
