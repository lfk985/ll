/*c4droid代码手册
 *SDLFPS测试
 *傻傻_痴痴编写
 *TTHHR收集整理
 *转载请说明出处
*/
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

SDL_Surface *screen, *m;
TTF_Font *font;

	Uint32 rgb;
	float t = 0, p = 0, f = 0;
	int q=0;
	char c[10];
	
const int F = 20;
Uint8 r, g, b;
SDL_Event event;
SDL_Rect  rect;
SDL_Color color = { 255, 255, 255 };

void apply(int x, int y, SDL_Surface * a, SDL_Surface * b)
{
	SDL_Rect off;
	off.x = x;
	off.y = y;
	SDL_BlitSurface(a, NULL, b, &off);
}

int test()
{
	font =  TTF_OpenFont("/system/fonts/DroidSansFallback.ttf", 60);
	while (q==0)
	{
		t = SDL_GetTicks();
		sprintf(c, "FPS:%0.2f", f / (t / 1000));
		m = TTF_RenderUTF8_Solid(font, c, color);
		r += 1;
		g += 2;
		b += 3;
		rgb = SDL_MapRGB(screen->format, r, g, b);
		SDL_FillRect(screen,&rect,rgb);
apply(100, 200, m, screen);
SDL_Flip(screen);
		f++;
	}
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	screen =SDL_SetVideoMode(540, 960, 32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL);
	rect.x=0;
	rect.y=0;
	rect.h=960;
	rect.w=540;
	test();
while (q==0)
{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				q = 1;
			}
		}
}
  return 0;
}