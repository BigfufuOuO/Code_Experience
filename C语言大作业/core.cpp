#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "Zuma.h"

long score = 0;//��ʼ����Ϸ����
using namespace std;
/*��������*/
void Create_zuma(int* color, double* x, double* y, double* speed_x, double* speed_y, int length)
{
	head = (struct Zuma*)malloc(sizeof(struct Zuma));
	head->color = color_initial[0];
	head->x = x_initial[0];
	head->y = y_initial[0];
	head->speed_x = speed_x_initial[0];
	head->speed_y = speed_y_initial[0];

	head->pre = NULL;

	Zuma* rear;    //����β�巨�е�βָ��
	rear = (struct Zuma*)malloc(sizeof(struct Zuma));
	rear = head;

	Zuma* p=NULL;

	for (int i = 1;i < length;i++)//β�巨
	{
		p = (struct Zuma*)malloc(sizeof(struct Zuma));
		p->color = color_initial[i];
		p->x = x_initial[i];
		p->y = y_initial[i];
		p->speed_x = speed_x_initial[i];
		p->speed_y = speed_y_initial[i];

		rear->next = p;
		p->pre = rear;
		rear = p;    //����
		rear->next = NULL;
	}
	tail = (struct Zuma*)malloc(sizeof(struct Zuma));//���һ�����
	tail = rear;

}

/*����p֮������³�������ball*/
void Insert(struct Zuma *p, struct Zuma *ball)
{
	if(NULL!=p->next)//���p�������һ����(˫������)
	{
		ball -> pre = p;
		ball->next = p->next;
		p->next->pre = ball;
		p-> next = ball;
	}
	else if(p->next==NULL)//ball������һ���� 
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
	//�����ȼ�1
	length++;

}

/*�ڲ���ball֮��������������ͬɫ����*/
void Remove(struct Zuma* ball)
{
	while (1)//ʵ����������
	{
		struct Zuma* before = ball->next;//ָ������ֵķ���
		struct Zuma* after = ball;//ָ���ͷ
		int count = 0;
		while(after!=head && after->color == ball->color)//���ͷ�������
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
			mciSendString("stop music", NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString("close music", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString("open C:\\Users\\admin\\Documents\\�пƴ�\\�����ʵ���\\����ҵ\\����\\��Ϸ��Դ\\����\\����.mp3 alias clearmusic", NULL, 0, NULL); // ����������
			mciSendString("play clearmusic", NULL, 0, NULL); // ������һ��
			
			length -= count;//�����ȸ���
			score += count * 1000;//�÷�����(�ɸ���)
			
			struct Zuma* p1, * p2;
			p1 = after->next;
			while (p1 != before)
			{
				p2 = p1->next;
				free(p1);
				p1 = p2;
			}
			after->next = before;

			if (before != NULL)//���������������һ��
				before->pre = after;
			if (length <= 1)//ʤ��
			{
				menu_Win();
			}
			ball = after;//��ϣ���ʵ����������
		}
		else
			break;
			
	}
}