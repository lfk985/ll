/*c4droid代码手册 
*乘法口诀表
 *TTHHR编写
  *转载请说明出处 */
   #include<stdio.h> 
   int main() 
   { 
   int i,j; 
   for (i=1;i<=9;i++)
    { 
    for (j=1;j<=9;j++)
    {
    	if(i*j>9)
     printf("%d  ",i*j);
     else
       printf(" %d  ",i*j);
     
    }
     printf("\n");
     } 
     return 0;
  }