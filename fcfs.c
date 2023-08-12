#include<stdio.h>

struct process{
    int ID;
    int AT;
    int BT;
}P[50];

int WT[50];
int TAT[50];

void calculate(int n){
    WT[0] = 0;
    TAT[0] = P[0].BT;

    for (int i = 1; i < n; i++) {
        WT[i] = P[i - 1].AT + WT[i-1] + P[i - 1].BT - P[i].AT;
        TAT[i] = WT[i] + P[i].BT;
    }    
}

void displayTable(int n){
    printf("Process\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", P[i].ID,P[i].AT,P[i].BT,TAT[i],WT[i]);
               
    }
}

void displayGanttChart(int n){
    printf(".");
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<P[i].BT ;j++){
             printf("---");
           //printf("   ");
           //printf("P1-");
        }
        printf("."); 
    }
    printf("\n");
    
    printf("|");
    for(int i=0 ; i<n ; i++){
        printf("P%d ",P[i].ID);
        for(int j=1 ; j<P[i].BT ;j++){
             printf("   ");
        }
        printf("|");
    }
    printf("\n");
    
    printf(".");
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<P[i].BT ;j++){
             printf("---");     
        }
        printf("."); 
    }
    printf("\n");
}

int main(){
    int n,i,j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    

    for (i = 0; i < n; i++) {
        printf("Enter Process ID:");
        scanf("%d", &P[i].ID);
        printf("Arrival Time: ");
        scanf("%d", &P[i].AT);
        printf("Burst Time: ");
        scanf("%d", &P[i].BT);
    }
    
    struct process temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (P[j].AT > P[j + 1].AT) {
                temp = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp;
            }
        }
    }

    calculate(n);

    float avgWT,avgTAT;
    for (i = 0; i < n; i++) {
        avgWT += WT[i];
        avgTAT += TAT[i];
    }

    avgWT /= n;
    avgTAT /= n;

    printf("\nFCFS Scheduling Table:\n");
    displayTable(n);

    printf("\nAverage Waiting Time: %.2f", avgWT);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT);

    displayGanttChart(n);

 return 0;

}

