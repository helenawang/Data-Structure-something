#include <stdio.h>
#include "Stack.h"

void Convert(int d, int n){
	Stack_sq s;
	InitStack(s);
	while(d>0){
		Push(s,d%n);
		d /= n;
	}
	int e;
	while(!StackEmpty(s)){
		Top(s,e);
		Pop(s);
		printf("%d",e);
	}
	printf("\n");
}

int main()
{
	printf("请输入要转换的数字（十进制）要转换成的进制：");
	int d, n;
	scanf("%d%d",&d,&n);
	printf("%d的%d进制表示为：",d,n);
	Convert(d,n);
}
