#include <stdio.h>        //printf()
#include <unistd.h>        //pause()
#include <signal.h>        //signal()
#include <string.h>        //memset()
#include <sys/time.h>    //struct itimerval, setitimer()

static int count = 0;

void printMes(int signo)
{
	
    printf("Get a SIGALRM, %d counts!\n", ++count);
}

int main()
{
    int res = 0;
    struct itimerval tick;
    signal(SIGALRM, printMes);
    memset(&tick, 0, sizeof(tick));

    //Timeout to run first time
    tick.it_value.tv_sec = 1;
    tick.it_value.tv_usec = 100000;

    //After first, the Interval time for clock
    tick.it_interval.tv_sec = 1;
    tick.it_interval.tv_usec = 100000;

    if(setitimer(ITIMER_REAL, &tick, NULL) < 0)
            printf("Set timer failed!");

    //When get a SIGALRM, the main process will enter another loop for pause()
    getchar();
   // while(1)
    {
//        pause();
    }
    return 0;
}