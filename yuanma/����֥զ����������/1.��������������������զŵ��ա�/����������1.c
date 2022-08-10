/* Sieve Prime 素数筛法 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* 
 * 把从1开始的、某一范围内的正整数从小到大顺序排列，1不是素数，首先把它筛掉。
 * 剩下的数中选择最小的数是素数，然后去掉它的倍数。依次类推，直到筛子为空时结束。
*/
/* M以内素数 */
const int M = 100;
int mark[M]; //1:prime number
int a=0;

void sieve_prime()
{
  for(int i=0; i <= M; i++)
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
          if(mark[j])
          {mark[j] = 0; a++;}
       }
    }
  }
}

int main(void)
{
  int i,j = 0;
  int k[23]={};
  int *p=k;
  sieve_prime();
  printf("%d范围内素数计算完成：\n",M);
  
  for(i=0;i<M;i++)
    if(mark[i])
      *p++=i;
     
printf("素数个数:%d\n",k[24]);
  return 0;
}