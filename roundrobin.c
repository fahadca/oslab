#include<stdio.h>
#include<string.h>

struct process{
    char ID[5];
    int AT,BT,CT,TAT,WT,status,left;
}P[20];

struct done{
    char name[5];
    int start_time,completion_time;
}d[20];

int Q[100],front=-1,rear=-1;

void enQueue(int item){
    if(front==-1 && rear==-1){
        front++;
    }
    rear++;
    Q[rear]=item;
}

int deQueue(){
    int item;
    item=Q[front];

    if(front==rear){
        front=rear=-1;
    }
    else{
       front++;
    }

    return item;
}





void calculate(int n,int tq){
    int process_completed=0,num=0,i,j,k,idle=0;

    for(i=0 ; process_completed<n ; i++){  //i represents time flow
       
       for(j=0 ; j<n ; j++){
        if(P[j].AT<=i && P[j].status==0){
            enQueue(j);
            P[j].status=1;
            idle=1;
        }
       }

       if(idle==0){
        strcpy(d[num].name,"idle");
        d[num].start_time=i;
        d[num].completion_time=i;
        num++;
       }
       else{
          k=deQueue();
          strcpy(d[num].name,P[k].ID);
          d[num].start_time=i;

          if(P[k].left<=tq){
            d[num].completion_time=i+P[k].left;
            P[k].CT=d[num].completion_time;
            P[k].TAT=P[k].CT-P[k].AT;
            P[k].WT=P[k].TAT-P[k].BT;
            P[k].status=2;
            i=d[num].completion_time;

            num++;
            process_completed++;

            for(j=0 ; j<n ; j++){
             if(P[j].AT<=i && P[j].status==0){
                enQueue(j);
                P[j].status=1;
             }
           }
           i--;
          }
          else{
            d[num].completion_time=i+tq;
            P[k].left=P[k].left-tq;
            i=i+tq;
            num++;

          for(j=0 ; j<n ; j++){
             if(P[j].AT<=i && P[j].status==0){
                enQueue(j);
                P[j].status=1;
             }
             
           }
           i--;
           enQueue(k);
          }
        }

    }

  printf("\nPROCESS NAME\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
  for (i = 0; i < n; i++)
  {
    printf("    %s\t\t\t%d\t\t\t%d\t\t\t%d\n", P[i].ID, P[i].CT, P[i].WT, P[i].TAT);
    //avwt += p[i].wt;
    //avtt += p[i].tt;
  }    
}

int main(){
  int n,tq,i;
  printf("ENTER THE NUMBER OF PROCESSES : ");
  scanf("%d", &n);
  printf("\nENTER THE TIME QUANTUM : ");
  scanf("%d", &tq);

  //enter process details
  
  for (i = 0; i < n; i++){
    //printf("\nENTER DETAILS OF PROCESS %d", i + 1);
    printf("\nENTER PROCESS ID : ");
    scanf(" %s", P[i].ID);
    printf("ARRIVAL TIME : ");
    scanf("%d", &P[i].AT);
    printf("BURST TIME : ");
    scanf("%d", &P[i].BT);
    P[i].status = 0;
    P[i].left = P[i].BT;
  }

  calculate(n,tq);
  
}

//6 4 1 0 5 2 1 6 3 2 3 4 3 1 5 4 5 6 6 4