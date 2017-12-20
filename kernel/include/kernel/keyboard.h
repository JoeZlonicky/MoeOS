// Header file
#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <stddef.h>


static inline uint8_t inb(uint16_t port);
char get_scancode();
char get_char();

#endif
