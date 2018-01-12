#include <kernel/shutdown.h>
#define SLP_EN (1 << 13)
#define GP 0x107
#define DI 0x07


#include <stdint.h>
#include <stdio.h>
#include <kernel/cursor.h>
#include <string.h>

static unsigned char crc8_table[256];
static int made_table=0;

static void init_crc8(){
  int i,j;
  unsigned char crc;

  if(!made_table){
    for(i = 0; i < 256; i++){
      crc = i;
      for(int j = 0; j < 8; j++){
        crc = (crc << 1) ^ ((crc & 0x80) ? DI : 0);
      }
      crc8_table[i] = crc & 0xFF;
    }
    made_table = 1;
  }
}

unsigned char crc8(unsigned char *crc, unsigned char m){

  if(!made_table)
    init_crc8();

  *crc = crc8_table[(*crc) ^ m];
  *crc &= 0xFF;
  return crc;
}

#define SLP_EN	(1 << 13)
void shutdown() // by Napalm and Falkman
{
	unsigned int i, j, len, count, found, *ptr, *rsdp = 0, *rsdt = 0, *facp = 0, *dsdt = 0;
	unsigned char *data, slp_typ[2];

	// find acpi RSDP table pointer
	for(ptr = (unsigned int *)0x000E0000; ptr < (unsigned int *)0x000FFFFF; ptr++){
		if(*ptr == ' DSR' && *(ptr + 1) == ' RTP'){ // "RSD PTR "
			if(crc8((unsigned char *)ptr, 20)) continue;
			rsdp = ptr;
			break;
		}
	}
	if(!rsdp) goto haltonly;

	// find RSDT table pointer
	ptr = (unsigned int *)*(ptr + 4);
	if(crc8((unsigned char *)ptr, *(ptr + 1))){
		printf("Error: RSDT checksum mismatch.\n");
		goto haltonly;
	}
	rsdt  = ptr;
	count = (*(ptr + 1) - 36) / 4;

	// find FACP table pointer
	ptr += 9; // skip RSDT entries
	for(i = 0; i < count; i++){
		for(j = 0; j < 24; j++){
			if(*(unsigned int *)*ptr == 'PCAF'){ // "FACP"
				facp = (unsigned int *)*ptr;
				i = count;
				break;
			}
		}
	}
	if(!facp){
		printf("Error: Could not find FACP table.\n");
		goto haltonly;
	}
	if(crc8((unsigned char *)facp, *(facp + 1))){
		printf("Error: FACP checksum mismatch.\n");
		goto haltonly;
	}

	// find DSDT table pointer
	ptr = (unsigned int *)*(facp+10); // DSDT address
	if(*ptr != 'TDSD'){ // "DSDT"
		printf("Error: Could not find DSDT table.\n");
		goto haltonly;
	}
	if(crc8((unsigned char *)ptr, *(ptr + 1))){
		printf("Error: DSDT checksum mistmatch.\n");
		goto haltonly;
	}
	dsdt = ptr;

	// Search DSDT byte-code for ACPI _S5 signature
	found = 0;
	len   = *(dsdt + 1) - 36;
	data  = (unsigned char *)(dsdt + 36);
	while(len--){
		if((*(unsigned int *)data & 0x00FFFFFF) == 0x0035535F){ // "_S5"
			data += 4;
			if(*data == 0x12){ // 0x012 = package opcode
				data += 3; // 0x0A = 8bit integer opcode
				slp_typ[0] = (*data == 0x0A) ? *++data : *data;
				data++;
				slp_typ[1] = (*data == 0x0A) ? *++data : *data;
				found = 1;
			}
			break;
		}
		data++;
	}
	if(!found) goto haltonly;

	// execute the actual shutdown and power-off
	outb(*(facp + 16), slp_typ[0] | SLP_EN);     // FACP[64] = PM1a_CNT_BLK
  printf(itoa(*(facp + 17), 10));
	if(*(facp + 17))
    outb(*(facp + 17), slp_typ[1] | SLP_EN); // FACP[68] = PM1b_CNT_BLK

  printf(" \nShutting down...\n");

haltonly:
	printf("It is now safe to turn-off your computer.\n");

}
