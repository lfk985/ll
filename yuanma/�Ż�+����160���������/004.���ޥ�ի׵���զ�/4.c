/*
例程4. 比较实数大小
整理优化by:千百度QAIU
QQ:736226400
编译环境:gcc/tcc
2017/10/20
*/
/* 输入两个浮点数，输出它们中的大数 */
#include <stdio.h>
int main()
{
	float x,y,c;				/* 变量定义 */
	printf("Please input x and y:\n");	/* 提示用户输入数据 */
	scanf("%f%f",&x,&y);
	c=x>y?x:y;				/* 计算c=max(x,y) */
	printf("MAX of (%f,%f) is %f",x,y,c);	/* 输出c */
	return 0;
}