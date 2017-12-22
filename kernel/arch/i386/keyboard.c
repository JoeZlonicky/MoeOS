#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <kernel/keyboard.h>


unsigned char scan_code[11] =
{
    'a', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'
};		

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
        printf(itoa(c, 10));
        return c;
    }
  } while(1);
}

char* get_char()
{
    int scan_code_number = get_scancode();
    return scan_code[scan_code_number];
}
