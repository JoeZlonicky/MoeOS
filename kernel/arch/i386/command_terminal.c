#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <kernel/command_terminal.h>
#include <kernel/keyboard.h>
#include <kernel/tty.h>

static char hello_command[80] = "hello";
static char clear_command[80] = "clear";
static char truth_command[80] = "do i know the way";
static char exit_command[80] = "exit";

void command_terminal_loop() {
  while(1) {
    char user_input[80];
    get_command(user_input);
    if(memcmp(user_input, hello_command, 80) == 0) {
      printf("\n Hello, world");
    }
    else if(memcmp(user_input, truth_command, 80) == 0) {
        printf("\n You do not know de way");
    }
    else if(memcmp(user_input, exit_command, 80) == 0) {
      terminal_clear();
      break;
    }

    printf("\n");

    if(memcmp(user_input, clear_command, 80) == 0) {
        terminal_clear();
    }
  }
}
void get_command(char command_array[80]) {
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
    else if(user_input == '\t') {
        position += 4;
        printf("    ");
    }
    else {
      command_array[position] = user_input;
      printf("%c", user_input);
      ++position;
    }
  }
}
