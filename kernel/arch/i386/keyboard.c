#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kernel/keyboard.h>


char* scan_codes[] = {0, 0, "1", "2", "3", "4", "5", "6", "7", "8", "9", "0"
, 0, 0, 0, 0, "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", 0, 0, 0, 0, "a",
"s", "d", "f", "g", "h", "j", "k", "l", 0, 0, 0, 0, 0, "z", "x", "c", "v", "b", "n", "m" };

char* valid_characters[] = {" ", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "a",
"b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s",
"t", "u", "v", "w", "x", "y", "z"};

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
        for(int x=0; x < sizeof(valid_characters)/sizeof(valid_characters[0]); ++x) {
            if (character == valid_characters[x]) return character;
        }
    }
}
