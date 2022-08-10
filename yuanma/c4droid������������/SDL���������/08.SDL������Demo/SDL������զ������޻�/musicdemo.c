/*c4droid代码手册
*播放音乐
*/
#include <smpeg2/smpeg.h>
#include <SDL.h>
 int main()
 {
 	SDL_Init( SDL_INIT_EVERYTHING );
 	SMPEG_Info* info=NULL;
 	SMPEG* s=SMPEG_new("/sdcard/Music/空瓶氧气 许嵩.mp3", info,1);
 	
 	SMPEG_play(s);
 	
 	SDL_Delay( 500000 );
 	SDL_Quit();
 	return 0;
 }