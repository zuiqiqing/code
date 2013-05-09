/*
 * 桶排序  时间复杂度：O(N+N*logN-N*logM)
 * 伪代码：
 * BUCKET-SORT(A)：
 *  n = length[A]
 *  let B[0..n-1] be a new array
 *  for i=0 to n-1
 *		make B[i] an empty list
 *	for i=1 to n
 *		insert A[i] into B[nA[i]]
 *	for i=0 to n-1
 *		sort list B[i] with insertion sort
 *	concatenate the lists B[0],B[1],...,B[n-1] together in orger
 *
 *
#include <stdlib.h>
#include <stdio.h>
#define N 200000
#define NUM_SIZE  100900
#define BUCKET_SIZE  (NUM_SIZE/10)

typedef struct node{
	int key;
	struct node *next; 
}KeyNode;

void inc_sort(int keys[],int size,int bucket_size)
{
	int i,j;
	

	KeyNode **bucket_table = (KeyNode **)malloc(bucket_size*sizeof(KeyNode *));
	//建立一个大小为bucket_size的桶
	for(i = 0; i < bucket_size; i++)
	{
		bucket_table[i] = (KeyNode *)malloc(sizeof(KeyNode));
		bucket_table[i]->key = 0; // 记录当前替bucket中的数据量
		bucket_table[i]->next = NULL;
	}



	for(j = 0; j < size; j++)
	{
		KeyNode  *node = (KeyNode *)malloc(sizeof(KeyNode));
		node->key = keys[j];
		node->next = NULL;

		//映射函数计算桶号
		int index = keys[j]/10;

		//初始化head成为桶中数据链表的头指针
		KeyNode *head = bucket_table[index];

		if(head->key == 0)
		{
			//head->next = node;
			bucket_table[index]->next = node;
			(bucket_table[index]->key)++;
		}else
		{	//链表结构的插入排序
			while(head->next != NULL && head->next->key <= node->key)
				head = head->next;
			node->next = head->next;
			head->next = node;
			(bucket_table[index]->key)++;
		}
	}


	//打印结果
	for(i = 0; i < bucket_size; i++)
	{
		KeyNode *Lnode = bucket_table[i]->next;
		for(; Lnode != NULL; Lnode = Lnode->next)
			printf("%d ",Lnode->key);
	}
	putchar('\n');
}


int main(int argc, char **argv)
{
	
//	int raw[]={12,31,90,8,28,23,65,15,97,1};
	
	int i;
	int raw[N];
	/*
	for(i = 0; i < 10; i++)
		printf("%d ",raw[i]);
	putchar('\n');
	*/
	srand((unsigned)time(NULL));
	for(i = 0; i < N; i++)
		raw[i] = rand()%NUM_SIZE;

	int size = sizeof(raw)/sizeof(int);
	inc_sort(raw,size,BUCKET_SIZE);
	return 0;
}
