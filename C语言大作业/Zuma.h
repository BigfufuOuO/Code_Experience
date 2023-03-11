#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>

#pragma comment(lib,"Winmm.lib")//ʹ��API

struct Zuma
{
	int color;//��ɫ
	double x;//x����
	double y;//y����
	double speed_x;//x�����ٶ�
	double speed_y;//y�����ٶ�
	Zuma* pre;//��������һ����
	Zuma* next;//��������һ����
};

extern struct Zuma* head;
extern struct Zuma* tail;

#define Width 1000
#define Height 700

#define BallNumber 200//��Ҫ�������� 
#define BallpopNumber 200//����ĸ�������������ʹ�ã�
#define ballmax BallNumber+BallpopNumber//������������

extern int length;//������
extern long score;//��Ϸ����
extern int gameStatus;//��Ϸ״̬ 0Ϊ�˵����棬1��Ϸ�У�2����3������4��ͣ��5ʧ�ܣ�6ʤ��

/*��Ϸ�е�ͼƬ*/
extern IMAGE background1;//���˵��ı���
extern IMAGE victory;//ʤ������
extern IMAGE defeat;//ʧ�ܱ���
extern IMAGE DanDan_1,DanDan_2,DanDan_3;//Ĩ�赩����1����ڵײ�ͼ��2����׵׺�ͼ��3����ԭͼ
extern IMAGE DanDan_Rotate;//��ת���Ĩ�赩��

extern MOUSEMSG m;//���������Ϣ

/*���ڳ�ʼ������������*/
extern int d_border;//��߿�ľ���
extern int balls_already_out;//�³�����
#define PI 3.1415926536


/*��ʼ������ĸ��ֲ���*/
extern double x_initial[ballmax];//λ��
extern double y_initial[ballmax];
extern double ball_radius;//�뾶
extern int color_initial[ballmax];//��ɫ
extern double speed_x_initial[ballmax];//�ٶ�
extern double speed_y_initial[ballmax];


/*Ĩ�赩������*/
#define dandan_x_initial Width/2 //�����ʼ��
#define dandan_y_initial Height/2 //�����ʼ��
extern double dandan_x, dandan_y;//Ĩ�赩����������
extern double d_mx_daddan,d_my_dandan,d_m_dandan;//���������ľ���
extern double angle;//Ĩ�赩����ת��;

/*��ʼ������ĸ�������*/
extern int balls_next_restrict[BallpopNumber];//����������ʧʱ��ֵΪ1�������³���һ����
extern double ballreadypop_x, ballreadypop_y;//��Ҫ�³����������
extern double ballpop_x[BallpopNumber],ballpop_y[BallpopNumber];//�³����������
extern double ballpop_vx[BallpopNumber],ballpop_vy[BallpopNumber];//�³�����ٶ�
extern int colorpop[BallpopNumber];//�������ɫ

extern double d_mx_ball, d_my_ball, d_m_ball;//�������ľ���


/*��Ϸ���к���*/
void Create_zuma(int* color, double* x, double* y, double* speed_x, double* speed_y, int length);//��������
void Insert(Zuma* p, Zuma* ball);//����p֮������³�������ball
void Remove(Zuma* ball);//�������������ϵ�ͬɫ��


/*��ӡ����*/
void menu_Main();//���˵�
void menu_Rules();//�������
void menu_Win();//ʤ������
void menu_Lose();//ʧ�ܽ���
void menu_Pause();//��ͣ����

/*��Ϸ�������*/
void startup();//���ݳ�ʼ��
void show();//��ʾ�������
void dandanrotate();
void popballs();//����
void gameover();//��Ϸ����
