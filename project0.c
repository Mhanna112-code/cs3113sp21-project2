#include <stdio.h>
#define MAX_BUF 1024
#include<fcntl.h> 
#include<errno.h>


int main(int argc, char **argv){
	char buffer[MAX_BUF];
	int fd;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		printf("can't open file");

//	while (charRead = read(fd, buffer, MAX_BUF) > 0)
		
	char test[3] = {'ݐ'};
	printf("orgchar = %d",test[0]);
	printf("char = %d",  test[0]|128);
	if (0x00 < test[0] <= 0x7f){
		test[0] = test[0] &  127;
		printf("%02x",test[0]);
	}
//	printf("%02x%02x", test[0] & 255, (test[0]/256)&255); 
	if (0x80 < test[0] < 0x7FF){
		test[0] = ((test[0] & 255)/256)&255;
		test[0] = test[0] & 49280;
		printf("%04x",test[0]);
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
//	if (0x80 < test[0] <= 0x7FF)
//		test[
}
