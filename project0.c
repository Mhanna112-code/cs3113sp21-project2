#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size1 1112064
#define size2 1112064
#define size3 1112064
#define size4 1112064
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
    // struct element *temporary;
    for (i  = 0; i < structSize - 1; i++){
        max = i;
        //structSize
        for (j = i + 1; j < structSize; j++) {
            // printf("orig = %s", elements[i].arr);
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
    struct element *ASCIInums = malloc(size1 * sizeof(struct element));
    struct element *UTFG1 = malloc(size2 * sizeof(struct element));
    struct element *UTFG2 = malloc(size3 * sizeof(struct element));
    struct element *UTFG3 = malloc(size4 * sizeof(struct element));
    memset(ASCIInums, 0, sizeof(ASCIInums));
    memset(UTFG1, 0, sizeof(UTFG1));
    memset(UTFG2, 0, sizeof(UTFG2));
    memset(UTFG3, 0, sizeof(UTFG3));
    char ch;
    //FILE fd;
    //fd = fopen("C:\\Users\\march\\CLionProjects\\cs3113-project0\\unicode.txt", "r");
    int result;
    int i = 0;
    int j = 0;
    int k = 0;
    int f = 0;
    int com = 0;
    ch = fgetc(stdin);
    while (ch  != EOF)
    {
        /*        printf("%c", ch);
                printf("====");
        */
        // printf("%08X", (unsigned char)ch)
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
        char twoC;
        char threeC;
        char fourC;
        if (result ==  1){
            for (a = 0; a < i; a++){
                com = (ASCIInums[a].byte1 == ch);
                //      printf("com = ");
                //      printf("%d", com);
                if (com == 1)
                    break;
            }
            if (com==1){
                ASCIInums[a].count++;
            }
            else{
                ASCIInums[i].count++;
                ASCIInums[i].byte1 = ch;
//      printf("ch = %c", ASCIInums[i].byte1);
                //ASCIInums[i].arr = enc1[e++];
                //printf("ASCIInums[i] = %s", ASCIInums[i].arr);
                ASCIInums[i].size = (unsigned char)ch;
                i++;
//      printf("%c", ASCIInums[i++].byte1);
            }
        }
        if (result == 2){
             twoC= fgetc(stdin);
            for (b = 0; b < j; b++){
                com = (UTFG1[b].byte1 == (unsigned char)ch)&(UTFG1[b].byte2 == (unsigned char)twoC);
                if (com == 1)
                    break;
            }
            if (com==1)
                UTFG1[b].count++;
            else{
                UTFG1[j].count++;
                UTFG1[j].byte1 = (unsigned char) ch;
                UTFG1[j].byte2 = (unsigned char) twoC;
                UTFG1[j].size =  UTFG1[j].byte1 +  UTFG1[j].byte2;
                //      printf("%c", enc2);
                j++;
            }
        }

        if (result == 3){
            twoC= fgetc(stdin);
            threeC= fgetc(stdin);
            for (c = 0; c < k; c++){
                com = (UTFG2[c].byte1 == (unsigned char)ch) & (UTFG2[c].byte2 == (unsigned char)twoC) & (UTFG2[c].byte3 == (unsigned char)threeC);
                if (com == 1)
                    break;
            }
            if (com==1)
                UTFG2[c].count++;
            else{
                UTFG2[k].count++;
                UTFG2[k].byte1 = (unsigned char)ch;
                UTFG2[k].byte2 = (unsigned char)twoC;
                UTFG2[k].byte3 = (unsigned char)threeC;
                // printf("%s", enc3);
                UTFG2[k].size = UTFG2[k].byte1 + UTFG2[k].byte2 + UTFG2[k].byte3;
//      printf("size of %08X:", UTFG2[k].size);
                k++;
            }
        }

        if (result == 4){
            twoC= fgetc(stdin);
            threeC= fgetc(stdin);
            fourC= fgetc(stdin);
            for (d = 0; d < f; d++){
                com = (UTFG3[d].byte1 == (unsigned char)ch) & (UTFG3[d].byte2 == (unsigned char)twoC) & (UTFG3[d].byte3 == (unsigned char)threeC) & (UTFG3[d].byte4 == (unsigned char)fourC);
                if (com == 1)
                    break;
            }
            if (com==1)
                UTFG3[d].count++;
            else{
                UTFG3[f].count++;
                UTFG3[f].byte1 = (unsigned char)ch;
                UTFG3[f].byte2 = (unsigned char)twoC;
                UTFG3[f].byte3 = (unsigned char)threeC;
                UTFG3[f].byte4 = (unsigned char)fourC;
                /*enc4[0] = UTFG3[f].byte1;
                enc4[1] = UTFG3[f].byte2;
                enc4[2] = UTFG3[f].byte3;
                enc4[3] = UTFG3[f].byte4;*/
                UTFG3[f].size = UTFG3[f].byte1 + UTFG3[f].byte2 + UTFG3[f].byte3 + UTFG3[f].byte4;
                //      printf("%s", enc4);
                f++;
            }
        }
        com = 0;
        ch = fgetc(stdin);
    }
    i -=1;
    j -=1;
    k -=1;
    f -=1;
    printOut(UTFG3, f);
    printOut(UTFG2, k);
    printOut(UTFG1, j);
    printOut(ASCIInums, i);
    return 0;
}
