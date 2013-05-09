/*利用最大二叉堆，实现优先队列。
 * 其中堆数组下标从1开始
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20
#define LARGEST -10000
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
void build_max_heap(int A[],int n)
{
	int i,h_size;
	h_size = n;
	for(i = n/2; i >= 1; i--)  //因为（n/2+1....n）节点都是叶节点
		max_heapify(A,h_size,i);    //没有儿子，所以从n/2处开始维护堆序性
}


/*返回优先队列的最大值*/
int heap_max(int A[],int n)
{
	return A[1];
}



int heap_extract_max(int A[],int n)//实现EXTRACT-MAX（S）操作，去掉并返回S中具有最大关键字的元素
{
    //heap_size为最大堆a中当前的元素数量 
    int max,i;
	int h_size = n;
    if(h_size<1)
    {
        printf("heap underflow!\n");
        return -1;
    }
    max=A[1];//将当前堆顶元素赋给max,即最大值
    A[1]=A[h_size];//将当前堆最后一个元素赋给堆顶，然后进行维护最大堆的操作
    h_size--;
    max_heapify(A,h_size,1);//从堆顶开始重新维护最大堆
    return max;
} 


void heap_increase_key(int A[],int n,int i,int key)//实现INCREASE-KEY(S,x,k)，将元素x的关键字值增加到key 
{
     if (key<A[i])//新的key必须大于原来的，才能执行位置 上升的操作
     {
          printf("new key is smaller than current key!\n");
        //  return -1;
     }
     A[i] = key;
	 //当新key比父节点大时，与父节点交换，父节点变成子节点后也能保证最大堆。直到比父节点小为止。
     while(i > 1 && A[Parent(i)] < A[i])
     {
		 swap(&A[i],&A[Parent(i)]);
		 i = Parent(i);
     }
}


void max_heap_insert(int A[],int n,int key)
{
     //实现INSERT（S,X）操作，将元素x插入到集合S中。通过先加入一个关键字值为-00的叶节点扩展最大堆，
     //然后调用heap_increase_key设置新节点的正确的值
     //heap_size为当前堆中的元素个数 
	 int h_size = n;
     h_size = h_size+1;
     A[h_size] = LARGEST;//以LARGEST代表 一个极小值
     heap_increase_key(A,n,h_size,key); 
}

int main(int argc, char **argv)
{
	int A[N] = {0};
	int i,num;
	srand((unsigned)time(NULL));
	for(i = 1; i <= N; i++)
	{
		A[i] = rand()%200;
		printf("%d ",A[i]);
	}
	putchar('\n');

    printf("------------------------\n");
    printf("建立最大堆以后\n");
    build_max_heap(A,N);

    for(i = 1; i <= N; i++)
		printf("%d ",A[i]);
    printf("\n------------------------\n");
    
	putchar('\n');	
	printf("请插入一个新的元素:\n");
    scanf("%d",&num); 
    max_heap_insert(A,N,num);
	for(i = 1; i <= N+1; i++)
		printf("%d ",A[i]);
	putchar('\n');	
	putchar('\n');	
    printf("逐个打印队列最大值\n");

	for(i = N + 1; i >= 1; i--)			//逐步调用heap_extract_max算法，打印最大值 
		printf("%d  ",heap_extract_max(A,i));
	putchar('\n');	
}
