#pragma once
#include "Sound.h"

struct Player;

//準備画面のストラクト
struct Ready
{
	int Steps;              //階段画像
	int Count;              //準備画面を表示させる時間をカウント
};


//
//関数プロトタイプ宣言
//
void InitReady(Ready&ready);
void UpdateReady(Ready&ready, Player&player);
void ResetReady(Ready&ready, Player&player);
void DrawReady(Ready&ready, Player&player, Sound&sound);