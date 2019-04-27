#pragma once
#include "map.h"

//出口関連のストラクト
struct Goal
{
	int X;
	int Y;
	int Graph;
    int StrGraph;
	//ゴールの位置設定
	int Posi[STAGE][2] =
	{
		{},
        { 20, 10},
        { 20, 10},
		{ 20, 2 },
		{ 11 , 2 },
		{ 19, 7 }
	};
};

//出口定義
void InitGoal(Goal&goal);
//ゴールとの当たり判定
int JudgeGoal(Goal&goal, int playerX, int playerY);
//出口位置更新
void UpdateGoal(Goal&goal, int stage);
//出口描画
void DrawGoal(Goal&goal, int playerX, int playerY);
