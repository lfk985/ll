#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
/*
	for (int i=0;i<18;i++)
	{
		printf("%d",ss());
		usleep(10000);
		}
		*/
int ss()
{
	srand(clock());//初始化伪随机数生成器 
	return  (double)rand()/RAND_MAX*6;
}

int main()
{
	typedef struct
	{
		int k;
		int j;
	}Py;
	Py a={1,2};
	Py b;
	b=a;
	printf("%d",b.k);
	return 0;
}