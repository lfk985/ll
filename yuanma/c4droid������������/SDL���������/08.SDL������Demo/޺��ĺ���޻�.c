/*c4droid代码手册
 *sdl2实现触控
 *傻傻_痴痴编写
 *TTHHT收集整理
 *转载请说明出处
*/
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_thread.h"
#include<stdio.h>
#include<string.h>

#define W 480
#define H 800

TTF_Font *font = NULL; //定义一个字体
SDL_Color color = { 178, 34, 34 };	// 设置字体颜色

	float x = 0, y = 0;			// 用于获取触控位置的坐标
	char ch[10];
	//用于储存x,y为字符串输出
	SDL_Thread*th=NULL;
	SDL_Event event;  //定义一个事件
	SDL_Surface *sur1 = NULL;  //定义刷屏表面
	SDL_Surface *sur2 = NULL;  //定义一个Surface表面用于显示字体
	SDL_Window *w = NULL;		// 创建一个窗口指针
	SDL_Renderer *ren = NULL;	// 创建一个渲染器指针
	SDL_Texture *tex1 = NULL;
	SDL_Texture *tex2 = NULL;	//在SDL2.0中得把Surface表面传递给Texture来实现硬件加速,再把图形显示在屏幕上
		SDL_Rect image;
		//设置一个矩形用于显示surface表面大小,如果不使用image的话图像拉伸得无法想象
void setFont()
{
	TTF_Init();					// 启动font
	font = TTF_OpenFont("/system/fonts/DroidSansFallback.ttf", 50);	// 打开系统自带字体并设置大小为50
}

int getTouch(void*data)
{
while (1)
{
while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_FINGERDOWN || event.type == SDL_FINGERMOTION)
			//当事件为触屏
			{
				x = event.tfinger.x;
				y = event.tfinger.y;
				//获取x,y的坐标
			}
		}
}
}

int main(int argc, char *argv[])
{
	bool q=false;
	image.x = 0;
	image.y = 100;
	image.h = 150;
	image.w = 500;
	w = SDL_CreateWindow("Touch Test",0,0,W,H,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_BORDERLESS);	// 配置窗口参数并创建 
ren = SDL_CreateRenderer(w, -1, SDL_RENDERER_PRESENTVSYNC);	// 为创建的窗口配置渲染器
	sur1 = SDL_CreateRGBSurface(0, W, H, 32, 0, 0, 0, 0);  //用于画一个矩形来刷屏
	SDL_FillRect(sur1, NULL, 0xffacca);
	//在sur1上画一个矩形
	tex1 = SDL_CreateTextureFromSurface(ren, sur1);  //把sur1传递给tex1
	setFont();
	th=SDL_CreateThread(getTouch,NULL,NULL);
		while (q==false )
	{
		SDL_RenderClear(ren);
				sprintf(ch, "X: %f    Y: %f",100*x,100*y);  //把坐标位置储存到ch字符串中,这里乘以100为了显示更方便直观
		sur2=TTF_RenderUTF8_Blended(font,ch,color); //让字符串生成surface表面并且传递给sur2
		tex2 = SDL_CreateTextureFromSurface(ren, sur2);
		SDL_FreeSurface(sur2);
		SDL_RenderCopy(ren, tex1, NULL, NULL);  //SDL2.0中是使用SDL_RenderCopy直接把Texture复制到窗口，而不是使用SDL_BlitSutface
			SDL_RenderCopy(ren, tex2, NULL, &image); 
		 //刷新屏幕
	SDL_DestroyTexture(tex2);
	SDL_RenderPresent(ren);
	}
	SDL_DestroyTexture(tex1);
	SDL_DestroyTexture(tex2);
	//释放Textrue
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(w);
    //释放渲染器和窗口并退出
}