#include <stdio.h>
#include "include.h"

//定长、顺序存储字符串
#define MAXLEN 100
typedef char SString[MAXLEN+1]; //SString[0]存储长度

Status StrAssign(SString S, char chars[]){
	int i=0;
	for(i=0; chars[i]!='\0'; i++){
		S[i+1] = chars[i];
	}
	S[0]=i; //记录长度
}

int Index(SString S, SString T, int pos){
//子串定位（模式匹配）蛮力版
//入口断言：1<=pos<=length
	int i=pos, j=1;
	while(i<=S[0] && j<=T[0]){
		if(S[i]==T[j]){i++; j++;}
		else{i=i-j+2; j=1;} //失配时，i回溯到开始的下一个位置，j回到1
	}
	if(j>T[0]) return i-T[0]; //j抵达模式串末尾,匹配成功
	else return 0; //匹配失败
}

int Index_KMP(SString S, SString T, int pos, int next[]){
//借助next[]
	int i=pos, j=1;
	while(i<=S[0] && j<=T[0]){
		if(j==0 || S[i]==T[j]){i++; j++;}
		else j=next[j];
	}
	if(j>T[0]) return i-T[0];
	else return 0;
}

void get_next(SString T, int next[]){
	int i=1, j=0;
	next[1]=0;
	while(i<T[0]){
		if(j==0 || T[i]==T[j]){next[++i] = ++j;}
		else j=next[j];
	}
}

void get_nextval(SString T, int nextval[]){
	int i=1, j=0;
	nextval[1]=0;
	while(i<T[0]){
		if(j==0 || T[i]==T[j]){
			nextval[++i] = ++j;
			if(T[i]==T[j]) nextval[i] = nextval[j];
		}
		else j=nextval[j];
	}
}

int main()
{
	SString s;
	StrAssign(s,"acabaabaabcacaabc");
	SString t;
	StrAssign(t,"abaabcac");
	int next[10];
	get_next(t,next);
	printf("%d %d\n",s[0],t[0]);
//	printf("%s\n%s\n",s,t);
	printf("%d\n",Index_KMP(s,t,1,next));
	return 0;
}
