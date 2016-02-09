#include <stdio.h>
#include <stdlib.h>
#include "include.h"

//定长字符串，malloc分配
typedef struct{
	char* ch; //基址(第一个字符存放在ch[0])
	int length; //长度
}HString;

Status StrAssign(HString& S, char* chars){
//将以\0结尾的字符串chars创建为S
	if(S.ch) free(S.ch);
	int len=0;
	char c=chars;
	while(*c != '\0'){c++; len++;} //取得chars长度
	if(!len) {S.ch = NULL; S.length=0;}
	else{
		S.ch = (char*)malloc(sizeof(char)*len);
		if(!S.ch) exit(OVERFLOW);
		for(int i=0; i<len; i++) S.ch[i]=chars[i];
		S.length = len;
	}
	return OK;
}

int StrLength(HString S){
	return S.length;
}

int StrCompare(HString S1, HString S2){
//字典序靠后为大,S1>S2返回大于0的值
	int i=0;
	for(i=0; i<S1.length && i<S2.length; i++){
		if(S1.ch[i]!=S2.ch[i]) //中途失配
			return S1.ch[i]-S2.ch[i];
	}
	return S1.length - S2.length; //存在子串关系
}

Status ClearString(HString& S){
	if(S.ch) free(S.ch);
	S.ch = NULL;
	S.length = 0;
	return OK;
}

Status Concat(HString& T, HString S1, HString S2){
//用T返回S1,S2连接而成的串
	if(T.ch) free(T.ch);
	T.ch = (char*)malloc(sizeof(char)*(S1.length+S2.length));
	if(!T.ch) exit(OVERFLOW);
	int i=0;
	for(i=0; i<S1.length; i++) T.ch[i] = S1.ch[i];
	for(; i<S1.length+S2.length; i++) T.ch[i] = S2.ch[i-S1.length];
	T.length = S1.length + S2.length;
	return OK;
}

Status SubString(HString& Sub, HString S, int pos, int len){
//用Sub返回S从第pos个字符开始长度为len的字串
	if(pos<0 || pos>S.length || len<0 || len>S.length-pos+1)
		return ERROR; //位置或长度非法
	if(Sub.ch) free(Sub.ch);
	if(!len) {Sub.ch = NULL; Sub.length=0;}
	else{
		Sub.ch=(char*)malloc(sizeof(char)*len);
		if(!Sub.ch) exit(OVERFLOW);
		for(int i=0; i<len; i++)
			Sub.ch[i] = S.ch[i-1+pos];//第pos个字符存放在数组的第pos-1单元
		Sub.length = len;
	}
	return OK;
}

