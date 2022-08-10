#include <stdio.h>
#include <wchar.h>
#include <locale.h>
int main(void) {
  setlocale(LC_ALL, "");
  	freopen("out.txt", "w", stdout);
  wchar_t xxx = 0x202e;
for (int i = 0; i < 32580; i++) {
   for (int z = 0; z < 32; z++) {
      putwchar(xxx++);
  }
  putchar('\n');
}
  return 0;
}