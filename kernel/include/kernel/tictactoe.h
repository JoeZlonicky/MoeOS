#ifndef _KERNEL_TICTACTOE_H
#define _KERNEL_TICTACTOE_H

#include<stdint.h>
#include<stdbool.h>

void tictactoe_loop();
void draw_board();
void draw_all_icons();
void draw_icon(char c, int x_pos, int y_pos);
void print_message();
void print_current_player();
void handle_input();
void attempt_place(int x, int y);
void set_message(char new_message[80]);
bool game_completed();
bool player_won(char c);
bool board_is_full();
bool wants_to_play_again();
void reset_game();

#endif
