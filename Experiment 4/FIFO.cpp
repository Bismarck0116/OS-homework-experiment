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
int access[MAX];	//工作集
int lost = 0;		//缺页数
int size = 4;		//给进程分配的内存的大小
int a[64] = { 52,56,49 ,51 ,50, 55 ,54, 51 ,57 ,57 ,57, 54, 52 ,53 ,56 ,53 ,56, 57 ,57 ,55 ,51 ,
52 ,55 ,53 ,54 ,59 ,57 ,57, 58 ,52 ,56, 55, 57 ,54 ,53, 53 ,58 ,53 ,59 ,57, 60, 56, 56, 59,61 ,57, 
58 ,57 ,62 ,60 ,62, 62 ,57, 58 ,58 ,55, 61 ,59, 57, 62, 63, 62 ,56 ,61 };

int main()
{
	Generate();
	//printf("工作集为：\n");
	//for (int i = 0; i < MAX; i++)
		//printf("%d ", access[i]);
	printf("\n\n");
	testFIFO();
	getchar();
	return 0;
}

void Generate()//生成具有局部访问特性的工作集
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
	printf("\nFIFO算法缺页率：%f  %d\n", lost / 32000.0, lost);
	destroy(&q);
}

void FIFO(pQueue q, int num) //实现先入先出置换算法
{
	if (findInQueue(q, num)){;}//检查是否缺页
	else{
		if (q->n == size){ 
			pop(q);
			push(q, num); //弹出队头，缺页数+1
			lost++;
		}
		else{
			push(q, num);
			lost++;
		}
	}
}
