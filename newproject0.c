#include <stdio.h>
#define MAX_BUF 1024
#include<fcntl.h>
#include<errno.h>
#include <string.h>
#include <stdlib.h>
#define size1 127
#define size2 1920
#define size3 63488
#define size4 1048576
struct element{
	int count;
	char hexString[];
};

int main(int argc, char *argv){
    struct element *ASCIInums  = (struct element*)malloc(size1*sizeof(struct element));
    struct element *UTFG1 = (struct element*)malloc(size2*sizeof(struct element));
    struct element *UTFG2 = (struct element*)malloc(size3*sizeof(struct element));
    struct element *UTFG3  = (struct element*)malloc(size4*sizeof(struct element));
    char en[] = "𐍈";
    int result = strlen(en);
    printf("%d", result);
   /* if (0x00 <= result <= 0x7F)
	printf("%d", 0);
    if (0x80 <= result  <= 0x7FF)
	printf("%d", 1);
    if (0x800 <= result <= 0xFFFF)
	printf("%d", 2);
    if (0x10000 <= result <= 0x1FFFFF)
	printf("%d", 3);
	*/
    return 0;
}

