#include<stdio.h>
/*
int rgb(int red, int green, int blue) {
  return 16 + (red * 36) + (green * 6) + blue;
}
*/
void reset(){
printf("\e[0m");
}
void hide(){
printf("\e[?25h");
}
int main() {
hide();
puts("\033[0mSystem color");
  for (int i = 0;i < 16; i++) {
        printf("\e[48;5;%dm ", i);
  }
  puts("\n\e[0mRgb color");
  for (int i = 16; i < 232; i++) {
        printf("\e[48;5;%dm    \e[0m", i);
        if ((i-15)%6==0){
        printf("\n");
        }
  }
  puts("\nGrayscale ramp:");
 for (int i = 232; i < 257; i++) {
        printf("\e[48;5;%dm 6", i);
        if (i%6==15){
        printf("\n");
        }
  }
  
  
  puts("\n");
puts("\033[0mSystem color");
  for (int i = 0;i < 16; i++) {
        printf("\e[38;5;%dm%02d  ", i,i);
  }
  puts("\nRgb color");
  for (int i = 16; i < 232; i++) {
        printf("\e[38;5;%dm %03d\e[0m", i,i-16);
        if ((i-15)%6==0){
        printf("\n");
        }
  }
  puts("\nGrayscale ramp:");
 for (int i = 232; i < 257; i++) {
        printf("\e[38;5;%dm %03d", i,i);
        if (i%36==15){
        printf("\n");
        }
  }
  return 0;
}