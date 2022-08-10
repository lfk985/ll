#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 4
int main()
{
	int i,j;
	int a[N*N],b[N][N];//这里设置旋转为4*4的矩形，自己在这里改成其它的矩形
	int *p=a;//用指针来指向这个一维数组。这样在旋转赋值的时候会轻松很多
	srand(time(NULL));
	for(i=0;i<N*N;i++)
	{
		a[i]=rand()%100;//随机生成0~99
		printf("%d\t",a[i]);
		if((i+1)%4==0)
			printf("\n");
	}
	for(j=N-1;j>=0;j--)	//旋转赋值，这里可修改旋转的方向和角度
		for(i=0;i<N;i++,p++){
			b[i][j]=*p;
			printf("a[%d][%d]=%d  ",i+1,j+1,*p);}
	printf("顺时针旋转90度后：\n");
	for(i=0;i<N;i++)	
	{for(j=0;j<N;j++)
			printf("%d\t",b[i][j]);
		printf("\n");
	}
}