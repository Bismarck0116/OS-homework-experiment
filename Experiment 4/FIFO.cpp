#include	"pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include	"stdio.h"
#include	"stdlib.h"
#include	"time.h"
#include	"node.h"
#define MAX 32000

void Generate();
void testFIFO();
void FIFO(pQueue q, int num);
int access[MAX];	//������
int lost = 0;		//ȱҳ��
int size = 4;		//�����̷�����ڴ�Ĵ�С
int a[64] = { 52,56,49 ,51 ,50, 55 ,54, 51 ,57 ,57 ,57, 54, 52 ,53 ,56 ,53 ,56, 57 ,57 ,55 ,51 ,
52 ,55 ,53 ,54 ,59 ,57 ,57, 58 ,52 ,56, 55, 57 ,54 ,53, 53 ,58 ,53 ,59 ,57, 60, 56, 56, 59,61 ,57, 
58 ,57 ,62 ,60 ,62, 62 ,57, 58 ,58 ,55, 61 ,59, 57, 62, 63, 62 ,56 ,61 };

int main()
{
	Generate();
	//printf("������Ϊ��\n");
	//for (int i = 0; i < MAX; i++)
		//printf("%d ", access[i]);
	printf("\n\n");
	testFIFO();
	getchar();
	return 0;
}

void Generate()//���ɾ��оֲ��������ԵĹ�����
{
	int m = 8, e = 8;
	int i, j;
	int p = rand() % 64;
	srand((unsigned)time(NULL));
	double t;
	t = rand() % 10 / 10.0;
	for (i = 0; i < 4000; i++){
		for (j = i * m; j < (i + 1) *m; j++){
			access[j] = (p + rand() % e) % 64;
		}
		double r = (rand() % 10) / 10.0;
		if (r < t){
			p = rand() % 64;
		}
		else
		{
			p = (p + 1) % 64;
		}
	}
}

void testFIFO()
{
	Queue q; pNode p;
	initQueue(&q);
	for (int i = 0; i < MAX; i++){
		FIFO(&q, access[i]);
		p = q.front->next;
		while (p){
			//printf("%d ", p->num);
			p = p->next;
		}
		//printf("\n");
	}
	printf("\nFIFO�㷨ȱҳ�ʣ�%f  %d\n", lost / 32000.0, lost);
	destroy(&q);
}

void FIFO(pQueue q, int num) //ʵ�������ȳ��û��㷨
{
	if (findInQueue(q, num)){;}//����Ƿ�ȱҳ
	else{
		if (q->n == size){ 
			pop(q);
			push(q, num); //������ͷ��ȱҳ��+1
			lost++;
		}
		else{
			push(q, num);
			lost++;
		}
	}
}
