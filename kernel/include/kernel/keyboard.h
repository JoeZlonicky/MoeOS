#ifndef _KEYBOARD_H
#define _KEYBOARD_H


#include <stdint.h>

uint8_t inb(uint16_t port);
char get_scancode();
char get_char();

#endif
