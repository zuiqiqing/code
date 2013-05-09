/* 归并排序
 *
 * 伪代码：
 *
 * MERGE(A,left,middle,right)
 * n1 <-- middle - left
 * n2 <-- r-q
 * creat arrays L[1..n1+1] and R[1..n2+2]
 * for i <-- 1 to n1
 *	do L[i] <-- A[p+i-1]
 * for j <-- 1 to n2
 *	do R[i] <-- A[q+j]
 * L[n1+1] <-- 哨兵
 * R[n2+1] <-- 哨兵
 * i <-- 1
 * j <-- 1
 * for k <--p to r
 *	do if L[i] <= R[i]
 *		then A[k] <-- L[i]
 *			 i <--i+1
 *		else A[k] <--R[j]
 *			 j <--j+1
 *
 * MERGE_SORT(A,left,right)
 * if p<r
 *	then middle<--(left+right)/2
 *		MERGE-SORT(A,left,middle);
 *		MERGE-SORT(A,middle+1,right);
 *		MERGE(A,left,middle,right);
 */

#include <stdio.h>
#include <stdlib.h>
#define N 20
#define SMALLEST -1000

/*数组打印*/
void print_arr(int *a, int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%d ",a[i]);
	putchar('\n');
}

/*合并两个子数组*/
void merge(int *a, int left, int middle, int right)
{
	int *L,*R;
	int n1,n2;
	int i,j,k;
	n1 = middle - left + 1;
	n2 = right - middle;
	L = (int *)malloc((n1+1)*sizeof(int)); //动态分配数组 长度
	R = (int *)malloc((n2+1)*sizeof(int));

	for(i = 0; i < n1; i++)
		L[i] = a[left+i];
	for(j = 0; j < n2; j++)
		R[j] = a[middle+1+j];
	
	i = j = 0;
	k = left;
	L[n1] = R[n2] = SMALLEST; //设立哨兵

	while(k <= right)         //比较L和R数组的元素，大的放入a中
	{
		if(L[i] > R[j])
			a[k++] = L[i++];
		else
			a[k++] = R[j++];
	}
/*
 * 不设哨兵，代码复杂一些；但是还是比较好理解；
 *
	while(i < n1 && j < n2)            //比较L和R，并将大的元素放入a
		if(L[i] > R[j])				   //直到L或R末尾
			a[k++] = L[i++];
		else
			a[k++] = R[j++];
	
	if(i == n1)
		while(j < n2)				//L已存完，将R的剩余元素全部给a
			a[k++] = R[j++];
	else
		while(i < n1)				//R已存完，将L的剩余元素全部给a
			a[k++] = L[i++];
*/
	free(L);
	free(R);  //记得释放内存
}


/*归并排序主程序*/
void m_sort(int *a,int left, int right)
{
	int middle;
	if(left < right)  //base case
	{
		middle = (left + right)/2;
		m_sort(a,left,middle);
		m_sort(a,middle+1,right);
		merge(a,left,middle,right);
	}
}


void meger_sort(int *a, int n)
{
	m_sort(a,0,n-1);
}


int main(int argc, char **argv)
{
	int array[N];
	int i;
	srand((unsigned)time(NULL));
	for(i = 0; i < N; i++)
		array[i] = rand() % 100;
	print_arr(array,N);

	meger_sort(array,N);
	print_arr(array,N);
	return 0;
}
