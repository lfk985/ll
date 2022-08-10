#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <conio.h>

int randint(int *a,int m, int max,int min)
{
	for (int i=0;i<max-min;i++)
	a[i]=i+min;
	for (int w,t,i=0;i<max-min;i++)
{
	w=rand()%(max-min-i)+i;
 t=a[i];
 a[i]=a[w];
 a[w]=t;
 }
}

int main()
{
	int n=0;
	int b[10]={};
	srand(time(NULL));

	for(int i=0;i<8;i++)
	{	randint(b,8,9,5);
		n=0;
while(n++<10) 
{
	
	printf("%2d  ",b[n-1]);
usleep(1000);
}
printf("\n");
	}
return 0;
}