#include <kernel/tictactoe.h>
#include <kernel/keyboard.h>
#include <stdio.h>
#include <kernel/menu_features.h>
#include <kernel/tty.h>
#include <stdbool.h>
#include <string.h>


char board_design[11][17] = {"     |     |     ",
                             "     |     |     ",
                             "     |     |     ",
                             "-----+-----+-----",
                             "     |     |     ",
                             "     |     |     ",
                             "     |     |     ",
                             "-----+-----+-----",
                             "     |     |     ",
                             "     |     |     ",
                             "     |     |     "};

char x_design[3][6] = {" \\ / ",
                       "  X  ",
                       " / \\ "};

char o_design[3][6] = {" /-\\ ",
                       " | | ",
                       " \\-/ "};

char board[3][3];

char message[80];

int current_player = 1;

void tictactoe_loop() {
  reset_game();
  while(1) {
    draw_board();
    draw_all_icons();
    print_message();
    print_current_player();
    handle_input();
    if(game_completed()) {
      if(wants_to_play_again())
        reset_game();
      else {
        break;
      }
    }

  }
}

void draw_board() {
  terminal_clear();
  for(int y=0; y < 11; ++y) {
    for(int x=0; x < 17; ++x) {
      printf("%c", board_design[y][x]);
    }
    printf("\n");
  }
}

void draw_all_icons() {
  for(int y=0; y < 3; ++y) {
    for(int x=0; x < 3; ++x) {
      if(board[y][x] == 'x')
        draw_icon('x', x, y);
      else if(board[y][x] == 'o'){
        draw_icon('y', x, y);
      }
    }
  }
}

void draw_icon(char c, int x_pos, int y_pos) {
  int starting_x = x_pos*6;
  int starting_y = y_pos*4;
  for(int y=0; y < 3; ++y) {
    for(int x=0; x < 5; ++x) {
      if(c == 'x') {
        char icon_c = x_design[y][x];
        terminal_place_entry(icon_c, x + starting_x, y + starting_y);
      }
      else {
        char icon_c = o_design[y][x];
        terminal_place_entry(icon_c, x + starting_x, y + starting_y);
      }
    }
  }
}

void print_message() {
  printf("%s\n", message);
}

void print_current_player() {
  printf("Player %s's turn\n", itoa(current_player, 10));
}

void handle_input() {
  char user_input = get_menu_input();
  if(user_input == '7')
    attempt_place(0, 0);
  else if(user_input == '8')
    attempt_place(1, 0);
  else if(user_input == '9')
    attempt_place(2, 0);
  else if(user_input == '4')
    attempt_place(0, 1);
  else if(user_input == '5')
    attempt_place(1, 1);
  else if(user_input == '6')
    attempt_place(2, 1);
  else if(user_input == '1')
    attempt_place(0, 2);
  else if(user_input == '2')
    attempt_place(1, 2);
  else if(user_input == '3')
    attempt_place(2, 2);
  else
    set_message("Invalid input");
}

void attempt_place(int x, int y) {
  if(board[y][x] == '\0') {
    if(current_player == 1) {
      board[y][x] = 'x';
      current_player = 2;
    }
    else if(current_player == 2) {
      board[y][x] = 'o';
      current_player = 1;
    }
    set_message("");
  }
  else {
    set_message("Sorry, that spot is taken");
  }
}

void set_message(char new_message[80]) {
  memcopy(message, new_message, 80);
}

bool game_completed() {
  if(player_won('x')) {
    set_message("Player 1 has won the game!!!");
    draw_board();
    draw_all_icons();
    print_message();
    return true;
  }
  else if(player_won('o')) {
    set_message("Player 2 has won the game!!!");
    draw_board();
    draw_all_icons();
    print_message();
    return true;
  }
  else if(board_is_full()) {
    set_message("The game is a draw");
    draw_board();
    draw_all_icons();
    print_message();
    return true;
  }
  else
    return false;
}

bool player_won(char c) {
  if(board[0][0] == c && board[1][0] == c && board[2][0] == c)
    return true;
  if(board[0][1] == c && board[1][1] == c && board[2][1] == c)
    return true;
  if(board[0][2] == c && board[1][2] == c && board[2][2] == c)
    return true;
  if(board[0][0] == c && board[0][1] == c && board[0][2] == c)
    return true;
  if(board[1][0] == c && board[1][1] == c && board[1][2] == c)
    return true;
  if(board[2][0] == c && board[2][1] == c && board[2][2] == c)
    return true;
  if(board[0][0] == c && board[1][1] == c && board[2][2] == c)
    return true;
  if(board[2][0] == c && board[1][1] == c && board[0][2] == c)
    return true;
  return false;
}

bool board_is_full() {
  bool full_board = true;
  for(int y=0; y < 3; ++y) {
    for(int x=0; x < 3; ++x) {
      if(board[y][x] == '\0')
        full_board = false;
    }
  }
  return full_board;
}

bool wants_to_play_again() {
  printf("Would you like to play again?(y or n)");
  while(1) {
    char user_input = get_menu_input();
    if(user_input == 'y') {
      return true;
    }
    else if(user_input == 'n')
      return false;
  }
}

void reset_game() {
  for(int y=0; y < 3; ++y) {
    for(int x=0; x < 3; ++x) {
      board[y][x] = '\0';
    }
  }
  current_player = 1;
  set_message("");
}
