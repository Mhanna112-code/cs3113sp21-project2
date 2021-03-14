#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1112064
//storing unicode objects in a struct
struct element{
    int count;
    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
    unsigned char byte4;
    int size;
};

//swaps positions of 2 unicode characters in memory by swapping all unicode object values
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

//sorts and prints out unicode characters by greatest count to least greatest count
void printOut(struct element elements[], int structSize){
    int i, j, max;
    //sorts unicode objects by count using selection sort
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
    //prints out unicode object values
    for (i  = 0; i < structSize; i++){
        unsigned char arr[4];
        arr[0] = elements[i].byte1;
        arr[1] = elements[i].byte2;
        arr[2] = elements[i].byte3;
        arr[3] = elements[i].byte4;
        unsigned char *str = &arr[0];
        printf("%s", str);
        printf("->");
        printf("%d\n", elements[i].count);
    }
}


int main(int argc, char **argv){
    //points to unicode objects in memory
    struct element *UTFG1 = malloc(MAX_SIZE * sizeof(struct element));
    //sets all unicode object values to 0
    memset(UTFG1, 0, sizeof(UTFG1));
    char ch;
    //stores byte size result
    int result;
    //int variable to access struct elements from memory
    int f = 0;
    //int variable to compare 2 unicode characters
    int com = 0;
    //reads in first byte of unicode character
    ch = fgetc(stdin);
    int a;
    //variable to store 2nd byte of unicode character
    char twoC;
    //variable to store 3rd byte of unicode character
    char threeC;
    //variable to store 4th byte of unicdoe character
    char fourC;
    //int isVal = 1;
    while (ch  != EOF) {
	//code to read certain number of bytes depending on 4 most leading bits
    	if ((unsigned char) ch < 192)
            result = 1;
        if ((unsigned char) ch >= 192 & (unsigned char)ch < 224)
            result = 2;
        if ((unsigned char) ch >= 224 & (unsigned char)ch < 240)
            result = 3;
        if ((unsigned char)ch >= 240)
            result = 4;
	//if byte size is 2, reads in 2nd byte of unicode character
        if (result == 2) 
            twoC = fgetc(stdin);
	//if byte size is 3, reads in 2nd and 3rd bytes of unicode character
        if (result == 3) {
            twoC = fgetc(stdin);
            threeC = fgetc(stdin);
        }
	//if byte size is 4, reads in 2nd, 3rd and 4th bytes of unicode character
        if (result == 4) {
            twoC = fgetc(stdin);
            threeC = fgetc(stdin);
            fourC = fgetc(stdin);
        }
            //checks if given unicode character was already read in
            for (a = 0; a < f; a++) {
                if (result == 1)
                    com = (UTFG1[a].byte1 == (unsigned char) ch);
                if (result == 2)
                    com = ((UTFG1[a].byte1 == (unsigned char) ch) & ((UTFG1[a].byte2) == (unsigned char) twoC));
                if (result == 3) 
                    com = (UTFG1[a].byte1 == (unsigned char) ch) & (UTFG1[a].byte2 == (unsigned char) twoC) & (UTFG1[a].byte3 == (unsigned char) threeC);
                if (result == 4) 
                    com = (UTFG1[a].byte1 == (unsigned char) ch) & (UTFG1[a].byte2 == (unsigned char) twoC) &
                          (UTFG1[a].byte3 == (unsigned char) threeC) & (UTFG1[a].byte4 == (unsigned char) fourC);
                if (com == 1)
                    break;
            }
            if (com == 1)
		//increases count of unicode character
                UTFG1[a].count++;
	    	//changes NULL values of unicode character
            else {
                UTFG1[f].count++;
                if (result == 1)
                    UTFG1[f].byte1 = (unsigned char) ch;
                if (result == 2) {
                    UTFG1[f].byte1 = (unsigned char) ch;
                    UTFG1[f].byte2 = (unsigned char) twoC;
                }
                if (result == 3){
                    UTFG1[f].byte1 = (unsigned char) ch;
                    UTFG1[f].byte2 = (unsigned char) twoC;
                    UTFG1[f].byte3 = (unsigned char) threeC;
                }
                if (result == 4){
                    UTFG1[f].byte1 = (unsigned char) ch;
                    UTFG1[f].byte2 = (unsigned char) twoC;
                    UTFG1[f].byte3 = (unsigned char) threeC;
                    UTFG1[f].byte4 = (unsigned char) fourC;
                }
                UTFG1[f].size = UTFG1[f].byte1 + UTFG1[f].byte2 + UTFG1[f].byte3 + UTFG1[f].byte4;
                f++;
            }
        com = 0;
        ch = fgetc(stdin);
    }
    //call printout function to print out unicode characters and their counts
    printOut(UTFG1, f);
    return 0;
}

