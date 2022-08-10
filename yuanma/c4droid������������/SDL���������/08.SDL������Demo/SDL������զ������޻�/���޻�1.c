#include "SDL2/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "SDL.h"
#include "EVENT.h"

struct
{
  float x;
  float y;
  bool display;
} id[EVENT_IDNUM];

int main()
{
  Init(0x000000);
  int n;
  char s[5];
  int j;
  EVENT_Event event;
  SDL_Surface *p[5],*pt;
  for(int i=0;i<EVENT_IDNUM;i++)
  {
    sprintf(s,"%d",i);
    p[i]=Text(s,70,0xFFFFFF);
  }
  while(1)
  {
    j=0;
    for(int i=0;i<EVENT_IDNUM;i++)
    {
      if(!EVENT_Poll(i,&event))
        continue;
      j++;
      if(event.type==EVENT_DOWN||event.type==EVENT_MOTION)
      {
        id[i].x=event.tfinger.x;
        id[i].y=event.tfinger.y;
        id[i].display=true;
      }
      else if(event.type==EVENT_UP)
        id[i].display=false;
    }
    if(!j)
    {
      SDL_Delay(10);
      continue;
    }
    Clear();
    for(int i=0;i<EVENT_IDNUM;i++)
      if(id[i].display)
        Blit(p[i],id[i].x,id[i].y,0,0);
    n=EVENT_QueryIDNum();
    sprintf(s,"%d",n);
    pt=Text(s,30,0xFFFFFF);
    Blit(pt,0.9,0.05,0,0);
    SDL_FreeSurface(pt);
    Present();
  }
  return 0;
}