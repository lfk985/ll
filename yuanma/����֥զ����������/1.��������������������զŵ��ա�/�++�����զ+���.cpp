#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define EVEN_DOUBLE_4 4         // 双偶的最基本类型，4阶双偶
#define SCREEN_SIZE 19          // 屏幕显示不变形的最大尺寸（主要是因为窗口大小限制）
#define MIN_SIZE 3              // 最小阶数为3
#define MAX_SIZE 30
/* 原则上是任意阶，算法是相同的，这里就以30为上限吧，
   当然如果你愿意，可以修改的更大一些 */
#define PRINT printf("Esc退出，Enter继续"); // 打印的宏
#define CLEAR row = 0; column = 0; // 清零
int Magic[MAX_SIZE][MAX_SIZE] = { 0 }; // 全局，幻方数组
int row = 0, column = 0;        // 全局，幻方的行列数
int main(void) {
  int read();                   // 读取函数
  void odd(int size, int ini_value); // 奇数阶幻方生成
  void mean_double_4(int size); // 4阶双偶生成
  void mean_double(int size);   // 双偶生成
  void mean_single(int size);   // 单偶生成
  void print_magic(int size);   // 打印幻方
  void sum_print(int data[], int size); // 行、列、对之和打印
  void clear_sum(int data[]);
  void check_magic(int data[], int size); // 检查所得矩阵是否为幻方阵
  int size;                     // 幻方阶数
  int sum[2 * MAX_SIZE + 2] = { 0 }; // 行、列、对之和
  do {
    CLEAR clear_sum(sum);
    size = read();
    system("cls");
    if (size % 2 != 0)
      odd(size, 0);
    else if (size % 4 == 0)
      mean_double(size);
    else
      mean_single(size);
    print_magic(size);
    sum_print(sum, size);
    check_magic(sum, size);
  PRINT} while (getch() != 27);
  return 0;
}
/* 读入数据 */
int read() {
  int min_size = MIN_SIZE;
  int max_size = MAX_SIZE;
  int size;
  do {
    printf("请输入幻方阶数n，n∈[%d,%d]\n", min_size, max_size);
    scanf("%d", &size);
    getchar();
    if (size < 3 || size > MAX_SIZE)
      printf("非法输入，请重新输入[%d,%d]的正整数\n", min_size,
             max_size);
    else if (size > SCREEN_SIZE) {
      printf("大于屏显最大阶数，输出将变形\n");
      usleep(2000);
    }
  } while (size < MIN_SIZE || size > MAX_SIZE);
  return size;
}
/* 奇数阶幻方，采用house法 */
void odd(int size, int ini_value) {
  int num;                      // 填充数字
  int min_num = 1 + ini_value;
  int max_num = 1 + size * size + ini_value; // 填充范围
  int x = size / 2;
  int y = 0;                    // 初始填充坐标
  for (num = min_num; num < max_num; num++) {
    Magic[y + row][x + column] = num;
    if (num % size == 0)
      y++;                      // 跳步
    else
      x++, y += 2;              // 马步，其实Horse法和Siamese是完全类似的
    x = x % size;
    y = y % size;
    /* 越界反弹，即触碰到边界，从另一边返回 */
  }
}
/* 双偶数阶幻方，采用对调法 */
/* 对调法的基础，4阶双偶。注意要求是将非主副对角线上的元素对调，
   其实换个角度，你也可以说就是把祝福对角线中心对调。只不过两种思路得到的矩阵
   正好是反着来的 */
/* 本函数实现主副对角线互调 */
void mean_double_4(int size) {
  int i;
  int total = size * size + 1;
  for (i = 0; i < EVEN_DOUBLE_4; i++) {
    Magic[row + i][column + i] = total - Magic[row + i][column + i];
    Magic[row + i][EVEN_DOUBLE_4 + column - i - 1] =
      total - Magic[row + i][EVEN_DOUBLE_4 + column - i - 1];
  }
}
/* 任意阶双偶 */
void mean_double(int size) {
  int num;                      // 填充数字
  int min_num = 1;
  int max_num = 1 + size * size; // 填充范围
  int i = 0;                    // 循环变量
  int temp;
  /* 双偶，初始化 */
  for (num = min_num; num < max_num; num++) {
    Magic[row][column] = num;
    if ((num) % (size) == 0) {
      column = 0, row++;
    } else
      column++;
  }
  /* 分割为4×4的小矩阵 */
  row = 0;
  column = 0;
  temp = size / EVEN_DOUBLE_4;
  for (i = 1; i <= temp * temp; i++) {
    mean_double_4(size);
    if (i % temp == 0)
      column = 0, row += 4;
    else
      column = (i % temp) * EVEN_DOUBLE_4;
  }
}
/* 单偶，用楼梯法 */
void mean_single(int size) {
  int i, j, k, m;
  int temp;
  /* 分象限处理， 14 32
     与普通直角坐标系象限区别，说白了，就是个分块的概念 */
  row = 0, column = 0;          // 第一象限
  odd(size / 2, 0);
  row = size / 2, column = size / 2; // 第二象限
  odd(size / 2, (size * size) / 4 * 1);
  row = 0, column = size / 2;   // 第三象限
  odd(size / 2, (size * size) / 4 * 2);
  row = size / 2, column = 0;   // 第四象限
  odd(size / 2, (size * size) / 4 * 3);
  m = size / 4;
  /* 对换 */
  for (i = 0; i < size / 2; i++) {
    /* 1、3象限对换 */
    for (j = 0; j < m; j++) {
      if (i == m)
        k = j + m;
      else
        k = j;
      temp = Magic[i][k];
      Magic[i][k] = Magic[i + 2 * size / 4][k];
      Magic[i + 2 * size / 4][k] = temp;
    }
    /* 2，4对换 */
    for (j = 0; j < m - 1; j++) {
      k = 3 * size / 4 + j;
      temp = Magic[i][k];
      Magic[i][k] = Magic[i + 2 * size / 4][k];
      Magic[i + 2 * size / 4][k] = temp;
    }
  }
}
/* 打印幻方 */
void print_magic(int size) {
  int i, j;
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++) {
      printf("%4d", Magic[i][j]);
      if (j == size - 1)
        putchar('\n');
    }
  putchar('\n');
}
/* 打印各行、各列、各对角线数据之和 */
void sum_print(int data[], int size) {
  int i, j;
  /* 打印每行数据之和 */
  printf("行之和：");
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++) {
      data[i] += Magic[i][j];   // 行之和
      if (j == size - 1)
        printf("%6d", data[i]);
    }
  putchar('\n');
  /* 打印每列数据之和 */
  printf("列之和：");
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++) {
      data[size + i] += Magic[j][i]; // 列之和
      if (j == size - 1)
        printf("%6d", data[size + i]);
    }
  putchar('\n');
  /* 打印主对角线之和 */
  for (i = 0; i < size; i++)
    data[2 * size] += Magic[i][i];
  printf("主对角线之和：%6d", data[2 * size]);
  putchar('\n');
  /* 打印副对角线之和 */
  for (i = 0; i < size; i++)
    data[2 * size + 1] += Magic[i][size - i - 1];
  printf("主对角线之和：%6d", data[2 * size]);
  putchar('\n');
}
/* 行列对和数组清零 */
void clear_sum(int data[]) {
  int i;
  for (i = 0; i < 2 * MAX_SIZE; i++)
    data[i] = 0;
}
/* 检查程序是否运转正常，所得结果是否是幻方 */
void check_magic(int data[], int size) {
  int i;
  int flag = 0;
  for (i = 1; i < size + 2; i++)
    if (data[0] - data[i])
      flag = 1;
  if (flag)
    printf("程序出错，Esc退出，Enter继续\n");
  else
    printf("\n恭喜你，获得了一个新的%d阶幻方!\n",size);
  putchar('\n');
}