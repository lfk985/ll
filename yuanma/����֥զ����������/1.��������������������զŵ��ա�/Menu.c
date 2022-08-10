#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
int menu()
{
	printf("\033[?25l"); //隐藏光标
	printf("\033[47;34;5m\033[2J");
	int Game=1;
	while (1)
	{
		gotoxy(20, 12);
		if (Game == 1)
		printf("\033[44;37;1m 开始游戏 \033[0m");
		else
		printf("\033[47;30m 开始游戏 \033[0m");
		gotoxy(20, 14);
		if (Game == 2)
		printf("\033[44;37;1m 得分排行 \033[0m");
		else
		printf("\033[47;30m 得分排行 \033[0m");
		gotoxy(20, 16);
		if (Game == 3)
		printf("\033[44;37;1m 游戏帮助 \033[0m");
		else
		printf("\033[47;30m 游戏帮助 \033[0m");
		gotoxy(20, 18);
		if (Game == 4)
		printf("\033[44;37;1m 退出帮助 \033[0m");
		else
		printf("\033[47;30m 退出游戏 \033[0m");
		char ch = getch();
		switch (ch)
		{
			case '2':
			if (Game - 1 < 1)
			Game = 4;
			else
			Game--;
	    	break;
    		case '8':
    		if (Game + 1 > 4)
            Game = 1;
            else
            Game++;
            break;
            case '5':
            if (Game == 1)
            return 1;
            else
            if (Game == 2)
            return 2;
            else
            if (Game == 3)
            return 3;
            else
            exit(0);
            break;
            default:
            break;
        }
    }
    return 0;
}

int main()
{
  int k= menu();
  printf("k=%d",k);
}