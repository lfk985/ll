#include <stdio.h>
#include <sys/timeb.h>
#include <iostream>
using namespace std;
main() {
  timeb t1, t2;
  long t;
  int i, sum = 0;
  ftime(&t1);                   // 开始运算时的时间
  for (i = 1; i <= 1000 000; i++) {
    sum += i;
  }
  ftime(&t2);                   // 记录运算完的时间
  t = (t2.time - t1.time) / 1000 + (t2.millitm - t1.millitm);
  cout << t << endl;            // 输出计算1到100万的和一共用了多少毫秒
}