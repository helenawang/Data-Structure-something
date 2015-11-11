#include "SqList.h"
#include <cstdio>
#include <malloc.h>
using namespace std;

Status print(ElemType &e)
{
	printf("%d ", e);
	return OK;
}

int main()
{
	SqList test;
	InitList_Sq(test);
	ListInsert_Sq(test,1,5);
	ListInsert_Sq(test,1,6);
	ListInsert_Sq(test,1,7);
	ListInsert_Sq(test,2,8);
	ElemType e;
	ListTraverse(test,&print);
	ListDelete_Sq(test,3,e);
	return 0;
}
