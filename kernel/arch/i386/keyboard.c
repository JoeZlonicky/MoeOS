#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kernel/keyboard.h>


char* scan_codes[] = {0, 0, "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"
, 0, 0, 0, 0, "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", 0, 0, 0, 0, "a",
"s", "d", "f", "g", "h", "j", "k", "l", 0, 0, 0, 0, 0, "z", "x", "c", "v", "b", "n", "m" };

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
  do {
    if(inb(0x60) != (unsigned)c) {
      c = inb(0x60);

      if(c > 0)
        return c;
    }
  } while(1);
}

char* get_char()
{
    int index = get_scancode();
    return scan_codes[index];
}
