#pragma once

//時間関連
struct Time
{
	int Now;
	int Frame;
	int Limit;
	int Display[3] = { 0,0,0 };
	int Graph[96];
    int WatchGraph;
};

//
//関数プロトタイプ宣言
//
//時間定義
void InitTime(Time&time);
//時間の更新情報
int UpdateTime(Time&time, int status);
//時間描画
void DrawTime(Time&time,int status);