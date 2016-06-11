#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

void swap(int& a, int& b){
	int temp = a;
	a = b;
	b = temp;
}

//双向快速划分排序（快速排序）
void quickSort(int A[], int l, int r){//[l, r]
	if(l >= r) return ;
	int i = l, j = r;
	int temp = A[l];//区间左端点为培养对象
	while(i < j){
		while(i < j && A[j] >= temp) j--;
		if(i < j) A[i++] = A[j];
		while(i < j && A[i] <= temp) i++;
		if(i < j) A[j--] = A[i];
	}
	A[i] = temp;
	quickSort(A, l, i-1);
	quickSort(A, i+1, r);
}

int main()
{
	int n = 10;
	int a[10];
	srand(time(0));
	for(int i=0; i<n; i++) a[i] = rand();
	printf("original sequence\n");
	for(int i=0; i<n; i++) printf("%d ", a[i]);
	quickSort(a, 0, n-1);
	printf("\nsorted sequence\n");
	for(int i=0; i<n; i++) printf("%d ", a[i]);
	
	return 0;
}