#pragma once
typedef struct disk {		//磁盘块
	int number;
	char disk_file[50];
}DISK; DISK disk[50];

typedef struct {
	int C;	//柱面
	int H;	//磁头
	int B;	//扇区
}BlockInfo; BlockInfo ldisk[512];

typedef struct index {		//文件用户目录
	char filename[50];		//文件名
	char username[50];		//用户名
	struct index *next;
}INDEX; INDEX *index;

typedef struct fileindex {	//文件目录
	char filename[50];
	int access;
	int length;					//长度
	struct fileindex *next;
}FILEINDEX; FILEINDEX *files;

typedef struct fileaccess {//文件读写目录			
	char filename[50];
	int access;
	int point;						//读写指针
	struct fileaccess *next;
}FILEACCESS; FILEACCESS *filea;
char Users[50];	