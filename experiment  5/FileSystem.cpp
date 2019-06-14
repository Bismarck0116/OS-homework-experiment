#include "pch.h"
#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "tools.h"
#define NULL 0
using namespace std;

void ReadBlock(int i, char *p, int B) 
//把第i个磁盘块拷贝到指针p指向的内存。拷贝的字符数为盘块的大小B
{
	if (*p != NULL && disk[i].disk_file)
		for(int j = 0 ; j<B; j++)
			strcpy(p, disk[i].disk_file);
	else
		return;
}

void WriteBlock(int i, char *p) 
//把p指向的内存位置开始的B个字符拷贝到第i个磁盘块中
{
	int j = 0;
	while (*(p + j) != NULL)
	{
		disk[i].disk_file[j] = *(p + j);
		j++;
	}
	return;
}

void InitFileIndex(char *name)//初始化文件目录
{
	FILE *fp;
	files = (FILEINDEX*)malloc(sizeof(FILEINDEX));
	FILEINDEX *p = files;
	if ((fp = fopen(name, "r+")) == NULL) {
		cout<<"文件目录出错!"<<endl;
		exit(1);
	}
	while (!feof(fp)) {//建立链表
		p->next = (FILEINDEX*)malloc(sizeof(FILEINDEX));
		p = p->next;
		fscanf(fp, "%s", p->filename);
		fscanf(fp, "%d", &p->access);
		fscanf(fp, "%d", &p->length);
		fgetc(fp);
	}
	p->next = NULL;
	fclose(fp);
}

void PrintFileIndex()
{
	cout<<"文件名\t\t长度"<<endl;
	FILEINDEX *p = files->next;
	while (p != NULL) {
		cout << p->filename << "\t\t"<< p->length << endl;
		p = p->next;
	}
}

int CheckUser()//检测登陆用户
{
	char input[20];
	while (1) {
		INDEX *p = index;
		cout<<"请输入用户名: "<<endl;
		cin >> input;
		while (p) {
			if (strcmp(input, p->username) == 0) { 
				strcpy(Users, p->filename);
				InitFileIndex(p->filename);
				PrintFileIndex();
				return 1;
			}
			p = p->next;
		}
		if (strcmp(input, p->username) != 0) {
			cout << "用户不存在！"<<endl;
			return 0;
		}	
	}
}

bool Create()//创建文件命令
{
	char filename[20];
	FILEACCESS *pa = filea;
	FILEINDEX *p = files->next;
	cout << "请输入要创建的文件名: "<<endl;
	scanf("%s", filename);
	while (p) {
		if (strcmp(filename, p->filename) == 0) {
			cout << "文件名已存在！"<<endl;
			return 0;
		}
		if (!p->next)
			break;
		p = p->next;
	}
	p->next = (FILEINDEX*)malloc(sizeof(FILEINDEX));
	p = p->next;
	strcpy(p->filename, filename);
	p->access = 2;
	p->length = 0;
	p->next = NULL;

	while (pa->next) {
		pa = pa->next;
	}
	pa->next = (FILEACCESS*)malloc(sizeof(FILEACCESS));
	pa = pa->next;
	strcpy(pa->filename, filename);
	pa->access = 2;
	pa->point = 0;
	pa->next = NULL;
	return 1;
}

bool Delete()//删除文件命令
{
	char filename[20];
	FILEINDEX *p = files;
	FILEINDEX *temp;
	cout << "请输入要删除的文件名: "<<endl;
	cin >> filename;
	while (p->next) {
		if (strcmp(filename, p->next->filename) == 0) {
			temp = p->next;
			p->next = p->next->next; //删除节点
			free(temp);
			printf("文件 %s 删除成功!\n", filename);
			return 1;
		}
		p = p->next;
	}
	cout << "文件不存在!"<<endl;
	return 0;
}

bool Open()//打开文件命令
{
	char filename[20];
	int temp = 2;
	cout << "请输入要打开的文件名: "<<endl;
	cin >> filename;
	FILEINDEX *pi = files->next;
	FILEACCESS *pa = filea->next;
	while (pa) {
		if (strcmp(filename, pa->filename) == 0) {
			printf("文件 %s 已打开!\n", filename);
			return 1;
		}
		if (!pa->next)
			break;
		pa = pa->next;
	}
	if (!pa) pa = filea;
	while (pi) {
		if (strcmp(filename, pi->filename) == 0) {
			pa->next = (FILEACCESS*)malloc(sizeof(FILEACCESS));
			pa = pa->next;
			strcpy(pa->filename, pi->filename);
			pa->access = temp;
			if (temp == 1) {
				pa->point = 0;
			}	
			else {
				pa->point = pi->length;
			}		
			printf("文件 %s 已打开!\n", filename);
			pa->next = NULL;
			return 1;
		}
		pi = pi->next;
	}
	cout<<"文件不存在!"<<endl;
	return 0;
}

void Close()//关闭文件命令
{
	char filename[20];
	FILEINDEX *pu = files->next;
	cout << "请输入要关闭的文件名: "<<endl;
	scanf("%s", filename);
	FILEACCESS *p = filea;
	FILEACCESS *temp;
	while (p&&p->next) {
		if (strcmp(filename, p->next->filename) == 0) {
			temp = p->next;
			p->next = p->next->next;
			if (temp->access == 2) {
				while (pu) {
					if (strcmp(temp->filename, pu->filename) == 0) {
						pu->length = temp->point;
						break;
					}
					pu = pu->next;
				}
			}
			free(temp);
			printf("文件 %s 关闭成功!\n", filename);
			return;
		}
		p = p->next;
	}
	cout << "文件未打开!" << endl;
}

int Read()//读文件命令
{
	char filename[20];
	int length;
	FILEACCESS *p = filea->next;
	cout << "请输入要读的文件名: "<<endl;
	cin >> filename;
	cout << "请输入要读的长度: "<<endl;
	cin >> length;
	while (p) {
		if (strcmp(filename, p->filename) == 0) {
			p->point += length;
			printf("文件 %s 读取成功!\n", filename);
			return 1;
		}
		p = p->next;
	}
	cout << "读取失败!"<<endl;
	return 0;
}

int Write()//写文件命令
{
	char filename[20];
	int length;
	FILEACCESS *p = filea->next;
	cout << "请输入要写的文件名: "<<endl;
	cin >> filename;
	while (p) {
		if (strcmp(filename, p->filename) == 0) {
			if (p->access != 2) {
				printf("文件 %s 不可写!\n", filename);
				return 0;
			}
			cout << "请输入要写入的内容长度"<<endl;
			cin >> length;
			p->point += length;
			cout<<"写入成功!"<<endl;
			return 1;
		}
		p = p->next;
	}
	cout << "写入失败!"<<endl;
	return 0;
}

void Directory() {
	FILEACCESS *pa = filea->next;
	FILEINDEX *pu = files->next;
	while (pa) {
		if (pa->access == 2) {
			while (pu) {
				if (strcmp(pa->filename, pu->filename) == 0) {
					pu->length = pa->point;
					break;
				}
				pu = pu->next;
			}
		}
		pa = pa->next;
	}
	FILE *fp;
	FILEINDEX *p = files->next;
	if ((fp = fopen(Users, "w")) == NULL) {
		cout << "用户名出错!" << endl;
		exit(1);
	}
	while (p) {
		fprintf(fp, "%s", "\n");
		fprintf(fp, "%s%s", p->filename, "\t\t");
		fprintf(fp, "%d%s", p->access, "\t\t");
		fprintf(fp, "%d", p->length);
		p = p->next;
	}
	fclose(fp);
	PrintFileIndex();
}

void Free()//释放内存
{
	INDEX *pm = index;
	while (pm) {
		index = index->next;
		free(pm);
		pm = index;
	}
	FILEACCESS *pa = filea;
	while (pa) {
		filea = filea->next;
		free(pa);
		pa = filea;
	}
	FILEINDEX *pu = files;
	while (pu) {
		files = files->next;
		free(pu);
		pu = files;
	}
}

void Exit()
{
	FILE *fp;
	FILEINDEX *p = files->next;
	if ((fp = fopen(Users, "w")) == NULL) {
		cout << "用户名出错!" << endl;
		exit(1);
	}
	while (p) {
		fprintf(fp, "%s", "\n");
		fprintf(fp, "%s%s", p->filename, "\t\t");
		fprintf(fp, "%d%s", p->access, "\t\t");
		fprintf(fp, "%d", p->length);
		p = p->next;
	}
	fclose(fp);
	cout << "系统已退出！" << endl;
	Free();
}

int main()
{
	cout << "16281027os实验五 文件系统启动！" << endl<<"功能列表"<<endl;
	cout << "create(filename)" << endl;
	cout << "delete(filename)" << endl;
	cout << "open(filename)" << endl;
	cout << "close(filename)" << endl;
	cout << "read(filename,count) " << endl;
	cout << "write(filename,count) " << endl;
	cout << "directory()" << endl;
	cout << "exit() " << endl;

	index = (INDEX*)malloc(sizeof(INDEX));
	INDEX *p = index;
	FILE *fp;
	if ((fp = fopen("MDF.txt", "r+")) == NULL) {
		cout << "Index file cannot open!" << endl;
		exit(1);
	}
	while (!feof(fp)) {
		p->next = (INDEX*)malloc(sizeof(INDEX));
		p = p->next;
		fscanf(fp, "%s", p->username);
		fscanf(fp, "%s", p->filename);
	}
	p->next = NULL;
	fclose(fp);
	CheckUser();
	filea = (FILEACCESS*)malloc(sizeof(FILEACCESS));
	filea->next = NULL;
	while (1) {
		cout << "请输入命令: " << endl;
		char function[][10] = {
			"create", "delete", "open", "close",
			"read", "write","directory","exit"
		};
		char command[15];
		cin >> command;
		if (strcmp(command, function[0]) == 0)
			Create();
		else if (strcmp(command, function[1]) == 0)
			Delete();
		else if (strcmp(command, function[2]) == 0)
			Open();
		else if (strcmp(command, function[3]) == 0)
			Close();
		else if (strcmp(command, function[4]) == 0)
			Read();
		else if (strcmp(command, function[5]) == 0)
			Write();
		else if (strcmp(command, function[6]) == 0)
			Directory();
		else if (strcmp(command, function[7]) == 0) {
			Exit();
			return 0;
		}
		else
			cout << "命令无效，请重新输入！" << endl;
	}
	return 0;
}