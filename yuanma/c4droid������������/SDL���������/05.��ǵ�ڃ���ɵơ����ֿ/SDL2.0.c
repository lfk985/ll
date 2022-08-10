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

   源码：SDL2音乐播放器
   作者：傻傻_痴痴
   来源：c4droid吧（欢迎加入交流）
   
   Version：1.1

 更新说明：
   1、修复播放歌曲完毕歌曲名称不改变bug，过滤ogg文件

 2、优化部分内存，释放垃圾内存
 
   更新日期：2014.4.20
   若要转载源码，请注明作者出处，禁止修改为自己名义发布源码

 */



/* 定义为SDL2 */
#ifndef _SDL2_
#define _SDL2_
#endif

#define LIST_NUM 10

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_thread.h>
#include <PlayMusic.c>



static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static TTF_Font *font = NULL;
const static SDL_Color color = { 0,0,0};
const static SDL_Color N_color = { 255, 255, 255 };

static SDL_Thread *thread;
static SDL_Surface *sur, *surName, *surWait;
static SDL_Texture *next, *upper, *artist, *b_artist, *play, *tex, *m_icon,
*texSearch, *texName, *texWait;
static SDL_Event event;

static int W, H;				/* 屏幕width，height */
static int LH, FW, FH, BW;		/* 列表高度，字体高度，按钮宽度 */

struct song *MyList;			/* 播放列表 */
static int Index = 1;			/* 用于引索列表 */

static int p = 0, nameX = 0, WaitFlag = 0;

/* 触摸X，Y坐标 */
static int TouchX, TouchY;

/* 是否扫描完毕 */
static bool FINDFINISH = false;

void init_SDL()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window =SDL_CreateWindow("Music Player", 0, 0, 480, 800,SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 30, 144, 255, 55);
	SDL_GetWindowSize(window, &W, &H);
	LH = H / 13;
	FH = H / 18;
	FW = W / 40;
	BW = W / 9;
	TTF_Init();
	font = TTF_OpenFont("/system/fonts/DroidSansFallback.ttf", 40);
}

/* 移动资源文件 */
void RemoveRES()
{
	system("mkdir -p /sdcard/Android/data/C4MusicPlayer");
	system("busybox tar -xf image.dat");
	system("busybox mv -f image/* /sdcard/Android/data/C4MusicPlayer/");
	system("busybox rmdir image/");
}

/* 启动资源文件 */
void InitRES()
{
	next =
		IMG_LoadTexture(renderer,	"/sdcard/Android/data/C4MusicPlayer/next.png");
	upper =
		IMG_LoadTexture(renderer,	"/sdcard/Android/data/C4MusicPlayer/upper.png");
	b_artist =
		IMG_LoadTexture(renderer,	"/sdcard/Android/data/C4MusicPlayer/b_artist.png");
	artist =
		IMG_LoadTexture(renderer,	"/sdcard/Android/data/C4MusicPlayer/artist.png");
	play =
		IMG_LoadTexture(renderer,	"/sdcard/Android/data/C4MusicPlayer/pause.png");
	m_icon =
		IMG_LoadTexture(renderer,	"/sdcard/Android/data/C4MusicPlayer/m_icon.png");
}

/* 绘制Texture函数 */
void RenderCopy(SDL_Renderer * ren, SDL_Texture * texture, float x, float y,float w, float h)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	offset.w = w;
	offset.h = h;
	SDL_RenderCopy(ren, texture, NULL, &offset);
}

/* 创建SDL_Rect函数 */
SDL_Rect CreateRect(int x, int y, int w, int h)
{
	SDL_Rect cr;
	cr.x = x;
	cr.y = y;
	cr.h = h;
	cr.w = w;
	return cr;
}

/* 绘制矩形函数，分别为：渲染器，是否填充，x，y，w，h，颜色 
 */

void DrawRect(SDL_Renderer * ren, bool isFill, int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Rect f_rect = CreateRect(x, y, w, h);
	/* 设置渲染器颜色 */
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	if (isFill)					/* 如果填充 */
		SDL_RenderFillRect(ren, &f_rect);
	else
		SDL_RenderDrawRect(ren, &f_rect);
}

/* 绘制背景 */
void drawBackground()
{
		/* 绘制背景矩形 */
	DrawRect(renderer, true, 0, 0, W, H, 255, 255, 255,0);
	/* 绘制顶部矩形 */
	DrawRect(renderer, true, 0, 0, W, LH, 255, 69, 0, 0);
	/* 绘制底部矩形 */
	DrawRect(renderer, true, 0, (LH) * 11, W, (LH) * 3, 255, 69, 0, 0);
	/* 分别绘制按钮 */
	RenderCopy(renderer, next, W / 1.2, H / 1.09, BW, BW);
	RenderCopy(renderer, upper, W / 3, H / 1.09, BW, BW);
	RenderCopy(renderer, play, W / 1.7, H / 1.09, BW, BW);
	RenderCopy(renderer, b_artist, 0, H / 1.20, W / 3, W / 3);
	RenderCopy(renderer, artist, 0, H / 1.18, W / 4, W / 4);
}

int GetTextW(char *ch)
{
	return strlen(ch) * FW;
}


/* 绘制歌曲列表 */
void drawListView()
{
	int i = 1;
	/* 创建当前顶部歌曲链表 */
	struct song *temp = MyList;
	/* 每个列表绘制十首 */
	while (i <= LIST_NUM && temp != NULL)
	{
		sur = TTF_RenderUTF8_Solid(font, temp->name, color);
		tex = SDL_CreateTextureFromSurface(renderer, sur);
		RenderCopy(renderer, tex, W / 9, LH * i, GetTextW(temp->name), FH);
		/* 分割线 */
		SDL_RenderDrawLine(renderer, 0, LH * i, W, LH * i);
		/* 歌曲图标 */
		RenderCopy(renderer, m_icon, 0, LH * i, W / 10, W / 10);
		SDL_FreeSurface(sur);
		SDL_DestroyTexture(tex);
		temp = temp->next;
		i++;
	}
}

/* 按钮是否按到，参数说明：按钮坐标位置，宽，高，触摸坐标 
 */
bool PressButton(int bx, int by, int bw, int bh, int tx, int ty)
{
	return (tx > bx && tx < (bx + bw)) && (ty > by&& ty < (by + bh)) ? true : false;
	/* 直接利用三目运算，虽然看着有点头晕 */
}

/* 获取触摸位置相对应的歌曲列表位置 */
int GetIndexTouch(int ty)
{
	return ty / LH - 1;
}


/* 绘制正在播放的歌曲名字 */
void drawName()
{
	if (ListNum == 0)
		return;
	char *name = indexSong(MySong, ListNum)->name;
	surName = TTF_RenderUTF8_Blended(font, name, N_color);
	texName = SDL_CreateTextureFromSurface(renderer, surName);
	RenderCopy(renderer, texName, W / 3.5, H / 1.18, GetTextW(name), FH);
	SDL_DestroyTexture(texName);
	SDL_FreeSurface(surName);
}

/* 改变播放，暂停图标 */
void changePlayIcon()
{
	SDL_DestroyTexture(play);
	if (PLAYSTATE == PLAYING)
	{
		play =IMG_LoadTexture(renderer,	"/sdcard/Android/data/C4MusicPlayer/play.png");
	}
	else
	{
		play =IMG_LoadTexture(renderer,	"/sdcard/Android/data/C4MusicPlayer/pause.png");
	}
}

/* 触屏监听，这里可能比较难理解 */
void onTouch()
{
	while (SDL_PollEvent(&event))
	{
		/* 获取触摸的x，y坐标 */
		TouchX = event.tfinger.x * W;
		TouchY = event.tfinger.y * H;
		switch (event.type)
		{
			/* 假如按下，设置p=1，主要用于区别移动跟按下操作 
			 */
		case SDL_FINGERDOWN:
			p = 1;
			break;
			/* 假如移动 */
		case SDL_FINGERMOTION:
			p = 2;				// p为2
			if (TouchY > LH * LIST_NUM || TouchY * H < LH * 2)
				break;			// 如果超出列表范围，直接跳出循环
			if (event.tfinger.dy > 0.015 && Index != 1)
			{
				/* 如果向下滑动，链表向上减 */
				Index--;
				MyList = indexSong(MySong, Index);
			}
			else if (event.tfinger.dy < -0.010 && Index != (MusicNum - 9))
			{
				/* 向上滑动，链表增加 */
				Index++;
				MyList = indexSong(MySong, Index);
			}
			break;
		case SDL_FINGERUP:
			/* 手指抬起 */
			if (p == 2)			/* 如果是滑动抬起，直接跳出 */
				break;
			/* 判断触摸的位置 */
			if (PressButton(W / 1.2, H / 1.09, BW, BW, TouchX, TouchY))
			{
				if (ListNum == 0)
					ListNum += 1;
				if (indexSong(MySong, ListNum) != NULL)
				{
					if (ListNum == 0)
						ListNum += 1;
					PlayNext(&ListNum);
					/* 播放下一曲 */
					changePlayIcon();
				}
				break;
			}
			if (PressButton(W / 3, H / 1.09, BW, BW, TouchX, TouchY))
			{
				if (ListNum == 0)
					ListNum += 1;
				if (indexSong(MySong, ListNum) != NULL)
				{
					PlayUpper(&ListNum);
					/* 播放上一曲 */
					changePlayIcon();
				}
				break;
			}
			if (PressButton(W / 1.7, H / 1.09, BW, BW, TouchX, TouchY))
			{
				if (ListNum == 0)
					ListNum += 1;
				if (indexSong(MySong, ListNum) != NULL)
				{
					PauseMUS();
					changePlayIcon();
					/* 暂停，播放 */
				}
				break;
			}
			/* 获取位置 */
			int n = GetIndexTouch(TouchY);
			if (n >= 0 && n < 10)
			{
				ListNum = Index + n;
				/* 如果是列表，则播放对应歌曲 */
				if (indexSong(MySong, ListNum) != NULL)
				{
					PlayMUS(indexSong(MySong, ListNum)->path);
					changePlayIcon();
				}
			}
			break;
		}
	}
}

/* 扫描歌曲线程 */
int thread01(void *data)
{
	SDL_Delay(100);
	InitMusic();
	MyList = MySong;
	RemoveRES();
	FINDFINISH = true;
	return 0;
}

/* 扫描文件等待动画 */
void drawInitThread()
{
	/* 当未扫描完成，一直播放动画 */
	while (FINDFINISH == false)
	{
		drawBackground();
		if (WaitFlag == 0)
			surWait =	TTF_RenderUTF8_Blended(font, "正在扫描音乐文件 ",color);
		else if (WaitFlag == 1)
			surWait =	TTF_RenderUTF8_Blended(font, "正在扫描音乐文件 . ",color);
		else if (WaitFlag == 2)
			surWait =	TTF_RenderUTF8_Blended(font, "正在扫描音乐文件 . . ",color);
		else
			surWait =	TTF_RenderUTF8_Blended(font, "正在扫描音乐文件 . . . ",color);
		texWait = SDL_CreateTextureFromSurface(renderer, surWait);
		RenderCopy(renderer, texWait, W / 6, H / 2.5, surWait->w, FH);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_FreeSurface(surWait);
		SDL_DestroyTexture(texWait);
		WaitFlag++;
		if (WaitFlag > 3)
			WaitFlag = 0;
		SDL_Delay(100);
	}
	/* 如果没有音乐文件 */
	while (MySong == NULL)
	{
		surWait = TTF_RenderUTF8_Blended(font, "未找到音乐文件", color);
		texWait = SDL_CreateTextureFromSurface(renderer, surWait);
		RenderCopy(renderer, texWait, W / 4, H / 2.5, surWait->w, surWait->h);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_FreeSurface(surWait);
		SDL_DestroyTexture(texWait);
	}
}

void Shutdown()
{
	PlayShutdown();
	SDL_FreeSurface(sur);
	SDL_FreeSurface(surName);
	SDL_FreeSurface(surWait);
	SDL_DestroyTexture(next);
	SDL_DestroyTexture(upper);
	SDL_DestroyTexture(artist);
	SDL_DestroyTexture(b_artist);
	SDL_DestroyTexture(play);
	SDL_DestroyTexture(tex);
	SDL_DestroyTexture(m_icon);
	SDL_DestroyTexture(texSearch);
	SDL_DestroyTexture(texName);
	SDL_DestroyTexture(texWait);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	init_SDL();
	/* 开辟线程 */
	thread = SDL_CreateThread(thread01, NULL, NULL);
	drawInitThread();
	InitRES();
	while (1)
	{
		onTouch();
		drawBackground();
		drawName();
		drawListView();
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}
	Shutdown();
	return 0;
}