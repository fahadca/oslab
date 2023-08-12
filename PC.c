#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t empty,full,mutex;

#define N 5

int in=0,out=0,buffer[N];

void *producer(void *arg){
   int i;
   for(i=0 ; i<10 ; i++){
      sem_wait(&empty);
      sem_wait(&mutex);
      buffer[in]=i;
      printf("\nProducer produces the item %d",buffer[in]);
      in = (in+1)%N;
      sleep(1);
      sem_post(&mutex);
      sem_post(&full);
   }
}

void *consumer(void *arg){
    int i,item;
    for(i=0 ; i<10 ; i++){
      sem_wait(&full);
      sem_wait(&mutex);
      item=buffer[out];
      printf("\nConsumer consumes item %d",item);
      out = (out+1)%N;
      sleep(1);
      sem_post(&mutex);
      sem_post(&empty);
    }
}

int main(){
    pthread_t P,C;
    sem_init(&empty,0,N);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    pthread_create(&P,NULL,producer,NULL);
    pthread_create(&C,NULL,consumer,NULL);
    pthread_join(P,NULL);
    pthread_join(C,NULL);
}