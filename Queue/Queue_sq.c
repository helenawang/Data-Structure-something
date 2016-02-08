#include <stdio.h>
#include <stdlib.h>
#include "include.h"

#define QSIZE 100
typedef int QElemType;
//顺序存储的循环队列，采取浪费一个存储单元的方法区分空和满
typedef struct{
	QElemType* base; //存储空间基址
	int front, rear; //首元指针，尾指针（下一空余单元）
}SqQueue;

Status InitQueue(SqQueue& Q){
//初始化容量为SIZE的空队列
	Q.base = (QElemType*)malloc(sizeof(QElemType)*QSIZE);
	if(!Q.base) exit(OVERFLOW);//存储空间不足
	Q.front = Q.rear = 0;
	return OK;
}

Status DestroyQueue(SqQueue& Q){
//销毁队列，释放空间
	free(Q.base);
	Q.front = Q.rear = 0;
	return OK;
}

Status ClearQueue(SqQueue& Q){
//清空队列
	Q.front = Q.rear = 0;
	return OK;
}

Status QueueEmpty(SqQueue Q){
	if(Q.front == Q.rear) return TRUE;
	else return FALSE;
}

int QueueLength(SqQueue Q){
	return (Q.rear - Q.front + QSIZE)%QSIZE;	
}

Status GetHead(SqQueue Q, QElemType& e){
	if(Q.front == Q.rear) return UNDERFLOW;
	e = Q.base[Q.front];
	return OK;
}

Status EnQueue(SqQueue& Q, QElemType e){
	if((Q.rear+1)%QSIZE == Q.front) return OVERFLOW; //队列满
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear+1)%QSIZE;
	return OK;
}

Status DeQueue(SqQueue& Q, QElemType& e){
	if(Q.front == Q.rear) return UNDERFLOW; //队列空
	e = Q.base[Q.front];
	Q.front = (Q.front+1)%QSIZE;
	return OK;
}

int main()
{
	SqQueue q;
	InitQueue(q);
	EnQueue(q,5);
	EnQueue(q,6);
	QElemType x;
	DeQueue(q,x);
	printf("%d\n",x);
	EnQueue(q,1);
	GetHead(q,x);
	printf("%d\n",x);
	return 0;
}
