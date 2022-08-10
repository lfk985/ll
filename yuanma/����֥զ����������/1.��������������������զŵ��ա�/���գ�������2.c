/* ctime example */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* main */
int main(void) {
  time_t timer;
  char *p;

  timer = time(NULL);
  p = ctime(&timer);
  printf("%s\n", p);

  return EXIT_SUCCESS;
}