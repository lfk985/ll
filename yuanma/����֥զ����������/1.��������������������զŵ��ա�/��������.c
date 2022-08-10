#include<conio.h>
//命令行扩展色，输出加法表
int main()
{
	for(int k=0;;k++)
	{
	clrscr();
	for (int i=1;i<=9;i++)
	{
		for (int j=1;j<=i;j++)
			printf("\e[48;5;%d;38;5;%d;4m%d+%d=%-2d\e[0m ",(i+j*3+k)%233+16,(i+j*3+25+k)%233+16,i,j,i+j);
		printf("\n");
	}
	usleep(50000);
	}
}