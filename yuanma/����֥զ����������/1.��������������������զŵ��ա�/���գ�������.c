/* gmtime example */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* main */
int main(void) {
  time_t timer;
  struct tm *utc;

  timer = time(NULL);
  utc = gmtime(&timer);

  printf("UTC时间: \n");
  printf("%4d/", utc->tm_year + 1900);
  printf("%2d/", utc->tm_mon + 1);
  printf("%2d ", utc->tm_mday);
  printf("%2d:", (utc->tm_hour+8)%24);
  printf("%2d:", utc->tm_min);
  printf("%2d", utc->tm_sec);
  printf(" %d\n", utc->tm_isdst);

  return EXIT_SUCCESS;
}