#include <stdio.h>
#include <stdlib.h>
#include "include.h"
typedef int ElemType;
typedef struct FreqNode{
	ElemType data;
	struct FreqNode *next, *prior;
	int freq;
}FreqNode, *FreqList, *Position;

void CreateList(FreqList& L, int n){
//头插法建表，频度都初始化为0
	L = (FreqList)malloc(sizeof(FreqNode));
	L->next = L->prior = L;
	L->freq = 0;
	Position p;
	while(n--){
		p = (FreqNode*)malloc(sizeof(FreqNode));
		p->data = n;
		p->next = L->next; p->prior = L;
		L->next->prior = p; L->next = p;
		p->freq = 0;
	}
}

Status LocatePos(FreqList L, int i, Position& p){
//入口断言：L存在（若L空，即只有一个头结点，也返回ERROR）
//用p返回指向第i个位置的指针并返回OK,若i不合法返回ERROR
	p = L->next;
	int j = 1;
	while(p!=L && j<i){p = p->next; j++;}
	if(p==L || j>i) return ERROR; //i<1或p在抵达第i个位置前已回到起点（即i>表长）为i不合法
	(p->freq)++;
	//调整p的位置,使链表按访问频度递减排列
	Position q = p->prior;
	while(q!=L && q->freq < p->freq) q = q->prior; //向前找到地一个大于p的位置q
	if(q->next != p){//确实需要前移
		p->prior->next = p->next;
		p->next->prior = p->prior; //摘除p
		p->next = q->next; p->prior = q;
		q->next->prior = p; q->next = p; //将p插到q和q->next之间
	}
	return OK;
}

Status GetElem(FreqList L, int i, ElemType& e){
//用e返回第i个位置结点的数据值并返回OK,若i不合法返回ERROR
	Position p;
	if(LocatePos(L, i, p)){
		e = p->data;
		return OK;
	}else return ERROR;
}

void Traverse(FreqList& L, void (*visit)(FreqNode)){
	Position p = L->next;
	while(p!=L){
		visit(*p);
		p = p->next;
	}
}

void print(FreqNode fn){
	printf("[%d]",fn.data);
}

int main()
{
	FreqList l;
	CreateList(l,10);
	Position p;
	if(LocatePos(l,5,p))
		Traverse(l,print);
	return 0;
}
