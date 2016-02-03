#include <stdio.h>
#include <stdlib.h>
#include "include.h"
typedef int ElemType;
typedef struct LNode{
	int id;
	ElemType data; //密码
	struct LNode* next;
}LNode, *Joseph, *Position;

void CreateList(Joseph& J, int n, int a[]){
//“尾插法”建表，无头结点
	J = (Joseph)malloc(sizeof(LNode));
	Position p = J;
	for(int i=0; i<n-1; i++){
		p->data = a[i];
		p->id = i+1;
		p->next = (LNode*)malloc(sizeof(LNode));
		p = p->next;
	}
	p->data = a[n-1];
	p->id = n;
	p->next = J;
}

void play(Joseph& J,Position p, int m){
//初始上限为m,初始报数位置为p,输出出列顺序
	if(p->next == p){
		printf("%d\n",p->id);
		return ;
	}
	while(m-->2) p = p->next;
	Position q = p;
	p = p->next;
	q->next = p->next;
	printf("%d ",p->id);
	play(J, p->next, p->data);
	free(p);
	return ;
}

void Traverse(Joseph J, void (*visit)(LNode)){
	Position p = J;
	visit(*p);
	p = p->next;
	while(p!=J){
		visit(*p);
		p = p->next;
	}
}

void print(LNode ln){
	printf("[%d]",ln.data);
}
int main()
{
	Joseph j;
	int a[] = {3,1,7,2,4,8,4};
	CreateList(j,7,a);
	Traverse(j,print);
	play(j,j,20);
	return 0;
}
