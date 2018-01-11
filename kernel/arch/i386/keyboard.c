#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <kernel/keyboard.h>


char scan_codes[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', '=',
 '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[',
 ']', '\n', 0, 'a','s', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 0, 0, 0,
 0, 0, 'z', 'x', 'c', 'v', 'b', 'n', 'm',',', '.', '/', 0, '*', 0,
 ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-',
 '4', '5', '6', '+', '1', '2', '3', '0', '.'};


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

char get_char()
{
  while(1) {
    unsigned int index = get_scancode();
    bool valid_character = scan_codes[index] != (char)0;
    bool in_range = index < sizeof(scan_codes)/sizeof(scan_codes[0]);
    if(valid_character && in_range)
      return scan_codes[index];
  }
}
