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
	char byte1;
	char byte2;
	char byte3;
	char byte4;
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
    char ch;
    FILE *fd;
    fd = fopen("example.txt", "r");
    int result;
    int i = 0;
    int j = 0;
    int k = 0;
    int f = 0;
    int com = 0;
    ch = fgetc(fd);
    while (ch  != EOF)
        {
    /*        printf("%c", ch);
	    printf("====");
    */
    printf("%08X", (unsigned char)ch);
    printf("===");
    if ((unsigned char)ch < 128)
	result = 1;
    if ((unsigned char)ch >= 128 & ch < 224)
	result = 2;
    if ((unsigned char)ch >= 224 & ch < 240 )
	result = 3;
    if ((unsigned char)ch >= 240)
	result = 4;
/*    printf("%d", result);
    printf("||");
    printf("%d", result);*/
    int a;
    int b;
    int c;
    int d;
    if (result ==  1){
	for (a = 0; a < size1; a++){
		if (ASCIInums[a].isVal == 0)
			continue;
		com = (ASCIInums[a].byte1 == ch);
		if (com == 1)
		   break;
	}
	if (com==1)
		ASCIInums[a].count++;
	else{
	ASCIInums[i].isVal = 1;
	ASCIInums[i].count++;
	ASCIInums[i].byte1 = ch;
	printf("%c", ASCIInums[i++].byte1);
	}
    }
    ch = fgetc(fd);
    /*
	com = 1;
    if (result == 2){
        for (b = 0; b < size2; b++){
                if (UTFG1[b].isVal == 0) 
                        continue;
                com = strcmp(UTFG1[b].hexString, en);
                if (com == 0)
                   break;
        }
        if (com==0)
                UTFG1[b].count++;
        else{
        UTFG1[j].isVal = 1;
        UTFG1[j].count++;
        UTFG1[j].hexString = malloc(1 + result);
        strcpy(UTFG1[j++].hexString, en);
        }
    }
    com = 1;
    if (result == 3){
        for (c = 0; c < size3; a++){
                if (UTFG2[c].isVal == 0)
                        continue;
                com = strcmp(UTFG2[c].hexString, en);
                if (com == 0)
                   break;
        }
        if (com==0)
                UTFG2[c].count++;
        else{
        UTFG2[k].isVal = 1;
        UTFG2[k].count++;
        UTFG2[k].hexString = malloc(1 + result);
        strcpy(UTFG2[k++].hexString, en);
        }
    }
    com = 1;
    printf("%d", result);
    if (result == 4){
        for (d = 0; d < size4; d++){
                if (UTFG3[d].isVal == 0)
                        continue;
                com = strcmp(UTFG3[d].hexString, en);
                if (com == 0)
                   break;
        }
        if (com==0)
                UTFG3[d].count++;
        else{
        UTFG3[f].isVal = 1;
        UTFG3[f].count++;
        UTFG3[f].hexString = malloc(1 + result);
        strcpy(UTFG3[f++].hexString, en);
        }
	    printf("%s", UTFG3[0].hexString);
	    printf("%d", UTFG3[0].count);
	    printf("%d", UTFG3[0].isVal);
	    printf("||");
    	}
    }
    */
	}
    return 0;
}
