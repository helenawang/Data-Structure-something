#include <stdio.h>
#include <stdlib.h>
#include "include.h"
typedef int ElemType;
typedef struct DulNode{
	ElemType data;
	struct DulNode *next, *prior;
}DulNode, *DulList, *Position;

void CreateList(DulList& L, int n){
//头插法建表
	L = (DulList)malloc(sizeof(DulNode));
	L->next = L->prior = L;
	Position p;
	while(n--){
		p = (DulNode*)malloc(sizeof(DulNode));
		p->data = n;
		p->next = L->next; p->prior = L;
		L->next->prior = p; L->next = p;
	}
}

Status GetElem(DulList L, int i, ElemType& e){
//用e返回第i个元素
	Position p = L->next;
	int j = 1;
	while(p!=L && j<i){p = p->next; j++;} //p指向i
	if(p==L || j>i) return ERROR;
	e = p->data;
	return OK;
}

Status Insert(DulList& L, int i, ElemType e){
//将e插到第i个位置之前
//入口断言：L不空，i>=1
	if(i==1){
		Position s = (DulNode*)malloc(sizeof(DulNode));
		s->data = e;
		s->next = L->next; s->prior = L;
		L->next->prior = s; L->next = s;
		return OK;
	}
	Position p = L->next;
	int j = 1;
	while(p!=L && j<i-1){p = p->next; j++;} //p指向i-1
	if(p==L) return ERROR;
	Position s = (DulNode*)malloc(sizeof(DulNode));
	s->data = e;
	s->next = p->next; s->prior = p;
	p->next->prior = s; p->next = s;
	return OK;
}

Status Delete(DulList& L, int i, ElemType& e){
//将第i个位置的元素删除，用e返回其值
//入口断言：L不空，i>=1
	if(i==1){
		Position q = L->next;
		e = q->data;
		L->next = q->next; q->next->prior = L;
		free(q);
		return OK;
	}
	Position p = L->next;
	int j = 1;
	while(p!=L && j<i-1){p = p->next; j++;} //p定位到i-1
	if(p==L) return ERROR; //表长不够i-1
	Position q = p->next;
	if(q==L) return ERROR; //表长不够i
	e = q->data;
	p->next = q->next; q->next->prior = p;
	free(q);
	return OK;
}

Status Reverse(DulList& L){
//就地置逆
	Position p = L->next;
	L->next = L; L->prior = L;
	while(p!=L){
		Position q = p; p = p->next;
		q->next = L->next; q->prior = L;
		L->next->prior = q; L->next = q;
	}
	return OK;
}

void Traverse(DulList& L, void(*visit)(DulNode)){
	Position p = L->next;
	while(p!=L){
		visit(*p);
		p = p->next;
	}
}

void print(DulNode dn){
	printf("[%d]",dn.data);
}

int main()
{
	DulList l;
	CreateList(l,10);
	if(Reverse(l))
		printf("置逆后：\n");
	Traverse(l,print);
	ElemType e;
	if(Insert(l,4,60)){
		printf("\n在第4个位置插入了60：\n");
		Traverse(l,print);
	}
	if(Delete(l,1,e)){
		printf("\n删除了第1个位置的%d\n",e);
		Traverse(l,print);
	}
	return 0;
}
