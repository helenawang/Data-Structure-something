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
	while(n-- >0){
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
	printf("遍历结果：");
	Position p = L->next;
	while(p!=L){
		visit(*p);
		p = p->next;
	}
	printf("\n");
}

void print(LNode ln){
	printf("[%d]",ln.data);
}

Status Merge(LinkList& La, LinkList& Lb, LinkList& Lc){
//归并有序链表La,Lb(所有重复元素均保留)，
//结果以Lc指代（利用原表La,Lb的结点空间构造Lc）
	Position pc = Lc ->next = Lc;
	Position pa = La->next, pb = Lb->next;
	while(pa!=La && pb!=Lb){
		if(pa->data <= pb->data){
			pc->next = pa; pc = pa;
			pa = pa->next;
		}else{
			pc->next = pb; pc = pb;
			pb = pb->next;
		}
	}
	if(pa != La){
		pc->next = pa;
		while(pa->next != La) pa = pa->next;
		pa->next = Lc;
	}
	if(pb != Lb){
		pc->next = pb;
		while(pb!=Lb) pb = pb->next;
		pb->next = Lc;
	}
	free(La); free(Lb);
	return OK;
}

//集合交、并、差运算
Status Intersect(LinkList& La, LinkList& Lb, LinkList& Lc){
//用Lc指代有序链表La,Lb的交集（重复元素都去掉）
//利用原结点的空间构造Lc，释放无用结点
//入口断言：La,Lb各自内部元素互异、有序
	Position pc = Lc->next = Lc;
	Position pa = La->next, pb = Lb->next;
	while(pa!=La && pb!=Lb){
		if(pa->data < pb->data)
		{Position q = pa; pa = pa->next; free(q);}
		else if(pa->data > pb->data)
		{Position q = pb; pb = pb->next; free(q);}
		else{
			pc->next = pa; pc = pa; pa = pa->next;
			Position q = pb; pb = pb->next; free(q);
		}
	}
	pc->next = Lc;
	while(pa != La){Position q = pa; pa = pa->next; free(q);}
	while(pb != Lb){Position q = pb; pb = pb->next; free(q);}
	free(La); free(Lb);
	return OK;

}

Status Unite(LinkList& La, LinkList& Lb, LinkList& Lc){
//用Lc指代有序链表La,Lb的并集（重复元素都去掉）
//利用原结点空间构造Lc,释放无用结点
//入口断言：La,Lb各自内部元素互异、有序
	Position pc = Lc->next = Lc;
	Position pa = La->next, pb = Lb->next;
	while(pa!=La && pb!=Lb){
		if(pa->data < pb->data)
		{pc->next = pa; pc = pa; pa = pa->next;}
		else if(pa->data > pb->data)
		{pc->next = pb; pc = pb; pb = pb->next;}
		else{
			printf("%d与%d相等\n",pa->data,pb->data);
			pc->next = pa; pc = pa; pa = pa->next;
			Position q = pb; pb = pb->next; free(q);
		}
	}
	while(pa != La){pc->next = pa; pc = pa; pa = pa->next;}
	while(pb != Lb){pc->next = pb; pc = pb; pb = pb->next;}
	pc->next = Lc;
	free(La); free(Lb);
	return OK;
}

Status Differ(LinkList& La, LinkList& Lb, LinkList& Lc){
//用Lc指代有序链表La-Lb
//利用原结点空间构造Lc,释放无用结点
//入口断言：La,Lb各自内部元素互异、有序
	Position pc = Lc->next = Lc;
	Position pa = La->next, pb = Lb->next;
	while(pa!=La && pb!=Lb){
		if(pa->data < pb->data)
		{pc->next = pa; pc = pa; pa = pa->next;}
		else if(pa->data > pb->data)
		{Position q = pb; pb = pb->next; free(q);}
		else{
			printf("%d与%d相等\n",pa->data,pb->data);
			Position q = pa; pa = pa->next; free(q);
			q = pb; pb = pb->next; free(q);
		}
	}
	while(pa != La){pc->next = pa; pc = pa; pa = pa->next;}
	pc->next = Lc;
	while(pb != Lb){Position q = pb; pb = pb->next; free(q);}
	free(La); free(Lb);
	return OK;
}


int main()
{
	LinkList l;
	CreateList(l, 10);
	Traverse(l, print);
	ElemType e;
	if(Delete(l,1,e)){
		printf("删除第个1元素后：\n");
		Traverse(l,print);
	}
	if(Insert(l,1,-55)){
		printf("在第1个位置插入-55之后：\n");
		Traverse(l,print);
	}
	printf("\n");	
	LinkList l2,l3;
	CreateList(l2,5);
	Traverse(l2,print);
	CreateList(l3,0);
/*	if(Merge(l,l2,l3)){
		printf("归并l,l2为：\n");
		Traverse(l3,print);
	}
	if(Intersect(l,l2,l3)){
		printf("l,l2取交集为：\n");
		Traverse(l3,print);
	}
	if(Unite(l,l2,l3)){
		printf("l,l2取并集为：\n");
		Traverse(l3,print);
	}
*/	
	if(Differ(l,l2,l3)){
		printf("l,l2取差集(l-l2)为：\n");
		Traverse(l3,print);
	}
	return 0;
}
