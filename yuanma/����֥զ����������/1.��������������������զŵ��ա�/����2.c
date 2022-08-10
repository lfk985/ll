#include<stdio.h>
#define N 1000    //要计算的N
long s[N]={1,1},n=N,t=2,a=1,b=0;
int main()//雨中飞燕之作
{
    for(;a<=s[0]||(++t<=n?(b=0,a=1):0);(s[0]==a++&&b)?(s[0])++:0)
        s[a]=(b+=s[a]*t)%10000,b/=10000;
    for(printf("%d",s[s[0]]);--s[0]>0;)printf("%04d",s[s[0]]);
    return 0;
}