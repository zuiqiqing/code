#include <stdio.h>
#include <stdlib.h>


void inputarray(int *p,int N)
{
	int i;
//	srand(time(NULL));
	printf("please input N numbers:\n");
	for(i=0;i<N;i++){
	//*(p+i)=rand()%1000;	
		scanf("%d",p+i);
	}

}


void sort(int *p,int N)
{
	int i,j,*test;
	for(i=0;i<N;i++)
		for(j=0;j<N-i-1;j++)
			if(*(p+j)<*(p+j+1)){
				*test=*(p+j);
				*(p+j)=*(p+j+1);
				*(p+j+1)=*test;
			}
		
}

void printarray(int *p,int N)
{
	int i;
	for(i=0;i<N;i++)
		printf("  %d",*(p+i));
	printf("\n");
}

int main(void)
{
	int N,*p;
	int i;
	printf("please input N:\n");
	scanf("%d",&N);
	p=malloc(N*sizeof(int));
	inputarray(p,N);
	sort(p,N);
	printarray(p,N);	
}
