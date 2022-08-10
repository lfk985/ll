#include <stdio.h>
#include <math.h>
#define Y 2099
#define K 19
char *solarterms[]={"        ",
"  \e[47;35m小寒  \e[0m","  \e[47;35m大寒  \e[0m","  \e[47;35m立春  \e[0m","  \e[47;35m雨水  \e[0m","  \e[47;35m惊蛰  \e[0m","  \e[47;35m春分  \e[0m","  \e[47;35m清明  \e[0m","  \e[47;35m谷雨  \e[0m","  \e[47;35m立夏  \e[0m","  \e[47;35m小满  \e[0m","  \e[47;35m芒种  \e[0m","  \e[47;35m夏至  \e[0m","  \e[47;35m小暑  \e[0m","  \e[47;35m大暑  \e[0m","  \e[47;35m立秋  \e[0m","  \e[47;35m处暑  \e[0m","  \e[47;35m白露  \e[0m","  \e[47;35m秋分  \e[0m","  \e[47;35m寒露  \e[0m","  \e[47;35m霜降  \e[0m","  \e[47;35m立冬  \e[0m","  \e[47;35m小雪  \e[0m","  \e[47;35m大雪  \e[0m","  \e[47;35m冬至  \e[0m"};
int main()
{
for (int i=73;i<133;i++)
for (int j=0;j<23;j++){
double a=365.242*(i)+6.2+15.22*j-1.9*sin(0.262*j);
    double b=365.242*(i)+6.18799+15.22567*j-1.9*sin(0.2618*j);
    if ((int)a!=(int)b)
    printf("%d  %d%s\n%f  %f\n\n",i+1900,j,solarterms[j+1],a,b);
}
	return 0;
}