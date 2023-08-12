#include<stdio.h>
#include<string.h>

struct process{
    int ID;
    int AT;
    int BT;
    int WT;
    int TAT;
    int CT;
    int priority;
    int status;
}P[50];

void calculate(int n){
    int completed_process=0,num_completed=0,min_index;
    int i,j; //i represents time flow

    for(i=0;completed_process<n;i++){
        min_index = -1;
        
        //int found_process=0;
        for (j = 0; j < n; j++) {
            if (P[j].AT <= i && P[j].status == 0) {
                if (min_index == -1 || P[j].priority < P[min_index].priority) {
                     min_index = j;
                 }
            }
       }   

        if(min_index != -1){
            P[min_index].status=1;

            P[min_index].CT = i + P[min_index].BT;
            P[min_index].TAT = P[min_index].CT - P[min_index].AT;
            P[min_index].WT = P[min_index].TAT - P[min_index].BT;
            
            i=P[min_index].CT -1;  
            
            completed_process++;
            
        }
        
    }
}

void displayTable(int n){
  printf("\nPROCESS ID\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
  for (int i = 0; i < n; i++)
  {
    printf("%d\t\t%d\t\t\t%d\t\t\t%d\n", P[i].ID, P[i].CT, P[i].WT, P[i].TAT);
   
  }
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
        printf("Priority: ");
        scanf("%d", &P[i].priority);
        P[i].status=0;
    }
    
    calculate(n);

    displayTable(n);


 return 0;

}

