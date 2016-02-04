#include <stdio.h>
#include <stdlib.h>
#include "include.h"

typedef struct{
	float coef; //系数
	int expn; //指数
}Term, ElemType; //两个名字，Term用于本ADT,ElemType用于LinkList的数据类型
#include "LinkList.h"
typedef LinkList Polynomial;

void CreatePoly(Polynomial& P, Term t[], int m){
//将按指数升序排列的项建成链表，保持升序
	P = (Polynomial)malloc(sizeof(LNode));
	P->next = P;
	Position p;
	for(int i=m-1; i>=0; i--){
	//头插法建表
		p = (LNode*)malloc(sizeof(LNode));
		p->data.coef = t[i].coef;
		p->data.expn = t[i].expn;
		p->next = P->next;
		P->next = p;
	}
}

Status AddPoly(Polynomial& p1, Polynomial& p2){
//将多项式p1,p2相加，结果存在p1中
	Position pc = p1; //pc初始化为p1的头结点
	Position pa = p1->next, pb=p2->next;
	while(pa!=p1 && pb!=p2){
		if(pa->data.expn < pb->data.expn){
			pc->next = pa; pc = pa;
			pa = pa->next;
		}else if(pa->data.expn > pb->data.expn){
			pc->next = pb; pc = pb;
			pb = pb->next;
		}else{
			pa->data.coef += pb->data.coef;
			Position q = pb; pb = pb->next;
			free(q);
			q = pa; pa = pa->next;
			if(q->data.coef){
				pc->next = q; pc = q;
			}else free(q);
		}
	}
	if(pa != p1){ //本就以p1为头结点
		pc->next = pa;
	}
	if(pb != p2){
		pc->next = pb;
		while(pb->next != p2) pb = pb->next;
		pb->next = p1;
	}
	free(p2);
	return OK;
}

void printElem(Term term){
//打印每一项
	printf("[%.2fx^%d]",term.coef, term.expn);
}

int main()
{
	Term t1[] = {6,-3,-1,0,4.4,2,-1.2,9};
	Term t2[] = {6,-3,-5.4,2,1,2,-7.8,15};
	Polynomial p1,p2;
	CreatePoly(p1, t1, 4);
	Traverse(p1,print);
	CreatePoly(p2, t2, 4);
	Traverse(p2,print);
	AddPoly(p1,p2);
	Traverse(p1,print);
	return 0;
}
