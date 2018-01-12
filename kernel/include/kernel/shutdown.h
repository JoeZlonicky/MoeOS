#ifndef _KERNEL_SHUTDOWN_H
#define _KERNEL_SHUTDOWN_H

void shutdown();
static void init_crc8();
unsigned char crc8(unsigned char *crc, unsigned char m);

#endif
