#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<process.h>
#include<direct.h>
#include<stdio.h>
#include<vector>
using namespace std;

#define mx getmaxx()
#define my getmaxy()


class game
{
	vector < vector <int> > bullets;
    int gap = 10;
    int width = 40;
    int x1 = mx/2-(gap/2+width);
    int x2 = x1 - (gap + width);
    int x3 = mx/2+(gap/2);
    int x4 = x3 + (gap + width);
	vector < vector <int> > enemy = {{x1,0},{x2,0},{x3,0},{x4,0},
                     {x1,9},{x2,9},{x3,9},{x4,9},
                     {x1,18},{x2,18},{x3,18},{x4,18}};
	int score = 0;
	public:
		void display()
		{
			int x=getmaxx()/2-5,y=getmaxy()/2+150,ch;
			int e=0,r =0;
			int page =0;
			while(1)
			{
				cleardevice();

				show_spaceship(x,y);
				show_enemies();
				show_bullets();
				show_borders();
				show_score();
				check();
				e++;
				r++;
				if (enemy.size()==0)
				{
					reset_enemies();
				}
				if (e==5)
				{
				 move_enemies();
				 e=0;
				}
				if(kbhit())
				{
					ch = getch();
					if(ch == 75 && x>=mx/2-90)
							{
						x = x - 5;
					}
					if(ch == 77 && x<=mx/2+80)
					{
						x = x +	5;
					}
					if(ch == 27)
					{
						break;
					}
					if(ch == 32 && r>=15)
					{
					    r =0;
						shoot(x,y);
					}
				}
				delay(15);
				void swapbuffers();

			}
		}
		void reset_enemies()
		{
			int gap = 10;
			int width = 40;
			int x1 = mx/2-(gap/2+width);
			int x2 = x1 - (gap + width);
			int x3 = mx/2+(gap/2);
			int x4 = x3 + (gap + width);

			enemy ={{x1,0},{x2,0},{x3,0},{x4,0},
                     {x1,9},{x2,9},{x3,9},{x4,9},
                     {x1,18},{x2,18},{x3,18},{x4,18}};
		}
		void show_spaceship(int x, int y)
		{
		    setfillstyle(1,BLUE);
			bar(x,y,x+10,y+50);
		}
		void shoot(int x,int y)
		{
			bullets.push_back({x+5, y-10});
		}
		void show_enemies()
		{
		    setfillstyle(1,RED);
			for(int i = 0;i<enemy.size();i++)
			{
				bar(enemy[i][0],enemy[i][1],enemy[i][0]+40,enemy[i][1]+5);
			}
		}
		void move_enemies()
		{
			for(int i = 0;i<enemy.size();i++)
			{
				enemy[i][1]++;
			}
		}
		void show_bullets()
		{
			setfillstyle(1,GREEN);
			for(int i=0;i<bullets.size();i++)
			{
				bar(bullets[i][0],bullets[i][1]-10,bullets[i][0]+2,bullets[i][1]);
				bullets[i][1] -= 3;
			}
		}
		void show_borders()
		{
			line(mx/2-100,0,mx/2-100,my);
			line(mx/2+100,0,mx/2+100,my);
		}
		void show_score()
		{   char str[128];
			sprintf(str,"Score: %u",score);
			outtextxy(450,50,str);
		}
		void check()
		{
			for (int i=0;i<bullets.size();i++)
			{
				int X1 = bullets[i][0];
				int Y1 = bullets[i][1];
				int H1 = 10;
				int W1 = 5;
				if (Y1<10)
                {
                    bullets.erase(bullets.begin()+i);
                }
				for (int j=0;j<enemy.size();j++)
				{
					int X2 = enemy[j][0];
					int Y2 = enemy[j][1];
					int H2 = 5;
					int W2 = 40;
					if (!(X1+W1<X2 || X2+W2<X1 || Y1+H1<Y2 || Y2+H2<Y1))
					{
						bullets.erase(bullets.begin()+i);
						i--;
						enemy.erase(enemy.begin()+j);
						j--;
						score += 100;
					}
				}
			}
		}
};

int main()
{
	int gd = DETECT,gm;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

	game g;
	g.display();
	getch();
	closegraph();
	return 0;
}
