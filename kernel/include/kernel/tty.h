#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

void terminal_initialize(void);
void terminal_set_color(uint8_t fg_color, uint8_t bg_color);
void terminal_place_char(char c);
void terminal_write(const char* data, size_t size);
void terminal_print(const char* string);
void terminal_clear(void);
void terminal_reverse_colors();
void backspace(void);
#endif
