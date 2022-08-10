#include <stdio.h>
//绘制心形心形线方程：(x²+y²-1)³+x²y³ = 0 
int main() {
    for (double y = 1.3f; y > -1.0f; y -= 0.1f) {
        for (double x = -1.5f; x < 1.5f; x += 0.05f) {
            double a = x * x + y * y - 1;
            putchar(a * a * a - x * x * y * y * y <= 0.0f ? ' *' : '  ');
        }
        putchar('\n');
    }
}