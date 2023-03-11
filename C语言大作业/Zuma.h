#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>

#pragma comment(lib,"Winmm.lib")//使用API

struct Zuma
{
	int color;//颜色
	double x;//x坐标
	double y;//y坐标
	double speed_x;//x方向速度
	double speed_y;//y方向速度
	Zuma* pre;//链表中上一个球
	Zuma* next;//链表中下一个球
};

extern struct Zuma* head;
extern struct Zuma* tail;

#define Width 1000
#define Height 700

#define BallNumber 200//需要消球数量 
#define BallpopNumber 200//吐球的个数（创建数组使用）
#define ballmax BallNumber+BallpopNumber//链表中最多的球

extern int length;//链表长度
extern long score;//游戏分数
extern int gameStatus;//游戏状态 0为菜单界面，1游戏中，2规则，3结束，4暂停，5失败，6胜利

/*游戏中的图片*/
extern IMAGE background1;//主菜单的背景
extern IMAGE victory;//胜利背景
extern IMAGE defeat;//失败背景
extern IMAGE DanDan_1,DanDan_2,DanDan_3;//抹茶旦旦（1代表黑底彩图，2代表白底黑图，3代表原图
extern IMAGE DanDan_Rotate;//旋转后的抹茶旦旦

extern MOUSEMSG m;//保存鼠标信息

/*用于初始化的杂乱数据*/
extern int d_border;//距边框的距离
extern int balls_already_out;//吐出的球
#define PI 3.1415926536


/*初始化出球的各种参数*/
extern double x_initial[ballmax];//位置
extern double y_initial[ballmax];
extern double ball_radius;//半径
extern int color_initial[ballmax];//颜色
extern double speed_x_initial[ballmax];//速度
extern double speed_y_initial[ballmax];


/*抹茶旦旦数据*/
#define dandan_x_initial Width/2 //坐标初始化
#define dandan_y_initial Height/2 //坐标初始化
extern double dandan_x, dandan_y;//抹茶旦旦中心坐标
extern double d_mx_daddan,d_my_dandan,d_m_dandan;//鼠标与佩奇的距离
extern double angle;//抹茶旦旦旋转角;

/*初始化吐球的各类数据*/
extern int balls_next_restrict[BallpopNumber];//吐球插入或消失时，值为1，方可吐出下一个球
extern double ballreadypop_x, ballreadypop_y;//将要吐出的球的坐标
extern double ballpop_x[BallpopNumber],ballpop_y[BallpopNumber];//吐出的球的坐标
extern double ballpop_vx[BallpopNumber],ballpop_vy[BallpopNumber];//吐出球的速度
extern int colorpop[BallpopNumber];//吐球的颜色

extern double d_mx_ball, d_my_ball, d_m_ball;//鼠标离球的距离


/*游戏运行核心*/
void Create_zuma(int* color, double* x, double* y, double* speed_x, double* speed_y, int length);//制作链表
void Insert(Zuma* p, Zuma* ball);//在球p之后插入吐出来的球ball
void Remove(Zuma* ball);//消除三个及以上的同色球


/*打印界面*/
void menu_Main();//主菜单
void menu_Rules();//规则界面
void menu_Win();//胜利界面
void menu_Lose();//失败界面
void menu_Pause();//暂停界面

/*游戏内容相关*/
void startup();//数据初始化
void show();//显示游玩界面
void dandanrotate();
void popballs();//吐球
void gameover();//游戏结束
