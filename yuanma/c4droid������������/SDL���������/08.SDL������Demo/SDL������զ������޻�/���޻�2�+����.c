#include "SDL2/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "SDL.h"
#include "EVENT.h"
#include<math.h>

int main()
{
  Init(0x000000);
  EVENT_Event event0,event1;
  float d1,d2;
  float x,y,w,h;
  SDL_Surface *p=Text("H",60,0xFFFFFF);
  w=(float)(p->w)/W;
  h=(float)(p->h)/H;
  x=(1-w)/2;
  y=(1-h)/2;
  while(1)
  {
    Clear();
    if(EVENT_QueryIDNum()==1)
    {
      if(!EVENT_Poll(0,&event0))
      {
        SDL_Delay(1);
        continue;
      }
      x+=event0.tfinger.dx;
      y+=event0.tfinger.dy;
    }
    if(EVENT_QueryIDNum()==2)
    {
      int i,j;
      i=EVENT_Poll(0,&event0);
      j=EVENT_Poll(1,&event1);
      if(i==0&&j==0)
      {
        SDL_Delay(1);
        continue;
      }
      if(event0.type==EVENT_DOWN||event1.type==EVENT_DOWN)
      {
        d1=sqrt((event0.tfinger.x-event1.tfinger.x)*(event0.tfinger.x-event1.tfinger.x)+(event0.tfinger.y-event1.tfinger.y)*(event0.tfinger.y-event1.tfinger.y));
        continue;
      }
      else
      {
        d2=sqrt((event0.tfinger.x-event1.tfinger.x)*(event0.tfinger.x-event1.tfinger.x)+(event0.tfinger.y-event1.tfinger.y)*(event0.tfinger.y-event1.tfinger.y));
        w+=(d2-d1)*0.05;
        h+=(d2-d1)*0.05;
        if(w<0||h<0)
        {
          w-=(d2-d1)*0.05;
          h-=(d2-d1)*0.05;
        }
        else
        {
          x-=(d2-d1)*0.05/2;
          y-=(d2-d1)*0.05/2;
        }
      }
    }
    Blit(p,x,y,w,h);
    Present();
  }
  return 0;
}