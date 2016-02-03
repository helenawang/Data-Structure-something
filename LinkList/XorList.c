#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "include.h"
typedef int ElemType;
typedef struct XorNode{
	ElemType data;
	struct XorNode* LRPtr;
}XorNode, *XorPointer;

typedef struct{//无头结点的异或指针双向链表
	XorPointer Left, Right;
}XorList;

XorPointer XorP(XorPointer p, XorPointer q){
//指针异或函数
	size_t x = (size_t)p;
	size_t y = (size_t)q;
	return (XorPointer)(x^y);
}

Status CreateList(XorList& L, int n){
//头插法建表，无头结点
	n--;
	XorPointer p;
	p = (XorPointer)malloc(sizeof(XorNode));
	L.Left = L.Right = p;
	p->data = n;
	p->LRPtr = XorP(p, p);
	while(n--){
		p = (XorPointer)malloc(sizeof(XorNode));
		p->data = n;
		p->LRPtr = XorP(L.Right, L.Left);
		L.Left->LRPtr = XorP(p, XorP(L.Right, L.Left->LRPtr));
		L.Right->LRPtr = XorP(XorP(L.Right->LRPtr,L.Left),p);
		L.Left = p;
	}
}

Status Insert(XorList& L, int i, ElemType e){
//在第i个位置前插入结点e（i的合法值为1～表长+1）
//由于无头结点，故判断表长是否够i，要通过计步变量k
	XorPointer p = L.Left, q = L.Right;
	int k = 1;
	while(p!=L.Right && k<i){ //p指向i, q指向i-1;保证至多扫描一遍后退出
		XorPointer t = p;
		p = XorP(q, p->LRPtr);
		q = t;
		k++;
	}
	if(k+1<i) return ERROR; //表长不够i-1
	if(k+1==i){p = L.Left; q = L.Right;} //插到表长+1的位置，即最后一个元素之后
	XorPointer s = (XorPointer)malloc(sizeof(XorNode));
	s->data = e;
	s->LRPtr = XorP(q, p);
	q->LRPtr = XorP(XorP(q->LRPtr, p), s);
	p->LRPtr = XorP(s, XorP(q, p->LRPtr));
	if(i==1) L.Left = s;
	if(i==k+1) L.Right = s;
	return OK;
}

Status Delete(XorList& L, int i, ElemType& e){
//删除第i个位置的元素，用e返回其值（i的合法值为1~表长）
	XorPointer p = L.Left, q = L.Right;
	int k = 1;
	while(p!=L.Right && k<i){ //p指向i, q指向i-1
		XorPointer t = p;
		p = XorP(q, p->LRPtr);
		q = t;
		k++;
	}
	if(k<i) return ERROR; //表长不够i
	if(p==L.Right) L.Right = q; //删除最后一个结点
	e = p->data;
	XorPointer m = XorP(q, p->LRPtr); //m暂存p的后继
	q->LRPtr = XorP(XorP(q->LRPtr, p), m);
	m->LRPtr = XorP(q, XorP(p, m->LRPtr));
	free(p);
	if(i==1) L.Left = m; //删除第一个结点
	return OK;
}

Status Traverse(XorList& L, void (*visit)(XorNode)){
	XorPointer p = L.Left, q = L.Right;
	while(p != L.Right){
		visit(*p);
		XorPointer t = p;
		p = XorP(q,p->LRPtr);
		q = t;
	}
	visit(*p);
	return OK;
}

void print(XorNode xn){
	printf("[%d]",xn.data);
}

int main()
{
	XorList l;
	CreateList(l,10);
	ElemType e;
	if(Delete(l,5,e))
		Traverse(l,print);
	return 0;
}
