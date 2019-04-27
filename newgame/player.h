#pragma once
#include "map.h"
#include "common.h"
#include "Sound.h"

struct Player
{
	float Posi[STAGE][2] = 
	{
		{},
        {200,590},
        {200,590},
		{100,680},
		{700,680},
		{400,680}
	};
	float X;				//X座標
	float Y;				//Y座標
	int W;					//横幅
	int H;					//縦幅
	int Graph[4];			//画像
    int HashigoGraph[4];    //梯子登り途中の画像
    int JumpGraph[2];       //ジャンプ中の画像
	int LaughGraph[2];      //笑う画像(準備画面で使用)
    int MissGraph[3];       //ミスした画像
    int EscapeGraph[2];     //脱出時のキョロキョロする画像
	int GladGraph;			//クリア時の飛び跳ねる画像
	float Speed;			//速度
	bool AtariFlag;			//敵に当たったか否か
	int AtariCount;			//次に敵に当たるまでのカウント
    int Life;               //残機
	float JumpVelocity;		//ジャンプ時の重力
	bool JumpFlag;			//ジャンプしているか否か
    bool PrevJumpFlag;      //ジャンプキーが押されているか否か
	bool HashigoFlag;		//はしごのところにいるか否か
    bool ContactFlag;       //マップチップと接触しているか否か
    bool GroundFlag;        //接地しているか否か判定
	bool Left;				//左向きか否か
    bool WalkFlag;          //地面について歩いているかいないか
	int Frame;
	int Timer;				//アニメーションにあたって
    int KeepGraph;          //現在の画像を保持
};

//
//関数プロトタイプ宣言
//
void InitPlayer(Player&player, int stage);
void ResetPlayer(Player&player, int stage);
void UpdatePlayer(Player&player, Sound&sound, int stage);
void DrawPlayer(Player&player, int status, int count);
void DrawPlayPlayer(Player&player);
void DrawMissPlayer(Player&player, int count);
void DrawOverPlayer(Player&player);
void DrawClearPlayer(Player&player, int count);
void DrawCongPlayer(Player&player, int count);

