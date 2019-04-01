#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <assert.h>

char buf[10] = {0};	//������ 
sem_t blanks;		//�ź���1����ʾbuf�������п��е�Ԫ�ĸ���
sem_t datas;		//�ź���2����ʾbuf�������зǿյ�Ԫ�ĸ���

void *worker1(void *arg){
	for (int i = 0; i < 10;) {
	sem_wait(&blanks);	//�ж��Ƿ��п��е�Ԫ�ɹ�����
	scanf("%c",&buf[i]);
	i++;
	i %= 10;			//ģ�⻷�ζ��У��Է�i++����10�������ݶ�ʧ
	sem_post(&datas);	//�ǿյ�Ԫ�� +1
	}
	return NULL;
}

void *worker2(void *arg){
	for (int i = 0; i < 10;) {
	sem_wait(&datas);	//�ж�buf���������Ƿ�������
	printf("%c  ",buf[i]);
	sleep(1);			//ÿ�����˯�� 1s
	i++;
	i %= 10;
	sem_post(&blanks);	//���һ�����ݺ󣬿��е�Ԫ��+1
	}
	return NULL;
}

int main(int argc, char *argv[]){	
	sem_init(&blanks, 0, 10);	//�ڶ��߳�֮ǰ��ʼ���ź���
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
