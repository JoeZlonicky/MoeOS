#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void terminal_initialize(void);
void terminal_place_char(char c);
void terminal_write(const char* data, size_t size);
void terminal_print(const char* string);
void terminal_clear(void);
#endif
