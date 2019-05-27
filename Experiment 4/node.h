#pragma once
#include "stdio.h"
#include"stdlib.h"

typedef struct node //链表形式存储节点
{
	int num;
	node* next;
} Node, *pNode;

typedef struct queue
{
	int n;
	pNode front;
	pNode rear;
} Queue, *pQueue;

struct LNode
{
	int data;
	int A;	//访问位
	int M;	//修改位
}; LNode* nodes;

void push(pQueue q, int num)//将页面移出内存
{
	pNode p = (pNode)malloc(sizeof(Node));
	if (p == NULL)
	{
		printf("failed");
	}
	else
	{
		p->next = NULL;
		p->num = num;
		if (q->front == q->rear)
		{
			q->front->next = p;
			q->rear = p;
		}
		else
		{
			q->rear->next = p;
			q->rear = p;
		}
		q->n++;
	}
}
void pop(pQueue q) //队列中加入新的页面结点
{
	pNode p;
	if (q->front != q->rear)
	{
		p = q->front->next;
		q->front->next = p->next;
		if (p == q->rear)
		{
			q->front = q->rear;
		}
		q->n--;
		free(p);
	}
}
void destroy(pQueue q)//销毁队列
{
	while (q->front != q->rear)
	{
		pop(q);
	}
}
void initQueue(pQueue q) //初始化队列
{
	q->rear = (pNode)malloc(sizeof(Node));
	if (q->rear == NULL) {
		printf("Error!\n");
	}
	else {
		q->front = q->rear;
		q->rear->next = NULL;
		q->front->next = NULL;
		q->n = 0;
	}
}
bool findInQueue(pQueue q, int num)//查找页面是否已经调入内存
{
	pNode p;
	if (q->front != q->rear) {
		p = q->front->next;
		while (p) {
			if (p->num == num) {
				return true;
			}
			else {
				p = p->next;
			}
		}
	}
	return false;
}
