/*顺序表的基本操作
 *
 */

#include "stdio.h"
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* 存储空间初始分配量 */
typedef int ElemType;   /* ElemType类型根据实际情况而定，这里假设为int */
typedef int Status;     /* Status是函数的类型,其值是函数结果状态代码，如OK等 */

typedef struct
{
	ElemType data[MAXSIZE]; /* 数组，存储数据元素 */
	int length;             /* 线性表当前长度 */
}SqList;

/* 初始化顺序线性表 */
Status InitList(SqList *L)
{
    L->length=0;
    return OK;
}

//顺序表的建立
SqList Create(SqList L)
{
    int i;
    srand((unsigned)time(NULL));
	for(i=0; i < 10; i++)
	{
		L.data[i] = rand()%100;
        L.length++;
	}
    return L;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(SqList *L)
{
    L->length=0;
    return OK;
}

Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(SqList L)
{
	int i;
    for(i=0;i < L.length;i++)
            visit(L.data[i]);
    printf("\n");
    return OK;
}

/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(SqList *L,int i,ElemType e)
{
	int k;
	if (L->length==MAXSIZE)  /* 顺序线性表已经满 */
		return ERROR;
	if (i < 1 || i>L->length+1)/* 当i比第一位置小或者比最后一位置后一位置还要大时 */
		return ERROR;

	if (i <= L->length)        /* 若插入数据位置不在表尾 */
	{
		for(k=L->length-1;k>=i-1;k--)  /* 将要插入位置之后的数据元素向后移动一位 */
			L->data[k+1]=L->data[k];
	}
	L->data[i-1]=e;          /* 将新元素插入 */
	L->length++;

	return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(SqList *L,int i,ElemType *e)
{
    int k;
    if (L->length==0)               /* 线性表为空 */
		return ERROR;
    if (i < 1 || i>L->length)         /* 删除位置不正确 */
        return ERROR;
    *e=L->data[i-1];
    if (i < L->length)                /* 如果删除不是最后位置 */
    {
        for(k=i; k < L->length; k++)/* 将删除位置后继元素前移 */
			L->data[k-1]=L->data[k];
    }
    L->length--;
    return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值,注意i是指位置，第1个位置的数组是从0开始 */
Status GetElem(SqList L,int i,ElemType *e)
{
    if(L.length==0 || i < 1 || i>L.length)
            return ERROR;
    *e=L.data[i-1];

    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(SqList L,ElemType e)
{
    int i;
    if (L.length==0)
            return 0;
    for(i=0;i < L.length;i++)
    {
            if (L.data[i]==e)
                    break;
    }
    if(i>=L.length)
            return 0;

    return i+1;
}

int main()
{
    SqList L;
    ElemType e;
    Status i;
    char opp;
    int j,k;
    int pos;
    ElemType value;

    i=InitList(&L);
    printf("初始化成功，L.length=%d\n",L.length);
    printf("\n1.遍历线性表 \n2.线性表赋值 \n3.清空线性表 \n4.线性表插入 \n5.查找表中元素 \n6.判断元素是否在表中 \n7.删除某个元素 \n0.退出 \n请选择你的操作：\n");
    while(opp != '0'){
        scanf("%c",&opp);
        switch(opp){
            case '1':
                ListTraverse(L);
                printf("\n");
                break;

            case '2':
                L = Create(L);
                printf("创建随机链表：L.data=");
                ListTraverse(L);
                printf("\n");
                break;

            case '3':
                i=ClearList(&L);
                printf("清空L后：L.length=%d\n",L.length);
                ListTraverse(L);
                printf("\n");
                break;


            case '4':
                printf("请输入插入元素位置：");
                scanf("%d",&pos);
                printf("请输入插入元素的值：");
                scanf("%d",&value);
                i = ListInsert(&L,pos,value);
                printf("插入完毕，现在线性表为：\n");
                ListTraverse(L);
                printf("\n");
                break;

            case '5':
                printf("你要查找第几个元素？ ");
                scanf("%d",&pos);
                GetElem(L,pos,&e);
                printf("第%d个元素的值为：%d\n",pos,e);
                break;

            case '6':
                printf("输入你想知道是否在表中的数值： ");
                scanf("%d",&e);
                k=LocateElem(L,e);
                // 这里假定随机数组中的元素互不重复
                if(k)
                    printf("值为%d是表中的第%d个元素\n",e,k);
                else
                    printf("没有值为%d的元素\n",e);
                break;

            case '7':
                printf("要删除第几个元素？");
                scanf("%d",&pos);
                ListDelete(&L,pos,&e);
                printf("删除完毕，现在线性表为：\n");
                ListTraverse(L);
                printf("\n");
                break;

            case '0':
                exit(0);
        }
    }
}
