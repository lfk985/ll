/*
素数筛法 验证哥德巴赫猜想
任何大于6的偶数都能写成两个素数之和
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* 
 *
素数筛法原理 把从1开始的、某一范围内的正整数从小到大顺序排列，1不是素数，首先把它筛掉。
 * 剩下的数中选择最小的数是素数，然后去掉它的倍数。依次类推，直到筛子为空时结束。
*/
/* M:要验证的偶数 */
#define M 12345678
int mark[M]; //1:prime number
long int sum=0;
int k[M];
int isp(int u)//素数判断
{
  if(u == 0 || u == 1)
    return 0;
  if(u == 2)
    return 1;
  if(u%2 == 0)
    return 0;
  for(int i=3;i <= sqrt((float)u);i+=2)
    if(u%i == 0)
      return 0;
  return 1;
}
void sieve_prime()//素数筛法
{
  for(int i=0; i <M; i++)
  {
    mark[i] = 1;
  }
  mark[0] = mark[1] = 0;
  for(int i=2; i <= sqrt((float)M); i++)
  {
    if(mark[i])
    {
      for(int j=i*i; j < M; j+=i)
      {
          if(mark[j]) { mark[j] = 0;sum++;}
      }
    }
  }
}

int main(void)
{
  int i,j = 0,n=0;
  long int m;
  sieve_prime();
  m=M-sum-2;
  
  for(i=0;i<M;i++)
  {
    if(mark[i])
    	k[j++]=i;
  }
  {
  for (i=0;i<m&&!isp(n);i++)
  	n=M-k[m-i];
      printf("计算结果\n%d-%d=%d",M,M-n,n);
  }
  return 0;
}