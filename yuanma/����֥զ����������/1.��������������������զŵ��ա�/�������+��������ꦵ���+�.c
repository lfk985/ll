/* fwrite example */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
  /* macros */
#define N 256
  /* structures */
  typedef struct player_tag {
  char no[N];
  char name[N];
  char team[N];
} player;

/* main */
int main(void) {
  int i;
  FILE *fp;
  char *filename = "sample.dat";
  player p[] = {
    {"第1名", "千百度", "120154"},
        {"第9名", "我我", "15756"},    {"0051", "馍馍呢我我", "1队"},    {"0051", "馍馍呢我我", "1队"},    {"0051", "馍馍呢我我", "1队"},    {"0051", "馍馍呢我我", "1队"},    {"0051", "馍馍呢我我", "1队"},    {"0051", "馍馍呢我我", "1队"},    {"0051", "馍馍呢我我", "1队"},    
    {"0055", "李四", "2队"}
  };

  /* 打开文件 */
  if ((fp = fopen(filename, "w")) == NULL) {
    fprintf(stderr, "%s打开失败: %s\n", filename, strerror(errno));
    return EXIT_FAILURE;
  }

  /* 写入 */
  for (i = 0; i < 10; i++) {
    fwrite(&p[i].no, 1, 8, fp);
    fwrite(&p[i].name, 1, 32, fp);
    fwrite(&p[i].team, 1, 8, fp);
  }

  printf("写入完毕．\n");

  /* 关闭文件 */
  fclose(fp);

  return EXIT_SUCCESS;
}