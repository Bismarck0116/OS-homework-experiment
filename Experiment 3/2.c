#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <assert.h>

int ticketcount = 1000;
int temp = 0;
sem_t blanks;	//
sem_t datas;	//

void *worker1(void *arg){
	while(1){
	sem_wait(&blanks);
	temp = ticketcount;
	pthread_yield();
	temp = temp - 1;
	pthread_yield();
	ticketcount = temp;
	printf("Sale:ticketCount now is: %d\n",ticketcount);
	sleep(1);
	sem_post(&datas);
	}
	return NULL;
}

void *worker2(void *arg){
	while(1){
	sem_wait(&datas);
	temp = ticketcount;
	pthread_yield();
	temp = temp + 1;
	pthread_yield();
	ticketcount = temp;
	printf("Refund:ticketCount now is: %d\n",ticketcount);
	sleep(1);
	sem_post(&blanks);
	}
	return NULL;
}

int main(int argc, char *argv[]){	
	sem_init(&blanks, 0, 1000);
	sem_init(&datas, 0, 0);

	pthread_t p1, p2;
	pthread_create(&p1, NULL, worker1, NULL);
	pthread_create(&p2, NULL, worker2, NULL);

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	sem_destroy(&blanks);
	sem_destroy(&datas);

	return 0;
}
