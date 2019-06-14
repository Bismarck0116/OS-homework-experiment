#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#define DISK_C 2
#define DISK_H 80
#define DISK_B 18
#define DISK_SIZE 512//ÉÈÇø´óÐ¡

class Block {
private:
	int C;
	int H;
	int B;
	int offset;
	char *data;
	char *readBlock();
public:
	Block(int C, int H, int B);
	Block(BlockInfo blockInfo);
	char *getData();
	int writeData(char *data, int offset, int lenth);
	Block nextBlock();
};