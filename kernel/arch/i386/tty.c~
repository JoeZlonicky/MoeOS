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
static uint16_t* terminal_buffer;

void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color =  vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = VGA_MEMORY;
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_set_color(uint8_t color) {
  terminal_color = color;
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
    printf(">");
  } else if (u_c == '\b') {
        if (terminal_column > 1) {
            --terminal_column;
            terminal_place_entry(' ', terminal_color, terminal_column, terminal_row);
        }
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
}
