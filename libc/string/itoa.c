#include <string.h>


char* itoa(int value, int base)
{
  static char buffer[32] = {0};
  int i = 30;

  for(; value && i; --i, value/= base)
  {
    buffer[i] = "0123456789abcdef"[value % base];
  }
  return &buffer[i+1];
}
