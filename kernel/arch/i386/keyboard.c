#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kernel/keyboard.h>


char* scan_codes[] = {0, 0, "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"
, "-", "=", "\b", "\t", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "\n", 0, "a",
"s", "d", "f", "g", "h", "j", "k", "l", 0, 0, 0, 0, 0, "z", "x", "c", "v", "b", "n", "m",
",", ".", "/", 0, "*", 0, " ", };

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
  char flag = inb(0x64);
  while(!(flag & 1)) {
    flag = inb(0x64);
  }
  return inb(0x60);
}

char* get_char()
{
    while(1) {
        int index = get_scancode();
        char* character = scan_codes[index];
        if (character != (char*)0) {
          return character;
        }
    }
}
