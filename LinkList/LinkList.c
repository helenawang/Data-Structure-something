#include <stdio.h>
#include <stdlib.h>
#include "include.h"
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList, *Position;

Status GetElem(LinkList L, int i, ElemType& e){
//用e返回第i个元素
	Position p = L->next;
	int j = 1;
	while(p && j < i){p = p->next; j++;} //p指向i
	if(!p || j>i) return ERROR; //表长不够i
	e = p->data;
	return OK;
}

void CreateList(LinkList& L, int n){
//头插法建表，有结点
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	Position p;
	while(n--){
		p = (LinkList)malloc(sizeof(LNode));
		p->data = n;
		p->next = L->next;
		L->next = p;
	}
}

Status Insert(LinkList& L, int i, ElemType e){
//将e插到第i个元素之前
	Position p = L;
	int j = 0;
	while(p && j < i-1){p = p->next; j++;} //p指向i-1
	if(!p || j>i-1) return ERROR; //表长不够i
	Position s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;

	return OK;
}

Status Delete(LinkList& L, int i, ElemType& e){
//将第i个位置的元素删除，用e返回其值
	Position p = L->next;
	int j = 1;
	while(p && j < i-1){p = p->next; j++;} //p指向i-1
	if(!p || j>i-1) return ERROR; //表长不够i
	Position prev = p; p = p->next;
	if(!p) return ERROR; //要删除的结点为空
	prev->next = p->next;
	e = p->data;
	free(p);
	
	return OK;
}

Status Reverse(LinkList& L){
//就地置逆
	Position p = L->next;
	L->next = NULL;	
	while(p){
		Position q = p; p = p->next;
		q->next = L->next;
		L->next = q;
	}

	return OK;
}

void Traverse(LinkList& L,void (*visit)(LNode)){
//遍历
	Position p = L->next;
	while(p){
		visit(*p);
		p = p->next;
	}
}

void print(LNode ln){
	printf("[%d]",ln.data);
}

int main()
{
	LinkList l;
	CreateList(l, 10);
	Reverse(l);
	Traverse(l, print);
	ElemType e;
	if(Delete(l,2,e)){
		printf("%d\n",e);	
		GetElem(l,2,e);
		printf("%d\n",e);
	}
	return 0;
}
