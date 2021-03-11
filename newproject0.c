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
	unsigned char byte1;
	unsigned char byte2;
	unsigned char byte3;
	unsigned char byte4;
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
	if (ch == 0X0A)
		break;
    /*        printf("%c", ch);
	    printf("====");
    */
   // printf("%08X", (unsigned char)ch);
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
    char enc2[2];
    char enc3[3];
    char enc4[4];
    memset(enc2, 0, sizeof(enc2));
    memset(enc3, 0, sizeof(enc3));
    memset(enc4, 0, sizeof(enc4));
    char twoC;
    char threeC;
    char fourC;
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

    if (result == 2){
	twoC = fgetc(fd);
        for (b = 0; b < size2; b++){
                if (UTFG1[b].isVal == 0) 
                        continue;
                com = (UTFG1[b].byte1 == ch)&(UTFG1[b].byte2 == twoC);
                if (com == 1)
                   break;
        }
        if (com==1)
                UTFG1[b].count++;
        else{
        UTFG1[j].isVal = 1;
        UTFG1[j].count++;
        UTFG1[j].byte1 = (unsigned char) ch;
	UTFG1[j].byte2 = (unsigned char) twoC;
	enc2[0] = UTFG1[j].byte1;
	enc2[1] = UTFG1[j].byte2;
	printf("%c", enc2);
	j++;
        }
    }

    if (result == 3){
	twoC = fgetc(fd);
	threeC = fgetc(fd);
        for (c = 0; c < size3; c++){
                if (UTFG2[c].isVal == 0)
                        continue;
                com = (UTFG2[c].byte1 == ch) & (UTFG2[c].byte2 == twoC) & (UTFG2[c].byte3 == threeC);
                if (com == 1)
                   break;
        }
        if (com==1)
                UTFG2[c].count++;
        else{
        UTFG2[k].isVal = 1;
        UTFG2[k].count++;
        UTFG2[k].byte1 = (unsigned char)ch;
	UTFG2[k].byte2 = (unsigned char)twoC;
	UTFG2[k].byte3 = (unsigned char)threeC;
        enc3[0] = UTFG2[k].byte1;
 	enc3[1] = UTFG2[k].byte2;
	enc3[2] = UTFG2[k].byte3;
        printf("%s", enc3);
	k++;
       	}
    }
    
    if (result == 4){
	twoC = fgetc(fd);
        threeC = fgetc(fd);
	fourC = fgetc(fd);
        for (d = 0; d < size4; d++){
                if (UTFG3[d].isVal == 0)
                        continue;
                com = (UTFG3[d].byte1 == ch)&(UTFG3[d].byte2 == twoC)&(UTFG3[d].byte3 == threeC)&(UTFG3[d].byte4 == fourC);
                if (com == 1)
                   break;
        }
        if (com==1)
                UTFG3[d].count++;
        else{
        UTFG3[f].isVal = 1;
        UTFG3[f].count++;
        UTFG3[f].byte1 = (unsigned char)ch;
        UTFG3[f].byte2 = (unsigned char)twoC;
	UTFG3[f].byte3 = (unsigned char)threeC;
	UTFG3[f].byte4 = (unsigned char)fourC;
	enc4[0] = UTFG3[f].byte1;
        enc4[1] = UTFG3[f].byte2;
	enc4[2] = UTFG3[f].byte3;
	enc4[3] = UTFG3[f].byte4;
	printf("%s", enc4);
        k++;
       	}
    }
    ch = fgetc(fd);
	}
    return 0;
}
