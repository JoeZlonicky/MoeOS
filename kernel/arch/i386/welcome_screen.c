#include <kernel/welcome_screen.h>
#include <kernel/keyboard.h>
#include <kernel/tty.h>
#include <kernel/menu_features.h>
#include <stdio.h>

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
  get_menu_input();
  terminal_clear();
}
