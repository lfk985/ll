/*c4droid代码手册
 *发送home键，后台运行
 *TTHHR编写
 *转载请说明出处
*/
#include<stdlib.h>
int main()
{
	system("su -c 'input keyevent 3'");
	return 0;
}