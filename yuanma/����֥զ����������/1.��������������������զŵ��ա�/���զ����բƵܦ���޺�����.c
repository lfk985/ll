#include <stdio.h>
#include <time.h>
 #include <conio.h>
#define MMAX 9
int k=0;
int m_data[MMAX][MMAX] = {
};
bool Check(int x, int y, int num) {
  for (int i = 0; i < MMAX; i++) {
    if (m_data[x][i] == num || m_data[i][y] == num) {
      return false;
    }
  }
  int m = x / 3 * 3;
  int n = y / 3 * 3;
  for (int i = m; i < m + 3; i++) {
    for (int j = n; j < n + 3; j++) {
      if (m_data[i][j] == num) {
        return false;
      }
    }
  }
  return true;
}
bool Go(int index) {
	k++;
  if (index >= MMAX * MMAX) {
    return true;
  }
  int x = index / MMAX, y = index % MMAX;
  if (m_data[x][y] != 0) {
    return Go(index + 1);
  }
  for (int i = 0; i < MMAX; i++) {
    if (Check(x, y, i + 1)) {
      m_data[x][y] = i + 1;
      if (Go(index + 1)) {
        return true;
      } else {
        m_data[x][y] = 0;
      }
    }
  }
  return false;
}

void ShowData() {
  for (int i = 0; i < MMAX; i++) {
    for (int j = 0; j < MMAX; j++) {
      printf("%d ", m_data[i][j]);
    }
    printf("\n");
  }
}

int main() {
	char str[MMAX][MMAX];
	int ch;
	
	for (int i=0;i<MMAX;i++)
	{
	for (int j=0;j<MMAX;j++)
	{
		do
		ch=getch();
		while (ch==32||ch==10);
		str[i][j]=ch;
		m_data[i][j] = ch-48;
		printf("%c ",str[i][j]);
	}
	printf("\n");
	}
  time_t start, end;
  start = clock();
  if (Go(0)) {
    end = clock();
    printf("total time:%d ms\ncount=%d\n", end - start,k);
    ShowData();
  }
  return 0;
}
