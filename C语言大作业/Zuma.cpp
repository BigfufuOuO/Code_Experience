#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include "Zuma.h"

int main()
{
	startup();//���ݳ�ʼ��
	while (1)//��Ϸѭ��ִ��
	{
		show();
		char input;
		if (kbhit())  // �ж��Ƿ�������
		{
			input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
			if (input == 27) // ESC����ACSII��Ϊ27
			{
				gameStatus = 4;
			}
		}

	}
	gameover();//��Ϸ��������������
	
	return 0;

}