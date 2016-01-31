#include <stdio.h>
#include <stdlib.h>
#include "include.h"
typedef int ElemType;
typedef struct LNode{ //带头结点的循环单链表
	ElemType data;
	struct LNode *next;
}LNode,*LinkList, *Position;

void CreateList(LinkList& L, int n){
//头插法建表，有头结点
	L = (LinkList)malloc(sizeof(LNode));
	L->next = L; //此为循环链表，若不循环则初始化L->next = NULL
	Position p;
	while(n--){
		p = (LNode*)malloc(sizeof(LNode));
		p->data = n;
		p->next = L->next;
		L->next = p;
	}
}

Status GetElem(LinkList L, int i, ElemType& e){
//用e返回第i个元素
//入口断言：L不空，i>=1
	Position p = L->next;
	int j = 1;
	while(p!=L && j < i){p = p->next; j++;} //p指向i
	if(p==L) return ERROR; //表长不够i
	e = p->data;
	return OK;
}

Status Insert(LinkList& L, int i, ElemType e){
//将e插到第i个元素之前
//入口断言：L不空，i>=1
	if(i==1){
		Position s = (LNode*)malloc(sizeof(LNode));
		s->data = e;
		s->next = L->next;
		L->next = s;
		return OK;
	}
	Position p = L->next;
	int j = 1;
	while(p!=L && j < i-1){p = p->next; j++;} //p指向i-1
	if(p==L) return ERROR; //表长不够i,导致抵达第i个位置前已被回到L
	Position s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;

	return OK;
}

Status Delete(LinkList& L, int i, ElemType& e){
//将第i个位置的元素删除，用e返回其值
//入口断言：L不空，i>=1
	if(i==1){
		Position q = L->next;
		e = q->data;
		L->next = q->next;
		free(q);
		return OK;
	}
	Position p = L->next;
	int j = 1;
	while(p!=L && j < i-1){p = p->next; j++;} //p指向i-1
	if(p==L) return ERROR; //表长不够i-1
	Position q = p->next;
	if(q==L) return ERROR; //要删除的结点为空
	e = q->data;
	p->next = q->next;
	free(q);
	
	return OK;
}

Status Reverse(LinkList& L){
//就地置逆
	Position p = L->next;
	L->next = L; //循环链表	
	while(p!=L){
		Position q = p; p = p->next;
		q->next = L->next;
		L->next = q;
	}

	return OK;
}

void Traverse(LinkList& L,void (*visit)(LNode)){
//遍历
	Position p = L->next;
	while(p!=L){
		visit(*p);
		p = p->next;
	}
}

void print(LNode ln){
	printf("[%d]",ln.data);
}

//集合交、并、差运算
Status Intersect(LinkList& La, LinkList& Lb){
	return OK;
}

int main()
{
	LinkList l;
	CreateList(l, 10);
	Reverse(l);
	printf("逆置后：\n");
	Traverse(l, print);
	ElemType e;
	if(Delete(l,1,e)){
		printf("\n删除第个1元素后：\n");
		Traverse(l,print);
	}
	if(Insert(l,1,55)){
		printf("\n在第1个位置插入55之后：\n");
		Traverse(l,print);
	}
	printf("%d\n",NULL);
	return 0;
}
