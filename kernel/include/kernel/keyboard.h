// Header file
#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <stddef.h>
#include <stdint.h>

static inline uint8_t inb(uint16_t port);
char get_scancode();
char get_char();

#endif
