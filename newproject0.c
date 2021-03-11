#include <stdio.h>
#define MAX_BUF 1024
#include<fcntl.h>
#include<errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define size1 127
#define size2 1920
#define size3 63488
#define size4 1048576
struct element{
	int count;
	char *hexString;
	bool isVal;
};

int main(int argc, char *argv){
    struct element *ASCIInums  = (struct element*)malloc(size1*sizeof(struct element));
    struct element *UTFG1 = (struct element*)malloc(size2*sizeof(struct element));
    struct element *UTFG2 = (struct element*)malloc(size3*sizeof(struct element));
    struct element *UTFG3  = (struct element*)malloc(size4*sizeof(struct element));
    memset(ASCIInums, 0, sizeof(ASCIInums));
    memset(UTFG1, 0, sizeof(UTFG1));
    memset(UTFG2, 0, sizeof(UTFG2));
    memset(UTFG3, 0, sizeof(UTFG3));
    char en[]  = "a";
    int result = strlen(en);
    en[result] = '\0';
//    printf("%d", result);
    int i = 0;
    int j = 0;
    int k = 0;
    int f = 0;
    int com = 1;
    int a = 0;
    ASCIInums[a].count = 1;
    ASCIInums[a].hexString = en;
    ASCIInums[a].isVal = 1;
    if (result == 0 | 1){
	for (a = 0; a < size1; a++){
		if (ASCIInums[a].isVal == 0)
			continue;
		com = strcmp(ASCIInums[a].hexString, en);
		if (com == 0)
		   break;
	}
	if (com==0)
		ASCIInums[a].count++;
	else{
	ASCIInums[i].count++;
	ASCIInums[i].hexString = malloc(1 + result);
        strcpy(ASCIInums[i++].hexString, en);
//	printf("%s", ASCIInums[i++].hexString);
//	printf("----");
	}
    }
    for (int i = 0; i < size1; i++){
	printf("%d", ASCIInums[i].count);
	printf("%s", ASCIInums[i].hexString);
	printf("||");
    }
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
