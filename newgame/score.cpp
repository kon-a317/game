#include "DxLib.h"
#include "common.h"
#include "score.h"

//ゲームスコア設定
void InitScore(Score&score)
{
	score.Number = 0;
	LoadDivGraph("texture/font.bmp", 96, 16, 6, 16, 18, score.Graph);
}
//スコア更新情報
void UpdateScore(Score&score)
{
	score.Digit[0] = score.Number / 10000;
	score.Digit[1] = (score.Number % 10000) / 1000;
	score.Digit[2] = (score.Number % 1000) / 100;
	score.Digit[3] = (score.Number % 100) / 10;
	score.Digit[4] = score.Number % 10;
}
//スコア描画
void DrawScore(Score&score, int status)
{
    if (status == PLAY || status == MISS || status == CLEAR)
    {
        for (int i = 0; i < 6; i++)
        {
            DrawRotaGraph(1100 + (32 * i), 50, 1.5f, 0, score.Graph[score.String[i]], TRUE);
        }
        for (int i = 0; i < 5; i++)
        {
            DrawRotaGraph(1300 + (32 * i), 50, 1.5f, 0, score.Graph[16 + score.Digit[i]], TRUE);
        }
    }
    else if(status == OVER || status == CONG)
    {
        for (int i = 0; i < 6; i++)
        {
            DrawRotaGraph(600 + (32 * i), 500, 1.5f, 0, score.Graph[score.String[i]], TRUE);
        }
        for (int i = 0; i < 5; i++)
        {
            DrawRotaGraph(800 + (32 * i), 500, 1.5f, 0, score.Graph[16 + score.Digit[i]], TRUE);
        }
    }
    //else if (status == CONG)
    //{
    //    for (int i = 0; i < 6; i++)
    //    {
    //        DrawRotaGraph(1100 + (32 * i), 50, 1.5f, 0, score.Graph[score.String[i]], TRUE);
    //    }
    //    for (int i = 0; i < 5; i++)
    //    {
    //        DrawRotaGraph(1300 + (32 * i), 50, 1.5f, 0, score.Graph[16 + score.Digit[i]], TRUE);
    //    }
    //}
}