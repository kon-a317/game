#pragma once
#include "common.h"
#include "Map.h"

//宝石関連のストラクト
struct Jewel
{
	int Graph;
	int X[STAGE][JEWEL];
	int Y[STAGE][JEWEL];
	//宝石の発生判定
	int Flag[STAGE][JEWEL] =
	{
		{},
        {},
        {},
		{ TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE },
		{ TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE },
		{ TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE }
	};
	//宝石の位置設定
	int Posi[STAGE][JEWEL][2] =
	{
		{},
        {},
        {},
		{
			{ 2, 5 },
			{ 20,11},
            {19,2},
            {0,0},
            {0,0},
			{0,0},
			{0,0}
		},
		{
			{23, 7},
			{10, 2},
            {16,8},
            {18,11},
            {7,2},
			{9,8},
			{}
		},
		{
			{ 2, 3},
			{ 20, 2},
            {8,3},
            {1,11},
            {0,0},
			{},
			{}
		},

	};
};

//
//関数プロトタイプ宣言
//
//宝石定義
void InitJewel(Jewel&jewel);
//宝石との当たり判定
int JudgeJewel(Jewel&jewel, int x, int y, int stage);
//宝石の位置更新
void UpdateJewel(Jewel&jewel, int stage);
//宝石描画
void DrawJewel(Jewel&jewel, int stage);