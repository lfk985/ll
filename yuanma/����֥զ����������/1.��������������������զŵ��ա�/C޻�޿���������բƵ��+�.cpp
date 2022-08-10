#include <stdio.h>
int i=3; //计数
void sum(int k,int a,int b,int c)
{
	int s=0;
	if (i++<k)
	{
    	s=a+b+c;
    	a=b;
		b=c;
    	sum(k,a,b,s);//递归
	}
	else 
	printf("sum=%d\n",c);
	
}
int main()
{
	int k;
	int num[3]={3,4,5};
	printf("请输入项数n(0<n<=35)\n");
	scanf("%d",&k);
	if (k>3)
	sum(k,num[0],num[1],num[2]);
	else if(k>0)
	printf("sum=%d",num[k-1]);
	return 0;
}