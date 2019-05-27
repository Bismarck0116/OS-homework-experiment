#include	"pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include	"stdio.h"
#include	"stdlib.h"
#include	"time.h"
#include	"node.h"
#define MAX 32000

int size = 3;
int access[MAX]; //访问序列
int* memory;
int lost = 0;		//缺页数
int index = 0;

void initSpace();
void Generate();
bool isInMemory(int n); 
void Optimal(int n); 
void testOptimal();
void LRU(int n);
void testLRU();
void Clock(int n);
void testClock();

int main()
{
	Generate();
	testOptimal(); printf("\n");
	testLRU(); printf("\n");
	testClock(); printf("\n");
	getchar();
	return 0;
}

void Generate()
{
	srand((unsigned)time(NULL)); 
	int p = rand() % 64;
	int m = 8, e = 8;
	int i, j;
	double t;
	t = rand() % 10 / 10.0;
	for (i = 0; i < 4000; i++)
	{
		for (j = i * m; j < (i + 1) *m; j++)
		{
			access[j] = (p + rand() % e) % 64;
		}
		double r = (rand() % 10) / 10.0;
		if (r < t)
		{
			p = rand() % 64;
		}
		else
		{
			p = (p + 1) % 64;
		}
	}
}

void initSpace()
{
	memory = (int*)malloc(size * sizeof(int));
	int i = 0;
	for (; i < size; i++)
	{
		memory[i] = -1;
	}
	return;
}

bool  isInMemory(int n)
{
	for (int i = 0;i < size; i++)
	{
		if (access[n] == memory[i])
		{
			return true;
		}
	}
	return false;
}

bool isInNodes(int n)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (nodes[i].data == access[n])
		{
			return true;
		}
	}
	return false;
}

//最佳置换算法OPT
void Optimal(int n)
{
	int i = 0, j = 0;
	if (isInMemory(n))
	{
		;//未发生缺页，继续
	}
	else
		if (index == size)
		{
			lost++;		//缺页数+1
			int max = 0;
			int position, tag;
			for (i = 0; i < size; i++)
			{
				tag = -1;
				for (j = n + 1; j < MAX; j++)
				{	//在整个工作集中找出距现在最长时间才会被访问的页面号
					if (access[j] == memory[i])
					{
						tag = j;
						break;
					}
				}
				if (tag == -1) //往后不会被访问，直接弹出
				{
					max = MAX;
					position = i;
					break;
				}
				else
				{
					if (max < tag)
					{
						max = tag;
						position = i;
					}
				}
			}
			memory[position] = access[n];
		}
		else 
		{
			memory[index] = access[n];
			index++;
		}
}
void testOptimal()
{
	initSpace();
	printf("最佳置换算法：\n");
	for (int i = 0; i < MAX; i++)
	{
		Optimal(i);
		//printf("%d %d %d\n", memory[0], memory[1], memory[2]);
	}
	printf("最佳置换算法 缺页率： %2f %d\n", lost / 32000.0, lost);
	lost = 0;
	free(memory);
	index = 0;
}

//LRU算法
void LRU(int n)
{
	int i, j;
	if (isInMemory(n))
	{
		;//未发生缺页，继续
	}
	else
		if (index == size)
		{
			int max = n, pos = -1, tag;
			for (i = 0; i < size; i++)
			{
				for (j = n - 1; j >= 0; j--) //向前查找
				{
					if (access[j] == memory[i])
					{
						tag = j;
						break;
					}
				}
				if (tag < max) //比较得出最近一段时间最长时间未被访问的页面
				{
					max = tag;
					pos = i;
					if (max == 0)
					{
						break;
					}
				}
			}
			memory[pos] = access[n];
			lost++;
		}
		else
		{
			memory[index] = access[n];
			index++;
		}
}
void testLRU()
{
	int i;
	initSpace();
	printf("LRU算法\n");
	for (i = 0; i < MAX; i++)
	{
		LRU(i);
		//printf("%d %d %d\n", memory[0], memory[1], memory[2]);
	}
	printf("LRU 缺页率： %2f %d \n", lost / 32000.0, lost);
	lost = 0;
	index = 0;
	free(memory);
}

//改进型Clock算法
void Clock(int n)
{
	if (isInNodes(n))
	{
		;//未发生缺页，继续
	}
	else
		if (index == size)
		{
			lost++;
			int i = 0, tag = -1;
			while (true) //循环遍历内存块
			{
				if ((i / size) % 2 == 0)
				{
					if (nodes[i % size].A == 0 && nodes[i % size].M == 0) //A=0且M=0
					{
						tag = i % size;
						break;
					}
				}
				if ((i / size) % 2 == 1)
				{
					if (nodes[i % size].A == 0 && nodes[i % size].M == 1) //A=0且M=1
					{
						tag = i % size;
						break;
					}
					else
					{
						nodes[i % size].A = 0; //将经过的所有页面访问位置为0
					}
				}
				i++;
			}

			nodes[tag].data = access[n];
			nodes[tag].A = 1;
			if (rand() % 10 < 4)
			{
				nodes[tag].M = 1;
			}
			else
			{
				nodes[tag].M = 0;
			}
		}
		else
		{
			nodes[index].data = access[n];
			nodes[index].A = 1;
			if (rand() % 10 < 4)
			{
				nodes[index].M = 1;
			}
			else
			{
				nodes[index].M = 0;
			}
			index++;
		}
}
void testClock()
{
	int i = 0, j = 0;
	nodes = (LNode*)malloc(size * sizeof(LNode));
	printf("改进型Clock置换算法\n");
	for (i = 0; i < size; i++) //初始化
	{
		nodes[i].data = -1;
		nodes[i].A = -1;
		nodes[i].M = -1;
	}
	for (i = 0; i < MAX; i++)
	{
		Clock(i);
		//for (j = 0; j < size; j++)
		//{
			//printf("%d ", nodes[j].data);
		//}
	}
	printf("改进型Clock置换算法 缺页率： %2f %d \n", lost / 32000.0, lost);
	lost = 0;
	index = 0;
}
