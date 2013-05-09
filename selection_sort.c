/*选择排序
 *
 * 伪代码：
 * SELECTION-SORT(A)
 * n <-- length[A]
 * for i<--1 to n-1
 *		do  key <-- i
 *			for j<--i+1 to n
 *				do if A[j] > A[key]
 *					then key<--j
 *			exchange A[j] <--> A[key]
 *
 */

#include <stdio.h>
#define N 20


/*打印数组函数*/
void print_arr(int *a, int n)
{
	int i;
	for( i = 0; i < n; i++)
		printf("%d ",a[i]);
	putchar('\n');
}

/*交换两个数的值函数*/
void swap(int *a,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/*选择排序主程序*/
void select_sort(int *a,int n)
{
	int key,i,j;//设一个key，存放最大值的下标
	for(i = 0; i < n - 1; i++)
	{
		key = i;
		for(j = i + 1; j < n; j++)
			if( a[j] > a[key])
				key = j;
		swap(&a[i], &a[key]);
	}

}

int main(int argc, char **argv) {
	int i,array[N];
	srand((unsigned)time(NULL));
	for(i = 0; i < N; i++)
		array[i] = rand() % 100;  //取随机数赋值
	print_arr(array,N);	
	select_sort(array,N);
	print_arr(array,N);
	return 0;
}
