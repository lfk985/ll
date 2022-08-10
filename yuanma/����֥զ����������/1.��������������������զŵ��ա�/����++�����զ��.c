//求k位自幂数
//by 千百度QAIU
#include <stdio.h> 
int main() 
{ 
    int k,i,j,max=1;
    int arr[10];
    scanf("%d",&k);
    j=k;
    while (k-->0)
    	max*=10;
    for (int n=max/10;n<max;n++) 
    {
    	int n0=n,sum=0;
    	for (int m=0;m<j;m++)
    	{
    		arr[m]=n0%10;
    		n0/=10;
    		int arr0=arr[m];
    		for (int i=0;i<j-1;i++)
        		arr[m]*=arr0;
    	}
    	for (int i=0;i<j;i++)
        	sum+=arr[i];
        if (sum==n)
    	printf("%d  ",n);
    }
} 