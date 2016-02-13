#include<stdio.h>
#include <stdlib.h>
#include "include.h"

//用带头结点的单链表实现串
typedef struct StrNode{
	char data;
	struct StrNode* next;
}StrNode, *StrPtr;

Status StrAssign(StrPtr& S, const char* chars){
//用S返回将字符串chars封装成的串对象
//入口断言：S不必已分配空间,S只是一个指针
	int i=0;
	S = (StrPtr)malloc(sizeof(StrNode));
	S->data = 0;
	StrNode *p, *q;
	p = S;
	int cnt=0;
	for(i=0; chars[i]!='\0'; i++){
		q = (StrNode*)malloc(sizeof(StrNode));
		q->data = chars[i];
		p->next = q;
		p = q;
		cnt++;
	}
	p->next = NULL;
	return OK;
}

Status StrEmpty(StrPtr S){
//入口断言：S已存在
	if(S->next) return FALSE;
	else return TRUE;
}

int StrLength(StrPtr S){
	int cnt=0;
	StrNode* p = S->next;
	while(p){
		cnt++;
		p = p->next;
	}
	return cnt;
}

int StrCompare(StrPtr S, StrPtr T){
//S>T返回值大于0，相等时返回0
	StrNode *p, *q;
	p = S->next; q = T->next;
	while(p && q){
		if(p->data != q->data) return p->data - q->data;
	}
	if(!p && !q) return 0;
	else if(p) return 1;
	else if(q) return -1;
}

Status Concat(StrPtr& T, StrPtr S1, StrPtr S2){
//用T返回S1,S2连接的结果，不破坏S1,S2原串
	T = (StrPtr)malloc(sizeof(StrNode));
	if(!S1->next && !S2->next){ //S1,S2均为空，结果亦为空
		T->next = NULL;
		return OK;
	}else{
		StrNode *p, *q;//分别指向T, S
		p = (StrNode*)malloc(sizeof(StrNode));
		T->next = p; //记下首元位置
		if(S1->next){//S1不空
			p->data = S1->next->data;
			q = S1->next->next;
			while(q){
				p->next = (StrNode*)malloc(sizeof(StrNode));
				p = p->next;
				p->data = q->data;
				q = q->next;
			}
			q = S2->next;
			while(q){
				p->next = (StrNode*)malloc(sizeof(StrNode));
				p = p->next;
				p->data = q->data;
				q = q->next;
			}
		}else{
			p->data = S2->next->data;
			q = S2->next->next;
			while(q){
				p->next = (StrNode*)malloc(sizeof(StrNode));
				p = p->next;
				p->data = q->data;
				q = q->next;
			}
		}
	}
	return OK;
}
Status StrPrint(StrPtr S){
//入口断言：S已存在
	StrNode* p = S->next;
	while(p){
		putchar(p->data);
		p = p->next;
	}
	putchar('\n');
	return OK;
}

int main()
{
	StrPtr s, t, v;
	StrAssign(s, "aaaabb");
	StrPrint(s);
	StrAssign(t, "ccdd");
	if(Concat(v,s,t)) StrPrint(v);
	return 0;
}
