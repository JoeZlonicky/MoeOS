#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/cursor.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint8_t fg_terminal_color = VGA_COLOR_LIGHT_GREY;
static uint8_t bg_terminal_color = VGA_COLOR_BLACK;
static uint16_t* terminal_buffer;

void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color =  vga_entry_color(fg_terminal_color, bg_terminal_color);
  terminal_buffer = VGA_MEMORY;
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_set_color(uint8_t fg_color, uint8_t bg_color) {
  fg_terminal_color = fg_color;
  bg_terminal_color = bg_color;
  terminal_color = fg_color | bg_color << 4;
}

void terminal_set_fg_color(uint8_t color) {
  terminal_set_color(color, bg_terminal_color);
}

void terminal_set_bg_color(uint8_t color) {
  terminal_set_color(fg_terminal_color, color);
}

void terminal_place_entry(unsigned char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_place_char(char c) {
  unsigned char u_c = c;
  if (u_c=='\n') {
    ++terminal_row;
    terminal_column = 0;
  } else if (u_c == '\t') {
      terminal_column += 4;
  } else {
    terminal_place_entry(u_c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
      terminal_column = 0;
      if (++terminal_row == VGA_HEIGHT)
        terminal_row = 0;
    }
  }
  update_cursor(terminal_column, terminal_row, VGA_WIDTH);
}

void terminal_write(const char* data, size_t size) {
  for (size_t i = 0; i < size; i++)
    terminal_place_char(data[i]);
}

void terminal_print(const char* string) {
  terminal_write(string, strlen(string));
}

void terminal_clear(void) {
  for(size_t y=0; y < VGA_HEIGHT; ++y) {
    for(size_t x=0; x < VGA_WIDTH; ++x) {
      terminal_place_entry(' ', terminal_color, x, y);
    }
  }
  terminal_row = 0;
  terminal_column = 0;
  update_cursor(terminal_column, terminal_row, VGA_WIDTH);
}

void backspace(void) {
  --terminal_column;
  terminal_place_char(' ');
  --terminal_column;
  update_cursor(terminal_column, terminal_row, VGA_WIDTH);
}

void terminal_reverse_colors(void) {
  terminal_set_color(bg_terminal_color, fg_terminal_color);
}

int get_terminal_fg_color(void) {
  return fg_terminal_color;
}

int get_terminal_bg_color(void) {
  return bg_terminal_color;
}
