/* strtok example */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* main */
int main(void) {
  char s[] = "http://www.cyuyan100.com";
  char *delim = ".";
  char *p;

  printf("%s\n", strtok(s, delim));
  
  while((p = strtok(NULL, delim)))
  {
    printf("%s\n", p);
  }  
  
  return EXIT_SUCCESS;
}