#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <assert.h>

char buf[10] = {0};	//缓冲区 
sem_t blanks;		//信号量1，表示buf缓存区中空闲单元的个数
sem_t datas;		//信号量2，表示buf缓存区中非空单元的个数

void *worker1(void *arg){
	for (int i = 0; i < 10;) {
	sem_wait(&blanks);	//判断是否有空闲单元可供输入
	scanf("%c",&buf[i]);
	i++;
	i %= 10;			//模拟环形队列，以防i++超过10导致数据丢失
	sem_post(&datas);	//非空单元数 +1
	}
	return NULL;
}

void *worker2(void *arg){
	for (int i = 0; i < 10;) {
	sem_wait(&datas);	//判断buf缓冲区中是否有数据
	printf("%c  ",buf[i]);
	sleep(1);			//每次输出睡眠 1s
	i++;
	i %= 10;
	sem_post(&blanks);	//输出一个数据后，空闲单元数+1
	}
	return NULL;
}

int main(int argc, char *argv[]){	
	sem_init(&blanks, 0, 10);	//在多线程之前初始化信号量
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
