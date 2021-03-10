#include <stdio.h>
#define MAX_BUF 1024
#include<fcntl.h> 
#include<errno.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char **argv){
	char buffer[MAX_BUF];
	int fd;
	char *hex;
//	fd = open(argv[1], O_RDONLY);
//	if (fd == -1)
//		while (charRead = fread(fd, buffer, MAX_BUF) > 0);		
	char test[] = "؈";
	int len = strlen(test);
	char mask[(len*2) + 1];
	int i=0;
   	int k=0;
	while(test[k] != '\0'){
		sprintf((char*)(mask + i), "%02X", test[k]);
		k += 1;
		i += 2;
	}
	mask[i++] = '\0';
	printf("hex_str: %s\n", mask);
	int i_mask = strtol(mask, NULL, 16);
	printf("%d", i_mask);
	return 0;
	}
//	printf("char = %d",  test[0]|128);
/*	if (0x00 <(int) test<= 0x7f){
		test[0] = test &  127;
		printf("%02x",test[0]);
	}
//	printf("%02x%02x", test[0] & 255, (test[0]/256)&255); 
	if (0x80 <(int) test < 0x7FF){
		mask = 24704;
		for (int i = 0; i < 6; i++)
			mask  = mask | (test & (i + 1));
		test = ((test &  255)/256)&255;
		test = test & mask;
		printf("%02x", mask);
	}
	if (0x800 < test[0] < 0xFFFF){
		test[0] = ((test[0] & 65535)/65536)&65535;
		test[0] = test[0] & 14712960;
		printf("%06x", test[0]);
	}
	if (0x10000 < test[0] < 0x1FFFFF){
//		test[0] = ((test[0] & )/256)&255
		test[0] = test[0] & 4034953344;
		printf("%08x", test[0]);
	}

	return 0;
}
//	if (0x80 < test[0] <= 0x7FF)
//		test[
		*/
