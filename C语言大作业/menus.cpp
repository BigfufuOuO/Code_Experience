#define _CRT_SECURE_NO_WARNINGS
#include<graphics.h>
#include<stdio.h>
#include "Zuma.h"
#pragma commment(lib,"Winmm.lib")

void menu_Main()//主菜单
{
	mciSendString("open C:\\Users\\admin\\Documents\\中科大\\计算机实验课\\大作业\\祖玛\\游戏资源\\音乐\\背景音乐.mp3 alias gemusic", NULL, 0, NULL); // 打开背景音乐
	mciSendString("play gemusic repeat", NULL, 0, NULL); // 循环播放

	putimage(0, 0, &background1);	// 显示背景
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50, 0, "黑体");
	outtextxy(Width * 0.3, Height * 0.2, "1 新游戏");
	
	outtextxy(Width * 0.3, Height * 0.4, "2 退出");
	settextstyle(30, 0, "黑体");
	outtextxy(Width * 0.3, Height * 0.6, "游戏规则");
	outtextxy(Width * 0.3, Height * 0.65, "鼠标移动控制抹茶旦旦转向");
	outtextxy(Width * 0.3, Height * 0.7, "鼠标左键发射弓箭");
	outtextxy(Width * 0.3, Height * 0.75, "鼠标右键改变弓箭颜色");
	outtextxy(Width * 0.3, Height * 0.8, "ESC键暂停游戏");
	outtextxy(Width * 0.3, Height * 0.85, "小球碰到城堡门游戏失败");

	FlushBatchDraw();//执行未完成的绘制任务
	Sleep(2);

	while (MouseHit())//检测当前是否有鼠标信息
	{
		m=GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.2 && m.y <= Height * 0.25)
			gameStatus = 1;//进入游戏
		
		else if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.3 && m.y <= Height * 0.5)
		{
			gameStatus = 3;//退出
			exit(0);
		}
	}
}

//void menu_Rules()//规则界面
//{
//	settextcolor(WHITE);
//	settextstyle(30, 0, "黑体");
//	outtextxy(Width * 0.3, Height * 0.2, "游戏规则");
//	outtextxy(Width * 0.3, Height * 0.3, "鼠标移动控制抹茶旦旦转向");
//	outtextxy(Width * 0.3, Height * 0.35, "鼠标左键发射弓箭");
//	outtextxy(Width * 0.3, Height * 0.4, "ESC键暂停游戏");
//	outtextxy(Width * 0.3, Height * 0.45, "小球碰到房顶游戏失败");
//	outtextxy(Width * 0.3, Height * 0.5, "返回主菜单");
//	while (MouseHit())//检测当前是否有鼠标信息
//	{
//		m=GetMouseMsg();
//		if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.5 && m.y <= Height * 0.55)
//			gameStatus = 0;
//	}
//}

void menu_Win()//胜利界面
{
	mciSendString("stop gemusic", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close gemusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open C:\\Users\\admin\\Documents\\中科大\\计算机实验课\\大作业\\祖玛\\游戏资源\\音乐\\胜利.mp3 alias winmusic", NULL, 0, NULL); // 打开胜利音乐
	mciSendString("play winmusic", NULL, 0, NULL); // 仅播放一次

	putimage(0, 0, &victory);	// 显示背景
	setbkmode(TRANSPARENT);

	settextcolor(WHITE);
	settextstyle(50, 0, "黑体");
	outtextxy(Width * 0.2, Height * 0.2, "恭喜！您的得分：");
	char s[10];
	sprintf(s, "%d", score);
	outtextxy(Width * 0.6, Height * 0.2, s);

	settextcolor(BLUE);
	settextstyle(60, 0, "黑体");
	outtextxy(Width * 0.1, Height * 0.4, "再玩一次？");


	settextcolor(WHITE);
	settextstyle(40, 0, "黑体");
	outtextxy(Width * 0.2, Height * 0.6, "冲！:)");

	settextcolor(WHITE);
	settextstyle(40, 0, "黑体");
	outtextxy(Width * 0.6, Height * 0.6, "不玩了:(");

	FlushBatchDraw();
	Sleep(2);

	while (MouseHit())//这个函数用于检测当前是否有鼠标信息
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.2 && m.x <= Width * 0.4 && m.y >= Height * 0.6 && m.y <= Height * 0.8)
		{
			startup();
			gameStatus = 1;//进行游戏
		}
		else if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.6 && m.x <= Width * 0.8 && m.y >= Height * 0.6 && m.y <= Height * 0.8)
		{
			gameStatus = 3;//退出游戏
			exit(0);
		}
	}

	system("pause");
}

void menu_Lose()//失败界面
{
	mciSendString("stop gemusic", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close gemusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
	mciSendString("open C:\\Users\\admin\\Documents\\中科大\\计算机实验课\\大作业\\祖玛\\游戏资源\\音乐\\失败.mp3 alias losemusic", NULL, 0, NULL); // 打开失败音乐
	mciSendString("play losemusic", NULL, 0, NULL); // 仅播放一次
	//POINT point[4] = {{0,0},{1000,0},{0,700},{1000,700}};
	//clearpolygon(point,4);
	putimage(0, 0, &defeat);	// 显示背景
	setbkmode(TRANSPARENT);

	settextcolor(WHITE);
	settextstyle(50, 0, "黑体");
	outtextxy(Width * 0.2, Height * 0.2, "很遗憾 您的得分：");
	char s[10];
	sprintf(s, "%d", score);
	outtextxy(Width * 0.6, Height * 0.2, s);

	//settextcolor(BLUE);
	//settextstyle(70, 0, "黑体");
	//outtextxy(Width * 0.1, Height * 0.4, "我在这里等着你回来.>_<.");

	//settextcolor(WHITE);
	//settextstyle(40, 0, "黑体");
	//outtextxy(Width * 0.2, Height * 0.6, "再玩一次");

	settextcolor(WHITE);
	settextstyle(40, 0, "黑体");
	outtextxy(Width * 0.4, Height * 0.6, "退出游戏");

	FlushBatchDraw();
	

	while (MouseHit())//这个函数用于检测当前是否有鼠标信息
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

void menu_Pause()//暂停界面
{
	putimage(0, 0, &background1);	// 显示背景
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(50, 0, "黑体");
	outtextxy(Width * 0.3, Height * 0.4, " 继续游戏");
	//outtextxy(Width * 0.3, Height * 0.3, "2 游戏规则");
	//outtextxy(Width * 0.3, Height * 0.4, "3 返回主菜单");

	FlushBatchDraw();//执行未完成的绘制任务
	Sleep(2);

	while (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.4 && m.y <= Height * 0.6)
			gameStatus = 1;
		//else if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.3 && m.y <= Height * 0.35)
		//{
		//	gameStatus = 2;//规则
		//}
		//else if (m.uMsg == WM_LBUTTONDOWN && m.x >= Width * 0.3 && m.x <= Width * 0.5 && m.y >= Height * 0.4 && m.y <= Height * 0.45)
		//{
		//	gameStatus = 0;
		//}
	}

}