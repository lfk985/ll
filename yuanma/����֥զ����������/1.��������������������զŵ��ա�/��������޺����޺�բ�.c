#include <stdio.h>
int main(void)
{
	int i,j,e,k;
	printf("请输入等腰三角形的边长:");
	scanf("%d",&e);
	for(i=e;i>=0;i--)
	{
		for(j=i;j>=0;j--)
		printf("* ");
		printf("\n");		
	}
	return 0;
}