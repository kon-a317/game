#include "DxLib.h"
#include "jewel.h"

//宝石定義
void InitJewel(Jewel&jewel)
{
	jewel.Graph = LoadGraph("texture/jewel.png");
    //全ステージの宝石の発生フラグをリセット(TRUEに)
    for (int i = 0; i < STAGE; i++)
    {
        for (int j = 0; j < JEWEL; j++)
        {
            jewel.Flag[i][j] = TRUE;
        }
    }
}

//宝石と自分との当たり判定
int JudgeJewel(Jewel&jewel, int x, int y, int stage)
{
    for (int i = 0; i < JEWEL; i++)
    {
        if (jewel.Posi[stage][i][0] || jewel.Posi[stage][i][1])
        {
            if (jewel.Flag[stage][i])//フラグがTRUEの時のみ判定
            {
                if (((jewel.X[stage][i] < x && jewel.X[stage][i] + 64 > x) || (jewel.X[stage][i] < x + 54 && jewel.X[stage][i] + 64 > x + 54)) &&
                    ((jewel.Y[stage][i] < y && jewel.Y[stage][i] + 54 > y) || (jewel.Y[stage][i] < y + 54 && jewel.Y[stage][i] + 64 > y + 54)))
                {
                    jewel.Flag[stage][i] = FALSE;
                    return 1;
                }
            }
        }
    }
	return 0;
}

//宝石位置情報更新(ステージ変更ごとに座標を読み込む)
void UpdateJewel(Jewel&jewel, int stage)
{
	for (int i = 0; i < JEWEL; i++)
	{
		jewel.X[stage][i] = jewel.Posi[stage][i][0] * MAP_BLOCK_SIZE;
		jewel.Y[stage][i] = jewel.Posi[stage][i][1] * MAP_BLOCK_SIZE;
	}
}

//宝石描画
void DrawJewel(Jewel&jewel, int stage)
{
	for (int i = 0; i < JEWEL; i++)
	{
		//XもYも0の場合は描画しない
		if (jewel.Posi[stage][i][0] || jewel.Posi[stage][i][1])
		{	//発生してるかしてないか
			if (jewel.Flag[stage][i])
			{
				DrawGraph(jewel.Posi[stage][i][0] * 64, jewel.Posi[stage][i][1] * 64, jewel.Graph, TRUE);
			}
		}
	}
}