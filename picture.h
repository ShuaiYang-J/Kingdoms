#pragma once
#include<graphics.h>   //画布上的一系列操作
#include<time.h>	//有各种时间函数
#include<conio.h>	//按键操作
//EasyX包的应用

class picture
{
public:
	void Welcome(); //开始界面绘制
	void End(int AI_HP ,int Player_HP);  //最后的界面，体现输赢
	void Data();
	void Show(int player_life, int npc_life, int player_shoupai_num, int player[], int player_desktop2, int npc_desktop2);
	//void interactive(int player_shoupai_num, int Play[]);
	int player_out=-1, isRoundover=0;
	int player_x[6], player_y[6], roundover_x = 748, roundover_y = 390, npc_desktop_x = 174, npc_desktop_y = 30;
	int pai_high = 150, pai_width = 93, roundover_high = 41, roundover_width = 100, isselected, answerover;
private:
	//定义画布尺寸
	int high = 600, width = 1000;
	//定义图片变量 背景 界面图片
	IMAGE img_bk1, img_bk2, img_ui, img_sha, img_shan, img_peach, img_hp, img_AI ,img_Player,img_Roundover, img_start,img_end;
	//各素材尺寸
	int ui_high = 168, ui_width = 861, AI_high = 246, AI_width = 174, firm_high = 42, firm_width = 125;
	int hp_high = 30, hp_width = 26, StagePlaycard_high = 50, StagePlaycard_width = 141, player_high = 200, player_width = 150;
	int ui_y = 432, Player_x = 850, Player_y = 400, AI_x = 0, AI_y = 30, restart_x = 300, restart_y = 390, Prompt_x=30, Prompt_y = 0;
	int player_desktop_x=650, player_desktop_y =280, npcHp_x = 0,npcHp_y = 0, HeroHp_x =850,HeroHp_y = 370;

};

void picture::Welcome()
{
  //画布展开
  initgraph(width, high);
  Data();

  while (1)
  {
	  putimage(0, 0, &img_bk1);
	  putimage(width / 2 - firm_width / 2, restart_y + 100, &img_start);
	  setbkmode(TRANSPARENT);
	  settextstyle(30, 0, _T("微软雅黑"));
	  outtextxy(Prompt_x + 80, 160, _T("三国杀小游戏，打发时间必备良品！"));
	  outtextxy(Prompt_x + 80, 200, _T("PS:感谢万能的github和百度，出现bug请告知。"));
	  outtextxy(Prompt_x + 80, 240, _T("友情提示，鼠标控制延迟较大，不要砸电脑哦。"));
	  outtextxy(Prompt_x + 350, 420, _T("天文与空间科学学院  杨帅 "));
	  //和次数也没关系emmm
	  MOUSEMSG m;
	  m = GetMouseMsg();

	  if (m.uMsg == WM_LBUTTONDOWN)
	  {
		  if ((m.x >= width / 2 - firm_width / 2) && (m.x <= width / 2 + firm_width / 2) && (m.y >= restart_y + 100) && (m.y <= restart_y + 100 + firm_high))
		  {
			  break;
		  }
	  }
	  FlushBatchDraw();
  }
  
}
void picture::End(int AI_HP, int Player_HP)
{
	if (AI_HP == 0)
	{
		while (1)
		{
			putimage(0, 0, &img_bk1);
			putimage(width / 2 - firm_width / 2, restart_y + 100, &img_end);
			setbkmode(TRANSPARENT);
			settextstyle(50, 0, _T("微软雅黑"));
			outtextxy(Prompt_x + 250, 200, _T("恭喜你打败了“智能”AI"));
			MOUSEMSG m;
			m = GetMouseMsg();

			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if ((m.x >= width / 2 - firm_width / 2) && (m.x <= width / 2 + firm_width / 2) && (m.y >= restart_y + 100) && (m.y <= restart_y + 100 + firm_high))
				{
					break;
				}
			}
			FlushBatchDraw();
		}
	}
	if (Player_HP == 0)
	{
		while (1)
		{
			putimage(0, 0, &img_bk1);
			putimage(width / 2 - firm_width / 2, restart_y + 100, &img_end);
			setbkmode(TRANSPARENT);
			settextstyle(50, 0, _T("微软雅黑"));
			outtextxy(Prompt_x + 250, 200, _T("怎么说呢，能输也是很强的！"));
			MOUSEMSG m;
			m = GetMouseMsg();

			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if ((m.x >= width / 2 - firm_width / 2) && (m.x <= width / 2 + firm_width / 2) && (m.y >= restart_y + 100) && (m.y <= restart_y + 100 + firm_high))
				{
					break;
				}
			}
			FlushBatchDraw();
		}
	}
}

void picture::Show(int player_life,int npc_life,int player_shoupai_num,int player[],int player_desktop2,int npc_desktop2)
{   
	//player_x直接定义会变 每次重新定义一次
	Data();
	int i;
	putimage(0, 0, &img_bk2);
	putimage(0, ui_y, &img_ui);
	putimage(AI_x, AI_y, &img_AI);
	putimage(Player_x, Player_y, &img_Player);
	putimage(roundover_x, roundover_y, &img_Roundover);
	//绘制血量
	for (i = 0; i < player_life; i++)
	{
		putimage(i*(hp_width+10) + HeroHp_x, HeroHp_y, &img_hp);
	}
	for (i = 0; i < npc_life; i++)
	{
		putimage(i*(hp_width + 10) + npcHp_x, npcHp_y, &img_hp);
	}

	//绘制手牌
	for (i = 0; i < player_shoupai_num; i++)
	{
		if (player[i] == 1)
		{
			putimage(player_x[i], player_y[i], &img_sha);
			continue;//杀
		}
		if (player[i] == 2)
		{
			putimage(player_x[i], player_y[i], &img_shan);
			continue;//闪
		}
		if (player[i] == 3)
		{
			putimage(player_x[i], player_y[i], &img_peach);
			continue;//桃
		}

	}
//绘制选择的手牌
	if (player_desktop2 == 1)
	{
		putimage(player_desktop_x, player_desktop_y, &img_sha);

	}
	if (player_desktop2 == 2)
	{
		putimage(player_desktop_x, player_desktop_y, &img_shan);

	}
	if (player_desktop2 == 3)
	{
		putimage(player_desktop_x, player_desktop_y, &img_peach);
	}
	if (npc_desktop2 == 1)
	{
		putimage(npc_desktop_x, npc_desktop_y, &img_sha);
	}
	if (npc_desktop2 == 2)
	{
		putimage(npc_desktop_x, npc_desktop_y, &img_shan);
	}
	if (npc_desktop2 == 3)
	{
		putimage(npc_desktop_x, npc_desktop_y, &img_peach);
	}

	FlushBatchDraw();
}
void picture::Data()
{   
	//loadimage 宽 高
	loadimage(&img_bk1, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\background1.jpg", width, high);
	loadimage(&img_bk2, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\background2.jpg", width, high);
	loadimage(&img_ui, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\ui.jpg", ui_width, ui_high);
	loadimage(&img_AI, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\AI.jpg", AI_width, AI_high);
	loadimage(&img_Player, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\Player.jpg", player_width, player_high);
	loadimage(&img_hp, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\hp.jpg", hp_width, hp_high);
	loadimage(&img_start, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\start.jpg", StagePlaycard_width, StagePlaycard_high);
	loadimage(&img_end, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\end.jpg", StagePlaycard_width, StagePlaycard_high);
	loadimage(&img_Roundover, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\roundover.jpg", roundover_width, roundover_high);
	//添加卡牌图案
	loadimage(&img_sha, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\sha.jpg", pai_width, pai_high);
	loadimage(&img_shan, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\shan.jpg", pai_width, pai_high);
	loadimage(&img_peach, "C:\\Users\\Pick\\source\\repos\\Kingdom\\Kingdom\\tao.jpg", pai_width, pai_high);

	BeginBatchDraw();
	//载入所需要的图片
	//重载牌的位置
	for (int i = 0; i < 6; i++) 
	{
		player_x[i] = i * pai_width;
		player_y[i] = high - pai_high;
	}
}
