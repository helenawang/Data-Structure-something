#include <cstdio>
using namespace std;
const int MAX_N = 100005;
const int INF = 0x7fffffff;
struct Node
{
	int k;
	int w;
	Node():k(INF){}
	Node(int kk):k(kk), w(random()){}
	bool operator<(Node& n)const{
		return k < n.k
	}
};
struct Treap
{
	Node nodes[MAX_N];
	int size;
	void zag(int p){
		int v = p*2+1;
		这里父子关系会变，导致下标对应关系不再成立，因此不能这样实现

	}
	void rotate(int cur){
		int p = cur / 2;
		while(nodes[p].k != INF){
			if(nodes[p].w > nodes[cur].w){
				zag(p);
			}else zig(p);
		}
	}
	void insert(int cur, int k){//节点下标，待插入关键码
		if(nodes[cur].k == INF){//抵达目标叶节点
			nodes[cur].k = k;
			nodes[cur].w = random();
			rotate(cur);//旋转调整
			return ;
		}
		if(k < nodes[cur].k) insert(cur*2, k);
		else insert(cur*2+1, k);
	}
};
Treap treap;

int main()
{
	int n, k;
	char c;
	scanf("%d", &n);
	while(n--){
		scanf("%c %d", &c, &k);
		switch(c){
			case 'I':
				if(treap.size == 0){
					treap.nodes[1] = Node(k);//根节点
					treap.size++;
				}
				else treap.insert(1, k);//从根开始查找
				break;
			case 'Q':
				printf("%d\n", treap.search(k));
				break;
		}
	}
	return 0;
}