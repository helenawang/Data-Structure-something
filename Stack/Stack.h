#include <stdlib.h>
#include "include.h"
typedef int ElemType;

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
typedef struct{
	ElemType * base; //base指向栈底，即最底的元素
	ElemType * top;	//top指向栈顶，即最高的元素的下一个空余位置
	int size; //栈的容量，注意不是栈的长度！不能作为栈空栈满的标志
}Stack_sq;

Status InitStack(Stack_sq& S){
//初始化一个空栈，大小为初始容量，栈顶栈底指针重合
	S.base = (ElemType*)malloc(sizeof(ElemType)*STACK_INIT_SIZE); //初始容量
	if(!S.base) exit(OVERFLOW); //空间不足
	S.top = S.base;
	S.size = STACK_INIT_SIZE;
	return OK;
}

Status ClearStack(Stack_sq& S){
//把S置为空栈，保持当前大小
	S.top = S.base;
	S.size = 0;
}

Status StackEmpty(Stack_sq S){
//栈空则返回1
	return S.top == S.base; //栈空的标志
}

Status Push(Stack_sq& S, ElemType e){
//元素e入栈
	if(S.top - S.base == S.size){
		S.base = (ElemType*)realloc(S.base, sizeof(S.size)+sizeof(ElemType)*STACK_INCREMENT); //采用追加固定数目的单元的扩容策略
		if(!S.base) exit(OVERFLOW);
		S.top = S.base + S.size;
		S.size += STACK_INCREMENT;
	}
	*S.top++ = e; //直接拷贝值
	return OK;
}

Status Pop(Stack_sq& S){
//栈顶元素出栈
	if(StackEmpty(S)) return ERROR;
	S.top--; //仅修改栈顶指针
	return OK;
}

Status Top(Stack_sq S, ElemType& e){
//用e返回栈顶元素值
	if(StackEmpty(S)) return ERROR;
	e = *(S.top-1);
	return OK;
}

