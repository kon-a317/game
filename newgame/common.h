#pragma once

#define SCREEN_W 1600
#define SCREEN_H 900

#define GRAVITY 0.8f
#define MIN_GRAVITY -10.0f

#define PI 3.1415926535897932384626433832795f

#define ENEMY 5
#define JEWEL 7


enum { TITLE, READY, PLAY, MISS, OVER, CLEAR, CONG, MANUAL, CREDIT, CLOSE };

//その他イラスト関連のストラクト
struct Graph
{
    int Back;
    int Title;
	int jewel;
};

//
//関数プロトタイプ宣言
//
//その他画像の読み込み
void InitOther(Graph&graph);
//背景画像読み込み
void InitBack(Graph&graph);
//背景画像描画
void DrawBack(Graph&graph);