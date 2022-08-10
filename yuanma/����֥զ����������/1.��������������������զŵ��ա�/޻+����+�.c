/* fread example */
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
  /*sample.dat内容为0051张三1队0055李四2队*/
  char *filename = "sample.dat";
  player p[10];

  /* 打开文件 */
  if ((fp = fopen(filename, "rb")) == NULL) {
    fprintf(stderr, "%s打开失败: %s\n",
      filename, strerror(errno));
    return EXIT_FAILURE;
  }

  for ( i = 0; i < 10; i++ ) {
    fread(&p[i].no, 1 ,8 ,fp);
//    p[i].no[8] = '\0';

    fread(&p[i].name, 1 ,32 ,fp);
//    p[i].name[32] = '\0';

    fread(&p[i].team, 1 ,8,fp);
//    p[i].team[8] = '\0';
  }
  
  for ( i = 0; i < 10; i++ ) {
    printf("%10s, %10s, %10s\n", p[i].no, p[i].name, p[i].team);
  }

  /* 关闭文件 */
  fclose(fp);

  return EXIT_SUCCESS;
}