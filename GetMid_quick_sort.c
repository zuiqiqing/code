/*3元取中的快速排序
 *
 * 伪代码：
 * PARTITION(A, p, r)
 * 1  x ← A[r]         //以最后一个元素，A[r]为主元
 * 2  i ← p - 1
 * 3  for j ← p to r - 1    //注，j从p指向的是r-1，不是r。
 * 4       do if A[j] ≤ x
 * 5             then i ← i + 1
 * 6                  exchange A[i] <-> A[j]
 * 7  exchange A[i + 1] <-> A[r]    //最后，交换主元
 * 8  return i + 1
 *
 * QUICKSORT(A, p, r)
 * 1 if p < r
 * 2    then q ← PARTITION(A, p, r)   //关键
 * 3         QUICKSORT(A, p, q - 1)
 * 4         QUICKSORT(A, q + 1, r)
 *
 */

#include <stdio.h>
#define N 20
#define MAX1(a,b)  (a)>(b)?(a):(b)
#define MAX(a,b,c)  (a)>(MAX1(b,c))?(a):(MAX1(b,c))

/*打印数组*/
void print_arr(int *a, int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%d ",a[i]);
	putchar('\n');
}

/*交换两个数的值*/
void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


int Getmid(int *A,int left, int right)
{
	int a = -1, b = -1, c = -1;
	int max;
	//取随机的3元
	/*
	while(a < left)
		a = rand() % right;
	while(b < left)
		b = rand() % right;
	while(c < left)
		c = rand() % right;
	*/


	//取第一 中间 及最后一个元素为3元	
	a = left; b = (left + right)/2; c = right;

	//return MAX(A[a],A[b],A[c]);
	if(A[a] > A[b]) 
		max = a;
	else max = b;
	if(A[c] > A[max])
		max = c;
	return max;
}

/*快排的核心，划分数组
 * 选定一个主元key，将数组划分为
 * [ (>key)  key (<key)]
 */
int partition(int *a, int left, int right)
{
	int i,j,m;
	int key;
	m = Getmid(a,left,right);
	swap(a+m,a+right);

	key = a[right];  //选末尾元素为主元key
	i = left - 1;                       // [a0,a1,a2,a3,a4,a5,a6,a7,a8,a9]
	for(j = left; j <= right-1; j++)   // i  j                         key
		if(a[j] >= key)
		{
			i++;
			swap(a+i,a+j);
		}
	swap(a+i+1,a+right);
	return i+1;
}

/*快排主程序*/
void q_sort(int *a, int left, int right)
{
	int point;
	if(left < right) //base case
	{
		point = partition(a,left,right); 

		q_sort(a,left,point - 1);
		q_sort(a,point + 1,right);
	}
}

void quicksort(int *a, int n)
{
	q_sort(a,0,n-1);
}

int main(int argc, char **argv)
{

	int array[N];
	int i;
	srand((unsigned)time(NULL));
 	for(i = 0; i < N; i++)
		array[i] = rand() % 100;
	print_arr(array,N);

	quicksort(array,N);
	print_arr(array,N);

	return 0;
}
