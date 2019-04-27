#include "DxLib.h"
#include "ready.h"
#include "common.h"
#include "player.h"

//準備画面初期定義
void InitReady(Ready&ready)
{
    //画像読み込み
	ready.Steps = LoadGraph("texture/kaidan.png");
}

//準備画面更新
void UpdateReady(Ready & ready, Player&player)
{
	ready.Count++;
	player.Timer = GetNowCount();
	if (ready.Count < 125)
	{
		player.X += 5;
		player.Frame = player.Timer / 200 % 4;
	}
	else if (ready.Count >= 125)
	{
		player.Frame = player.Timer / 100 % 4;
	}
}

//準備画面のアニメーションにあたって、数値のリセット
void ResetReady(Ready&ready, Player&player)
{
	ready.Count = 0;
	player.X = 300;
	player.Y = 600;
}

//準備画面描画(プレイヤー、階段描画)&SE
void DrawReady(Ready & ready, Player&player, Sound&sound)
{
	if (ready.Count < 125)
	{
		DrawGraph(player.X, player.Y, player.Graph[player.Frame], TRUE);
        if (CheckSound(sound, WALK) == FALSE)
        {
            ONSound(sound, WALK);
        }
	}
	else if (125 <= ready.Count && ready.Count < 200)
	{
        OFFSound(sound, WALK);
		DrawGraph(player.X, player.Y, player.LaughGraph[player.Frame % 2], TRUE);
	}
    else if(ready.Count >= 200)
    {
        if (CheckSound(sound, KAIDAN) == FALSE)
        {
            ONSound(sound, KAIDAN);
        }
    }
    DrawGraph(1000, 600, ready.Steps, TRUE);
}