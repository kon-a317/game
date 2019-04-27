#include "DxLib.h"
#include "common.h"
#include "Map.h"
#include "time.h"

//制限時間定義&リセット
void InitTime(Time&time)
{
	time.Now = 0;
	time.Limit = 150;
	LoadDivGraph("texture/font.bmp", 96, 16, 6, 16, 18, time.Graph);
    time.WatchGraph = LoadGraph("texture/watch.png");
	time.Display[0] = time.Limit / 100;
	time.Display[1] = (time.Limit % 100) / 10;
	time.Display[2] = time.Limit % 10;
}
//制限時間の更新情報
int UpdateTime(Time&time, int status)
{
	time.Now++;

	if (time.Now == 60)
	{
		time.Now = 0;
		time.Limit--;
		if (time.Limit < 0)
		{
			time.Limit = 0;
			return 1;
		}
	}
	time.Display[0] = time.Limit / 100;
	time.Display[1] = (time.Limit % 100) / 10;
	time.Display[2] = time.Limit % 10;
	return 0;
}
//制限時間の描画
void DrawTime(Time&time,int status)
{
	if (status == READY)
	{
		if (time.Limit <= 10)
		{
			SetDrawBright(255, 0, 0);
		}
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph(960 + (32 * i), 450, 1.5f, 0, time.Graph[16 + time.Display[i]], TRUE);
		}
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawRotaGraph(950 - 32, 50, 1, 0, time.WatchGraph, TRUE);
		if (time.Limit <= 10)
		{
			SetDrawBright(255, 0, 0);
		}
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraph(950 + (32 * i), 50, 1.5f, 0, time.Graph[16 + time.Display[i]], TRUE);
		}
		SetDrawBright(255, 255, 255);
	}
}