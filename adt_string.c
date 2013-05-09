/*数据结构 串 的基本操作*/

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 40 /* 存储空间初始分配量 */

typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char String[MAXSIZE+1]; /*  0号单元存放串的长度 */

/*  输出字符串T */
void StrPrint(String T)
{
	int i;
	for(i=1;i<=T[0];i++)
		printf("%c",T[i]);
	printf("\n");
}

/* 若S为空串,则返回TRUE,否则返回FALSE */
Status StrEmpty(String S)
{
	if(S[0]==0)
		return TRUE;
	else
		return FALSE;
}

/* 生成一个其值等于chars的串T */
Status StrAssign(String T,char *chars)
{
	int i;
	if(strlen(chars)>MAXSIZE)
		return ERROR;
	else
	{
		T[0]=strlen(chars);
		for(i=1;i<=T[0];i++)
			T[i]=*(chars+i-1);
		return OK;
	}
}

/* 返回串的元素个数 */
int StrLength(String S)
{
	return S[0];
}

/*  初始条件: 串S和T存在 */
/*  操作结果: 若S>T,则返回值>0;若S=T,则返回值=0;若S < T,则返回值< 0 */
int StrCompare(String S,String T)
{
	int i;
	for(i=1;i<=S[0]&&i<=T[0];++i)
		if(S[i]!=T[i])
			return S[i]-T[i];
	return S[0]-T[0];
}

/* 用T返回S1和S2联接而成的新串。若未截断，则返回TRUE，否则FALSE */
Status Concat(String T,String S1,String S2)
{
	int i;
	if(S1[0]+S2[0]<=MAXSIZE)
	{ /*  未截断 */
		for(i=1;i<=S1[0];i++)
			T[i]=S1[i];
		for(i=1;i<=S2[0];i++)
			T[S1[0]+i]=S2[i];
		T[0]=S1[0]+S2[0];
		return TRUE;
	}
	else
	{ /*  截断S2 */
		for(i=1;i<=S1[0];i++)
			T[i]=S1[i];
		for(i=1;i<=MAXSIZE-S1[0];i++)
			T[S1[0]+i]=S2[i];
		T[0]=MAXSIZE;
		return FALSE;
	}
}

/* 用Sub返回串S的第pos个字符起长度为len的子串。 */
Status SubString(String Sub,String S,int pos,int len)
{
	int i;
	if(pos < 1||pos>S[0]||len < 0||len>S[0]-pos+1)
		return ERROR;
	for(i=1;i<=len;i++)
		Sub[i]=S[pos+i-1];
	Sub[0]=len;
	return OK;
}

/* 返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数返回值为0。 */
/* 其中,T非空,1≤pos≤StrLength(S)。 */
int Index(String S, String T, int pos)
{
	int i = pos;	/* i用于主串S中当前位置下标值，若pos不为1，则从pos位置开始匹配 */
	int j = 1;				/* j用于子串T中当前位置下标值 */
	while (i <= S[0] && j <= T[0]) /* 若i小于S的长度并且j小于T的长度时，循环继续 */
	{
		if (S[i] == T[j]) 	/* 两字母相等则继续 */
      	{
			++i;
         	++j;
      	}
      	else 				/* 指针后退重新开始匹配 */
      	{
         	i = i-j+2;		/* i退回到上次匹配首位的下一位 */
         	j = 1; 			/* j退回到子串T的首位 */
      	}
	}
	if (j > T[0])
		return i-T[0];
	else
		return 0;
}

/*  初始条件: 串S和T存在,1≤pos≤StrLength(S)+1 */
/*  操作结果: 在串S的第pos个字符之前插入串T。完全插入返回TRUE,部分插入返回FALSE */
Status StrInsert(String S,int pos,String T)
{
	int i;
	if(pos< 1||pos>S[0]+1)
		return ERROR;
	if(S[0]+T[0]<=MAXSIZE)
	{ /*  完全插入 */
		for(i=S[0];i>=pos;i--)
			S[i+T[0]]=S[i];  // 末尾->pos的元素 后移T[0]位
		for(i=pos;i < pos+T[0];i++)
			S[i]=T[i-pos+1];
		S[0]=S[0]+T[0];
		return TRUE;
	}
	else
	{ /*  部分插入 */
		for(i=MAXSIZE;i<=pos;i--)
			S[i]=S[i-T[0]];  //pos ->末尾后移T[0]位，超出的截断
		for(i=pos;i < pos+T[0];i++)
			S[i]=T[i-pos+1];
		S[0]=MAXSIZE;
		return FALSE;
	}
}

/*  初始条件: 串S存在,1≤pos≤StrLength(S)-len+1 */
/*  操作结果: 从串S中删除第pos个字符起长度为len的子串 */
Status StrDelete(String S,int pos,int len)
{
	int i;
	if(pos < 1||pos>S[0]-len+1||len < 0)
		return ERROR;
	for(i=pos+len;i<=S[0];i++)
		S[i-len]=S[i];
	S[0]-=len;
	return OK;
}

/*  初始条件: 串S,T和V存在,T是非空串（此函数与串的存储结构无关） */
/*  操作结果: 用V替换主串S中出现的所有与T相等的不重叠的子串 */
Status Replace(String S,String T,String V)
{
	int i=1; /*  从串S的第一个字符起查找串T */
	if(StrEmpty(T)) /*  T是空串 */
		return ERROR;
	do
	{
		i=Index(S,T,i); /*  结果i为从上一个i之后找到的子串T的位置 */
		if(i) /*  串S中存在串T */
		{
			StrDelete(S,i,StrLength(T)); /*  删除该串T */
			StrInsert(S,i,V); /*  在原串T的位置插入串V */
			i+=StrLength(V); /*  在插入的串V后面继续查找串T */
		}
	}while(i);
	return OK;
}

int main()
{
    int i, j, opp, pos;
    char s, str;
	String t,s1,s2,sub;
	Status k;

    printf("\n1.StrAssign 生成串 \n2.StrLength 求串长 \n3.StrCompare 串比较 ");
    printf("\n4.Concat 串连接 \n5.SubString 求子串 \n6.Index 求子串位置");
    printf("\n7.StrInsert 子串插入 \n8.StrDelete 子串删除 \n9.Replace 子串替换");
    printf("\n0.退出 \n请选择你的操作：\n");
    while(opp != '0')
    {
        scanf("%d",&opp);
        switch(opp)
        {
        case 1:
            k=StrAssign(s1,"nowamagic.net");
            if(!k)
            {
                printf("串长超过MAXSIZE(=%d)\n",MAXSIZE);
                exit(0);
            }
            printf("串s1为：");
            StrPrint(s1);
            printf("\n");
            break;

        case 2:
            printf("串s1长为%d \n",StrLength(s1));
            break;

        case 3:
            k=StrAssign(s2,"google.com");
            if(!k)
            {
                printf("串长超过MAXSIZE(%d)\n",MAXSIZE);
                exit(0);
            }
            printf("串s2为：");
            StrPrint(s2);
            printf("\n");

            i=StrCompare(s1,s2);
            if(i < 0)
                s=' < ';
            else if(i==0)
                s='=';
            else
                s='>';
            printf("串s1%c串s2\n",s);
            break;

        case 4:
            Concat(t,s1,s2);
            StrPrint(t);
            break;

        case 5:
            printf("求串s1的子串,请输入子串的起始位置: ");
            scanf("%d", &i);
            printf("请输入子串的长度: ");
            scanf("%d", &j);
            printf("起始位置：%d，子串长度：%d\n", i, j);
            k=SubString(sub,s1,i,j);
            if(k)
            {
                printf("子串sub为: ");
                StrPrint(sub);
            }
            break;

        case 6:
            printf("主串s1为: ");
            StrPrint(s1);
            k=StrAssign(sub,"magic");
            printf("子串sub为: ");
            StrPrint(sub);
            i=Index(s1,sub,1);
            printf("s1的第%d个字母起和sub第一次匹配\n",i);
            break;

        case 7:
            printf("主串s1为: ");
            StrPrint(s1);
            k=StrAssign(sub,"lol");
            printf("子串sub为: ");
            StrPrint(sub);
            printf("请输入要插入的位置: ");
            scanf("%d", &pos);
            StrInsert(s1,pos,sub);
            StrPrint(s1);
            break;

        case 8:
            printf("从串s1的第pos个字符起,删除len个字符，请输入pos: \n");
            scanf("%d", &i);
            printf("再输入len: \n");
            scanf("%d", &j);
            StrDelete(s1,i,j);
            StrPrint(s1);
            break;

        case 9:
            printf("主串s1为: ");
            StrPrint(s1);
            StrAssign(t,"a");
            printf("串t为：");
            StrPrint(t);
            StrAssign(sub,"aa");
            printf("串sub为：");
            StrPrint(sub);
            printf("用串s2取代串s1中和串t相同的不重叠的串后,串s1为: ");
            Replace(s1,t,sub);
            StrPrint(s1);
            break;

        case 0:
            exit(0);
        }
    }
}
