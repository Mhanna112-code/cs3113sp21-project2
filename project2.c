#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
//data structure to hold process in memory
struct Process{
    int full; //boolean to check if process slot taken
    int end;  //boolean to check if last process
    char *PID; //process ID
    int size; //process size
};

//size of max memory
unsigned long long maxMemory;
//gets algorithm type
char *fitType;
//points to algoParams textfile
FILE *fp;
//data structures to hold instructions and algoParams contents
struct algoParams
{
    char ID[17];
    int isEmpty;
    int size;
    char command[10];
    char subcommand[10];
}instructions[500 * USHRT_MAX] = {0};
//reads from textfile
int readinstructions(FILE *file)
{
    struct algoParams algoParams;
    char string[10];
    int insPtr = 0;
    //keep scanning the file until the end
    while (fscanf(file, "%s", string) != EOF)
    {
        //copies string to algoParams command
        strcpy(algoParams.command, string);
        //if algoParams is release or find, copy next string to algoParams.ID
        if (strcmp(string, "RELEASE") == 0 || strcmp(string, "FIND") == 0)
        {
            fscanf(file, "%s", string);
            strcpy(algoParams.ID, string);
        }
        //if string is "REQUEST", copy PID and size to algoParams.ID and algoParams.size
        else if (strcmp(algoParams.command, "REQUEST") == 0)
        {
            fscanf(file, "%s", string);
            strcpy(algoParams.ID, string);
            fscanf(file, "%s", string);
            algoParams.size = atoi(string);
        }
        //if string is subcommand, copy string to algoParams.subcommand
        else
        {
            fscanf(file, "%s", string);
            strcpy(algoParams.subcommand, string);
        }
        //if algoParams is not a comment, insert algoParams to instructions data struct
        if (strcmp(algoParams.command, "#") != 0)
        {
            algoParams.isEmpty = -700;
            instructions[insPtr] = algoParams;
            insPtr++;
        }
    }
    //returns algoParams index
    return insPtr;
}
//calculate and return available size index for firstfit
int calculateAvailableSize(int idx, struct Process processes[], struct algoParams ins){
    int availableSize = 0;
    int tmpIdx = maxMemory;
    for (int i = idx; i < maxMemory; i++){
        tmpIdx = i;
        if (processes[i].full != 700)
            availableSize++;
        else
            break;
        if (availableSize == ins.size)
            return idx;
        if (i == maxMemory - 1)
            return -1;
    }
    int temp = tmpIdx;
    temp = tmpIdx;
    tmpIdx = tmpIdx - idx;
    int newIdx = idx + tmpIdx + processes[temp].size;
    if (newIdx >= maxMemory)
        return -1;
    calculateAvailableSize(newIdx, processes, ins);
}

//calculate and return available size index for nextfit
int endFlag = 0;
int calculateAvailableSizeForNextFit(int idx, struct Process processes[], struct algoParams ins){
    int availableSize = 0;
    int tmpIdx = maxMemory;
    for (int i = idx; i < maxMemory; i++){
        tmpIdx = i;
        if (processes[i].full != 700)
            availableSize++;
        else
            break;
        if (availableSize == ins.size)
            return idx;
        if (i == maxMemory - 1 && endFlag != 1) {
            endFlag = 1;
            return calculateAvailableSizeForNextFit(0, processes, ins);
        }
    }
    int temp = tmpIdx;
    tmpIdx = tmpIdx - idx;
    int newIdx = idx + tmpIdx + processes[temp].size;
    if (newIdx >= maxMemory - 1) {
        if (endFlag != 1) {
            endFlag = 1;
            return calculateAvailableSizeForNextFit(0, processes, ins);
        }
        return -1;
    }
    calculateAvailableSizeForNextFit(newIdx, processes, ins);
}

//calculate and return available size index for worstfit
unsigned long long max = 0;
int oPtr = 0;
int tFlag = 0;
int calculateAvailableSizeForWorstFit(int idx, struct Process processes[], struct algoParams ins) {
    int endFlag = 0;
    int tmpIdx = 0;
    int availableSize = 0;
    int bestHole = 0;
    int mFlag = 0;
    int err = 0;
    int newIdx;
    for (int i = idx; i < maxMemory; i++){
        tmpIdx = i;
        if (processes[i].full != 700)
            availableSize++;
        else{
            if (mFlag == 1){
                if (bestHole > max){
                    max = bestHole;
                    oPtr = idx;
                    }
                }
                break;
            }
            if (availableSize >= ins.size) {
                mFlag = 1;
                tFlag = 1;
                bestHole++;
            }
        if (i == maxMemory - 1) {
            endFlag = 1;
            if (mFlag == 1) {
                if (bestHole > max) {
                    max = bestHole;
                    oPtr = idx;
                }
            }
            break;
        }
    }
    if (endFlag == 1) {
        if (tFlag == 1)
            return oPtr;
        return -1;
    }
    int temp = tmpIdx;
    tmpIdx = tmpIdx - idx;
    newIdx = idx + tmpIdx + processes[temp].size;
    if (newIdx >= maxMemory) {
        if (tFlag == 1)
            return oPtr;
        return -1;
    }
    calculateAvailableSizeForWorstFit(newIdx, processes, ins);
}

//calculate and return available size index for bestfit
unsigned long long min = LLONG_MAX;
int pPtr = 0;
int pFlag = 0;
int calculateAvailableSizeForBestFit(int idx, struct Process processes[], struct algoParams ins) {
    int endFlag = 0;
    int tmpIdx = 0;
    int availableSize = 0;
    int bestHole = 0;
    int mFlag = 0;
    int newIdx;
    for (int i = idx; i < maxMemory; i++){
        tmpIdx = i;
        if (processes[i].full != 700)
            availableSize++;
        else{
            if (mFlag == 1){
                if (bestHole < min){
                    min = bestHole;
                    pPtr = idx;
                }
            }
            break;
        }
        if (availableSize >= ins.size) {
            mFlag = 1;
            pFlag = 1;
            bestHole++;
        }
        if (i == maxMemory - 1) {
            if (mFlag == 1) {
                if (bestHole < min) {
                    min = bestHole;
                    pPtr = idx;
                }
            }
            endFlag = 1;
            break;
        }
    }
    if (endFlag == 1) {
        if (pFlag == 1)
            return pPtr;
        return -1;
    }
    int temp = tmpIdx;
    tmpIdx = tmpIdx - idx;
    newIdx = idx + tmpIdx + processes[temp].size;
    if (newIdx >= maxMemory) {
        if (pFlag == 1)
            return pPtr;
        return -1;
    }
    calculateAvailableSizeForBestFit(newIdx, processes, ins);
}

//lists available spaces in processes data struct
void listAvailable(struct Process processes[]){
    int tmpIdx = 0;
    int *availableSpaces = (int*) malloc(maxMemory * sizeof(int));
    for (int i = 0; i < maxMemory; i++){
            if (processes[i].full != 700)
                availableSpaces[tmpIdx] += 1;
            else if(i < maxMemory - 1 && processes[i].full == 700) {
                if (processes[i + 1].full == 700)
                    continue;
                else
                    tmpIdx = i + 1;
            }
        }
    int fFlag = 0;
    for (int i = 0; i < maxMemory; i++){
        if (availableSpaces[i] > 0) {
            printf("(%d, %d) ", availableSpaces[i], i);
            fFlag = 1;
        }
    }
    if (fFlag == 1)
        printf("%c",'\n');
    if (fFlag == 0)
        printf("FULL\n");
}
//finds process in processes data struct
void findProcess(char* PID, struct Process processes[]){
    int fFlag = 0;
    char* str;
    for (int i = 0; i < maxMemory; i++){
        if (processes[i].PID != NULL) {
            str = strstr(processes[i].PID, PID);
            if (str != NULL && fFlag != 1) {
                printf("(%s, %d, %d)\n", PID, processes[i].size, i);
                fFlag = 1;
            }
        }
    }
        if (fFlag == 0)
            printf("FAULT\n");
}
//lists allocated processes in processes data struct
void listAssigned(struct Process processes[]) {
    int *assignedProcesses = (int*) malloc(maxMemory * sizeof(int));
    int tmpIdx = 0;
    char* tmpPID = NULL;
    int iFlag = 0;
    for (int i = 0; i < maxMemory; i++) {
        if (processes[i].full == 700) {
            if (processes[i].PID != tmpPID){
                tmpPID = processes[i].PID;
                tmpIdx = i;
                assignedProcesses[tmpIdx] += 1;
            }
        }
    }
    int fFlag = 0;
    for (int i = 0; i < maxMemory; i++){
        if (assignedProcesses[i] > 0) {
            printf("(%s, %d, %d) ", processes[i].PID, processes[i].size, i);
            fFlag = 1;
        }
    }
    if (fFlag == 1)
        printf("%c",'\n');
    if (fFlag == 0)
        printf("NONE\n");
}

//performs instructions on firstfit algorithm
void performFirstFit(struct algoParams instructions[], int numinstructions, struct Process processes[]){
    int idx = 0;
    int iFlag = 0;
    int rFlag = 0;
    int processFound = 0;
    int availableSize = maxMemory;
    for (int m = 0; m < maxMemory; m++)
        processes[m].PID = NULL;
    for (int i = 0; i < numinstructions; i++) {
        if (instructions[i].isEmpty == -700)
            iFlag = 1;
        if (iFlag == 1) {
            char* str = strstr(instructions[i].command, "REQUEST");
            if (str != NULL) {
                if (rFlag == 0) {
                    if (availableSize >= instructions[i].size) {
                        for (int j = idx; j < idx + instructions[i].size; j++) {
                            processes[j].full = 700;
                            availableSize--;
                            processes[j].PID = instructions[i].ID;
                            processes[j].size = instructions[i].size;
                        }
                        printf("ALLOCATED %s %d\n", instructions[i].ID, idx);
                        idx += instructions[i].size;
                    } else
                        printf("FAIL REQUEST %s %d\n", instructions[i].ID, instructions[i].size);
                } else {
                    idx = 0;
                    idx = calculateAvailableSize(idx, processes, instructions[i]);
                    if (idx == -1)
                        printf("FAIL REQUEST %s %d\n", instructions[i].ID, instructions[i].size);
                    else {
                        for (int j = idx; j < idx + instructions[i].size; j++) {
                            processes[j].full = 700;
                            processes[j].PID = instructions[i].ID;
                            processes[j].size = instructions[i].size;
                        }
                        printf("ALLOCATED %s %d\n", instructions[i].ID, idx);
                    }
                }
            }
            str = strstr(instructions[i].command, "RELEASE");
            if (str != NULL) {
                rFlag = 1;
                if (instructions[i].size < 1)
                    printf("FAIL RELEASE %s\n", instructions[i].ID);
                int temp;
                for (int m = 0; m < maxMemory; m++) {
                    str = NULL;
                    if (processes[m].PID != NULL)
                        str = strstr(instructions[i].ID, processes[m].PID);
                    if (str != NULL) {
                        if (processFound == 0) {
                            temp = m;
                            instructions[i].size = processes[m].size;
                            processFound = 1;
                            processes[m].PID = 0;
                            processes[m].full = -700;
                            processes[m].size = 0;
                            processes[m].end = 0;
                        } else {
                            processes[m].PID = 0;
                            processes[m].full = -700;
                            processes[m].size = 0;
                            processes[m].end = 0;
                        }
                    }
                }
                if (processFound == 1)
                    printf("FREE %s %d %d\n", instructions[i].ID, instructions[i].size, temp);
                else
                    printf("FAIL RELEASE %s\n", instructions[i].ID);
            }
            str = strstr(instructions[i].command, "LIST") && strstr(instructions[i].subcommand, "AVAILABLE");
            if (str != NULL)
                listAvailable(processes);
            str = strstr(instructions[i].command, "LIST") && strstr(instructions[i].subcommand, "ASSIGNED");
            if (str != NULL)
                listAssigned(processes);
            str = strstr(instructions[i].command, "FIND");
            if (str != NULL)
                findProcess(instructions[i].ID, processes);
        }
        processFound = 0;
    }
}
//performs instructions on nextfit algorithm
void performNextFit(struct algoParams instructions[], int numinstructions, struct Process processes[]){
    int idx = 0;
    int iFlag = 0;
    int rFlag = 0;
    int availableSize = maxMemory;
    int endPtr = 0;
    for (int m = 0; m < maxMemory; m++)
        processes[m].PID = NULL;
    for (int i = 0; i < numinstructions; i++) {
        int processFound = 0;
        if (instructions[i].isEmpty == -700)
            iFlag = 1;
        if (iFlag == 1) {
            char* str1 = strstr(instructions[i].command, "REQUEST");
            if (str1 != NULL) {
                if (rFlag == 0) {
                    if (availableSize >= instructions[i].size) {
                        for (int j = idx; j < idx + instructions[i].size; j++) {
                            processes[j].full = 700;
                            availableSize--;
                            processes[j].PID = instructions[i].ID;
                            processes[j].size = instructions[i].size;
                        }
                        processes[idx + instructions[i].size - 1].end = 700;
                        printf("ALLOCATED %s %d\n", instructions[i].ID, idx);;
                        idx += instructions[i].size;
                    } else
                        printf("FAIL REQUEST %s %d\n", instructions[i].ID, instructions[i].size);
                } else {
                    idx = endPtr;
                    idx = calculateAvailableSizeForNextFit(idx, processes, instructions[i]);
                    endFlag = 0;
                    if (idx == -1)
                        printf("FAIL REQUEST %s %d\n", instructions[i].ID, instructions[i].size);
                    else {
                        for (int j = idx; j < idx + instructions[i].size; j++) {
                            processes[j].full = 700;
                            processes[j].PID = instructions[i].ID;
                            processes[j].size = instructions[i].size;
                        }
                        processes[idx + instructions[i].size - 1].end = 700;
                        printf("ALLOCATED %s %d\n", instructions[i].ID, idx);;
                    }
                }
            }
            int uFlag = 0;
            char* str2 = strstr(instructions[i].command, "RELEASE");
            int temp;
            int fFlag = 0;
            if (str2 != NULL) {
                rFlag = 1;
                if (instructions[i].size < 1)
                    printf("FAIL RELEASE %s\n", instructions[i].ID);
                for (int m = 0; m < maxMemory; m++) {
                    str2 = NULL;
                    if (processes[m].PID != NULL)
                        str2 = strstr(instructions[i].ID, processes[m].PID);
                    if (str2 != NULL) {
                        if (processFound == 0) {
                            temp = m;
                            for (int k = m + 1; k < maxMemory; k++) {
                                if (k == maxMemory - 1) {
                                    endPtr = 0;
                                    break;
                                }
                                if (processes[k].full == 700 && processes[k+1].full != 700) {
                                    endPtr = k + 1;
                                    break;
                                }
                            }
                            instructions[i].size = processes[m].size;
                            processFound = 1;
                            processes[m].PID = 0;
                            processes[m].full = -700;
                            processes[m].size = 0;
                            processes[m].end = 0;
                        } else {
                            processes[m].PID = 0;
                            processes[m].full = -700;
                            processes[m].size = 0;
                            if (m == maxMemory - 1)
                                endPtr = 0;
                            processes[m].end = 0;
                        }
                    }
                }
                if (processFound == 1)
                    printf("FREE %s %d %d\n", instructions[i].ID, instructions[i].size, temp);
                else
                    printf("FAIL RELEASE %s\n", instructions[i].ID);
            }
        char* str = strstr(instructions[i].command, "LIST") && strstr(instructions[i].subcommand, "AVAILABLE");
        if (str != NULL)
            listAvailable(processes);
        str = strstr(instructions[i].command, "LIST") && strstr(instructions[i].subcommand, "ASSIGNED");
        if (str != NULL)
            listAssigned(processes);
        str = strstr(instructions[i].command, "FIND");
        if (str != NULL)
            findProcess(instructions[i].ID, processes);
        }
        processFound = 0;
    }
}
//performs instructions on worstfit algorithm
void performWorstFit(struct algoParams instructions[], int numinstructions, struct Process processes[]){
    int idx = 0;
    int iFlag = 0;
    int rFlag = 0;
    int processFound = 0;
    int availableSize = maxMemory;
    for (int m = 0; m < maxMemory; m++)
        processes[m].PID = NULL;
    for (int i = 0; i < numinstructions; i++) {
        if (instructions[i].isEmpty == -700)
            iFlag = 1;
        if (iFlag == 1) {
            char* str1 = strstr(instructions[i].command, "REQUEST");
            if (str1 != NULL) {
                if (rFlag == 0) {
                    if (availableSize >= instructions[i].size) {
                        for (int j = idx; j < idx + instructions[i].size; j++) {
                            processes[j].full = 700;
                            availableSize--;
                            processes[j].PID = instructions[i].ID;
                            processes[j].size = instructions[i].size;
                        }
                        printf("ALLOCATED %s %d\n", instructions[i].ID, idx);
                        idx += instructions[i].size;
                    } else
                        printf("FAIL REQUEST %s %d\n", instructions[i].ID, instructions[i].size);
                } else {
                    idx = 0;
                    idx = calculateAvailableSizeForWorstFit(idx, processes, instructions[i]);
                    max = 0;
                    oPtr = 0;
                    tFlag = 0;
                    if (idx == -1)
                        printf("FAIL REQUEST %s %d\n", instructions[i].ID, instructions[i].size);
                    else {
                        for (int j = idx; j < idx + instructions[i].size; j++) {
                            processes[j].full = 700;
                            processes[j].PID = instructions[i].ID;
                            processes[j].size = instructions[i].size;
                        }
                        printf("ALLOCATED %s %d\n", instructions[i].ID, idx);
                    }
                }
            }
            char* str2 = strstr(instructions[i].command, "RELEASE");
            if (str2 != NULL) {
                rFlag = 1;
                if (instructions[i].size < 1)
                    printf("FAIL RELEASE %s\n", instructions[i].ID);
                int temp;
                for (int m = 0; m < maxMemory; m++) {
                    str2 = NULL;
                    if (processes[m].PID != NULL)
                        str2 = strstr(instructions[i].ID, processes[m].PID);
                    if (str2 != NULL) {
                        if (processFound == 0) {
                            temp = m;
                            instructions[i].size = processes[m].size;
                            processFound = 1;
                            processes[m].PID = 0;
                            processes[m].full = -700;
                            processes[m].size = 0;
                            processes[m].end = 0;
                        } else {
                            processes[m].PID = 0;
                            processes[m].full = -700;
                            processes[m].size = 0;
                            processes[m].end = 0;
                        }
                    }
                }
                if (processFound == 1)
                    printf("FREE %s %d %d\n", instructions[i].ID, instructions[i].size, temp);
                else
                    printf("FAIL RELEASE %s\n", instructions[i].ID);
            }
            char* str = strstr(instructions[i].command, "LIST") && strstr(instructions[i].subcommand, "AVAILABLE");
            if (str != NULL)
                listAvailable(processes);
            str = strstr(instructions[i].command, "LIST") && strstr(instructions[i].subcommand, "ASSIGNED");
            if (str != NULL)
                listAssigned(processes);
            str = strstr(instructions[i].command, "FIND");
            if (str != NULL)
                findProcess(instructions[i].ID, processes);
        }
        processFound = 0;
    }
}
//performs instructions on bestfit algorithm
void performBestFit(struct algoParams instructions[], int numinstructions, struct Process processes[]){
    int idx = 0;
    int iFlag = 0;
    int rFlag = 0;
    int processFound = 0;
    int availableSize = maxMemory;
    for (int m = 0; m < maxMemory; m++)
        processes[m].PID = NULL;
    for (int i = 0; i < numinstructions; i++) {
        if (instructions[i].isEmpty == -700)
            iFlag = 1;
        if (iFlag == 1) {
            char* str1 = strstr(instructions[i].command, "REQUEST");
            if (instructions[i].size < 1){
                printf("FAIL REQUEST %s %d\n", instructions[i].ID, instructions[i].size);
                continue;
            }
            if (str1 != NULL) {
                if (rFlag == 0) {
                    if (availableSize >= instructions[i].size) {
                        for (int j = idx; j < idx + instructions[i].size; j++) {
                            processes[j].full = 700;
                            availableSize--;
                            processes[j].PID = instructions[i].ID;
                            processes[j].size = instructions[i].size;
                        }
                        printf("ALLOCATED %s %d\n", instructions[i].ID, idx);
                        idx += instructions[i].size;
                        continue;;
                    } else {
                        printf("FAIL REQUEST %s %d\n", instructions[i].ID, instructions[i].size);
                        continue;
                    }
                } else {
                    idx = 0;
                    idx = calculateAvailableSizeForBestFit(idx, processes, instructions[i]);
                    min = ULLONG_MAX; 
                    pPtr = 0;
                    pFlag = 0;
                    if (idx == -1) {
                        printf("FAIL REQUEST %s %d\n", instructions[i].ID, instructions[i].size);
                        continue;
                    }
                    else {
                        for (int j = idx; j < idx + instructions[i].size; j++) {
                            processes[j].full = 700;
                            processes[j].PID = instructions[i].ID;
                            processes[j].size = instructions[i].size;
                        }
                        printf("ALLOCATED %s %d\n", instructions[i].ID, idx);
                        continue;
                    }
                }
            }
            char* str2 = strstr(instructions[i].command, "RELEASE");
            if (str2 != NULL) {
                rFlag = 1;
                int temp;
                for (int m = 0; m < maxMemory; m++) {
                    str2 = NULL;
                    if (processes[m].PID != NULL)
                        str2 = strstr(instructions[i].ID, processes[m].PID);
                    if (str2 != NULL) {
                        if (processFound == 0) {
                            temp = m;
                            instructions[i].size = processes[m].size;
                            processFound = 1;
                            processes[m].PID = 0;
                            processes[m].full = -700;
                            processes[m].size = 0;
                            processes[m].end = 0;
                        } else {
                            processes[m].PID = 0;
                            processes[m].full = -700;
                            processes[m].size = 0;
                            processes[m].end = 0;
                        }
                    }
                }
                if (processFound == 1) {
                    printf("FREE %s %d %d\n", instructions[i].ID, instructions[i].size, temp);
                    processFound = 0;
                    continue;
                }
                else {
                    printf("FAIL RELEASE %s\n", instructions[i].ID);
                    processFound = 0;
                    continue;
                }
            }
            char* str = strstr(instructions[i].command, "LIST") && strstr(instructions[i].subcommand, "AVAILABLE");
            if (str != NULL)
                listAvailable(processes);
            str = strstr(instructions[i].command, "LIST") && strstr(instructions[i].subcommand, "ASSIGNED");
            if (str != NULL)
                listAssigned(processes);
            str = strstr(instructions[i].command, "FIND");
            if (str != NULL)
                findProcess(instructions[i].ID, processes);
        }
    }
}
//gets input from main function parameters
void getInput(char **argv){
    fitType = argv[1];
    maxMemory = atoi(argv[2]);
    fp = fopen(argv[3], "r");
}

int main(int argc, char**argv) {
    getInput(argv);
    struct Process *processes = (struct Process*) malloc(maxMemory * sizeof(struct Process));
    int numI = readinstructions(fp);
    char* str = strstr(fitType, "FIRSTFIT");
    if (str != NULL)
        performFirstFit(instructions,numI,processes);
    str = strstr(fitType, "NEXTFIT");
    if (str != NULL)
        performNextFit(instructions,numI,processes);
    str = strstr(fitType, "WORSTFIT");
    if (str != NULL)
        performWorstFit(instructions,numI,processes);
    str = strstr(fitType, "BESTFIT");
    if (str != NULL)
        performBestFit(instructions,numI,processes);
}
