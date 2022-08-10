#ifndef SDL.H
#define SDL.H 0
SDL_Window *g_win;
SDL_Renderer *g_ren;
int W,H;

Uint32 RGBToHex(int r,int g,int b)
{
  Uint32 hex=0;
  hex+=b;
  hex+=g*256;
  hex+=r*65536;
  return hex;
}

void HexToRGB(Uint32 hex,int *r,int *g,int *b)
{
  *b=hex%256;
  hex/=256;
  *g=hex%256;
  hex/=256;
  *r=hex%256;
  hex/=256;
}

void Blit(SDL_Surface *surface,float x,float y,float w,float h)
{
  if(!surface)
    return;
  SDL_Texture *texture=SDL_CreateTextureFromSurface(g_ren,surface);
  SDL_Rect rect;
  rect.x=x*W;
  rect.y=y*H;
  if(w<=0||h<=0)
    SDL_QueryTexture(texture,NULL,NULL,&(rect.w),&(rect.h));
  else
  {
    rect.w=(int)(w*W)?(w*W):1;
    rect.h=(int)(h*H)?(h*H):1;
  }
  if(rect.x<=W&&rect.x+rect.w>=0&&rect.y<=H&&rect.y+rect.h>=0)
  SDL_RenderCopy(g_ren,texture,NULL,&rect);
  SDL_DestroyTexture(texture);
}

void Clear()
{
  SDL_RenderClear(g_ren);
}

void Present()
{
  SDL_RenderPresent(g_ren);
}

//初始化
int Init(Uint32 color)
{
  int r,g,b;
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);
  HexToRGB(color,&r,&g,&b);
  SDL_CreateWindowAndRenderer(0,0,0,&g_win,&g_ren);
  SDL_GetWindowSize(g_win,&W,&H);
  SDL_SetRenderDrawColor(g_ren,r,g,b,255);
  SDL_RenderClear(g_ren);
  SDL_RenderPresent(g_ren);
  return 0;
}
//创建字体表面
SDL_Surface *Text(char *s,int fontsize,Uint32 colorHex)
{
  SDL_Color color;
  int r,g,b;
  HexToRGB(colorHex,&r,&g,&b);
  color.r=r;
  color.g=g;
  color.b=b;
  color.a=0;
  SDL_Surface *surface;
  static TTF_Font *library;
  static int size=0;
  if(fontsize<=0)
    return NULL;
  //新字体大小打开新字体库
  if(size!=fontsize)
  {
    if(library)
      TTF_CloseFont(library);
    size=fontsize;
    library=TTF_OpenFont("/system/fonts/DroidSansFallback.ttf",size*W/480);
  }
  surface=TTF_RenderUTF8_Blended(library,s,color);
  return surface;
}
//创建空表面
SDL_Surface *CreateSurface(float w,float h,Uint32 color)
{
  if(w<=0||h<=0)
    return NULL;
  if(w<1)
    w*=W;
  if(h<1)
    h*=H;
  SDL_Surface *surface=SDL_CreateRGBSurface(0,w,h,32,0,0,0,255);
  SDL_FillRect(surface,NULL,color);
  return surface;
}
#endif