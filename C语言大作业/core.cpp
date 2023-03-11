#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "Zuma.h"

long score = 0;//初始化游戏分数
using namespace std;
/*创建链表*/
void Create_zuma(int* color, double* x, double* y, double* speed_x, double* speed_y, int length)
{
	head = (struct Zuma*)malloc(sizeof(struct Zuma));
	head->color = color_initial[0];
	head->x = x_initial[0];
	head->y = y_initial[0];
	head->speed_x = speed_x_initial[0];
	head->speed_y = speed_y_initial[0];

	head->pre = NULL;

	Zuma* rear;    //定义尾插法中的尾指针
	rear = (struct Zuma*)malloc(sizeof(struct Zuma));
	rear = head;

	Zuma* p=NULL;

	for (int i = 1;i < length;i++)//尾插法
	{
		p = (struct Zuma*)malloc(sizeof(struct Zuma));
		p->color = color_initial[i];
		p->x = x_initial[i];
		p->y = y_initial[i];
		p->speed_x = speed_x_initial[i];
		p->speed_y = speed_y_initial[i];

		rear->next = p;
		p->pre = rear;
		rear = p;    //换针
		rear->next = NULL;
	}
	tail = (struct Zuma*)malloc(sizeof(struct Zuma));//最后一个结点
	tail = rear;

}

/*在球p之后插入吐出来的球ball*/
void Insert(struct Zuma *p, struct Zuma *ball)
{
	if(NULL!=p->next)//如果p不是最后一个球(双向链表)
	{
		ball -> pre = p;
		ball->next = p->next;
		p->next->pre = ball;
		p-> next = ball;
	}
	else if(p->next==NULL)//ball变成最后一个球 
	{
		ball->pre = p;
		ball->next = NULL;
		p->next = ball;
	}
	else
	{
		ball->pre=NULL;
		ball->next = p;
		p->pre=ball;

	}
	//链表长度加1
	length++;

}

/*在插入ball之后消除三个以上同色的球*/
void Remove(struct Zuma* ball)
{
	while (1)//实现连环消球
	{
		struct Zuma* before = ball->next;//指向球出现的方向
		struct Zuma* after = ball;//指向火车头
		int count = 0;
		while(after!=head && after->color == ball->color)//向火车头方向查重
		{
			after = after->pre;
			count++;
		}
		while (before != tail && before->color == ball->color)
		{
			before = before->next;
			count++;
		}

		if (count >= 3)
		{
			mciSendString("stop music", NULL, 0, NULL);   // 先把前面一次的音乐停止
			mciSendString("close music", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open C:\\Users\\admin\\Documents\\中科大\\计算机实验课\\大作业\\祖玛\\游戏资源\\音乐\\消球.mp3 alias clearmusic", NULL, 0, NULL); // 打开消球音乐
			mciSendString("play clearmusic", NULL, 0, NULL); // 仅播放一次
			
			length -= count;//链表长度更新
			score += count * 1000;//得分增加(可更改)
			
			struct Zuma* p1, * p2;
			p1 = after->next;
			while (p1 != before)
			{
				p2 = p1->next;
				free(p1);
				p1 = p2;
			}
			after->next = before;

			if (before != NULL)//如果消完的球不是最后一个
				before->pre = after;
			if (length <= 1)//胜利
			{
				menu_Win();
			}
			ball = after;//缝合，即实现连环消球
		}
		else
			break;
			
	}
}