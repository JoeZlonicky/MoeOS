#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int place_char(int);
int place_string(const char*);

#ifdef __cplusplus
}
#endif

#endif
