#include "SqList.h"
#include <cstdio>
#include <malloc.h>

Status ListTraverse(SqList &L, Status (*visit)(ElemType&))
{
	if(L.length<1) return ERROR;
	for(ElemType *p=L.base;p<=&(L.base[L.length-1]);p++)
		(*visit)(*p);
}

Status InitList_Sq(SqList &L)//initialize an empty linear list
{
	L.base=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.base) exit(OVERFLOW);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return OK;
}

//insert e before the ith element
Status ListInsert_Sq(SqList &L,int i,ElemType e)
{
	if(i<1||i>L.length+1) return ERROR;//can be one position after the last element
	if(L.length>=L.listsize)
	{
		ElemType* newbase=(ElemType*)realloc(L.base,(L.listsize+LIST_INCREMENT)*sizeof(ElemType));
		if(!newbase) return OVERFLOW;
		L.base=newbase;
		L.listsize+=LIST_INCREMENT;
	}
	ElemType* q=&(L.base[i-1]);
	for(ElemType* p=&(L.base[L.length-1]);p>=q;p--) *(p+1)=*p;//capasity has been extended
	*q=e;
	++L.length;
	return OK;
}

Status ListDelete_Sq(SqList &L,int i,ElemType &e)
{
	if(i<1||i>L.length) return ERROR;
	ElemType* q=&(L.base[i-1]);
	e=*q;
	for(ElemType* p=q;p<&(L.base[L.length-1]);p++) *p=*(p+1);//do not free the last element
	--L.length;
	return OK;
}

