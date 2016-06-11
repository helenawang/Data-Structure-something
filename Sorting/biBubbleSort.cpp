#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

void swap(int& a, int& b){
	int temp = a;
	a = b;
	b = temp;
}

//双向起泡排序
void biBubbleSort(int A[], int n){
	int l = 0, r = n - 1;
	bool flag = 1;
	int i, j;
	while(flag){
		flag = 0;
		for(i = l; i < r; i++){
			if(A[i] > A[i+1]){
				swap(A[i], A[i+1]);
				flag = 1;
			}
		}
		r--;
		for(j = r; j > l; j--){
			if(A[j] < A[j-1]){
				swap(A[j], A[j-1]);
				flag = 1;
			}
		}
		l++;
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

	biBubbleSort(a, n);

	printf("\nsorted sequence\n");
	for(int i=0; i<n; i++) printf("%d ", a[i]);
	
	return 0;
}