#include <stdio.h>
#include "include.h"

//定长(宏MAXLEN)、顺序存储字符串
#define MAXLEN 100
typedef char SString[MAXLEN+1]; //SString[0]存储长度,注意下标从1开始，结尾无\0

Status StrAssign(SString& S, const char* chars){
//用S返回将字符串chars封装成的串对象
	int i=0;
	for(i=0; chars[i]!='\0'; i++){
		S[i+1] = chars[i];
	}
	S[0]=i; //记录长度
}

Status StrCopy(SString& S, SString T){
//用S返回T的拷贝
	int i=0;
	for(i=0; i<=T[0]; i++)
		S[i] = T[i];
	return OK;
}

Status ClearString(SString& S){
//入口断言：S存在
//操作结果：将S清为空串
	S[0] = 0;
	return OK;
}

Status StrEmpty(SString S){
//入口断言：S存在
	if(S[0]==0) return TRUE;
	else return FALSE;
}

int StrLength(SString S){
//入口断言：S存在
	return S[0];
}

int StrCompare(SString S, SString T){
//入口断言：S,T存在
//操作结果：按字典序比较，S>T返回值>0,S=T返回0，S<T返回值<0
	int i, j;
	for(i=1, j=1; i<=S[0] && j<=T[0]; i++, j++){
		if(S[i] != T[j]) return S[i]-T[i];
	}
	return S[0]-T[0]; //存在子串关系
}

Status Concat(SString& S1, SString S2){
//入口断言：S1, S2存在
//操作结果：用S1返回S1连接S2而成的新串，若S1的空间不足，截断并返回FALSE
	if(S1[0]+S2[0] <= MAXLEN){ //S1足够容纳完整的S1+S2
		int i;
		for(i=S1[0]+1; i<=S1[0]+S2[0]; i++) S1[i] = S2[i-S1[0]];
		S1[0] += S2[0];
		return TRUE;
	}else{
		int i;
		for(i=S1[0]+1; i<=MAXLEN; i++) S1[i] = S2[i-S1[0]];
		S1[0] = MAXLEN;
		return FALSE; //截断了S2
	}
}

Status SubString(SString& Sub, SString S, int pos, int len){
//入口断言：S存在
//操作结果：用Sub返回S从第pos个字符开始长度为len的字串；若pos或len值非法，返回ERROR
	if(pos<1 || pos>S[0] || len<0 || len>S[0]-pos+1) return ERROR;
	int i, j;
	for(i=1, j=pos; i<=len; i++, j++)
		Sub[i] = S[j];
	Sub[0] = len;
	return OK;
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

void StrPrint(SString S){
	for(int i=1; i<=S[0]; i++)
		putchar(S[i]);
	putchar('\n');
}

Status Replace(SString& S, SString T, SString V){
//入口断言：S,T,V存在
//操作结果：将S中出现的所有不重复的T都替换为V
	int k = Index(S, T, 1);
	if(k){
		SString suffix;	StrAssign(suffix,"");
		int n = T[0], m = S[0];
		while(k){
			printf("%d\n",k);
			SString temp;	
			SubString(temp, S, 1, k-1); //当前第一个T的前缀
			StrPrint(temp);
			if(Concat(suffix, temp)){
				StrPrint(suffix);
				Concat(suffix, V); //追加上V
				StrPrint(suffix);
				m -= (k-1)+n; //处理掉上一组后剩余的后缀长度
				SubString(temp, S, k+n, m);
				StrCopy(S, temp); //S被截断为尚未处理的后缀
				k = Index(S, T, 1);
			}else return OVERFLOW; //S空间不足
		}
		if(Concat(suffix, S)){
			StrCopy(S, suffix);
			return OK;
		}else return OVERFLOW;
	}
	else return OK; //T未出现过
}

Status Reverse(SString& S){
//入口断言：S存在
//操作结果：对S置逆
	int len = S[0];
	if(len>1){
		SString t1; SubString(t1, S, 1, len/2 );
		SString t2; SubString(t2, S, len/2+1, len-len/2);
		Reverse(t1); Reverse(t2);
		Concat(t2, t1);
		StrCopy(S, t2);
	}
	return OK;
}

Status Count(SString S, SString& C, int cnt[]){
//入口断言：S存在
//操作结果：C顺序存放S中出现过的互异的字符，cnt顺序存放C中字符出现的次数,下标与C中的下标一致
	for(int i=0; i<sizeof(cnt); i++) cnt[i] = 0;
	int k=0;//cnt的末尾指针，即当前记录的字符个数
	for(int i=1; i<=S[0]; i++){
		int flag=0; //假设之前没记过
		for(int j=1; j<=k; j++){
			if(S[i]==C[j]){//复现的字符
				cnt[j]++;
				flag=1;
				break;
			}
		}
		if(!flag){ //新字符
			C[++k] = S[i];
			cnt[k] = 1;
		}
	}
	C[0] = k;
	return OK;
}

int main()
{
	SString s;
	StrAssign(s,"acabaabaabcacaabc");
	SString t;
	StrAssign(t,"abaabcac");
	StrPrint(s);
	StrPrint(t);

	int next[10];
	get_next(t,next);
	
	SString v;
	StrAssign(v,"xy");
	if(Replace(s,t,v)) StrPrint(s);
	if(Reverse(v)) StrPrint(v);
	
	int cnt[10];
	if(Count(s,v,cnt)){
		StrPrint(v);
		for(int i=0; i<v[0]; i++)
			printf("%d ",cnt[i]);
	}

	return 0;
}
