#ifndef _KERNEL_CURSOR_H
#define _KERNEL_CURSOR_H

#include <stddef.h>
#include <stdint.h>

void update_cursor(int x, int y, size_t vga_width);

#endif
