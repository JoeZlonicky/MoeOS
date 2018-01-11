#define SLP_EN (1 << 13)

#include <stdint.h>
#include <stdio.h>


void shutdown(){

  unsigned int i, j, len, count, found, *ptr, *rsdp = 0, *rsdt = 0,
  facp = 0;, dsdt = 0;

  unsigned char *data, slp_typ[2];

  for(ptr = (unsigned int *)0x000E0000; ptr < (unsigned int *)0x000FFFFF; ptr++){
    if(*ptr == ' DSR' && *(ptr + 1) == ' RTP'){
      if(crc8((unsigned char *)ptr, 20)) continue;
      rsdp = ptr;
      break;
    }
  }
  if(!rsdp) goto haltonly;

  //find RSDT table pointer
  ptr = (unsigned int *)*(ptr + 4);
  if(crc8((unsigned char *)ptr, *(ptr + 1))){
    printf("Error: RSDT checksum mismatch.\n");
    goto haltonly;
  }
  rsdt = ptr;
  count = (*(ptr + 1) - 36) / 4;


}
