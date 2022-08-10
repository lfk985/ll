#include <conio.h>
#include <stdlib.h>
#define MAX 100//最大数组
int main()
{
	/*求交集*/
	int array0[MAX]={},array1[MAX]={};
	int array[MAX*2]={};
	int arraySize0,arraySize1,arraySize=0;
	printf("请分别输入数组1和数组2的大小\n");
	scanf("%d %d",&arraySize0,&arraySize1);
	for (int i=0;i<arraySize0;i++)
	{
		printf("请输入数组1第%d个元素",i+1);
		scanf("%d",&array0[i]);
	}
	for (int i=0;i<arraySize1;i++)
	{
		printf("请输入数组2第%d个元素",i+1);
		scanf("%d",&array1[i]);
	}
	for (int i=0,k=0;i<arraySize0;i++)
	    for (int j=0;j<arraySize1;j++)
	    	if ( array0[i]== array1[j])
	    	{
	        	array[arraySize++]=array0[i];
	        	for (int k=i;k<arraySize0-1;k++)
    	    	array0[k]=array0[k+1];
    	    	for (int k=j;k<arraySize1-1;k++)
    	    	array1[k]=array1[k+1];
    	    	arraySize0--,arraySize1--,i--;
	        	break;
	    	}
	printf("\n数组1交数组2\n");
	for (int i=0;i<arraySize;i++)
		printf("%d  ", array[i]);	
	/*求并集*/
	int a[MAX]={};
	for (int i=0;i<arraySize0;i++)
		a[i]=array0[i];
	for (int i=arraySize0;i<arraySize0+arraySize1;i++)
		a[i]=array1[i-arraySize0];
	for (int i=arraySize0+arraySize1;i<arraySize0+arraySize1+arraySize;i++)	
		a[i]=array[i-arraySize1-arraySize0];
	printf("\n数组1并数组2\n");
	for (int i=0;i<arraySize0+arraySize1+arraySize;i++)
		printf("%d  ", a[i]);
}