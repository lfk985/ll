#include <conio.h>
#include <math.h>
#include <stdlib.h>

void drawline(char *s, int x0, int y0, int x1, int y1) 
{
  int dx, dy, epsl, k;
  float x, y, xIncre, yIncre;
  dx = x1 - x0;
  dy = y1 - y0;
  x = x0;
  y = y0;
  if (abs(dx) > abs(dy))
    epsl = abs(dx);
  else
    epsl = abs(dy);
  xIncre = (float)(dx) / epsl;
  yIncre = (float)(dy) / epsl;
  for (k = 0; k <= epsl; k++)
  {
    int tx = (int)(x + 0.5);
    int ty = (int)(y + 0.5);
    gotoxy(tx, ty);
    printf(s);
    x += xIncre;
    y += yIncre;
  }
}
int main() {
  int x0, y0, x1, y1;
//  drawline("*", 1, 1, 29, 22 );
   
     drawline("*",1,7,34,7); drawline("*",1,7,28,17); drawline("*",8,17,34,7);
     drawline("*",18,1,28,17); drawline("*",18,1,8,17); 


  return 0;
}