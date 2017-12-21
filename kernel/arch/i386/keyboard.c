#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kernel/keyboard.h>


static inline uint8_t inb(uint16_t port)
{
  uint8_t ret;
  asm volatile ( "inb %1, %0"
                 : "=a"(ret)
                 : "Nd"(port) );
  return ret;
}

char get_scancode()
{
  char c = 0;
  while(1) {
    if(inb(0x60) != (unsigned)c) {
      c = inb(0x60);
      if(c > 0)
        return c;
    }
  }
}

char get_char()
{
    return get_scancode() + 1;
}
