#include "Calculator.h"
#include <ctype.h>

bool check_paren(char s[]){
	Stack_sq st;
	InitStack(st);
	int i=0;
	int e;
	while(s[i]!='#'){
		switch(s[i]){
			case '(' : Push(st, s[i]); i++; break;
			case ')' : if(!StackEmpty(st)){Pop(st); i++; break;} else return false;
			default : i++;
		}
	}
	if(!StackEmpty(st)) return false;
	return true;
}

char Precede(char a, char b){
	a = hash(a); b = hash(b);
	if(a==-1 || b==-1) return '!'; //出现非法算符
	return PrecTable[a][b];
}

int Operate(int a, int b, char op){
	switch(op){
		case '+' : return a+b;
		case '-' : return a-b;
		case '*' : return a*b;
		case '/' : if(b!=0) return a/b; else{printf("divider cannot be 0!"); return -1;}
		default : printf("invalid operator\n"); return -1;
	}
}

int readNum(char s[], int& i){ //返回读入的整数，i指针移动到下一个非数字字符
	Stack_sq num;
	InitStack(num);
	while(isdigit(s[i])){
		Push(num,s[i++]);
	}
	int base = 1;
	int res = 0;
	while(!StackEmpty(num)){
		int e;
		Top(num,e);
		Pop(num);
		e -= '0'; //将ASCII码变为真值
		res += e*base;
		base *= 10;
	}
	return res;
}

int calculate(char s[]){
	int i=0;
	Stack_sq opnd, optr;
	InitStack(opnd); InitStack(optr);
	Push(optr,'#');
	while(s[i]!='\0'){
		if(isdigit(s[i])){Push(opnd, readNum(s,i)); continue;}
		int e; //是操作符
		Top(optr,e);
		switch(Precede(e,s[i])){
			case '<' : Push(optr, s[i]); i++; break;
			case '>' : Pop(optr); int op1, op2;
					Top(opnd,op2); Pop(opnd); Top(opnd,op1); Pop(opnd);
					Push(opnd,Operate(op1,op2,e)); break;
			case '=' : Pop(optr); i++; break;
			default: printf("Error when calculate.\n"); return -1;
		}
	}
	int res;
	Top(opnd,res);
	return res;
}

int main()
{
	char s[MAX_LEN];
	printf("请输入运算表达式，以#结尾");
	scanf("%s",s);
	if(!check_paren(s)){printf("括号不匹配\n"); return 0;}
	printf("括号匹配成功\n");
	printf("表达式结果为 %d\n",calculate(s));
	return 0;
}
