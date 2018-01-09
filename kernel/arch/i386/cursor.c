#include <stdint.h>
#include <stddef.h>
#include <kernel/cursor.h>

static inline void outb(uint16_t port, uint8_t value) {
  asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port) );
}

void update_cursor(int x, int y, size_t vga_width) {
  uint16_t pos = y * vga_width + x;
  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t) (pos & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}
