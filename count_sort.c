/*计数排序
 *
 * 伪代码：
 *
 * COUNTING-SORT(A, B, n, k)：
 * for i ← 0 to k
 *	 do C[i ] ← 0
 * for j ← 1 to n
 *	 do C[A[ j ]] ← C[A[ j ]] + 1
 * for i ← 1 to k
 *   do C[i ] ← C[i ] + C[i − 1]
 * for j ← n downto 1
 *   do B[C[A[ j ]]] ← A[ j ]
 *      C[A[ j ]] ← C[A[ j ]] − 1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20
#define MAX 2000


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

/*计数排序主程序*/
void countsort(int *a, int n,int m)
{
	int *c;
	c = (int *)malloc(sizeof(int)*m); //临时数组，用来存放A中的元素
	memset(c,0,m);                    
	int b[n];                         //存放排序好的数组
	int i,j;
	
	for(j = 0; j < n;j++)
		c[a[j]] = c[a[j]] + 1;        //A中元素的值作为c数组的下标，并计数

	for(i = 1; i <= m; i++)
		c[i] = c[i] + c[i-1];   

	for(j = n-1; j >= 0; j--)
	{
		b[c[a[j]]-1] = a[j];             
		c[a[j]]--;
	}

	for( j = 0; j < n; j++)
		a[ n-j-1] = b[j];
	free(c);
}

void countsort2(int *a, int n, int m)
{
	int i,j,t=0;
	int *c;
	c = (int *)malloc(sizeof(int)*m);
	memset(c,0,m);

	for(j = 0; j < n; j++)
		c[a[j]] = c[a[j]] + 1;
//	printf("_________________________________\n");
//	print_arr(c,m);
//	printf("_________________________________\n");
	for(i = 0; i <= m && t < n; i++)
	{
		while(c[i] > 0)
		{
			a[t++] = i;
			c[i]--;
		}
	}
	
	t--;
	free(c);
}

int main(int argc, char **argv)
{
	int i,array[N];
	srand((unsigned)time(NULL));
	for(i = 0; i < N; i++)
		array[i] = rand() % 1000;  //取随机数赋值
	print_arr(array,N);	
	countsort(array,N,MAX);
	print_arr(array,N);
//	countsort2(array,N,MAX);
//	print_arr(array,N);
	return 0;
}
