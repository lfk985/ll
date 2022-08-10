#include <time.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

int getday(int year,int month,int day)
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
    return count+365;
}

int main()
{
	
	printf("%d",getday(1900,12,31));
}