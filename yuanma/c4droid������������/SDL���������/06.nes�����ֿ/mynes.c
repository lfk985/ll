/**
  ******************************************************************************
  * 版本: 240*240
  * @version 002
  * @date 20140108
  * @b移植人员: LOTOOHE
  ******************************************************************************
  * @说明:源码来源于网络,作者佚名,属开源共享资源.
  * 以下的ROM,望各路高手共同优化,共享之.
  * 
  ******************************************************************************/

#include <SDL/SDL.h>
#include<string.h>
#include<stdlib.h>
#include "stdio.h"
#include"nes_main.c"
#include"JoyPad.c"
#include"6502.C"
#include"PPU.c"
// #include"mapper.c"
#define P_W 240
#define P_H 240

SDL_Surface *chuang = NULL;

extern void nes_main();
extern void startopcodetable(void);

int8 KEY[8];					// 按键逻辑 1:按下


int32 ROM_len;
unsigned char *rom_file;
// unsigned char *ram_nes; 
void keyscan(void)
{

}

void drawTxt(char *txt)
{
}

void keyinit(void)
{
	memset(KEY, 0, sizeof(KEY));

	// memset(ram_nes,0,256*1024); 
}

void setkey(void)
{

}

void Start()
{
	SDL_FillRect(chuang, &chuang->clip_rect, 0xffffff);
	SDL_Delay(500);
	nes_main();
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	chuang = SDL_SetVideoMode(P_W, P_H, 16, SDL_HWSURFACE);


	ROM_len = 0;
	rom_file = NULL;
	FILE *fp = NULL;
	fp = fopen("nes.nes", "rb");
	fseek(fp, 0, SEEK_END);
	ROM_len = ftell(fp);
	rewind(fp);
	rom_file = (unsigned char *)malloc(sizeof(unsigned char) * ROM_len);
	fread(rom_file, sizeof(unsigned char), ROM_len, fp);
	fclose(fp);
	// ram_nes =(unsigned char *)malloc(sizeof(unsigned char) * 256*1024); 
	keyinit();
	if (rom_file != NULL && ROM_len > 1024 && ROM_len <= 42 * 1024)
	{
		startopcodetable();
		Start();
	}
	return 0;
}