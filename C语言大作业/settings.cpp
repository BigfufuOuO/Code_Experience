#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<graphics.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#include "Zuma.h"

/*��������*/
int length = BallNumber;//��Ҫ�����������
int gameStatus;
struct Zuma* head=NULL;
struct Zuma* tail=NULL;
IMAGE background1;//���˵��ı���
IMAGE background2;//��Ϸ����
IMAGE victory;//ʤ������
IMAGE defeat;//ʧ�ܱ���
IMAGE DanDan;//Ĩ�赩��
IMAGE DanDan_Rotate;//��ת���Ĩ�赩��
MOUSEMSG m;//�����Ϣ
int d_border;//��߿�ľ���
int balls_already_out;//�³�����
double dandan_x, dandan_y;//Ĩ�赩����������
double d_mx_daddan, d_my_dandan, d_m_dandan;//���������ľ���
double angle;//Ĩ�赩����ת��;
double x_initial[ballmax];//λ��
double y_initial[ballmax];
double ball_radius;//�뾶
int color_initial[ballmax];//��ɫ
double speed_x_initial[ballmax];//�ٶ�
double speed_y_initial[ballmax];
int balls_next_restrict[BallpopNumber];//����������ʧʱ��ֵΪ1�������³���һ����
double ballreadypop_x, ballreadypop_y;//��Ҫ�³����������
double ballpop_x[BallpopNumber], ballpop_y[BallpopNumber];//�³����������
double ballpop_vx[BallpopNumber], ballpop_vy[BallpopNumber];//�³�����ٶ�
int colorpop[BallpopNumber];//�������ɫ
double d_mx_ball, d_my_ball, d_m_ball;//�������ľ���


void startup()//���ݳ�ʼ��
{
	gameStatus = 0;//������˵�

	d_border = 80;//��߿����

	initgraph(Width, Height);//���ƻ���

	HWND hwnd  =  GetHWnd();//��ȡ���ڣ����¾����
	SetWindowText(hwnd, "Ĩ�赩��");

	loadimage(&background1, "C:\\Users\\admin\\Documents\\�пƴ�\\�����ʵ���\\����ҵ\\����\\��Ϸ��Դ\\ͼƬ\\����.png");//���ñ���
	putimage(0, 0, &background1);
	loadimage(&DanDan, "C:\\Users\\admin\\Documents\\�пƴ�\\�����ʵ���\\����ҵ\\����\\��Ϸ��Դ\\ͼƬ\\Ĩ�赩��.png");
	loadimage(&victory, "C:\\Users\\admin\\Documents\\�пƴ�\\�����ʵ���\\����ҵ\\����\\��Ϸ��Դ\\ͼƬ\\victory.png");
	loadimage(&defeat, "C:\\Users\\admin\\Documents\\�пƴ�\\�����ʵ���\\����ҵ\\����\\��Ϸ��Դ\\ͼƬ\\defeat.png");

	BeginBatchDraw();

	angle = 0;//����Ĭ����ת��;

	/*����*/
	balls_already_out = 1;//��ʼ���³�����
	balls_next_restrict[0] = 1;//��һ�����³�
	
	int i,j;//��ʽ����
	for(i=1;i<BallNumber;i++)
		balls_next_restrict[i]=0;

	/*����*/
	//��ʼ��С��λ��
	x_initial[0]=40;
	for(i=1;i<BallNumber;i++)
		x_initial[i]=x_initial[i-1]-50;

	y_initial[0]=d_border;
	for(i=1;i<BallNumber;i++)
		y_initial[i]=y_initial[i-1];

	//��ʼ��С��뾶
	ball_radius=20;
	//��ʼ��С���ٶ�
	for(i=0;i<BallNumber;i++)
	{
		speed_x_initial[i]=0.2;
		speed_y_initial[i]=0;
	}


	//����С����ɫ
	int ColorRGB_const[5];
	ColorRGB_const[0]=RGB(255,255,0);//��ɫ
	ColorRGB_const[1]=RGB(255,0,0);//��ɫ
	ColorRGB_const[2]=RGB(0,255,0);//��ɫ
	ColorRGB_const[3]=RGB(204,51,255);//��ɫ
	ColorRGB_const[4] = RGB(255, 255, 255);//��ɫ
	srand(time(NULL));

	for(i=0;i<BallNumber;i++)//��ʼ��������Ϣ
	color_initial[i]=ColorRGB_const[rand()%5];//�������С��
	
	//Ĩ�赩����������;
	dandan_x=dandan_x_initial;
	dandan_y=dandan_y_initial;

	/*����*/
	//��ʼ���³���С��
	
	colorpop[0]=color_initial[0];

	//��������
	for(i=1;i<BallpopNumber;i++)//��ʼ���������Ϣ
	{
		ballpop_x[i]=ballreadypop_x;
		ballpop_y[i]=ballreadypop_y;
		ballpop_vx[i]=0;
		ballpop_vy[i]=0;
		colorpop[i]=ColorRGB_const[rand()%5];
	}

	Create_zuma(color_initial,x_initial,y_initial,speed_x_initial,speed_y_initial,BallNumber);//��������
	//��ʼ�˵�����.
	while (gameStatus==0)
	{
		menu_Main();//��ʼ�˵�����
	}
	
}

void show()//��ʾ�������
{
	//if (gameStatus == 2)
	//{
	//	menu_Rules();//�������
	//}
	while (gameStatus == 4)
	{
		menu_Pause();//��ESC����ʾ��ͣ�˵�
	}

	putimage(0, 0, &background1);	// ��ʾ����,�����Ͳ��ᱻ����
	dandanrotate();//��ʾĨ�赩��
	putimage(dandan_x_initial-40,dandan_y_initial-40 ,&DanDan_Rotate);

	/*��ʾ�����µ���*/
	setcolor(WHITE);//С��������ɫ
	setfillcolor(colorpop[balls_already_out]);//���������ɫ
	fillcircle((int)ballreadypop_x,(int)ballreadypop_y,ball_radius);//��Բ���

	/*��ʾ����Ĺ켣*/
	popballs();//����������
	if(balls_already_out>=2 && balls_next_restrict[balls_already_out-2]==1 && balls_next_restrict[balls_already_out-1]!=1)//���������ˣ�������ɫ
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
        //����С����ɾ����
		//�н��е�С���ٶ�
			//if( p->x <= (Width-d_border) && p->y == d_border)//�н�  ��
			//{
			//	p->speed_x=0.2;
			//	p->speed_y=0;
			//}
			//else if( p->x >= (Width-d_border) &&  (p->y <= (Height-d_border) && p->y >= d_border) )//�н���
			//{
			//	p->speed_x=0;
			//	p->speed_y=0.2;
			//}
			//else if( p->x <= Width && p->x >= (Width-3*d_border) && p->y >= (Height-d_border) )//�н� �� 
			//{
			//	p->speed_x=-0.2;
			//	p->speed_y=0;
			//}

			//else if( p->x <= (Width-3*d_border) && (p->y >= 3*d_border && p->y <= Height))//�н���
			//{
			//	p->speed_x=0;
			//	p->speed_y=-0.2;
			//}
			//else if( p->x <= (Width - 3 * d_border) && p->x >= (Width - 4*d_border) && p->y <= 3 * d_border)//�н���
			//{
			//	p->speed_x=-0.2;
			//	p->speed_y=0;
			//}
			//else if(p->x <= (Width-4*d_border) && p->y >= 0 && p->y <= (Height-d_border))//�н���
			//{
			//	p->speed_x=0;
			//	p->speed_y=0.2;
			//}
			//else if(p->x >= 3.5*d_border && p->x <= (Width-7*d_border) && p->y >= (Height-d_border))//�н���
			//{
			//	p->speed_x=-0.2;
			//	p->speed_y=0;
			//}
			//else if( p->x <= 3.5*d_border && (p->y >= (Height-3*d_border) && p->y <= Height))//�н���
			//{
			//	p->speed_x=0;
			//	p->speed_y=-0.2;
			//}
			if (p->x <= (Width - d_border) && p->y == d_border)//�н�  ��
			{
				p->speed_x = 0.2;
				p->speed_y = 0;
			}
			else if (p->x >= (Width - d_border) && (p->y <= (Height - d_border) && p->y >= d_border))
			{
				p->speed_x = 0;
				p->speed_y = 0.2;
			}
			else if ((p->x <= Width && p->x >= 3.5 * d_border) && p->y >= (Height - d_border)) //�н� �� 
			{
				p->speed_x = -0.2;
				p->speed_y = 0;
			}
			else if (p->x <= 3.5 * d_border && (p->y >= (Height - 3 * d_border) && p->y <= Height))//�н���
			{
				p->speed_x = 0;
				p->speed_y = -0.2;
			}
			else if( p->speed_x==0 && p->speed_y==-0.2 && p->y<=(Height-3*d_border) && p->x<=3.5*d_border )
			{
				menu_Lose();
				break;
			}
		
        //���������ƶ���
		if (!(p->x>40 && (fabs((p->x) - (p->next->x))>50.0 || fabs((p->y)-(p->next->y))>50.0) && p->next!=tail->pre))
		{
			p->x += p->speed_x;
			p->y += p->speed_y;
		}

		//��ʾС��(��ɾ��)
	
			setcolor(WHITE); // С�������Ϊ��ɫ
			setfillcolor(p->color);    // С���ڲ�λ��ɫ���
			fillcircle(p->x,p->y,ball_radius);
	
			//Sleep(1);
		
		p = p->next;
    }
	FlushBatchDraw();

	//��ʾʵʱ�÷�
	//settextcolor(YELLOW);
	//settextstyle(20,0,"����");
	//outtextxy(Width*0.48,Height*0.95,"�÷�:");
	//char s[10];
	//sprintf(s,"%d",score);
	//settextcolor(YELLOW);
	//settextstyle(20,0,"����");
	//outtextxy(Width*0.55,Height*0.95,s);

}

void dandanrotate()//������ת
{
	loadimage(&DanDan, "C:\\Users\\admin\\Documents\\�пƴ�\\�����ʵ���\\����ҵ\\����\\��Ϸ��Դ\\ͼƬ\\Ĩ�赩��.png");//���ص���ͼƬ

	if (MouseHit())
	{
		m=GetMouseMsg();
		if (m.uMsg==WM_MOUSEMOVE)	
		{
			d_mx_daddan=m.x-dandan_x_initial;
			d_my_dandan=m.y-dandan_y_initial;
			d_m_dandan = sqrt(d_mx_daddan* d_mx_daddan + d_my_dandan * d_my_dandan);//����뵩���ľ�������
			if (d_m_dandan>1.0)
			{

				if (m.x<dandan_x_initial)//��Ϊarctanx������ֵ�����⣬Ҫ������λ�÷�������
				{
					angle=atan(-d_my_dandan/d_mx_daddan)+PI;
					rotateimage(&DanDan_Rotate,&DanDan,angle,RGB(160,211,255),false,false);//��ת
							
					
					setcolor(TRANSPARENT);
					setfillcolor(TRANSPARENT);
					fillcircle((int)ballreadypop_x,(int)ballreadypop_y,ball_radius);
					//���ڵ�С��Բ������
					ballreadypop_x=dandan_x+75*cos(angle);
					ballreadypop_y=dandan_y-75*sin(angle);

					
					
					
				}
				else if (m.x>dandan_x_initial)
				{
					angle=atan(-d_my_dandan/d_mx_daddan);
					rotateimage(&DanDan_Rotate,&DanDan,angle,RGB(160,211,255),false,false);//��ת
					
					//����ɫ����֮ǰ����
					setcolor(TRANSPARENT);
					setfillcolor(TRANSPARENT);
					fillcircle((int)ballreadypop_x,(int)ballreadypop_y,ball_radius);
					
					//���ڵ�С��Բ������
					ballreadypop_x=dandan_x+75*cos(angle);
					ballreadypop_y=dandan_y-75*sin(angle);
					
				}
				
			}
			
		}
		
	}	
	
}


void popballs()//����
{
	if(MouseHit())//���
	{
		m=GetMouseMsg();
		if(m.uMsg==WM_LBUTTONDOWN && balls_next_restrict[balls_already_out-1]==1)//����������
		{
			/*������������*/
			mciSendString("stop music", NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
			mciSendString("close music", NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
			mciSendString("open C:\\Users\\admin\\Documents\\�пƴ�\\�����ʵ���\\����ҵ\\����\\��Ϸ��Դ\\����\\���(����).mp3 alias gemusic", NULL, 0, NULL); // ����������
			mciSendString("play gemusic", NULL, 0, NULL); // ������һ��

			balls_already_out++;

			d_mx_ball=m.x-ballreadypop_x;//���Ȼ�ȡ�����룬Ϊ��������귽���ƶ�
			d_my_ball=m.y-ballreadypop_y;

			d_m_ball=sqrt(d_mx_ball*d_mx_ball+d_my_ball*d_my_ball);

			ballpop_vx[balls_already_out-1]=d_mx_ball/d_m_ball;
			ballpop_vy[balls_already_out-1]=d_my_ball/d_m_ball;
			
			ballpop_x[balls_already_out-1]=ballreadypop_x;
			ballpop_y[balls_already_out-1]=ballreadypop_y;

			

		}
		if(m.uMsg==WM_RBUTTONDOWN)//�Ҽ�����ɫ
		{
			balls_already_out++;

			ballpop_x[balls_already_out-1]=ballreadypop_x;
			ballpop_y[balls_already_out-1]=ballreadypop_y;

			balls_next_restrict[balls_already_out-1]=1;//����ɫ�������������³�
		}

	}

	if(balls_next_restrict[balls_already_out-2]==1 && balls_next_restrict[balls_already_out-1]!=1)//��������³�
	{
		//����С��(ɾ��)

		//4���³�
		ballpop_x[balls_already_out-1] += 4*ballpop_vx[balls_already_out-1];
		ballpop_y[balls_already_out-1] += 4*ballpop_vy[balls_already_out-1];

		//Sleep(1);


	}

	if((ballpop_x[balls_already_out-1]>Width|| ballpop_x[balls_already_out-1]<0)
		|| (ballpop_y[balls_already_out-1]>Height || ballpop_y[balls_already_out-1]<0))//�������������һ����
	{
		balls_next_restrict[balls_already_out-1]=1;
	}

	struct Zuma *p;
	p=head;
	double distant;
	double insert_x,insert_y;//������������. �����ж������Ƿ񴥼��������
	while(p->next!=tail)
	{
		insert_x=ballpop_x[balls_already_out-1]-p->x;
		insert_y=ballpop_y[balls_already_out-1]-p->y;

		distant=sqrt(insert_x*insert_x+insert_y*insert_y);//�������깫ʽ
		
		if(distant<ball_radius && balls_next_restrict[balls_already_out-1]!=1)//�������������
		{
			//�³�����ȡ��p��λ��
			ballpop_x[balls_already_out-1]=p->next->x;
			ballpop_y[balls_already_out-1]=p->next->y;
			ballpop_vx[balls_already_out-1]=p->next->speed_x;
			ballpop_vy[balls_already_out-1]=p->next->speed_y;//����һ��ͬ��

			balls_next_restrict[balls_already_out-1]=1;//��һ����³�


			struct Zuma *insertp=(struct Zuma*)malloc(sizeof(struct Zuma));
			
			insertp->color = colorpop[balls_already_out - 1];
			insertp->x = ballpop_x[balls_already_out - 1] ;
			insertp->y = ballpop_y[balls_already_out - 1];
			insertp->speed_x = ballpop_vx[balls_already_out - 1];
			insertp->speed_y = ballpop_vy[balls_already_out - 1];
			

			Insert(p,insertp);

			struct Zuma *move;
			move=p->next;
			while(move->next!=tail->pre)//�������ڶ����˳�
			{
				move->x=move->next->x;
				move->y=move->next->y;
				move=move->next;

			}
			move->x -= 300*move->speed_x;//
			move->y -= 300*move->speed_y;//

			

			Remove(insertp);
			break;//�����˳���ǰ���������ѭ��
			


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