#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1112064

struct element{
    int count;
    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
    unsigned char byte4;
    int size;
};
void swap (struct element  *A, struct element *B) {
    unsigned char temp1 = A->byte1;
    unsigned char temp2 = A->byte2;
    unsigned char temp3 = A->byte3;
    unsigned char temp4 = A->byte4;
    int tempSize = A->size;
    int tempCount = A->count;
    A->byte1 = B->byte1;
    A->byte2 = B->byte2;
    A->byte3 = B->byte3;
    A->byte4 = B->byte4;
    A->size = B->size;
    A->count = B->count;
    B->byte1 = temp1;
    B->byte2 = temp2;
    B->byte3 = temp3;
    B->byte4 = temp4;
    B->size = tempSize;
    B->count = tempCount;
}
void printOut(struct element elements[], int structSize){
    int i, j, max;
    for (i  = 0; i < structSize - 1; i++){
        max = i;
        for (j = i + 1; j < structSize; j++) {
            if (elements[j].count > elements[max].count)
                max = j;
        }
        if (max != i) {
            swap(&elements[i], &elements[max]);
        }
    }
    for (i  = 0; i < structSize; i++){
        char arr[4];
        arr[0] = elements[i].byte1;
        arr[1] = elements[i].byte2;
        arr[2] = elements[i].byte3;
        arr[3] = elements[i].byte4;
        char *str = &arr[0];
        printf("%s", str);
        printf("->");
        printf("%d\n", elements[i].count);
    }
}

int main(int argc, char **argv){
    struct element *UTFG1 = malloc(MAX_SIZE * sizeof(struct element));
    memset(UTFG1, 0, sizeof(UTFG1));
    char ch;
    //FILE *fd;
    //fd = fopen("C:\\Users\\march\\CLionProjects\\cs3113-project0\\e.txt", "r");
    int result;
    int f = 0;
    int com = 0;
    ch = fgetc(stdin);
    int a;
    char twoC;
    char threeC;
    char fourC;
    int isVal = 1;
    while (ch  != EOF) {
        if ((unsigned char) ch < 192)
            result = 1;
        if ((ch == '\n') || (ch == ' '))
            result = 0;
        if ((unsigned char) ch >= 192 & (unsigned char)ch < 224)
            result = 2;
        if ((unsigned char) ch >= 224 & (unsigned char)ch < 240)
            result = 3;
        if ((unsigned char)ch >= 240)
            result = 4;

        if (result == 0) {
            isVal = 0;
        }
        if (result == 2) {
            twoC = fgetc(stdin);
        }

        if (result == 3) {
            twoC = fgetc(stdin);
            threeC = fgetc(stdin);
        }

        if (result == 4) {
            twoC = fgetc(stdin);
            threeC = fgetc(stdin);
            fourC = fgetc(stdin);
        }
        if (isVal == 1) {
            for (a = 0; a < f; a++) {
                if (result == 1)
                    com = (UTFG1[a].byte1 == ch);
                if (result == 2)
                    com = ((UTFG1[a].byte1 == ch) & ((UTFG1[a].byte2) == twoC));
                if (result == 3) 
                    com = (UTFG1[a].byte1 == ch) & (UTFG1[a].byte2 == twoC) &
                          (UTFG1[a].byte3 == threeC);
                if (result == 4) 
                    com = (UTFG1[a].byte1 == ch) & (UTFG1[a].byte2 == twoC) &
                          (UTFG1[a].byte3 == threeC) & (UTFG1[a].byte4 == fourC);
                if (com == 1)
                    break;
            }
            if (com == 1)
                UTFG1[a].count++;
            else {
                UTFG1[f].count++;
                if (result == 1)
                    UTFG1[f].byte1 = ch;
                if (result == 2) {
                    UTFG1[f].byte1 = ch;
                    UTFG1[f].byte2 = twoC;
                }
                if (result == 3){
                    UTFG1[f].byte1 = ch;
                    UTFG1[f].byte2 = twoC;
                    UTFG1[f].byte3 = threeC;
                }
                if (result == 4){
                    UTFG1[f].byte1 = ch;
                    UTFG1[f].byte2 = twoC;
                    UTFG1[f].byte3 = threeC;
                    UTFG1[f].byte4 = fourC;
                }
                UTFG1[f].size = (unsigned char)UTFG1[f].byte1 + (unsigned char)UTFG1[f].byte2 + (unsigned char)UTFG1[f].byte3 + (unsigned char)UTFG1[f].byte4;
                f++;
            }
        }
        isVal = 1;
        com = 0;
        ch = fgetc(stdin);
    }
    printOut(UTFG1, f);
    return 0;
}
