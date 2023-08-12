#include <stdio.h>
#include <stdlib.h>

int allocated[10][10];
int maxRequirement[10][10];
int needed[10][10];
int available[10];
int processCount, resourceCount;

void printMatrix(int matrix[][10], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        printf("\n");
        for (j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
    }
}

void resourceRequest(int processId) {
    int requestArray[10];
    int i;

       if (processId < 0 || processId >= processCount) {
        printf("\n Invalid process ID.\n");
        exit(0);
       }  

    printf("\n Enter additional request :- \n");
    for (i = 0; i < resourceCount; i++) {
        printf(" Request for resource %d : ", i + 1);
        scanf("%d", &requestArray[i]);
    }

    for (i = 0; i < resourceCount; i++) {
        if (requestArray[i] > needed[processId][i]) {
            printf("\n Error encountered.\n");
            exit(0);
        }
    }

    for (i = 0; i < resourceCount; i++) {
        if (requestArray[i] > available[i]) {
            printf("\n Resources unavailable.\n");
            exit(0);
        }
    }

    for (i = 0; i < resourceCount; i++) {
        available[i] -= requestArray[i];
        allocated[processId][i] += requestArray[i];
        needed[processId][i] -= requestArray[i];
    }
}

int safetyAlgorithm(int processCount, int resourceCount, int safeSequence[]) {
    int i, j, k, x = 0;
    int finish[10], work[10];
    int processFlag = 0, flag = 0;

    for (i = 0; i < processCount; i++)
        finish[i] = 0;

    for (i = 0; i < resourceCount; i++)
        work[i] = available[i];

    for (k = 0; k < processCount; k++) {
        for (i = 0; i < processCount; i++) {
            if (finish[i] == 0) {
                flag = 0;
                for (j = 0; j < resourceCount; j++) {
                    if (needed[i][j] > work[j])
                        flag = 1;
                }
                if (flag == 0 && finish[i] == 0) {
                    for (j = 0; j < resourceCount; j++)
                        work[j] += allocated[i][j];
                    finish[i] = 1;
                    processFlag++;
                    safeSequence[x++] = i;
                }
            }
        }
        if (processFlag == processCount)
            return 1;
    }
    return 0;
}

int bankersAlgorithm() {
    int i, j, safeSequence[10];
    i = safetyAlgorithm(processCount, resourceCount, safeSequence);
    if (i != 0) {
        printf("\n\n");
        for (j = 0; j < processCount; j++)
            printf(" P%d  ", safeSequence[j]);
        printf("\n A safety sequence has been detected.\n");
        return 1;
    } else {
        printf("\n Deadlock has occurred.\n");
        return 0;
    }
}

void input() {
    int i, j;

    printf("\n Enter total no. of processes : ");
    scanf("%d", &processCount);
    printf("\n Enter total no. of resources : ");
    scanf("%d", &resourceCount);

    printf("Max Requirement Matrix:\n");
    for (i = 0; i < processCount; i++) {
        for (j = 0; j < resourceCount; j++) {
            scanf("%d", &maxRequirement[i][j]);
        }
    }

    printf("Allocation Matrix:\n");
    for (i = 0; i < processCount; i++) {
        for (j = 0; j < resourceCount; j++) {
            scanf("%d", &allocated[i][j]);
        }
    }

    printf("\n Available resources : \n");
    for (i = 0; i < resourceCount; i++) {
        scanf("%d", &available[i]);
    }

    for (i = 0; i < processCount; i++)
        for (j = 0; j < resourceCount; j++)
            needed[i][j] = maxRequirement[i][j] - allocated[i][j];

    printf("\n Allocation Matrix");
    printMatrix(allocated, processCount, resourceCount);
    printf("\n Maximum Requirement Matrix");
    printMatrix(maxRequirement, processCount, resourceCount);
    printf("\n Need Matrix");
    printMatrix(needed, processCount, resourceCount);
}

int main() {
    int returnValue, processId, choice;

    printf("\n DEADLOCK AVOIDANCE USING BANKER'S ALGORITHM\n");
    input();
    returnValue = bankersAlgorithm();

    if (returnValue != 0) {
        printf("\n Do you want to make an additional request? (1=Yes | 0=No)");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("\n Enter process no. : ");
            scanf("%d", &processId);
            resourceRequest(processId - 1);
            returnValue = bankersAlgorithm();
            if (returnValue == 0)
                exit(0);
        }
    } else {
        exit(0);
    }
    return 0;
}


// max 7 5 3 3 2 2 9 0 2 2 2 2 4 3 3
// allo 0 1 0 2 0 0 3 0 2 2 1 1 0 0 2
//avai 3 3 2