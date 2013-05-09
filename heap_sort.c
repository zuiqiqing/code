/*利用最大二叉堆，实现堆排序。
 * 其中堆数组下标从1开始
 * 
 * 伪代码：
 * MAX-HEAPIFY（A，i)
 * l <-- LEFT(i)
 * r <-- RIGHT(i)
 * if l<=heap_size[A] and A[l]>A[i]
 *	  then largest <--l
 *    else largest <--i
 * if r<=heap_size[A] and A[r]>A[largest]
 *	  then largest <--r
 * if largest != i
 *    then exchange A[i] <--> A[largest]
 *         MAX-HEAPIFY(A,largest)
 *
 * BUILD-MAX-HEAP(A)
 * heap_size[A] <-- length[A]
 * for i <-- length[A]/2 downto 1
 *		do MAX-HEAPIFY(A,i)
 *
 * HEAPSORT(A)
 *  BUILD-MAX-HEAP(A)
 *  for i <--length[A] downto 2
 *		do exchange A[1] <--> A[i]
 *		   heap_size[A] <-- heap_size[A] -1
 *		   MAX-HEAPIFY(A,1)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20

/*返回父节点*/
int Parent(int i)
{
	return i/2;
}

/*返回左儿子节点*/
int Left(int i)
{
	return 2*i;
}

/*返回右儿子节点*/
int Right(int i)
{
	return 2*i+1;
}

/*交换两个数的值*/
void swap(int *p, int *q)
{
	int temp;
	temp = *p;
	*p = *q;
	*q = temp;
}

/*维护i节点的最大堆的堆序性*/
void max_heapify(int A[],int h_size,int i) //h_size是堆的长度，i是节点下标
{										   //堆长度h_size <= 数组的长度n
	int l,r,largest;
	l = Left(i);
	r = Right(i);
	if(l <= h_size && A[l] > A[i]) //左儿子存在且节点值>父节点值
		largest = l;
	else largest = i;

	if(r <= h_size && A[r] > A[largest])//右儿子存在且节点值>largest
		largest = r;

/*	largest = i 满足堆序性；否则交换i和largest节点的值;
 *	递归 max_heapify直到树叶处
 */
	if(largest != i) 
	{
		swap(&A[i],&A[largest]);    
	/*	int temp;
		temp =A[i];
		A[i] = A[largest];
		A[largest] = temp;*/
		max_heapify(A,h_size,largest); 
	}
}

/*利用自下向上的方法把大小为n的数组转化为最大堆
 */
void build_heap(int A[],int n)
{
	int i,h_size;
	h_size = n;
	for(i = n/2; i >= 1; i--)  //因为（n/2+1....n）节点都是叶节点
		max_heapify(A,h_size,i);    //没有儿子，所以从n/2处开始维护堆序性
}

/*堆排序主程序*/
void heap_sort(int A[],int n)
{
	int i,h_size = n;
	build_heap(A,n);  //把一个普通的数组建成最大堆
	for(i = n; i >= 2; i--)
	{
		swap(&A[1],&A[i]); //根据最大堆性质，A[1]是最大值，与数组最后一位
		/*int temp;		   //调换
		temp = A[i];
		A[i] = A[1];
		A[1] = temp;*/
		h_size = h_size - 1;//数组减1
		max_heapify(A,h_size,1); //这里的实参是h_size，不是n；
}
}



int main(void)
{
	int i;
	int  A[N+1] = {0};
	srand((unsigned)time(NULL));

	for(i = 1; i <= N; i++)
	{
		A[i] = rand()%200;
		printf("%d ",A[i]);
	}
	printf("\n");
	heap_sort(A,N);

	for(i = 1; i <= N; i++)
		printf("%d ",A[i]);
	putchar('\n');
	return 0;
}
