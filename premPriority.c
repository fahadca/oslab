#include <stdio.h>

int main() {
    int numberOfProcesses, arrivalTime[20], priority[20], burstTime[20], completionTime[20], remainingTime[20], turnaroundTime[20], waitingTime[20], tempBurstTime[20];
    int smallestPriorityIndex, processCount = 0, currentTime = 0, endTime = 0;
    float averageWaitingTime = 0, averageTurnaroundTime = 0;

    printf("\n Enter the number of processes: ");
    scanf("%d", &numberOfProcesses);

    printf("\n Enter Arrival Time, Burst Time & Priority for each process:\n");
    for (int i = 0; i < numberOfProcesses; i++) {
        printf("P%d : ", i + 1);
        scanf("%d%d%d", &arrivalTime[i], &burstTime[i], &priority[i]);
        tempBurstTime[i] = burstTime[i];
    }

    for (currentTime = 0; processCount != numberOfProcesses; currentTime++) {
        smallestPriorityIndex = -1;
        for (int i = 0; i < numberOfProcesses; i++) {
            if (arrivalTime[i] <= currentTime && burstTime[i] > 0) {
                if (smallestPriorityIndex == -1 || priority[i] < priority[smallestPriorityIndex]) {
                    smallestPriorityIndex = i;
                }
            }
        }
        
        if (smallestPriorityIndex != -1) {
            burstTime[smallestPriorityIndex] = burstTime[smallestPriorityIndex] - 1;

            if (burstTime[smallestPriorityIndex] == 0) {
                processCount++;
                endTime = currentTime + 1;
                completionTime[smallestPriorityIndex] = endTime;
                waitingTime[smallestPriorityIndex] = endTime - arrivalTime[smallestPriorityIndex] - tempBurstTime[smallestPriorityIndex];
                turnaroundTime[smallestPriorityIndex] = endTime - arrivalTime[smallestPriorityIndex];
            }
        }
    }

    printf("\n Process\tAT\tBT\tCT\tTAT\tWT\n");
    printf("-------------------------------------------\n");
    for (int i = 0; i < numberOfProcesses; i++) {
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\n", i + 1, arrivalTime[i], tempBurstTime[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
        averageTurnaroundTime += turnaroundTime[i];
        averageWaitingTime += waitingTime[i];
    }
    averageTurnaroundTime /= numberOfProcesses;
    averageWaitingTime /= numberOfProcesses;
    printf("\n Avg TAT is : %f\n", averageTurnaroundTime);
    printf(" Avg WT is  : %f\n", averageWaitingTime);

    return 0;
}
