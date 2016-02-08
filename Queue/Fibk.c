#include <stdio.h>
#include <stdlib.h>
#include "include.h"

typedef struct{
	int* base;
	int front, rear;
	int size; //容量，即k+1
}Queue;

Status Init(Queue& Q, int k){
//创建一个容量为k的空队列
	Q.base = (int*)malloc(sizeof(int)*(k+1));
	if(!Q.base) exit(OVERFLOW);
	Q.front = Q.rear = 0;
	Q.size = k+1;
	return OK;
}

Status EnQueue(Queue& Q, int e){
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear+1)%Q.size;
}

void fib(int k, int n){
	Queue q;
	if(Init(q, k)){
		for(int i=0; i<k-1; i++){
			printf("f[%d] = 0\n",i);
			EnQueue(q, 0);//f[0]~f[k-2]=0入队
		}
		printf("f[%d] = 1\n",k-1);
		EnQueue(q, 1); //f[k-1]=1
		printf("f[%d] = 1\n", k);
		EnQueue(q, 1); //f[k]=1
		//长为k+1的队列恰好满,rear=0
		k++; //从f[k+1]开始用公式f[i+1] = f[i]*2 - f[i-k]
		q.rear = q.size-1; //rear指向f[k]
		while(k<=n){
			q.base[q.front] = q.base[q.rear]*2 - q.base[q.front];
			printf("f[%d] = %d\n", k++, q.base[q.front]);
			q.front = (q.front+1)%q.size;//front指向f[i-k]即f[i]的位置
			q.rear = (q.rear+1)%q.size; //rear指向f[i-1]
		}
	}
}

int main()
{
	printf("打印k阶fibonacci序列的前n项\n");
	printf("请输入k n值: ");
	int k, n;
	scanf("%d%d",&k,&n);
	fib(k, n);
	
	return 0;
}
