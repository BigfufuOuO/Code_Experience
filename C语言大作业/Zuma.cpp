#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include "Zuma.h"

int main()
{
	startup();//数据初始化
	while (1)//游戏循环执行
	{
		show();
		char input;
		if (kbhit())  // 判断是否有输入
		{
			input = getch();  // 根据用户的不同输入来移动，不必输入回车
			if (input == 27) // ESC键的ACSII码为27
			{
				gameStatus = 4;
			}
		}

	}
	gameover();//游戏结束，后续处理
	
	return 0;

}