#include <stdio.h>
#include "Stack.h"

void check_paren(){
	Stack_sq s;
	InitStack(s);
	int c;
	int e;
	while((c=getchar())!='\n'){
		switch(c){
		case '(':
		case '[':
		case '{': Push(s,c); break;
		case ')': 
		case ']':
		case '}': Top(s,e); if(c-e <=2) Pop(s);
					else{printf("unmatched\n"); return ;}
				break;
		default: break;
		}
	}
	printf("matched\n");
	return ;
}

int main()
{
	printf("请输入待检验的表达式串，以回车结尾：");
	check_paren();
}
