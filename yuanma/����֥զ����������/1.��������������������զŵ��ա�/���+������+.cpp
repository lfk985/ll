#include <stdio.h>
#include <stdlib.h>
void move(int *arr,int n,int m);
int main()
{
	int m=0,n=0;
	scanf("%d",&n);
	int *arr=(int *)malloc(sizeof(int)*n);	
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);		
	scanf("%d",&m);
	move(arr,n,m);
	return 0;
}

void move(int *arr,int n,int m)
{
	int *arr1=(int *)malloc(sizeof(int)*n);
	for(int i=0;i<n;i++)
	arr1[i]=(i+n-m)%n;
	for(int i=0;i<n;i++)
		printf("%d",arr[arr1[i]]);	
}