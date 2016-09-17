//from textbook
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define RINT(V) scanf("%d", &(V))
#define FREAD() freopen("in.txt", "r", stdin)
#define REP(N) for(int i=0; i<(N); i++)
#define REPE(N) for(int i=1; i<=(N); i++)
#define PINT(N) printf("%d", (N))
#define PSTR(S) printf("%s", S)
#define RSTR(S) scanf("%s", S)
#define pn() printf("\n")
#define pb(V) push_back(V)
using namespace std;
typedef long long ll;
const int MAX_N = 15;
const int MOD = 100000000;

int* buildNext(char* P){
	size_t m = strlen(P), j=0;//主串指针
	int* N = new int[m];//next表
	int t = N[0] = -1;//模式串指针
	while(j < m-1){
		if(t < 0 || P[j] == P[t]){
			j++; t++;
			N[j] = t;
		}else t = N[t];
	}
	return N;
}

int match(char* P, char* T){
	int* next = buildNext(P);//构造next表
	int n = (int)strlen(T), i = 0;//文本串
	int m = (int)strlen(P), j = 0;//模式串
	while(j < m && i < n){
		if(j < 0 || T[i] == P[j]){
			i++; j++;
		}else j = next[j];
	}
	delete [] next;
	return i - j;
}

int main()
{
	char T[10] = "hello";
	char P[5] = "llo";
	printf("%d\n", match(P, T));
	return 0;
}
