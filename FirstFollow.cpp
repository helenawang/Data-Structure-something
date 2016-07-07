#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <assert.h>
#define FREAD(fn) freopen((fn), "r", stdin)
#define RINT(vn) scanf("%d", &(vn))
#define PINT(vb) printf("%d", vb)
#define RSTR(vn) scanf("%s", (vn))
#define PSTR(vn) printf("%s", (vn))
#define CLEAR(A, X) memset(A, X, sizeof(A))
#define REP(N) for(int i=0; i<(N); i++)
#define REPE(N) for(int i=1; i<=(N); i++)
#define pb(X) push_back(X)
#define pn() printf("\n")
using namespace std;

const int MAX_N = 20;//产生式体的最大长度
const char nullStr = '$';//空串的字面值
typedef int Type;//符号类型

const Type NON = -1;//非法类型
const Type T = 0;//终结符
const Type N = 1;//非终结符
const Type NUL = 2;//空串

struct Production//产生式
{
	char head;
	char* body;
	Production(){}
	Production(char h, char b[]){
		head = h;
		body = (char*)malloc(strlen(b)*sizeof(char));
		strcpy(body, b);
	}
	bool operator<(const Production& p)const{//不加外面的const会报很多错
		if(head == p.head) return body[0] < p.body[0];//注意此处只适用于LL(1)文法，即同一VN各候选的首符不能有相同的，否则这里的小于符号还要向前多看几个字符，就不是LL(1)文法了
		return head < p.head;
	}
	void print() const{//此处不加const会报错
		printf("%c -- > %s\n", head, body);
	}
};

//以下几个集合可以再封装为一个大结构体--文法
set<Production> P;//产生式集
set<char> VN, VT;//非终结符号集，终结符号集
char S;//开始符号
map<char, set<char> > FIRST;//FIRST集
map<char, set<char> > FOLLOW;//FOLLOW集

set<char>::iterator first;//全局共享的迭代器
set<char>::iterator follow;
set<char>::iterator vn;
set<char>::iterator vt;
set<Production>::iterator p;

Type get_type(char alpha){//判读符号类型
	if(alpha == '$') return NUL;//空串
	else if(VT.find(alpha) != VT.end()) return T;//终结符
	else if(VN.find(alpha) != VN.end()) return N;//非终结符
	else return NON;//非法字符
}

void put_first_first(char A, char B){//把FIRST[B]-{$}加到FIRST[A]
	first = FIRST[B].begin();
	for(; first != FIRST[B].end(); first++){
		if(*first != nullStr)
			FIRST[A].insert(*first);
	}
}

void put_body(char A, char* pb){//用产生式体从pb开始往后的部分扩充A的FIRST集
	if(*pb == '\0'){//抵达产生式体的末尾
		FIRST[A].insert(nullStr);//向FIRST(A)加入空串
		return ;
	}
	switch(get_type(*pb)){
		case 1://pb[0]为非终结符，把pb[0]的FIRST集加到A的FIRST集
			put_first_first(A, *pb);
			if(FIRST[*pb].find(nullStr) != FIRST[*pb].end())
				put_body(A, pb+1);
			break;
		case 0://pb[0]位终结符，把pb[0]加到A的FIRST集
			FIRST[A].insert(*pb);
			break;
		case 2: //pb[0]为空，把空串加入A的FIRST集
			FIRST[A].insert(nullStr);
			break;
		default: return ;
	}
}

void put_follow_first(char B, char beta){//把FIRST[beta]加到FOLLOW[B]
	first = FIRST[beta].begin();
	for(; first != FIRST[beta].end(); first++){
		if(*first != nullStr)
			FOLLOW[B].insert(*first);
	}
}

void put_follow_follow(char B, char A){//把FOLLOW[A]加到FOLLOW[B]
	follow = FOLLOW[A].begin();
	for(; follow != FOLLOW[A].end(); follow++){
		FOLLOW[B].insert(*follow);
	}
}

void get_first(){//生成FIRST集
	for(vt = VT.begin(); vt != VT.end(); vt++)
		FIRST[*vt].insert(*vt);//终结符的FIRST集包含它自身
	FIRST[nullStr].insert(nullStr);//空串的FIRST集包含它自身
	bool flag = true;
	while(flag){//上一轮迭代中集合有扩大
		flag = false;
		for(vn = VN.begin(); vn != VN.end(); vn++){//对于每个非终结符
			for(p = P.begin(); p != P.end(); p++){
				//(*p).print();
				if(p->head == *vn){//找所有左部为A的产生式
					int before = FIRST[*vn].size();
					put_body(*vn, &(p->body)[0]);
					if(FIRST[*vn].size() > before)//集合有扩大
						flag = true;
					//printf("%c size %d -> %d\n", *vn, before, FIRST[*vn].size());
				}
			}
		}	
	}
}

void get_follow(){//生成FOLLOW集
	FOLLOW[S].insert('#');//结束符放入文法开始符号的FOLLOW集
	bool flag = true;
	while(flag){
		flag = false;
		for(vn = VN.begin(); vn != VN.end(); vn++){//对于每个非终结符
			for(p = P.begin(); p != P.end(); p++){
				//(*p).print();
				char A = p->head;
				int i;
				for(i=0; (p->body)[i+1] != '\0'; i++){
					char B = (p->body)[i];
					char beta = (p->body)[i+1];
					int before = FOLLOW[B].size();
					if(get_type(B) == N){//跟在B后面的可以扩充B的FOLLOW集
						put_follow_first(B, beta);
						if(get_type(beta) == NUL)//beta为空串
							put_follow_follow(B, A);
						else if(FIRST[beta].find(nullStr) != FIRST[beta].end())
							put_follow_follow(B, A);
						if(FOLLOW[B].size() > before) flag = true;
						//printf("%c size %d -> %d\n", B, before, FOLLOW[B].size());
					}
				}
				put_follow_follow((p->body)[i], A);
			}
		}	
	}
}

int main()
{
	FREAD("grammar2.txt");//从文件读取文法
	int numN = 0;
	int numT = 0;
	char c = ' ';
	S = getchar();//开始符号
	printf("%c", S);
	VN.insert(S);
	numN++;
	while((c=getchar()) != '\n'){//读入非终结符
		printf("%c", c);
		VN.insert(c);
		numN++;
	}
	pn();
	while((c=getchar()) != '\n'){//读入终结符
		printf("%c", c);
		VT.insert(c);
		numT++;
	}
	pn();
	REP(numN){//读入产生式
		c = getchar();
		int n; RINT(n);
		while(n--){
			char body[MAX_N];
			scanf("%s", body);
			printf("%c --> %s\n", c, body);
			P.insert(Production(c, body));
		}
		getchar();
	}

	get_first();//生成FIRST集
	for(vn = VN.begin(); vn != VN.end(); vn++){//打印非终结符的FIRST集
		printf("FIRST(%c) = { ", *vn);
		for(first = FIRST[*vn].begin(); first != FIRST[*vn].end(); first++){
			printf("%c, ", *first);
		}
		printf("}\n");
	}

	get_follow();//生成非终结符的FOLLOW集
	for(vn = VN.begin(); vn != VN.end(); vn++){//打印非终结符的FOLLOW集
		printf("FOLLOW(%c) = { ", *vn);
		for(follow = FOLLOW[*vn].begin(); follow != FOLLOW[*vn].end(); follow++){
			printf("%c, ", *follow);
		}
		printf("}\n");
	}
	return 0;
}
