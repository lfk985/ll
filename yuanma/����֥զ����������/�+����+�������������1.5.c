/*
Vi经典俄罗斯方块v1.5 (17.9.25)
by 千百度 2017-5-1 
最后修改时间: 17-9-25
请调整键盘高度为最低，建议字号10
更新日志:
v1.1
新增最高分
新增7种颜色的彩色方块
v1.3
使用汉字方块解决了方块对不齐的bug
优化旋转算法
v1.4
调整框使之闭合
使用emoji表情方块
v1.5
修复有时无法左移的bug
美化UI界面
修改随机算法
增加锁定延时 定时器bug
新增等级系统
方块落地后重置定时器
v1.51
下一版本:
可以自定义方块字符，颜色
新增详细排行系统
简易菜单
可设置游戏参数
踢墙规则
*/
#include <conio.h> //usleep() getch() stdio.h ……
#include <stdlib.h>  //rand()
#include <stdbool.h>  //bool类型
#include <pthread.h>  //多线程
#include <signal.h>        //signal()定时器信号函数
#include <sys/time.h>    //定时器struct itimerval, setitimer()

#define H 21
#define W 16
#define W0 5
#define T_SIZE 4
#define T0 800000

typedef struct
{
	int x[4][4];
	int y[4][4];
	int type;
}TETRIS;
TETRIS tet[8]={};//方块结构体

TETRIS GetTetris();//随机获取一组方块
void initmap();//初始化地图数据(缓冲画面)
void drawmap();//绘制地图 (打印画面)
void draw(int tim);//刷新一帧画面
void *refresh_map(void*p); //刷新地图，独立线程
void *event(void *);//按键事件监听，独立线程
bool can_move(TETRIS tet);//判断方块能否下落(是否触底)
void move(int delay);//下落一格，触底延时锁定
void CreateTimer(int t); //创建下落定时器
void SetTimer(int t); //设置定时器间隔时间
void TimerMove(int t);//定时执行的下降函数
TETRIS gyrate(TETRIS t);//旋转方块
void judge();//判断消除行得分
void loading();//载入游戏
void gameover();//游戏结束

#if 0
char str[7][16]= {     "💟💟","💚💚","💜💜","💖💖","💘💘","💛💛","❤️❤️"};//
#else
char str[7][16]= {"经","典","俄","罗","斯","方","块"};
#endif

// char str[7][16]= {"[]","[]","[]","[]","[]","[]","[]"};
// char str[7][16]= {"##","##","##","##","##","##","##"};


static int x1[7][4][4]=
{//方块横坐标
	{0,2,0,0,1,2,3,0},//T型方块
	{0,0,0,0,1,2,3,4},//I
	{0,2,3,0,0,2,3,0},//O
	{1,2,0,0,0,2,3,0},//Z
	{0,2,3,0,1,2,0,0},//S
	{1,0,0,0,1,2,3,0},//J
	{0,0,3,0,1,2,3,0}//L
	
},_y1[7][4][4]=
{//方块纵坐标
	{0,1,0,0,2,2,2,0},//T型方块
	{0,0,0,0,2,2,2,2},//I
	{0,1,1,0,0,2,2,0},//O
	{1,1,0,0,0,2,2,0},//Z
	{0,1,1,0,2,2,0,0},//S
	{1,0,0,0,2,2,2,0},//J
	{0,0,1,0,2,2,2,0}//L
};
enum //DIRECTION
{
	UP  = '2',
	DOWN = '5',
	LEFT = '4',
	RIGHT = '6',
	PAUSE = '0',
	DIRECT = ' ',
};

/*       int pau
暂停flag 用于控制子线程 
pau=-1 
暂停按键监听(将监听交给主线程)
暂停界面刷新
pau=0 
按键暂停 保持监听
pau=1
按键继续
*/
volatile int pau=1; 

/*       bool k
下降flag 用于确定下降和锁定 
k=0 下面没有方块阻挡可以下落
k=1 下面有方块阻挡应当锁定
*/
volatile bool k=0;  

volatile int t_sum[8]; //方块数统计
volatile int line_sum[5]={}; //消行数统计
volatile int top=0;  //最高分
volatile int score=0;  //分数
volatile int map[H+1][W+1];  //地图数组
volatile int t=T0;//步时 (下落速度)
volatile int lv=0,lv0=0;  //等级
volatile int history[4]={};  //历史方块记录
const char *filename = "sample.dat";//分值记录文件

//主函数
int main(void)
{
	loading();
	while(true) usleep(1000000000);
}
/*设置级别*/
void setlv()
{
	setbuf(stdin,NULL);
	printf("\e[5;20H\e[37m'5'键开始游戏\n");
	printf("\e[6;20H\e[37m'1'键设置级别\n");
	int k=getch();
	while( true )
	{
	if (k=='1')
	{
    	clrscr();
    	do
    	{
    		printf("请输入初始级别(0-32)\n ");
    		scanf("%d",&lv0);
    	} while (lv0>32||lv0<0);
    	break;
	}
	else if(k=='5') break;
	k=getch();
	}
	lv=lv0;
	t= lv>15?T0 /( lv*1.2):T0-lv*50000;
	setbuf(stdin,NULL);
	while(kbhit())	getch();	
}
/*暂停帮助*/
void help()
{

	printf("\e[9;20H\e[43;30m+------------+\n");
	printf("\e[18;20H\e[43;30m+------------+\n");
		printf("\e[10;20H\e[43;30m|\e[47;31m'4'或'a'左移\e[0;43;30m|\e[0m\n");
	printf("\e[11;20H\e[43;30m|\e[47;31m'6'或'd'右移\e[0;43;30m|\e[0m\n");
	printf("\e[12;20H\e[43;30m|\e[47;31m'2'或'w'旋转\e[0;43;30m|\e[0m\n");
	printf("\e[13;20H\e[43;30m|\e[47;31m'5'或's'下移\e[0;43;30m|\e[0m\n");
	printf("\e[14;20H\e[43;30m|\e[47;31m空格回车硬降\e[0;43;30m|\e[0m\n");
	printf("\e[15;20H\e[43;30m|\e[47;31m'0'或'p'暂停\e[0;43;30m|\e[0m\n");
	printf("\e[16;20H\e[43;30m|\e[47;30m使用\e[47;31m← \e[47;35m→ \e[31m↓ \e[35m↑ \e[0;43;30m|\e[0m\n");
	printf("\e[17;20H\e[0;43;30m|\e[0m\e[47;30m可以连续移动\e[0;43;30m|\e[0m\n");
}

//加载界面,初始化
void loading()
{
	FILE *fp;
	char readline[256] = {'\0'};
	if ((fp = fopen(filename, "r")) != NULL)
    {
    	fgets(readline, 64, fp);
        top=atoi(readline);
        fclose(fp);
    }
    else
    {
    	fopen(filename, "w");
    }
	printf("\e[?25l"); //隐藏光标
	srand(time(NULL));//初始化伪随机数生成器 
	for (int i=0;i<8;i++)
	tet[i]=GetTetris();
	draw(0);
	help();
	setlv();
	pthread_t pid1, pid2;
	pthread_create(&pid1, NULL, event, NULL);
	pthread_create(&pid2, NULL, refresh_map, NULL);
	CreateTimer(t);
}

void draw(int tim)
{
	initmap();
	clrscr();
	drawmap();
	usleep(tim);
}
void *refresh_map(void*p)
{
	while (true )
	{
		if (pau>0)
		    draw(50000);//刷新频率,每秒20帧 略微闪屏
	}
}

/*创建/关闭定时器*/
void TimerMove(int t)
{
	if (pau>0)
	move(200000);
}

void CreateTimer(int t)
{
	
	signal(SIGALRM, TimerMove);
    struct itimerval tick={};
    tick.it_value.tv_usec = t;
    tick.it_interval.tv_usec = t;
    setitimer(ITIMER_REAL, &tick, NULL);
}
void SetTimer(int t)
{
	struct itimerval tick={};
	tick.it_value.tv_usec = t;
    tick.it_interval.tv_usec = t;
    setitimer(ITIMER_REAL, &tick, NULL);
}

//初始化地图
void initmap(void)
{
	for (int i=0;i<=H;++i)//定义地图
	for (int j=0;j<=W;++j)
	{
		if ((i==H||i==0)&&j>=W0)
		map[i][j]=3;
		else if ((i==H||i==0)&&j<4)
		map[i][j]=-6;
		else if (j==W0||j==W)
		map[i][j]=2;
		else if (j==W0-1)
		map[i][j]=-7;
		else if (map[i][j]<W0-1)
		map[i][j]=0;
	}
	map[H][4]=map[0][W0-1]=-8;
	map[0][W]=map[H][W]=map[0][W0]=map[H][W0]=-2;
	for (int i=0;i<T_SIZE;i++)
	for (int j=0;j<T_SIZE;j++)
	{
		if (tet[0].y[i][j]!= 0&&tet[0].x[i][j]!= 0)
		{
		    map[tet[0].y[i][j]][tet[0].x[i][j]]=1;
	    	map[H][tet[0].x[i][j]]=11;
		}
		for (int k=1;k<=7;k++)
    	if (tet[k].y[i][j]!= 0&&tet[k].x[i][j]!= 0)
		    map[tet[k].y[i][j]+(k-1)*3][tet[k].x[i][j]-9]=-9-k;
	}
}
//获取随机方块
TETRIS GetTetris()
{
	TETRIS a;
    int k = (double)rand() / RAND_MAX*7;
    for (int i=0;i<4;i++)
    {
    	if (k!=history[0]&&k!=history[1]&&k!=history[2]&&k!=history[3])
    	break;
    	k = (double)rand() / RAND_MAX*7;
    }
    history[0]=history[1];
    history[1]=history[2];
    history[2]=history[3];
    history[3]=k;
//	k=1;                 //单个调试
	a.type=k;
	for (int i=0;i<T_SIZE;i++)
	for (int j=0;j<T_SIZE;j++)
	{
		a.x[i][j]=x1[k][i][j];
		a.y[i][j]=_y1[k][i][j];
		if (a.y[i][j]!= 0&&a.x[i][j]!= 0)
		a.x[i][j]+=8;
	}
	return a;
}
/*消除和得分*/
void judge(int high)
{
	pau=0;
	bool line[4]={};
	int sum=0;
	/*判断消行*/
	for (int i=high,k=0;i>high-4;i--)
	{
		line[k++]=true;
		for (int j=W0+1;j<W;j++)
		{
		if (map[i][j]<4)
		line[k-1]=false;
		}
	}	
	/*实现动态消行*/
	if (line[0]||line[1]||line[2]||line[3])
	{
		for (int j=0;j<5;j++)
		{
			for (int i=0;i<4;i++)
			{
				if (line[i])
				{
					map[high-i][11+j]=0;
					map[high-i][10-j]=0;
				}
			}
			clrscr();
			drawmap();
			usleep(50000);
		}
	}
	for (int i=high-3,k=3;i<=high;++i)
	{
		if (line[k--])
		{
			for (int j=i;j>1;--j)
			{
				for (int i=W0+1;i<W;++i)
				{
	    	    	map[j][i]=map[j-1][i];
				}
			}
			sum++;
		}
	}

	/*得分*/
	switch (sum)
	{
		case 1:
    	score+=(40*(lv+1));
    	line_sum[0]++;
    	break;
		case 2:
    	score+=(100*(lv+1));
    	line_sum[1]++;
    	break;
		case 3:
    	score+=(300*(lv+1));
    	line_sum[2]++;
    	break;
		case 4:
    	score+=(1200*(lv+1));
    	line_sum[3]++;
    	break;
	}
	line_sum[4]=0;
	for (int i=0;i<4;i++)
		line_sum[4]+=line_sum[i]*(i+1);
	lv=line_sum[4]/10+lv0;
	t= lv>15?T0 /( lv+1):T0-lv*50000;
	if (score>top)
	{
		top=score;
		FILE *fp;
        char str[256];
        sprintf(str,"%d",top);
        if ((fp = fopen(filename, "w")) != NULL)//打开文件
        fputs(str,fp);
        fclose(fp);
	}
			SetTimer(t);
		pau=1;
}

bool can_move(TETRIS tet)
{
	for (int i=0;i<T_SIZE;i++)
		for (int j=0;j<T_SIZE;j++)
		{
			if (map[tet.y[i][j]+1][tet.x[i][j]]>=3)
			{
				return true;
			}
		}
		return false;
}
//方块平移
void HorizontalMove(int fax)
{
	int flag=false;
	for (int i=0;i<T_SIZE;i++)
	{
		for (int j=0;j<T_SIZE;j++)
		{
			if (tet[0].x[i][j]&&(map[tet[0].y[i][j]][tet[0].x[i][j]+fax]==2||map[tet[0].y[i][j]][tet[0].x[i][j]+fax]>3||map[tet[0].y[i][j]][tet[0].x[i][j]+fax]<0))
			{
				flag=false;
				return;
			}
			else
			{
				flag=true;
			}
		}
	}
	if (flag)
	{
		for (int i=0;i<T_SIZE;i++)
		{
			for (int j=0;j<T_SIZE;j++)
			{
				if (tet[0].y[i][j]!= 0&&tet[0].x[i][j]!= 0)
			    	tet[0].x[i][j]+=fax;
			}
		}
	}	
	if (k=can_move(tet[0]))
	return;
}
//按键事件
void *event(void*p)
{
while( true )
{
	if (pau)
	while (kbhit())//判断输入，有则循环
	{
		int key = getch();//获取按键
		switch(key)
		{
			case 'C' :
			case RIGHT:
			case 'd':
			if (pau>0)
			HorizontalMove(1);
			break;
			case 'D':
			case 'a':
			case LEFT:
			if (pau>0)
			HorizontalMove(-1);
			break;
			case 'A':
			case UP:
			case 'w':
			if (pau>0)
			{
		    	tet[0]=gyrate(tet[0]);
	        	k=can_move(tet[0]);
		    }	
			break;
			case 'B':
			case 's':
			case DOWN:
			if (pau>0)
			move(0);
			break;
			case DIRECT:
			case 10:
			if (pau>0)
			{
				pau=false;
				usleep(5000);
				while(!k) move(0);
        		draw(0);
        		setbuf(stdin,NULL);
        		while(kbhit()) getch();
    			move(0);
    			pau=true;
			}
			break;
			case PAUSE:
			case 'p':
			pau=-pau;
			if (pau<0)
			{
				usleep(50000);
			//	clrscr();
				printf("\e[5;23H休息一下!");
				help();
			}		
			break;
		}
	}
	usleep(3000);
}
return NULL;
}

//方块下落
void move(int delay)
{
	if (!k)
	{
		k=can_move(tet[0]);
	for (int i=0;i<T_SIZE;i++)
	{
		for (int j=0;j<T_SIZE;j++)
		{
			if (map[tet[0].y[i][j]][tet[0].x[i][j]]<2)
			tet[0].y[i][j]++;
		}
	}
		k=can_move(tet[0]);
		return;
	}
	/*锁定延时*/
	SetTimer(0);
	usleep(250000);
	SetTimer(t);//锁定0.25s后 重启定时器
	if (!k) return;//通过按键监听 动态化k
	
	int high;
	for (int i=0;i<T_SIZE;i++)
	{
		for (int j=0;j<T_SIZE;j++)
		{
			if (tet[0].y[i][j]!= 0&&tet[0].x[i][j]!= 0)
			{
				map[tet[0].y[i][j]][tet[0].x[i][j]]=tet[0].type+4;
				high=tet[0].y[i][j];
			}
		}
	}
	
	if (map[2][8]>3||map[2][9]>3||map[2][10]>3||map[2][11]>3)
	{
	    gameover();
	}
	else
	{
		score+=high/2;
    	judge(high);
		t_sum[tet[0].type]++;
		t_sum[7]++;
		for (int i=0;i<7;i++)
	    	tet[i]=tet[i+1];
    	tet[7]=GetTetris();
		k=can_move(tet[1]);
	}
}
//游戏结束
void gameover()
{
	pau=false;
	usleep(5000);
	draw(1000);
	printf("\e[2;18H\e[47;30m游戏结束,回车继续\e[40;37m \n");
	lv0=k=0;
	score=line_sum[0]=line_sum[1]=line_sum[2]=line_sum[3]=0;
	getchar();
	usleep(1000);
	srand(time(NULL));
	for (int i=0;i<5;i++)
		tet[i]=GetTetris();
	for (int i=0;i<7;i++)
	t_sum[i]=0;
	for (int i=1;i<H;i++)
	{
		for (int j=1;j<W;j++)
		{
		map[i][j]=0;
		}
	}
	/*清除键盘缓冲区*/
	setbuf(stdin,NULL);
	while(kbhit())	getch();
	draw(1000);
	setlv();
	SetTimer(t);
	pau=true;
}
//绘制主界面
void drawmap()
{
	printf("   \e[31m+");
	for (int i=0;i<=H;i++)//画地图
	{
	for (int j=0;j<=W;j++)
	{
		switch(map[i][j])
		{
			case 0:
			printf("\e[40m  ");
			break;
			case -2:
			printf("\e[1;33m++\e[0m");
			break;
			case -6:
    		printf("\e[31m--\e[0m");
			break;
	    	case -7:
    		printf("\e[31m| \e[0m");
			break;
			case -8:
    		printf("\e[31m+ \e[0m");
    		break;
			case 2:
			printf("\e[1;33m||\e[0m");
			break;
			case 3:
			printf("\e[33;1m--\e[0m");
			break;
			case 11:
			printf("\e[3%d;1m==\e[0m",tet[0].type);
			break;
			case 1:
			printf("\e[47;3%dm%s\e[0m",tet[0].type,str[tet[0].type]);
			break;
			case -10:
			printf("\e[47;3%dm%s\e[0m",tet[1].type,str[tet[1].type]);
			break;
			case -11:
			printf("\e[47;3%dm%s\e[0m",tet[2].type,str[tet[2].type]);
			break;
			case -12:
			printf("\e[47;3%dm%s\e[0m",tet[3].type,str[tet[3].type]);
			break;
			case -13:
			printf("\e[47;3%dm%s\e[0m",tet[4].type,str[tet[4].type]);
			break;
			case -14:
			printf("\e[47;3%dm%s\e[0m",tet[5].type,str[tet[5].type]);
			break;
			case -15:
			printf("\e[47;3%dm%s\e[0m",tet[6].type,str[tet[6].type]);
			break;
			case -16:
			printf("\e[47;3%dm%s\e[0m",tet[7].type,str[tet[7].type]);
			break;
			default:
			printf("\e[4%d;37;%dm%s️\e[0m",map[i][j]-4,map[i][j]==4?5:2,str[map[i][j]-4]);
			break;
		}
	}
	printf("%s",i<=20?(i==20?"\n   \e[31m+\e[0m":"\n   \e[31m|\e[0m"):"\n    ");
	
	}
		if (score>=top)
		printf("\e[9;41H\e[36;1m新记录!\n");
		printf("\e[11;41H\e[34m| \e[37mT %03d\e[34m        |\n\e[12;41H\e[34m| \e[31mI %03d\e[34m        |\n\e[13;41H\e[34m| \e[32mO %03d\e[34m        |\n\e[14;41H\e[34m| \e[33mZ %03d \e[38;5;245m消1 %03d\e[34m|\n\e[15;41H\e[34m| \e[34;1mS %03d \e[38;5;247m消2 %03d\e[0;34m|\n\e[16;41H\e[34m| \e[35mJ %03d \e[38;5;248m消3 %03d\e[34m|\n\e[17;41H\e[34m| \e[36mL %03d \e[38;5;251m消4 %03d\e[34m|\n\e[19;41H\e[34m|  \e[33;1m%04d    \e[38;5;253m%04d\e[0;34m|\n\e[5;41H\e[32m| \e[33;1m 得分  %06d\e[0m\e[32m|\n\e[4;41H\e[32m| \e[32;1m 最佳  %06d\e[0m\e[32m|\n\e[6;41H\e[32m| \e[36;1m 级别  %02d    \e[0m\e[32m|\n\e[10;41H\e[34m+--------------+\n\e[18;41H\e[34m+\e[32m------\e[34;1msum\e[0;32m-----\e[34m+\n\e[20;41H\e[34m+--------------+\n\e[1;41H\e[32m+--------------+\n\e[3;41H\e[32m+--------------+\n\e[7;41H\e[32m+--------------+\n\e[2;41H\e[32m|  \e[38;5;248mTETRIS v1.5 \e[32m|\n\e[22;41H \e[36m ©千百度 2017\e[0m\n",t_sum[0],t_sum[1],t_sum[2],t_sum[3],line_sum[0],t_sum[4],line_sum[1],t_sum[5],line_sum[2],t_sum[6],line_sum[3],t_sum[7],line_sum[4],score,top,lv);
}
	/*方块的旋转*/
TETRIS gyrate(TETRIS t)
{
	bool k=true;
	TETRIS t0={};
	t0.type=t.type;
	if (t.type==2)//方块O不旋转
	return t;
	else if (t.type==1)//基于SRS(超级旋转系统)对I方块做特殊处理
	{
		if (t.x[1][0]!=0&&!map[t.y[1][2]-1][t.x[1][2]]&&!map[t.y[1][2]+1][t.x[1][2]]&&!map[t.y[1][2]+2][t.x[1][2]])
		{
			t.y[1][0]=t.y[1][1]=t.y[1][3]=t.x[1][0]=t.x[1][1]=t.x[1][3]=0;
		    t.y[0][2]=t.y[1][2]-1;
		    t.y[2][2]=t.y[1][2]+1;
		    t.y[3][2]=t.y[1][2]+2;
		    t.x[0][2]=t.x[2][2]=t.x[3][2]=t.x[1][2];
		}
		else if (t.x[0][2]!=0&&!map[t.y[2][2]][t.x[2][2]+1]&&!map[t.y[2][2]][t.x[2][2]-1]&&!map[t.y[2][2]][t.x[2][2]-2])
		{
			t.y[0][2]=t.y[1][2]=t.y[3][2]=t.x[0][2]=t.x[1][2]=t.x[3][2]=0;
		    t.x[2][0]=t.x[2][2]-2;
		    t.x[2][1]=t.x[2][2]-1;
		    t.x[2][3]=t.x[2][2]+1;
		    t.y[2][0]=t.y[2][1]=t.y[2][3]=t.y[2][2];
		}
		else if (t.x[2][0]!=0&&!map[t.y[2][1]+1][t.x[2][1]]&&!map[t.y[2][1]-1][t.x[2][1]]&&!map[t.y[2][1]-2][t.x[2][1]])
		{
			t.y[2][0]=t.y[2][2]=t.y[2][3]=t.x[2][0]=t.x[2][2]=t.x[2][3]=0;
		    t.y[0][1]=t.y[2][1]-2;
		    t.y[1][1]=t.y[2][1]-1;
		    t.y[3][1]=t.y[2][1]+1;
		    t.x[0][1]=t.x[1][1]=t.x[3][1]=t.x[2][1];
		}
		else if (t.x[0][1]!=0&&!map[t.y[1][1]][t.x[1][1]-1]&&!map[t.y[1][1]][t.x[1][1]+1]&&!map[t.y[1][1]][t.x[1][1]+2])
		{
			t.y[0][1]=t.y[2][1]=t.y[3][1]=t.x[0][1]=t.x[2][1]=t.x[3][1]=0;
		    t.x[1][0]=t.x[1][1]-1;
		    t.x[1][2]=t.x[1][1]+1;
		    t.x[1][3]=t.x[1][1]+2;
		    t.y[1][0]=t.y[1][2]=t.y[1][3]=t.y[1][1];
		}
		return t;
	}
	else
	{
	if (t.x[0][0]!=0)
	{
		t0.x[0][2]=t.x[0][0]+2;
		t0.y[0][2]=t.y[0][0];
		if (map[t0.y[0][2]][t0.x[0][2]]>1) 
		k=false;
	}
	if (t.x[0][1]!=0)
	{
		t0.x[1][2]=t.x[0][1]+1;
		t0.y[1][2]=t.y[0][1]+1;
		if (map[t0.y[1][2]][t0.x[1][2]]>1) 
		k=false;
	}
	if (t.x[0][2]!=0)
	{
		t0.x[2][2]=t.x[0][2];
		t0.y[2][2]=t.y[0][2]+2;
		if (map[t0.y[2][2]][t0.x[2][2]]>1) 
		k=0;
	}
	if (t.x[1][0]!=0)
	{
		t0.x[0][1]=t.x[1][0]+1;
		t0.y[0][1]=t.y[1][0]-1;
		if (map[t0.y[0][1]][t0.x[0][1]]>1) 
		k=false;
	}
	t0.x[1][1]=t.x[1][1];
	t0.y[1][1]=t.y[1][1];
	if (t.x[1][2]!=0)
	{
		t0.x[2][1]=t.x[1][2]-1;
		t0.y[2][1]=t.y[1][2]+1;
		if (map[t0.y[2][1]][t0.x[2][1]]>1) 
		k=false;
	}
	if (t.x[2][0]!=0)
	{
		t0.x[0][0]=t.x[2][0];
		t0.y[0][0]=t.y[2][0]-2;
		if (map[t0.y[0][0]][t0.x[0][0]]>1) 
		k=false;
	}
	if (t.x[2][1]!=0)
	{
		t0.x[1][0]=t.x[2][1]-1;
		t0.y[1][0]=t.y[2][1]-1;
		if (map[t0.y[1][0]][t0.x[1][0]]>1) 
		k=false;
	}
	if (t.x[2][2]!=0)
	{
		t0.x[2][0]=t.x[2][2]-2;
		t0.y[2][0]=t.y[2][2];
		if (map[t0.y[2][0]][t0.x[2][0]]>1) 
		k=false;
	} 
	return k?t0:t;
	}
}