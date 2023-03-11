#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<graphics.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#include "Zuma.h"

/*变量定义*/
int length = BallNumber;//需要消球的总数量
int gameStatus;
struct Zuma* head=NULL;
struct Zuma* tail=NULL;
IMAGE background1;//主菜单的背景
IMAGE background2;//游戏背景
IMAGE victory;//胜利背景
IMAGE defeat;//失败背景
IMAGE DanDan;//抹茶旦旦
IMAGE DanDan_Rotate;//旋转后的抹茶旦旦
MOUSEMSG m;//鼠标信息
int d_border;//距边框的距离
int balls_already_out;//吐出的球
double dandan_x, dandan_y;//抹茶旦旦中心坐标
double d_mx_daddan, d_my_dandan, d_m_dandan;//鼠标与佩奇的距离
double angle;//抹茶旦旦旋转角;
double x_initial[ballmax];//位置
double y_initial[ballmax];
double ball_radius;//半径
int color_initial[ballmax];//颜色
double speed_x_initial[ballmax];//速度
double speed_y_initial[ballmax];
int balls_next_restrict[BallpopNumber];//吐球插入或消失时，值为1，方可吐出下一个球
double ballreadypop_x, ballreadypop_y;//将要吐出的球的坐标
double ballpop_x[BallpopNumber], ballpop_y[BallpopNumber];//吐出的球的坐标
double ballpop_vx[BallpopNumber], ballpop_vy[BallpopNumber];//吐出球的速度
int colorpop[BallpopNumber];//吐球的颜色
double d_mx_ball, d_my_ball, d_m_ball;//鼠标离球的距离


void startup()//数据初始化
{
	gameStatus = 0;//主界面菜单

	d_border = 80;//离边框距离

	initgraph(Width, Height);//绘制画面

	HWND hwnd  =  GetHWnd();//获取窗口，与下句搭配
	SetWindowText(hwnd, "抹茶旦旦");

	loadimage(&background1, "C:\\Users\\admin\\Documents\\中科大\\计算机实验课\\大作业\\祖玛\\游戏资源\\图片\\背景.png");//放置背景
	putimage(0, 0, &background1);
	loadimage(&DanDan, "C:\\Users\\admin\\Documents\\中科大\\计算机实验课\\大作业\\祖玛\\游戏资源\\图片\\抹茶旦旦.png");
	loadimage(&victory, "C:\\Users\\admin\\Documents\\中科大\\计算机实验课\\大作业\\祖玛\\游戏资源\\图片\\victory.png");
	loadimage(&defeat, "C:\\Users\\admin\\Documents\\中科大\\计算机实验课\\大作业\\祖玛\\游戏资源\\图片\\defeat.png");

	BeginBatchDraw();

	angle = 0;//设置默认旋转角;

	/*吐球*/
	balls_already_out = 1;//初始化吐出的球
	balls_next_restrict[0] = 1;//第一个球吐出
	
	int i,j;//形式变量
	for(i=1;i<BallNumber;i++)
		balls_next_restrict[i]=0;

	/*出球*/
	//初始化小球位置
	x_initial[0]=40;
	for(i=1;i<BallNumber;i++)
		x_initial[i]=x_initial[i-1]-50;

	y_initial[0]=d_border;
	for(i=1;i<BallNumber;i++)
		y_initial[i]=y_initial[i-1];

	//初始化小球半径
	ball_radius=20;
	//初始化小球速度
	for(i=0;i<BallNumber;i++)
	{
		speed_x_initial[i]=0.2;
		speed_y_initial[i]=0;
	}


	//定义小球颜色
	int ColorRGB_const[5];
	ColorRGB_const[0]=RGB(255,255,0);//黄色
	ColorRGB_const[1]=RGB(255,0,0);//红色
	ColorRGB_const[2]=RGB(0,255,0);//绿色
	ColorRGB_const[3]=RGB(204,51,255);//蓝色
	ColorRGB_const[4] = RGB(255, 255, 255);//白色
	srand(time(NULL));

	for(i=0;i<BallNumber;i++)//初始化出球信息
	color_initial[i]=ColorRGB_const[rand()%5];//随机赋予小球
	
	//抹茶旦旦中心坐标;
	dandan_x=dandan_x_initial;
	dandan_y=dandan_y_initial;

	/*吐球*/
	//初始化吐出的小球
	
	colorpop[0]=color_initial[0];

	//创建链表
	for(i=1;i<BallpopNumber;i++)//初始化吐球的信息
	{
		ballpop_x[i]=ballreadypop_x;
		ballpop_y[i]=ballreadypop_y;
		ballpop_vx[i]=0;
		ballpop_vy[i]=0;
		colorpop[i]=ColorRGB_const[rand()%5];
	}

	Create_zuma(color_initial,x_initial,y_initial,speed_x_initial,speed_y_initial,BallNumber);//创建链表
	//初始菜单界面.
	while (gameStatus==0)
	{
		menu_Main();//初始菜单界面
	}
	
}

void show()//显示游玩界面
{
	//if (gameStatus == 2)
	//{
	//	menu_Rules();//规则界面
	//}
	while (gameStatus == 4)
	{
		menu_Pause();//按ESC后，显示暂停菜单
	}

	putimage(0, 0, &background1);	// 显示背景,背景就不会被擦掉
	dandanrotate();//显示抹茶旦旦
	putimage(dandan_x_initial-40,dandan_y_initial-40 ,&DanDan_Rotate);

	/*显示旦旦吐的球*/
	setcolor(WHITE);//小球轮廓颜色
	setfillcolor(colorpop[balls_already_out]);//设置填充颜色
	fillcircle((int)ballreadypop_x,(int)ballreadypop_y,ball_radius);//画圆填充

	/*显示吐球的轨迹*/
	popballs();//调用吐球函数
	if(balls_already_out>=2 && balls_next_restrict[balls_already_out-2]==1 && balls_next_restrict[balls_already_out-1]!=1)//可以吐球了，设置颜色
	{
		setcolor(WHITE);
		setfillcolor(colorpop[balls_already_out-1]);
		fillcircle((int)ballpop_x[balls_already_out-1],(int)ballpop_y[balls_already_out-1],ball_radius);
	}

	struct Zuma *p;
	p = (struct Zuma*)malloc(sizeof(struct Zuma));
	p = head;
	while (p->next != tail)
	{
        //隐藏小球（已删除）
		//行进中的小球速度
			//if( p->x <= (Width-d_border) && p->y == d_border)//行进  →
			//{
			//	p->speed_x=0.2;
			//	p->speed_y=0;
			//}
			//else if( p->x >= (Width-d_border) &&  (p->y <= (Height-d_border) && p->y >= d_border) )//行进↓
			//{
			//	p->speed_x=0;
			//	p->speed_y=0.2;
			//}
			//else if( p->x <= Width && p->x >= (Width-3*d_border) && p->y >= (Height-d_border) )//行进 ← 
			//{
			//	p->speed_x=-0.2;
			//	p->speed_y=0;
			//}

			//else if( p->x <= (Width-3*d_border) && (p->y >= 3*d_border && p->y <= Height))//行进↑
			//{
			//	p->speed_x=0;
			//	p->speed_y=-0.2;
			//}
			//else if( p->x <= (Width - 3 * d_border) && p->x >= (Width - 4*d_border) && p->y <= 3 * d_border)//行进←
			//{
			//	p->speed_x=-0.2;
			//	p->speed_y=0;
			//}
			//else if(p->x <= (Width-4*d_border) && p->y >= 0 && p->y <= (Height-d_border))//行进↓
			//{
			//	p->speed_x=0;
			//	p->speed_y=0.2;
			//}
			//else if(p->x >= 3.5*d_border && p->x <= (Width-7*d_border) && p->y >= (Height-d_border))//行进←
			//{
			//	p->speed_x=-0.2;
			//	p->speed_y=0;
			//}
			//else if( p->x <= 3.5*d_border && (p->y >= (Height-3*d_border) && p->y <= Height))//行进↑
			//{
			//	p->speed_x=0;
			//	p->speed_y=-0.2;
			//}
			if (p->x <= (Width - d_border) && p->y == d_border)//行进  →
			{
				p->speed_x = 0.2;
				p->speed_y = 0;
			}
			else if (p->x >= (Width - d_border) && (p->y <= (Height - d_border) && p->y >= d_border))
			{
				p->speed_x = 0;
				p->speed_y = 0.2;
			}
			else if ((p->x <= Width && p->x >= 3.5 * d_border) && p->y >= (Height - d_border)) //行进 ← 
			{
				p->speed_x = -0.2;
				p->speed_y = 0;
			}
			else if (p->x <= 3.5 * d_border && (p->y >= (Height - 3 * d_border) && p->y <= Height))//行进↑
			{
				p->speed_x = 0;
				p->speed_y = -0.2;
			}
			else if( p->speed_x==0 && p->speed_y==-0.2 && p->y<=(Height-3*d_border) && p->x<=3.5*d_border )
			{
				menu_Lose();
				break;
			}
		
        //球距过大则不移动球
		if (!(p->x>40 && (fabs((p->x) - (p->next->x))>50.0 || fabs((p->y)-(p->next->y))>50.0) && p->next!=tail->pre))
		{
			p->x += p->speed_x;
			p->y += p->speed_y;
		}

		//显示小球(已删除)
	
			setcolor(WHITE); // 小球的线条为白色
			setfillcolor(p->color);    // 小球内部位颜色填充
			fillcircle(p->x,p->y,ball_radius);
	
			//Sleep(1);
		
		p = p->next;
    }
	FlushBatchDraw();

	//显示实时得分
	//settextcolor(YELLOW);
	//settextstyle(20,0,"黑体");
	//outtextxy(Width*0.48,Height*0.95,"得分:");
	//char s[10];
	//sprintf(s,"%d",score);
	//settextcolor(YELLOW);
	//settextstyle(20,0,"黑体");
	//outtextxy(Width*0.55,Height*0.95,s);

}

void dandanrotate()//旦旦旋转
{
	loadimage(&DanDan, "C:\\Users\\admin\\Documents\\中科大\\计算机实验课\\大作业\\祖玛\\游戏资源\\图片\\抹茶旦旦.png");//加载旦旦图片

	if (MouseHit())
	{
		m=GetMouseMsg();
		if (m.uMsg==WM_MOUSEMOVE)	
		{
			d_mx_daddan=m.x-dandan_x_initial;
			d_my_dandan=m.y-dandan_y_initial;
			d_m_dandan = sqrt(d_mx_daddan* d_mx_daddan + d_my_dandan * d_my_dandan);//鼠标离旦旦的距离限制
			if (d_m_dandan>1.0)
			{

				if (m.x<dandan_x_initial)//因为arctanx函数的值域问题，要对鼠标的位置分类讨论
				{
					angle=atan(-d_my_dandan/d_mx_daddan)+PI;
					rotateimage(&DanDan_Rotate,&DanDan,angle,RGB(160,211,255),false,false);//旋转
							
					
					setcolor(TRANSPARENT);
					setfillcolor(TRANSPARENT);
					fillcircle((int)ballreadypop_x,(int)ballreadypop_y,ball_radius);
					//现在的小球圆心坐标
					ballreadypop_x=dandan_x+75*cos(angle);
					ballreadypop_y=dandan_y-75*sin(angle);

					
					
					
				}
				else if (m.x>dandan_x_initial)
				{
					angle=atan(-d_my_dandan/d_mx_daddan);
					rotateimage(&DanDan_Rotate,&DanDan,angle,RGB(160,211,255),false,false);//旋转
					
					//背景色覆盖之前的球
					setcolor(TRANSPARENT);
					setfillcolor(TRANSPARENT);
					fillcircle((int)ballreadypop_x,(int)ballreadypop_y,ball_radius);
					
					//现在的小球圆心坐标
					ballreadypop_x=dandan_x+75*cos(angle);
					ballreadypop_y=dandan_y-75*sin(angle);
					
				}
				
			}
			
		}
		
	}	
	
}


void popballs()//吐球
{
	if(MouseHit())//鼠标
	{
		m=GetMouseMsg();
		if(m.uMsg==WM_LBUTTONDOWN && balls_next_restrict[balls_already_out-1]==1)//左键点击吐球
		{
			/*播放吐球音乐*/
			mciSendString("stop music", NULL, 0, NULL);   // 先把前面一次的音乐停止
			mciSendString("close music", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open C:\\Users\\admin\\Documents\\中科大\\计算机实验课\\大作业\\祖玛\\游戏资源\\音乐\\射箭(吐球).mp3 alias gemusic", NULL, 0, NULL); // 打开吐球音乐
			mciSendString("play gemusic", NULL, 0, NULL); // 仅播放一次

			balls_already_out++;

			d_mx_ball=m.x-ballreadypop_x;//首先获取鼠标距离，为了求沿鼠标方向移动
			d_my_ball=m.y-ballreadypop_y;

			d_m_ball=sqrt(d_mx_ball*d_mx_ball+d_my_ball*d_my_ball);

			ballpop_vx[balls_already_out-1]=d_mx_ball/d_m_ball;
			ballpop_vy[balls_already_out-1]=d_my_ball/d_m_ball;
			
			ballpop_x[balls_already_out-1]=ballreadypop_x;
			ballpop_y[balls_already_out-1]=ballreadypop_y;

			

		}
		if(m.uMsg==WM_RBUTTONDOWN)//右键换颜色
		{
			balls_already_out++;

			ballpop_x[balls_already_out-1]=ballreadypop_x;
			ballpop_y[balls_already_out-1]=ballreadypop_y;

			balls_next_restrict[balls_already_out-1]=1;//换颜色后的球可以立即吐出
		}

	}

	if(balls_next_restrict[balls_already_out-2]==1 && balls_next_restrict[balls_already_out-1]!=1)//该球可以吐出
	{
		//覆盖小球(删除)

		//4倍吐出
		ballpop_x[balls_already_out-1] += 4*ballpop_vx[balls_already_out-1];
		ballpop_y[balls_already_out-1] += 4*ballpop_vy[balls_already_out-1];

		//Sleep(1);


	}

	if((ballpop_x[balls_already_out-1]>Width|| ballpop_x[balls_already_out-1]<0)
		|| (ballpop_y[balls_already_out-1]>Height || ballpop_y[balls_already_out-1]<0))//出界则可以吐下一个球
	{
		balls_next_restrict[balls_already_out-1]=1;
	}

	struct Zuma *p;
	p=head;
	double distant;
	double insert_x,insert_y;//吐球与出球距离. 用于判断吐球是否触及出球队列
	while(p->next!=tail)
	{
		insert_x=ballpop_x[balls_already_out-1]-p->x;
		insert_y=ballpop_y[balls_already_out-1]-p->y;

		distant=sqrt(insert_x*insert_x+insert_y*insert_y);//两点坐标公式
		
		if(distant<ball_radius && balls_next_restrict[balls_already_out-1]!=1)//若触及出球队列
		{
			//吐出的球取代p的位置
			ballpop_x[balls_already_out-1]=p->next->x;
			ballpop_y[balls_already_out-1]=p->next->y;
			ballpop_vx[balls_already_out-1]=p->next->speed_x;
			ballpop_vy[balls_already_out-1]=p->next->speed_y;//与下一球同步

			balls_next_restrict[balls_already_out-1]=1;//下一球可吐出


			struct Zuma *insertp=(struct Zuma*)malloc(sizeof(struct Zuma));
			
			insertp->color = colorpop[balls_already_out - 1];
			insertp->x = ballpop_x[balls_already_out - 1] ;
			insertp->y = ballpop_y[balls_already_out - 1];
			insertp->speed_x = ballpop_vx[balls_already_out - 1];
			insertp->speed_y = ballpop_vy[balls_already_out - 1];
			

			Insert(p,insertp);

			struct Zuma *move;
			move=p->next;
			while(move->next!=tail->pre)//链表倒数第二个退出
			{
				move->x=move->next->x;
				move->y=move->next->y;
				move=move->next;

			}
			move->x -= 300*move->speed_x;//
			move->y -= 300*move->speed_y;//

			

			Remove(insertp);
			break;//插入退出当前遍历链表的循环
			


		}
		else
			p=p->next;
	}
}

void gameover()
{
	EndBatchDraw();
	getch();
	closegraph();
}