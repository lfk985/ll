#include <stdio.h>
#include <unistd.h>
// 绘制心形心形线方程：(x²+y²-1)³+x²y³ = 0 
main()
{
	printf("\e[?25h\e[35;1m");
	for (double y = 1.3f; y > -1.1f; y -= 0.1f)
	{
		for (double x = -1.5f; x < 1.5f; x += 0.05f)
		{
			double a = x * x + y * y - 1;
			printf("%s",a * a * a - x * x * y * y * y <= 0.0f ? "*": " ");
			setbuf(stdout,NULL);
			usleep(2000);
		}

		printf("\n");
	}
	printf("\e[6;18H\e[0;43;31mFavorite C language forever");
} 