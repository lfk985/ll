/*
基于SLES播放音频并滚动歌词Demo
by 千百度
for c4droid
注意!!!请修改 GCC或G++编译 参数:
在(c4droid:SRC)后面加个空格，再加上-lOpenSLES
g++修改后为

cd (c4droid:GCCROOT)tmpdir
export TEMP=(c4droid:GCCROOT)tmpdir
(c4droid:GCCROOT)bin/(c4droid:PREFIX)-g++ (c4droid:SRC) -lOpenSLES -lm -ldl -llog -lz -I(c4droid:CURSRCDIR) -std=c++14 -Wfatal-errors (c4droid:MODEARGS) -o (c4droid:BIN)
(c4droid:ERROUT)
*/
#include <stdlib.h>          //get环境变量路径值
 #include <unistd.h>        //pause()
#include <signal.h>        //signal()
#include <string.h>        //memset()
#include <sys/time.h>    //struct itimerval, setitimer()
#include <conio.h>         //gotoxy() clrscr();和stdio.h
#include "music.h"
#define STRLEN 256

int arr[STRLEN]={};
char str[STRLEN][STRLEN]={};
int k=0;
 
/*解析包含时间标签的LRC文件的字符串*/
void parse_lrc_line2(char *line)
{
    char *p = NULL;
    char *right = NULL;
    char *left = NULL;
    char buff[STRLEN] = {0};
    char *p2 = NULL;

    p = line;
    int n;
    //left为左边的[所在的位置
    left = strchr(p,'[');
    if (left == NULL)
    {
        return ;
    }
    //right为右边的]所在的位置
    right = strchr(p,']');
 
    while(right != NULL && left != NULL)
    {
        n = right - left - 1;
        strncpy(buff,left + 1,n);
        if (strstr(buff,"ar")||strstr(buff,"al")||strstr(buff,"ti")||strstr(buff,"off")||strstr(buff,"by"))
    return ;
    /*ASCII to int :字符数组的每个元素为一个ASCII(char型0到9)减48就是对应的int型0到9,然后转化为毫秒*/
    arr[k]=(((buff[0]-48)*10+(buff[1])-48)*60+(buff[3]-48)*10+(buff[4]-48))*1000+(buff[6]-48)*100+(buff[7]-48)*10;
        p2 = strrchr(p,']');
        if (p2 != NULL)
        {
            p2++;
            strcpy(str[k],p2[0]==10?"\0":p2);
        }
        k++; //这里把buff清空为\0。。反正总归要清空的，这样就不用计算字符串长度再补\0了
        memset(buff,'\0',n);
        p = right;
        //strchr函数只向后查找,把这段字符串划分成两个
        *p = '\0';
        p = p + 1;
        left = strchr(p,'[');
        if (left == NULL)
        {
            continue;
        }
        right = strchr(p,']');
    }
}
 
 void Swap(int *a,int *b,char *s1,char *s2)  //交换数值
{  
    int temp = *a;  
    *a = *b;  
    *b = temp; 
    char s[STRLEN]={};
    strcpy(s,s1);
    strcpy(s1,s2);
	strcpy(s2,s);
}

/* 冒泡排序算法 */
void BubbleSort(int *a,int len,char str[][STRLEN])
{  
    for(int i = len-1;i >=0 ;--i)  
    {  
        for(int j = i;j <=len-2 ;++j)  
        {
        	if(a[j] > a[j + 1])  
        		Swap(&a[j],&a[j + 1],str[j],str[j+1]);
        }  
    }
}

    /*创建/关闭定时器*/
static int timer_m = 0; //定时器计时变量
void printMes(int sig)
{ ++timer_m;
if (timer_m%100==0)
{
gotoxy(1,22);
printf("\e[32;1m-----------------------------------------------------------\n\t\t%02d : %02d\n\e[0m",timer_m/1000/60,timer_m/1000%60);
}
}
void CreateTimer()
{
	
	signal(SIGALRM, printMes);
    struct itimerval tick={};
    tick.it_value.tv_usec = 1000;
    tick.it_interval.tv_usec = 1000;
    setitimer(ITIMER_REAL, &tick, NULL);
}
void CloseTimer()
{
	struct itimerval tick={};
    setitimer(ITIMER_REAL, &tick, NULL);
}

void PlayMusic(char *Path)
{
	createEngine();   //创建声音引擎接口
    createUriAudioPlayer(Path);   //载入音源
    setPlayingUriAudioPlayer(true);   // 播放音乐
}

/*解析歌词文件*/
void ReadLrc(char *Path)
{
	
	FILE *f = NULL;
    char line[STRLEN] = {0};
    
    if ((f = fopen(Path,"r"))==NULL)
    {
    	printf("lrc歌词路径错误\n");
        return;
    };
    rewind(f);
    //读取每一行，并在其中解析
    while(fgets(line,STRLEN,f))
    {    //每行解析一次
        parse_lrc_line2(line);
    }
    fclose(f);
    BubbleSort(arr,k,str);
}

int main()
{
    //根据实际情况，自己修改路径
     char MusicFilePath[]="/storage/sdcard1/music/download/陈一发儿 - 童话镇/童话镇.mp3"; //MP3路径 
    char LrcFilePath[]="/storage/sdcard1/music/lyric/陈一发儿 - 童话镇.lrc";    //Lrc歌词路径
    printf("\033[?25l");
    CreateTimer();
    PlayMusic(MusicFilePath);
    ReadLrc(LrcFilePath);
    
    for (int i=0;i<k;)
    {
    	if (arr[i]<timer_m&&(i==k-1?1:timer_m<arr[i+1]))
    	{
            clrscr();
        	for (int j=i>10?i-10:0;j<i;j++)
        	{
        		if(str[j][0])
        	 	printf("\t\t\e[38;5;%dm%s",255+(j-i)*2,str[j]);       	    
        	}
        	if(str[i][0])
            printf("\t\t\e[36;4;1m%s\e[0m",str[i]);//滚动歌词 
            for (int j=i;j<i+10;j++)
            {
            	if(str[j+1][0])
                printf("\t\t\e[38;5;%dm%s",255-(j-i)*2,str[j+1]);
            }
            i++;
    	}
    }
   CloseTimer();
//    sleep(10);
    printf("\n\n\t谢谢欣赏\n");
    pause();
 //   return 0;
}