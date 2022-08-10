#include <conio.h>
//画爱心(⑉°з°)-♡ by千百度 于2017七夕节
//运行后请收起输入法,不然显示不全
void print1(void )
{
	clrscr();
	  for (double y = 1.3f; y > -1.0f; y -= 0.095f)
    {
        for (double x = -1.5f; x < 1.5f; x += 0.05f)
        {
            double a = x * x + y * y - 1;
            putchar(a * a * a - x * x * y * y * y <= 0.0f ? '*' : ' ');
        }
        putchar('\n');
    }
}
void print2(void )
{
	clrscr();
	for (double y = 1.2f; y > -1.0f; y -= 0.095f)
    {
        for (double x = -1.5f; x < 1.5f; x += 0.05f)
        {
            double z = x * x + y * y - 1;
            double f = z * z * z - x * x * y * y * y;
            putchar(f <= 0.0f ? "ILOVEUUU"[(int)(f * -8.0)] : ' ');
            setbuf(stdout,NULL);
            usleep(10000);
        }
        putchar('\n');
    }
}
int main(void )
{
	printf("\033[?25l"); //隐藏光标
	printf("\e[36;1m设置字体大小不超过10点阵(建议9)\n请收起输入法\n5秒后程序自动开始\e[0m\n");
	usleep(5000000);
	for (int i=17;i<233;i++)
	{
	    print1();
	    printf("\e[38;5;%dmloading...%0.2lf%%\n",i%255,(i-17)/2.33);
    	usleep(100000);
	}
	printf("\e[35m");
	print2();
	printf("\n\t\t\e[36;1m特别的礼物🎁，送给特别的你\e[35m💝💘\n");//告白语，自己写
	return 0;
}