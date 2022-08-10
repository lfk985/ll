#include<iostream>
using namespace std;
void swap(int &a, int &b) //实现a、b两个数据元素的简单交换
{
int t=a;
a=b;
b=t;
}
void swap(int &a, int &b, int &c) //实现三个元素最少交换次数的交换，使得a <= b <= c;其功能实现可由可由三个元素交换的分类讨论中得到
{
if((a>=b && b>c) || (a>b && b==c)) swap(a, c);
else if(a>b && b<c)
{
if(a<=c) swap(a,b);
else { swap(a,b); swap(b, c);}
}
else if(a<b && b>c)
{
if(a<=c) swap(b, c);
else { swap(b, c); swap(a, b);}
}
}
void swap(int A[], int a, int b, int c) //此函数实现转换功能，将数组调用简化为简单三个元素的比较交换
{
swap(A[a], A[b], A[c]);
}
int sortcheck(int A[], int n) //实现进位，并以返回值表示是否已经完成排序
{
int check=0;
for(int i=0; i+1<n; i+=2)
{
if(A[i]>A[i+1]){ swap(A[i], A[i+1]); check++;} //1步
if(i+2<n && A[i+1]>A[i+2]) check++; //2步
}
return check;
}
void sort(int A[], int n, int r=1) //实现二叉排序，主要对2步的对应元素排序
{ //其基本思想是将数组A的地址视作二叉树，通过对二叉树的排序实现功能，使 R <= L <= R 根节点值小于左子树值小于右子树值
if(2*r+1<=n)
{
swap(A, r-1, 2*r-1, 2*r);
sort(A, n, 2*r);
sort(A, n, 2*r+1);
swap(A, r-1, 2*r-1, 2*r); //此步为回溯算法，在左右子树子排序完成后对根结点重新排序
}
else if(2*r==n && A[r-1]>A[2*r-1]) swap(A[r-1],A[2*r-1]);
}
int Sort(int A[], int n) //此函数用于将排序总体包装方便调用
{
int count=0;
while(sortcheck(A, n)) //当排序未完成对1组的排序，
{
int r=1;
sort(A, n, r); //并调用2组排序
count ++;
}
return count; //以count的返回值可知两组排序一起结合工作被调用的次数
}
void BinarySort(int A[], int n)
{
cout<<endl<<"排序前数组为："<<endl;
for(int i=0; i<n; i++)cout<<A[i]<<" ";
cout<<endl;
cout<<endl<<"本次排序共经历"<<Sort(A,n)<<"个周期，参与排序排序元素"<<n<<"个"<<endl;
cout<<endl<<"排序后数组为："<<endl;
for(int i=0; i<n; i++)cout<<A[i]<<" ";
cout<<endl;
}
int main()
{
int A[35]={34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
BinarySort(A, 35);
}