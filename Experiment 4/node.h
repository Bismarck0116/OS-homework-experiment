#pragma once
#include "stdio.h"
#include"stdlib.h"

typedef struct node //������ʽ�洢�ڵ�
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
	int A;	//����λ
	int M;	//�޸�λ
}; LNode* nodes;

void push(pQueue q, int num)//��ҳ���Ƴ��ڴ�
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
void pop(pQueue q) //�����м����µ�ҳ����
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
void destroy(pQueue q)//���ٶ���
{
	while (q->front != q->rear)
	{
		pop(q);
	}
}
void initQueue(pQueue q) //��ʼ������
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
bool findInQueue(pQueue q, int num)//����ҳ���Ƿ��Ѿ������ڴ�
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
