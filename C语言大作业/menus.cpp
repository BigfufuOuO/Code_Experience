#define _CRT_SECURE_NO_WARNINGS
#include<graphics.h>
#include<stdio.h>
#include "Zuma.h"
#pragma commment(lib,"Winmm.lib")

void menu_Main()//���˵�
{
	mciSendString("open C:\\Users\\admin\\Documents\\�пƴ�\\�����ʵ���\\����ҵ\\����\\��Ϸ��Դ\\����\\��������.mp3 alias gemusic", NULL, 0, NULL); // �򿪱�������
	mciSendString("play gemusic repeat", NULL, 0, NULL); // ѭ������

	putimage(0, 0, &background1);	// ��ʾ����
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, "����");
	outtextxy(Width * 0.3, Height * 0.2, "1 ����Ϸ");
	
	outtextxy(Width * 0.3, Height * 0.4, "2 �˳�");
	settextstyle(30, 0, "����");
	outtextxy(Width * 0.3, Height * 0.6, "��Ϸ����");
	outtextxy(Width * 0.3, Height * 0.65, "����ƶ�����Ĩ�赩��ת��");
	outtextxy(Width * 0.3, Height * 0.7, "���������乭��");
	outtextxy(Width * 0.3, Height * 0.75, "����Ҽ��ı乭����ɫ");
	outtextxy(Width * 0.3, Height * 0.8, "ESC����ͣ��Ϸ");
	outtextxy(Width * 0.3, Height * 0.85, "С�������Ǳ�����Ϸʧ��");

	FlushBatchDraw();//ִ��δ��ɵĻ�������
	Sleep(2);

	while (MouseHit())//��⵱ǰ�Ƿ��������Ϣ
	{
		m=GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.2 && m.y <= Height * 0.25)
			gameStatus = 1;//������Ϸ
		
		else if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.3 && m.y <= Height * 0.5)
		{
			gameStatus = 3;//�˳�
			exit(0);
		}
	}
}

//void menu_Rules()//�������
//{
//	settextcolor(WHITE);
//	settextstyle(30, 0, "����");
//	outtextxy(Width * 0.3, Height * 0.2, "��Ϸ����");
//	outtextxy(Width * 0.3, Height * 0.3, "����ƶ�����Ĩ�赩��ת��");
//	outtextxy(Width * 0.3, Height * 0.35, "���������乭��");
//	outtextxy(Width * 0.3, Height * 0.4, "ESC����ͣ��Ϸ");
//	outtextxy(Width * 0.3, Height * 0.45, "С������������Ϸʧ��");
//	outtextxy(Width * 0.3, Height * 0.5, "�������˵�");
//	while (MouseHit())//��⵱ǰ�Ƿ��������Ϣ
//	{
//		m=GetMouseMsg();
//		if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.5 && m.y <= Height * 0.55)
//			gameStatus = 0;
//	}
//}

void menu_Win()//ʤ������
{
	mciSendString("stop gemusic", NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
	mciSendString("close gemusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
	mciSendString("open C:\\Users\\admin\\Documents\\�пƴ�\\�����ʵ���\\����ҵ\\����\\��Ϸ��Դ\\����\\ʤ��.mp3 alias winmusic", NULL, 0, NULL); // ��ʤ������
	mciSendString("play winmusic", NULL, 0, NULL); // ������һ��

	putimage(0, 0, &victory);	// ��ʾ����
	setbkmode(TRANSPARENT);

	settextcolor(WHITE);
	settextstyle(50, 0, "����");
	outtextxy(Width * 0.2, Height * 0.2, "��ϲ�����ĵ÷֣�");
	char s[10];
	sprintf(s, "%d", score);
	outtextxy(Width * 0.6, Height * 0.2, s);

	settextcolor(BLUE);
	settextstyle(60, 0, "����");
	outtextxy(Width * 0.1, Height * 0.4, "����һ�Σ�");


	settextcolor(WHITE);
	settextstyle(40, 0, "����");
	outtextxy(Width * 0.2, Height * 0.6, "�壡:)");

	settextcolor(WHITE);
	settextstyle(40, 0, "����");
	outtextxy(Width * 0.6, Height * 0.6, "������:(");

	FlushBatchDraw();
	Sleep(2);

	while (MouseHit())//����������ڼ�⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.2 && m.x <= Width * 0.4 && m.y >= Height * 0.6 && m.y <= Height * 0.8)
		{
			startup();
			gameStatus = 1;//������Ϸ
		}
		else if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.6 && m.x <= Width * 0.8 && m.y >= Height * 0.6 && m.y <= Height * 0.8)
		{
			gameStatus = 3;//�˳���Ϸ
			exit(0);
		}
	}

	system("pause");
}

void menu_Lose()//ʧ�ܽ���
{
	mciSendString("stop gemusic", NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
	mciSendString("close gemusic", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
	mciSendString("open C:\\Users\\admin\\Documents\\�пƴ�\\�����ʵ���\\����ҵ\\����\\��Ϸ��Դ\\����\\ʧ��.mp3 alias losemusic", NULL, 0, NULL); // ��ʧ������
	mciSendString("play losemusic", NULL, 0, NULL); // ������һ��
	//POINT point[4] = {{0,0},{1000,0},{0,700},{1000,700}};
	//clearpolygon(point,4);
	putimage(0, 0, &defeat);	// ��ʾ����
	setbkmode(TRANSPARENT);

	settextcolor(WHITE);
	settextstyle(50, 0, "����");
	outtextxy(Width * 0.2, Height * 0.2, "���ź� ���ĵ÷֣�");
	char s[10];
	sprintf(s, "%d", score);
	outtextxy(Width * 0.6, Height * 0.2, s);

	//settextcolor(BLUE);
	//settextstyle(70, 0, "����");
	//outtextxy(Width * 0.1, Height * 0.4, "����������������.>_<.");

	//settextcolor(WHITE);
	//settextstyle(40, 0, "����");
	//outtextxy(Width * 0.2, Height * 0.6, "����һ��");

	settextcolor(WHITE);
	settextstyle(40, 0, "����");
	outtextxy(Width * 0.4, Height * 0.6, "�˳���Ϸ");

	FlushBatchDraw();
	

	while (MouseHit())//����������ڼ�⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		//if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.2 && m.x <= Width * 0.4 && m.y >= Height * 0.6 && m.y <= Height * 0.8)
		//{
		//	startup();
		//	gameStatus = 1;
		//}
		 if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.6 && m.y >= Height * 0.5 && m.y <= Height * 0.8)
		{
			gameStatus = 3;
			exit(0);
		}
	}
}

void menu_Pause()//��ͣ����
{
	putimage(0, 0, &background1);	// ��ʾ����
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(50, 0, "����");
	outtextxy(Width * 0.3, Height * 0.4, " ������Ϸ");
	//outtextxy(Width * 0.3, Height * 0.3, "2 ��Ϸ����");
	//outtextxy(Width * 0.3, Height * 0.4, "3 �������˵�");

	FlushBatchDraw();//ִ��δ��ɵĻ�������
	Sleep(2);

	while (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.4 && m.y <= Height * 0.6)
			gameStatus = 1;
		//else if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.3 && m.y <= Height * 0.35)
		//{
		//	gameStatus = 2;//����
		//}
		//else if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.4 && m.y <= Height * 0.45)
		//{
		//	gameStatus = 0;
		//}
	}

}