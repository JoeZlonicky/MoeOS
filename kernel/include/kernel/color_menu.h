#ifndef _KERNEL_COLOR_MENU_H
#define _KERNEL_COLOR_MENU_H

#include <stdint.h>
#include <stdbool.h>

void color_menu_loop(char fg_or_bg);
void update_color_menu_options(int x_pos, int y_pos);
void print_option(char* name, bool highlighted);
#endif
