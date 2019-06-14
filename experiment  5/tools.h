#pragma once
typedef struct disk {		//���̿�
	int number;
	char disk_file[50];
}DISK; DISK disk[50];

typedef struct {
	int C;	//����
	int H;	//��ͷ
	int B;	//����
}BlockInfo; BlockInfo ldisk[512];

typedef struct index {		//�ļ��û�Ŀ¼
	char filename[50];		//�ļ���
	char username[50];		//�û���
	struct index *next;
}INDEX; INDEX *index;

typedef struct fileindex {	//�ļ�Ŀ¼
	char filename[50];
	int access;
	int length;					//����
	struct fileindex *next;
}FILEINDEX; FILEINDEX *files;

typedef struct fileaccess {//�ļ���дĿ¼			
	char filename[50];
	int access;
	int point;						//��дָ��
	struct fileaccess *next;
}FILEACCESS; FILEACCESS *filea;
char Users[50];	