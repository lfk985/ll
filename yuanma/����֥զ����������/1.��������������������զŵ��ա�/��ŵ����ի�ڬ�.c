#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 20
int rand0(void)
{
	srand(rand());//初始化伪随机数生成器 
    return (double)rand() / RAND_MAX*7;
}
int main()
{
	srand(time(NULL));//初始化伪随机数生成器 
	int x,k[MAX]={};
	int m[100];
	for(int i=0;i<MAX;i++)
	{
		k[i]=rand0();
		printf("x%d=%d\n",i,k[i]);
	}
	for (int p=0,i=0;i<7;i++)
	{
	for (int j=0;j<MAX;j++)
	{
		if (k[j]==i)
		p++;
	}
	printf("%d =  %d次\n",i,p);
	p=0;
	}
}