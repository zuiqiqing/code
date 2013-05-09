/*
 * c语言冒泡排序
 *
 * 伪代码：
 * for i<--1 to length[A]-1
 *		do for j<--length[A] downto i+1
 *			do if A[j] < A[j-1]
 *				then exchange A[j] <--> A[j-1]
 *
 */
#include <stdio.h>
#define N 20

/*打印数组的函数，n是数组长度*/
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

/*冒泡函数主程序*/
void bobsort(int *a,int n)
{
	int i,j;
	for(i = 0; i < n - 1; i++)//排序次数
		for(j = n - 1; j >= i + 1; j--)//每次排序从最后一个数开始两两比较
			if(a[j] > a[j-1])          
				swap(a+j,a+j-1);        //大的值上浮
	
}

int main(int argc, char **argv)
{
	int i,array[N];
	srand((unsigned)time(NULL));
	for(i = 0; i < N; i++)
		array[i] = rand() % 100;  //取随机数赋值
	print_arr(array,N);	
	bobsort(array,N);
	print_arr(array,N);
	return 0;
}
