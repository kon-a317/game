#include "DxLib.h"
#include "goal.h"

//出口定義
void InitGoal(Goal&goal)
{
	goal.Graph = LoadGraph("texture/deguchi.png");
    goal.StrGraph = LoadGraph("texture/press-a.png");
	goal.X = MAP_BLOCK_SIZE * goal.Posi[3][0];
	goal.Y = MAP_BLOCK_SIZE * goal.Posi[3][1] - 64;
}
//出口と自分との当たり判定
int JudgeGoal(Goal&goal, int playerX, int playerY)
{
    if (((goal.X      < playerX && goal.X +  64 > playerX) || (goal.X      < playerX + 54 && goal.X +  64 > playerX + 54)) &&
        ((goal.Y + 64 < playerY && goal.Y + 128 > playerY) || (goal.Y + 64 < playerY + 54 && goal.Y + 128 > playerY + 54)))
        //ゴール地点と自分が重なっていたら
	{
        return 1;
	}
	return 0;
}
//出口位置更新
void UpdateGoal(Goal&goal, int stage)
{
	goal.X = MAP_BLOCK_SIZE * goal.Posi[stage][0];
	goal.Y = MAP_BLOCK_SIZE * goal.Posi[stage][1] - 64;
}
//出口描画
void DrawGoal(Goal&goal, int playerX, int playerY)
{
	DrawGraph(goal.X, goal.Y, goal.Graph, TRUE);
    //if (JudgeGoal(goal, playerX, playerY))
    if (((goal.X - 50 < playerX && goal.X + 114 > playerX) || (goal.X - 50 < playerX + 54 && goal.X + 114 > playerX + 54)) &&
        ((goal.Y - 50 < playerY && goal.Y + 172 > playerY) || (goal.Y - 50 < playerY + 54 && goal.Y + 172 > playerY + 54)))
    {//出口上部の文字描画
        DrawGraph(goal.X, goal.Y - 64, goal.StrGraph, TRUE);
    }
}