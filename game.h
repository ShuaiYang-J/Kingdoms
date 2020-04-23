#pragma once
#include"picture.h"
#include"resource.h"
#include<windows.h>
#include<Mmsystem.h>  //音频播放 PlaySound需要
#pragma comment(lib,"winmm.lib")

//游戏音乐播放 玩家和AI的操作判定
class game
{
public:
	void Star();
	void Pai(int Xi);
	void MoPai(int AI,int Player);
	void Choose(int AI, int Player);
	void interactive(int player_shoupai_num, int Play[],int AI,int Player);
	void Abadon(int AI, int Player);
	void RePai(int AI, int Player);
	void ReSha();
	//需要调用的参数
	int paihao, player_life, player_shoupai_num, npc_life, npc_shoupai_num;
	int paidui[57],player[7] = { 0 }, npc[7] = { 0 }, player_desktop2, npc_desktop2;
	int Play[4]; //Play[4]={player_out;answerover;isselected,isAbadon}
	//因为要调用 就不设为私有
private:
	int over = 0, isAbadon = 0;
	int player_sha_num = 0, npc_sha_num = 0, player_shan_num = 0, npc_shan_num = 0, diss = 0, Abadon_num = 0, dissing = 0;
};
void game::Star()
{   
	//游戏开始函数
	//背景音乐---添加到资源中更好一点
	//PlaySound(TEXT("C://WINDOWS//Media//Alarm01.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//非资源文件的调用音频方式。
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
	//画出开始界面
	picture draw;
	draw.Welcome();
	//Show(int player_life, int npc_life, int player_shoupai_num, int player[], int player_desktop2);
	//Pai(0)初始化 Pai(1)打乱牌堆
	Pai(0);
	draw.Show(player_life, npc_life, player_shoupai_num,  player, player_desktop2, npc_desktop2);
	
	while (!over)
	{   
		MoPai(0 , 1);// 0 1 判定摸牌对象 先玩家
		Choose(0, 1);
		//玩家出完牌 如果存在一方血量为0 推出
		if (over)
		{
			break;
		}
		MoPai(1 , 0);
		Choose(1 , 0);
		ReSha();
		if (over)
		{
			break;
		}
	}
	draw.End( npc_life, player_life);
}
void game::Pai(int Xi)
{   
	if (!Xi)
	{   
		//设定生命值 最大为4
		//初始化手牌  1 杀 2闪 3桃
		paihao = 0;
		player_life = 4;
		player[0] = 1;//杀
		player[1] = 3;//桃
		player[2] = 2;//闪
		player[3] = 1;//杀
		player_shoupai_num = 4;
		npc_life = 4;
		npc[0] = 1;//杀
		npc[1] = 1;
		npc[2] = 1;
		npc[3] = 2;//闪
		npc_shoupai_num = 4;
		//desktop 显示在桌面上体现玩家和AI的出牌
		//初始化为-1
		player_desktop2 = -1;
		npc_desktop2 = -1;
	}
	else 
	{   
		//摸牌需要重置桌面上的牌 防止显示错误
		player_desktop2 = -1;
		npc_desktop2 = -1;
		int temp, i, j;
		for (i = 0; i < 25; i++)
		{
			paidui[i] = 1;//给牌堆赋值为杀
		}
		for (i = 25; i < 50; i++)
		{
			paidui[i] = 2;//给牌堆赋值为闪
		}
		for (i = 50; i < 57; i++)
		{
			paidui[i] = 3;//给牌堆赋值为桃
		}

		for (i = 0; i < 57; i++)
		{
			j = rand() % 57; //随即打乱
			temp = paidui[i];
			paidui[i] = paidui[j];
			paidui[j] = temp;
		}
	}
}
void game::MoPai(int AI, int Player)
{   
	picture P;
	if (AI)
	{   
		Pai(1);
		setbkmode(TRANSPARENT);
		settextstyle(40, 0, _T("微软雅黑"));
		outtextxy(180, 210, _T("敌方摸牌中！"));
		FlushBatchDraw();
		Sleep(300);
		int t;
		int i, j;
		for (i = 0; npc[i] != 0; i++)
		{
		}//找到牌尾
		t = i;
		for (j = t; j < t + 2; j++)
		{
			if (paihao > 55)	//考虑牌堆抽完
			{
				Pai(1);
				paihao = 0;
			}
			npc[j] = paidui[paihao];
			paidui[paihao] = 0;  //玩家抽两张牌，抽完牌堆处的数就清零
			paihao++;
		}
		npc_shoupai_num += 2;//加二
	}
    if (Player)
	{   
		Pai(1);
		setbkmode(TRANSPARENT);
		settextstyle(40, 0, _T("微软雅黑"));
		outtextxy(180, 210, _T("摸牌中！"));
		FlushBatchDraw();
		Sleep(300);

		int t;
		int i, j;
		for (i = 0; player[i] != 0; i++)
		{ }//找到牌尾
		t = i;
		for (j = t; j < t + 2; j++)
		{
			if (paihao > 55)	//考虑牌堆抽完
			{
				Pai(1);
				paihao = 0;
			}
			player[j] = paidui[paihao];
			paidui[paihao] = 0;  //玩家抽两张牌，抽完牌堆处的数就清零
			paihao++;
		}
		player_shoupai_num += 2;//加二
		Sleep(500);
		P.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
	}
}

void  game::Choose(int AI, int Player)
{   
	//出牌的决策

	if (AI)
	{
		RePai(1, 0);
		Abadon(1, 0);
     }
	if (Player)
	{   
		//Play[3]={player_out;isRoundover;isselected}
		//用Play 数组来传递值 
		//有点延迟 需要等待一会操作----选牌 
		while (Play[0]!=-2)
		{   

			interactive(player_shoupai_num, Play, 0, 1);

			if (Play[1] == 0)			//出牌
			{   
				Play[3] = 0;
				//根据选择出的牌做提示 杀 闪 桃 两次杀
				RePai(0,1);

			}
			if (Play[1] == 1)   //玩家回合结束 弃牌
			{
				//直接弃牌
				while (Play[0] != -2)
				{
					Abadon(0, 1);
					interactive(player_shoupai_num, Play, 0, 1);
					RePai(0, 1);
				}
				break;
				
			}
		}
		
	}
}
void game::interactive(int player_shoupai_num, int Play[], int AI, int Player)
{   
	//交互选牌 AI为1时为回应--杀
	if (AI)
	{
		picture M;
		M.Data();
		M.isselected = 0;
		M.answerover = 0;
		int i;
		MOUSEMSG m;
		if (MouseHit()) //有鼠标消息时执行
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				for (i = 0; (i < player_shoupai_num) && (!M.isselected); i++)
				{
					if (((m.x >= M.player_x[i]) && (m.x <= M.player_x[i] + M.pai_width)) && ((m.y >= M.player_y[i]) && (m.y <= M.player_y[i] + M.pai_high)))
					{
						M.player_out = i;
						M.isselected = 1;
						break;
					}

				}
				if (((m.x >= M.roundover_x) && (m.x <= M.roundover_x + M.roundover_width)) && (m.y >= M.roundover_y) && (m.y <= M.roundover_y + M.roundover_high))
				{
					//点击结束本回合
					M.answerover = 1;
					M.isselected = 0;

				}

			}
			FlushMouseMsgBuffer();
			//刷新鼠标缓存区 否则无法选牌
		}

		Play[0] = M.player_out;
		Play[1] = M.answerover;
		Play[2] = M.isselected;

	}
	if (Player && (Play[0]!=-2))
	{
		picture M;
		M.Data();
		M.isselected = 0;
		int i;
		MOUSEMSG m;
		if (MouseHit()) //有鼠标消息时执行
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				for (i = 0; (i < player_shoupai_num) && (!M.isselected); i++)
				{
					if (((m.x >= M.player_x[i]) && (m.x <= M.player_x[i] + M.pai_width)) && ((m.y >= M.player_y[i]) && (m.y <= M.player_y[i] + M.pai_high)))
					{
						M.player_out = i;
						M.isselected = 1;
						break;
					}

				}
				if (((m.x >= M.roundover_x) && (m.x <= M.roundover_x + M.roundover_width)) && (m.y >= M.roundover_y) && (m.y <= M.roundover_y + M.roundover_high))
				{
					//点击结束本回合
					M.isselected = 0;
					M.isRoundover = 1;
					isAbadon = 1; //玩家弃牌 
				}

			}
			FlushMouseMsgBuffer();
			//刷新鼠标缓存区 否则无法选牌
		}

		Play[0] = M.player_out;
		Play[1] = M.isRoundover;
		Play[2] = M.isselected;
		Play[3] = isAbadon;
	}
}

inline void game::Abadon(int AI, int Player)
{   //刷新界面都要用到picture
	picture clear;	
	//弃牌操作
	if (AI)
	{
		int t = 0;
		Abadon_num = npc_shoupai_num - npc_life;
		while ((Abadon_num > 0) && (t < Abadon_num))
		{
			npc[0] = 0;
			//整理手牌
			int k;
			for (k = 0; k < npc_shoupai_num; k++)
			{
				if (npc[k] == 0)
				{
					npc[k] = npc[k + 1];
					npc[k + 1] = 0;
				}             //整理npc手牌
			}
			npc_shoupai_num--;
			t++;
		}
		setbkmode(TRANSPARENT);
		settextstyle(40, 0, _T("微软雅黑"));
		outtextxy(180, 210, _T("敌方弃牌中！"));
		FlushBatchDraw();
		Sleep(300);
		player_desktop2 = 0;
		npc_desktop2 = 0;
		clear.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
	}
	if (Player)
	{   
		//第一次弃牌时规定下弃牌数
		if (Play[1]==1)
		{
		 Abadon_num = player_shoupai_num - player_life;
		}
		if (Abadon_num > 0 &&(diss != Abadon_num))
		{   
			player_desktop2 = 0;
			npc_desktop2 = 0;
			clear.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
			dissing = 1;
			//文字显示 在考虑一下
			setbkmode(TRANSPARENT);
			settextstyle(40, 0, _T("微软雅黑"));
			outtextxy(180, 210, _T("请弃牌！"));
			FlushBatchDraw();
			Sleep(500);
		}
		if (Abadon_num == 0)
		{
			dissing = 0;
		}
		if (diss >= Abadon_num)//已经弃牌完成
		{
			dissing = 0;
			diss = 0;
			Play[0] = -2;
			Abadon_num = 0;
			setbkmode(TRANSPARENT);
			settextstyle(40, 0, _T("微软雅黑"));
			outtextxy(180, 210, _T("弃牌结束！"));
			FlushBatchDraw();
			Sleep(300);
			player_desktop2 = 0;
			npc_desktop2 = 0;
			clear.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
			Sleep(500);
		}
	}
}

inline void game::RePai(int AI, int Player)
{   
	//对出牌作出反应并整理手牌
	//AI部分
	if (AI)
	{   
		picture A;
		//第一个Show 清除摸牌字符
		A.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
		int tempnpcshoupai = 0;		//临时记录npc手牌数
		int k;
		//首先判定玩家出杀
		if ((player_desktop2 == 1) && (player_sha_num == 1))
		{
			for (k = 0; k < npc_shoupai_num; k++)
			{
				if (npc[k] == 2)         //找到闪
				{
					setbkmode(TRANSPARENT);
					settextstyle(30, 0, _T("微软雅黑"));
					outtextxy(180, 230, _T("敌方出闪！"));
					FlushBatchDraw();
					Sleep(300);
					npc_desktop2 = npc[k];//记录npc桌面牌
					npc[k] = 0;
					npc_shoupai_num--;  //手牌减一
					npc_shan_num++;
					//整理手牌
					int k;
					for (k = 0; k < npc_shoupai_num; k++)
					{
						if (npc[k] == 0)
						{
							npc[k] = npc[k + 1];
							npc[k + 1] = 0;
						}             //整理npc手牌
					}
					A.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
				}
			}
			if (npc_shan_num == 0)   //未使用闪。电脑扣血
			{
				npc_life--;
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(180, 230, _T("敌方受到一单位伤害！"));
				FlushBatchDraw();
				Sleep(300);
				player_desktop2 = 0;
				npc_desktop2 = 0;
				A.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
				if (npc_life <= 0)   //AI死亡
					{
						over = 1;
						goto end;
					}
			}
			npc_shan_num = 0;//npc出闪次数清空
		}
		//player_out 增加
		if (Play[0] == -2)//玩家回合结束，可主动出牌
		{
			tempnpcshoupai = npc_shoupai_num;
				//电脑的逻辑 先加血 后出杀 都无，就推出
			for (k = 0; k < tempnpcshoupai; k++)
				{
					if ((npc_life < 4) && (npc[k] == 3))   //先找桃奶自己一口
					{
						npc_desktop2 = npc[k];//记录npc桌面
						npc[k] = 0;
						npc_life++;			//生命加一
						npc_shoupai_num--;  //手牌减一
						//整理手牌
						int k;
						for (k = 0; k < npc_shoupai_num; k++)
						{
							if (npc[k] == 0)
							{
								npc[k] = npc[k + 1];
								npc[k + 1] = 0;
							}             //整理npc手牌
						}
						player_desktop2 = 0;
						A.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
					}
				}
			tempnpcshoupai = npc_shoupai_num;
			for (k = 0; k < tempnpcshoupai; k++)
			{
				if ((npc[k] == 1) && (npc_sha_num == 0))        //找到杀且本回合第一次使用
				{
					npc_desktop2 = npc[k];//记录npc桌面牌
					npc[k] = 0;

					//整理手牌
					int k;
					for (k = 0; k < npc_shoupai_num; k++)
					{
						if (npc[k] == 0)
						{
							npc[k] = npc[k + 1];
							npc[k + 1] = 0;
						}             //整理npc手牌
					}
					npc_shoupai_num--;  //手牌减一
					npc_sha_num++;

					setbkmode(TRANSPARENT);
					settextstyle(40, 0, _T("微软雅黑"));
					outtextxy(180, 180, _T("敌方出杀！"));
					outtextxy(180, 230, _T("请出闪，点结束会扣血哦！"));
					FlushBatchDraw();
					Sleep(500);
					//循环 直至选择出牌
					//int *test=NULL;  指针尝试
					while (Play[0] == -2 || ((Play[0] == -1||player[Play[0]]==1|| player[Play[0]] == 3) && Play[1]== 0))
					{
						interactive(player_shoupai_num, Play, 1, 0);
					 }
					RePai(0,1);
					A.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
					Sleep(300);
					if (player_life <= 0)   //有人已死
					{
						over = 1;
						goto end;
					}

				}
			}
			npc_sha_num = 0;
			Play[0] = -1;
		}
     
	end:;
	}

	//玩家部分
	if (Player)
	{  
		picture PP;
		//首先判定是否回合结束  //Play[3]={player_out;isRoundover;isselected;isAbadon
		if (Play[1] == 0)   //玩家未结束回合，所点击的是有效牌
		{
			if ((player[Play[0]] == 1) && (player_sha_num == 0) && (Play[0] != -1) && (Play[2] == 1)&& Play[3]!=1)    //玩家出杀且是第一次出杀
			{
				player_desktop2 = player[Play[0]];//记录桌面牌
				player[Play[0]] = 0;
				Play[0] = -1;        //出牌号清空
				//整理手牌
				int k;
				for (k = 0; k < player_shoupai_num; k++)
				{
					if (player[k] == 0)
					{
						player[k] = player[k + 1];
						player[k + 1] = 0;
					}             //整理player手牌
				}
				player_shoupai_num--;           //手牌数减一
				player_sha_num++;
				RePai(1, 0);
				PP.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
				Play[2] = 0;

			}
			if ((player[Play[0]] == 1) && (player_sha_num != 0) && (Play[0] != -1) && (Play[2] == 1)&&Play[3] != 1)   //玩家一回合内第二次出杀
			{
				player_desktop2 = player[Play[0]];//记录桌面牌
				player_sha_num++;
				Play[0] = -1;				//出牌号清空
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(180, 230, _T("目前不支持连续出杀哦！"));
				FlushBatchDraw();
				Sleep(300);
				Play[2] = 0;
				npc_desktop2 = 0;//
				PP.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
				return;  //退出判定
			}
			if ((player[Play[0]] == 2) && (npc_desktop2 != 1)&&Play[2]==1 && Play[3] != 1)  //玩家出闪且电脑未出杀
			{
				player_desktop2 = player[Play[0]];//记录桌面牌
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(180,230, _T("不可以随意出闪哦！"));
				FlushBatchDraw();
				Sleep(300);
				Play[0] = -1;				
				Play[2] = 0;
				npc_desktop2 = 0;
				PP.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
				return;  //退出判定
			}

			if ((player[Play[0]] == 3) && (player_life < 4) && (Play[2] == 1) && Play[3] != 1)
			{
				player_desktop2 = player[Play[0]];//记录桌面牌
				player_life++;		//使用桃加血
				player[Play[0]] = 0;
				Play[0] = -1;		

				int k;
				for (k = 0; k < player_shoupai_num; k++)
				{
					if (player[k] == 0)
					{
						player[k] = player[k + 1];
						player[k + 1] = 0;
					}             //整理player手牌
				}
				Play[2] = 0;
				player_shoupai_num--; //手牌减一
				npc_desktop2 = 0;
				PP.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
			}
			if ((player[Play[0]] == 3) && (player_life == 4) && (Play[2] == 1) && Play[3] != 1)
			{
				player_desktop2 = player[Play[0]];//记录桌面牌
				setbkmode(TRANSPARENT);
				settextstyle(30, 0, _T("微软雅黑"));
				outtextxy(180, 230, _T("血是满的，奶不了了！"));
				FlushBatchDraw();
				Sleep(300);
				Play[0] = -1;				//出牌号清空
				Play[2] = 0;
				npc_desktop2 = 0;
				PP.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
				//为了显示你点击的牌是什么
				return;  //退出判定
			}
		}
		//以上为玩家不结束回合时反应
		//AI出杀 玩家的反应
		if ((npc_desktop2 == 1) && (npc_sha_num == 1) && (Play[2] == 1)&& player[Play[0]] == 2) //npc出有效杀,玩家点击闪
			{
					player_desktop2 = player[Play[0]];//记录桌面牌
					player[Play[0]] = 0;
					Play[0] = -1;				//出牌号清空
					player_shan_num++;			//玩家出闪次数加一

					int k;
					for (k = 0; k < player_shoupai_num; k++)
					{
						if (player[k] == 0)
						{
							player[k] = player[k + 1];
							player[k + 1] = 0;
						}             //整理player手牌
					}
					player_shoupai_num--;
					Play[2] = 0;
					PP.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
			}
		if ((npc_desktop2 == 1) && (player_shan_num == 0))	//npc出杀玩家没有闪
			{
				player_life--;
				if (player_life==0)
				{
					over = 1;
				}
				player_desktop2 = 0;
				PP.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
				npc_desktop2 = 0;
				player_shan_num = 0;
				npc_sha_num++;
			}
		if ((Play[1] == 0) && ( Play[2]== 1) && (dissing == 1) && (Play[0]!= -1) && Play[3]==1)//玩家回合结束 选择弃牌
		{
			player_desktop2 = player[Play[0]];//记录以显示
			player[Play[0]] = 0;

			int k;
			for (k = 0; k < player_shoupai_num; k++)
			{
				if (player[k] == 0)
				{
					player[k] = player[k + 1];
					player[k + 1] = 0;
				}             //整理player手牌
			}
			player_shoupai_num--;
			diss++;
			npc_desktop2 = 0;
			PP.Show(player_life, npc_life, player_shoupai_num, player, player_desktop2, npc_desktop2);
		}
	}
}

inline void game::ReSha()
{
	npc_sha_num = 0;
	player_sha_num = 0;
	player_shan_num = 0;
	npc_shan_num = 0;
}
