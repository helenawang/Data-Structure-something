#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

void swap(int& a, int& b){
	int temp = a;
	a = b;
	b = temp;
}

//一般起泡排序
void bubbleSort(int A[], int n){
	for(int i=n-1; i>=1; i--){
		int flag = 0;
		for(int j=1; j<=i; j++){
			if(A[j-1] > A[j]){
				swap(A[j-1],A[j]);
				flag = 1;
			}
		}
		if(!flag) break;
	}
}

int main()
{
	int n = 10;
	int a[10];
	srand(time(0));
	for(int i=0; i<n; i++) a[i] = rand();
	printf("original sequence\n");
	for(int i=0; i<n; i++) printf("%d ", a[i]);
	bubbleSort(a, n);
	printf("\nsorted sequence\n");
	for(int i=0; i<n; i++) printf("%d ", a[i]);
	
	return 0;
}