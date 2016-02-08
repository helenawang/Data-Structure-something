#include <stdio.h>
#include <stdlib.h>
#include "include.h"

typedef int QElemType;

 //链式，非循环，带头结点、头指针、末指针
typedef struct QNode{
	QElemType data;
	struct QNode* next;
}QNode, *QueuePtr;
typedef struct{
	QueuePtr front, rear;
}LinkQueue;


Status InitQueue(LinkQueue& Q){
//初始化为空队列
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode)); //头结点
	if(!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

Status DestroyQueue(LinkQueue& Q){
//销毁队列
	while(Q.front){
		Q.rear = Q.front->next; //rear配合front一起前向移动销毁
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

Status ClearQueue(LinkQueue& Q){
//清为空队列
	QNode* p = Q.front->next; //头结点不能删，需辅助指针
	while(p){
		Q.rear = p->next; //rear配合
		free(p);
		p = Q.rear;
	}
	Q.front->next = NULL;
	return OK;
}

Status QueueEmpty(LinkQueue Q){
	if(Q.front==Q.rear) return TRUE;
	else return FALSE;
}

int QueueLength(LinkQueue Q){
//不显示维护长度，需要时再计算
	QNode* p = Q.front->next; //和单链表实现一致
	int cnt=0;
	while(p){
		cnt++;
		p = p->next;
	}
	return cnt;
}

Status GetHead(LinkQueue Q, QElemType& e){
	if(Q.front==Q.rear) return UNDERFLOW;
	e = Q.front->next->data;
	return OK;
}

Status EnQueue(LinkQueue& Q, QElemType e){
	QNode* p = (QNode*)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);//存储空间不足
	p->data = e; p->next = NULL;
	Q.rear->next = p; Q.rear = p;
	return OK;
}

Status DeQueue(LinkQueue& Q, QElemType& e){
	if(Q.front==Q.rear) return UNDERFLOW;
	QNode* p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	free(p);
	if(p==Q.rear) Q.rear = Q.front; //仅有的一个元素被删除
	return OK;
}

int main()
{
	LinkQueue q;
	InitQueue(q);
	QElemType x;
	EnQueue(q,5);
	EnQueue(q,4);
	DeQueue(q,x);//x=5
	EnQueue(q,6);
	printf("[%d]\n",x);
	GetHead(q,x);//x=4
	printf("[%d]\n",x);
	return 0;
}
