#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *func_1(void *)
{
  //  while(1){
        sleep(1);
        printf("this is func_1!\n");
 //    }
}

void *func_2(void*)
{
  while(1){
      usleep(2000000);
      printf("this is func_2!\n");
   }
}

int main()
{
    pthread_t pid1, pid2;

    pthread_create(&pid1, NULL, func_1, NULL);
    pthread_create(&pid2, NULL, func_2, NULL);
//while(1)
sleep(5);
//    return 0;
}