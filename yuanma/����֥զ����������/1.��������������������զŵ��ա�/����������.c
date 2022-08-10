#include<iostream>
#include<cmath>
  using namespace std;
int main() {
  int N;
   cout << "请输入最大范围"<< endl;
  cin >> N;
  int Location[N+1];
  for (int i = 0; i != N + 1; ++i)
    Location[i] = i;
  Location[1] = 0;              // 筛除部分 
  int p, q, end;
  end = sqrt((double)N) + 1;
  for (p = 2; p != end; ++p) {
    if (Location[p]) {
      for (q = p; p * q <= N; ++q) {
        for (int k = p * q; k <= N; k *= p)
          Location[k] = 0;
      }
    }
  }
  int m = 0;
  for (int i = 1; i != N + 1; ++i) {
    if (Location[i] != 0) {
      cout << Location[i] << " ";
      ++m;
    }
  }
  cout << endl <<"总计";
  cout << m << endl;
  return 0;
}