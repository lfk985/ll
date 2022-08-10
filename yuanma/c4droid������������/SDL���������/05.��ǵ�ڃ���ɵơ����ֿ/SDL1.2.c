/*
c4droid代码手册
使用前说明
！！！！！！！！！！！！！！！
首先进入设置，找到G++参数设置（英文版G++ arguments），在(c4droid:SRC)后面加个空格，再加上-lOpenSLES，同时要与后面的参数留个空格，l是小写字母L，不是符号，也不是大写 i 。
修改后的参考：
cd (c4droid:GCCROOT)tmpdir
export TEMP=(c4droid:GCCROOT)tmpdir
(c4droid:GCCROOT)bin/(c4droid:PREFIX)-g++ (c4droid:SRC) -lOpenSLES -lm -ldl -llog -lz -I(c4droid:CURSRCDIR) -Wfatal-errors (c4droid:MODEARGS) -o (c4droid:BIN)
(c4droid:ERROUT)
！！！！！！！！！！！！！
*/
/* 

   源码：SDL1.2音乐播放器 作者：傻傻_痴痴

   来源：c4droid吧（欢迎加入交流）

   Version：1.1

   更新说明：
   1、修复播放歌曲完毕歌曲名称不改变bug

2、优化部分内存，释放垃圾内存

   更新日期：2014.4.20
 若要转载源码，请注明作者出处，禁止修改为自己名义发布源码


 */


#ifndef _SDL_
#define _SDL_
#endif

#include <PlayMusic.c>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_thread.h>

#define W 540
#define H 960

static TTF_Font *font = NULL;
static SDL_Color color = { 0, 0, 0 };
static SDL_Color N_color = { 255, 255, 255 };

static SDL_Surface *screen = NULL;
static SDL_Surface *background = NULL, *PlayName = NULL, *surWait=NULL,*sur=NULL;
static SDL_Event event;
static struct song *MyList;
SDL_Rect ChooseRect;
static int Index = 1;
static int chIndex = 1, WaitFlag = 0;
static SDL_Thread *thread;
static bool FINDFINISH = false;

/* 启动SDL */
void init_SDL()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(W, H, 32, SDL_RESIZABLE|SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);	// 设置屏幕
	TTF_Init();
	font = TTF_OpenFont("/system/fonts/DroidSansFallback.ttf", 30);
}

/* 准备资源 */
void InitRES()
{
	system("mkdir -p /sdcard/Android/data/C4MusicPlayer");
	system("busybox tar -xf image.dat");
	system("busybox mv -f image/* /sdcard/Android/data/C4MusicPlayer/");
	system("busybox rmdir image/");
	font = TTF_OpenFont("/system/fonts/DroidSansFallback.ttf", 30);
	background = IMG_Load("/sdcard/Android/data/C4MusicPlayer/background.png");
}

/* 绘制surface */
void SurfaceCopy(SDL_Surface * a, SDL_Surface * b, float x, float y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(b, NULL, a, &offset);
}

/* 创建SDL矩形 */
SDL_Rect CreateRect(int x, int y, int w, int h)
{
	SDL_Rect cr;
	cr.x = x;
	cr.y = y;
	cr.h = h;
	cr.w = w;
	return cr;
}

void drawBackground()
{
	SurfaceCopy(screen, background, 0, 0);
}

// 绘制选择条
void drawChoose()
{
	ChooseRect.y = (H / 13) * chIndex;
	SDL_FillRect(screen, &ChooseRect, 0xffcc99);
}

void drawSong(struct song *s)
{
	int i = 0;
	struct song *temp = s;
	while (i < 10 && temp != NULL)
	{
		i++;
		sur = TTF_RenderUTF8_Solid(font, temp->name, color);
		SurfaceCopy(screen, sur, W / 8, (H / 12.8) * i);
		SDL_FreeSurface(sur);
		temp = temp->next;
	}
}

void drawName()
{
	if (ListNum == 0)
		return;
	char *name = indexSong(MySong, ListNum)->name;
	PlayName = TTF_RenderUTF8_Solid(font, name, N_color);
	SurfaceCopy(screen, PlayName, W / 3.5, H / 1.13);
	SDL_FreeSurface(PlayName);
}

int onTouch(void*data)
{
	while (1)
	{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{

			case SDLK_DOWN:
				{
					if (chIndex > 0 && chIndex < 10)
					{
						chIndex++;
						break;
					}
					else if (chIndex == 10 && Index != (MusicNum - 9))
					{
						Index++;
						MyList = indexSong(MySong, Index);
					}
					break;
				}
			case SDLK_UP:
				{
					if (chIndex > 1 && chIndex <= 10)
					{
						chIndex--;
						break;
					}
					else if (chIndex == 1 && Index != 1)
					{
						Index--;
						MyList = indexSong(MySong, Index);
					}
					break;
				}
			case SDLK_RETURN:
				{
					ListNum = Index + chIndex - 1;
					struct song *p = indexSong(MySong, ListNum);
					if (p != NULL)
					{
						PlayMUS(p->path);
					}
					break;
				}
			case SDLK_LEFT:
				{
					if (ListNum == 0)
						ListNum += 1;
					if (indexSong(MySong, ListNum) != NULL)
					{
						PlayUpper(&ListNum);
					}
					break;
				}
			case SDLK_RIGHT:
				{
					if (ListNum == 0)
						ListNum += 1;
					if (indexSong(MySong, ListNum) != NULL)
					{
						PlayNext(&ListNum);
					}
					break;
				}
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
						case SDLK_RIGHT:
						SDL_Delay(200);
						break;
						case SDLK_LEFT:
						SDL_Delay(200);
						break;
						default:break;
			}
			break;
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			if (event.motion.yrel > 10 && Index != 1)
			{
				Index--;
				MyList = indexSong(MySong, Index);
			}
			else if (event.motion.yrel < -10 && Index != (MusicNum - 9))
			{
				Index++;
				MyList = indexSong(MySong, Index);
			}
		}
	}
	}
	return 0;
}

/* 线程01 */
int thread01(void *date)
{
	SDL_Delay(100);
	InitMusic();
	MyList = MySong;
	InitRES();
	FINDFINISH = true;
	return 0;
}

/* 绘制线程 */
void drawInitThread()
{
	while (!FINDFINISH)
	{
		SDL_FillRect(screen, &screen->clip_rect, 0xffffff);
		if (WaitFlag == 0)
			surWait =
				TTF_RenderUTF8_Blended(font, "正在扫描音乐文件 ",
									   color);
		else if (WaitFlag == 1)
			surWait =
				TTF_RenderUTF8_Blended(font, "正在扫描音乐文件 . ",
									   color);
		else if (WaitFlag == 2)
			surWait =
				TTF_RenderUTF8_Blended(font, "正在扫描音乐文件 . . ",
									   color);
		else
			surWait =
				TTF_RenderUTF8_Blended(font, "正在扫描音乐文件 . . . ",
									   color);
		SurfaceCopy(screen, surWait, W / 4, H / 2.5);
		SDL_Flip(screen);
		SDL_FreeSurface(surWait);
		WaitFlag++;
		if (WaitFlag > 3)
			WaitFlag = 0;
		SDL_Delay(100);
	}
	while (MySong == NULL)
	{
		SDL_FillRect(screen, &screen->clip_rect, 0xffffff);
		surWait = TTF_RenderUTF8_Blended(font, "未找到音乐文件", color);
		SurfaceCopy(screen, surWait, W / 4, H / 2.5);
		SDL_Flip(screen);
		SDL_FreeSurface(surWait);
	}
}

void Shutdown()
{
	PlayShutdown();
	SDL_FreeSurface(screen);
	SDL_FreeSurface(background);
	SDL_FreeSurface(PlayName);
	SDL_FreeSurface(surWait);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	init_SDL();
	ChooseRect = CreateRect(0, (H / 13), W, H / 13);
	thread = SDL_CreateThread(thread01, NULL);
	drawInitThread();
	SDL_KillThread(thread);
	thread = SDL_CreateThread(onTouch, NULL);
	while (1)
	{
		//onTouch();
		drawBackground();
		drawChoose();
		drawName();
		drawSong(MyList);
		SDL_Flip(screen);
	}
	Shutdown();
	return 0;
}