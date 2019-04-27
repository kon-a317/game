#pragma once

//ゲームスコア関連のストラクト
struct Score
{
	int Number;
	int String[6] = { 51,35,47,50,37,26 };
	int Digit[5] = { 0,0,0,0,0 };
	int Graph[96];
};

//
//関数プロトタイプ宣言
//
//ゲームスコア定義
void InitScore(Score&score);
//スコアの更新情報
void UpdateScore(Score&score);
//スコア描画
void DrawScore(Score&score,int status);