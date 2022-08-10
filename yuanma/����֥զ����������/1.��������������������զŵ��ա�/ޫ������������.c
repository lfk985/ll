#include <time.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
/*

函数名称：int GetWeekDay(int year,int month,int day)
函数功能: 返回输入日期对应的一周中的第几天。
函数参数：year 输入日期的年；month 输入日期的月；day输入日期的日
         如：2000年1月1日则是GetWeekDay(2000,1,1)
*/
int GetWeekDay(int year,int month,int day)
{
    int i,j,count=0;
    int Day_Index;
    int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int MonthAdd[13] = {0,31,59,90,120,151,181,212,243,273,304,334,365};
    count = MonthAdd[month-1];
    count = count + day;
    if((year%4 == 0&&year %100 != 0||year % 400 == 0)&& month >= 3)
       count += 1;
    count = count + (year - 1901) * 365;
    for(j = 1901;j < year;j++)
    {
       if(j % 4 == 0 && j % 100 != 0 || j % 400 == 0)
           count++;
    }
    return ((count+1) % 7);
}

main()

{

    const char *Week[]={"星期日","星期一","星期二","星期三","星期四","星期五","星期六"};

    struct tm * Local;

    long t;

    int year,month,day;

#if 1

    //下面仅仅是拿当前的日期作为计算，当然你也可以用来计算其他的日期。

    //如：2000年1月1日则是GetWeekDay(2000,1,1)

    t = time(NULL);

    Local = localtime(&t);

    year = Local->tm_year + 1900;

    month = Local->tm_mon + 1;

    day = Local-> tm_mday;

    printf("%d年%d月%d日/t",year,month,day,GetWeekDay(year,month,day));

    puts(Week[GetWeekDay(year,month,day)]);

    //下面是访问tm结构体来得到当前是星期几

    printf("%d年%d月%d日/t",year,month,day);

    puts(Week[Local->tm_wday]);

#else

    year = 2006;

    month = 10;
    day = 1;
    printf("%d年%d月%d日/t",year,month,day);

    puts(Week[GetWeekDay(year,month,day)]);

#endif

//    system("pause");

}