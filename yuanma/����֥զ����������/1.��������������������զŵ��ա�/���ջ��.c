#include<stdio.h>
int main() {
  int a, b, i, n;
  for (a = 1; a <= 10000; a++) {
    for (b = 0, i = 1; i <= a / 2; i++)
      if (a % i == 0)
        b += i;
    for (n = 0, i = 1; i <= b / 2; i++)
      if (b % i == 0)
        n += i;
    if (n == a && a != b && a < b)
      printf("%d-%d\n", a, b);
  }
  return 0;
}