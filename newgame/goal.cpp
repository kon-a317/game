#include "DxLib.h"
#include "goal.h"

//�o����`
void InitGoal(Goal&goal)
{
	goal.Graph = LoadGraph("texture/deguchi.png");
    goal.StrGraph = LoadGraph("texture/press-a.png");
	goal.X = MAP_BLOCK_SIZE * goal.Posi[3][0];
	goal.Y = MAP_BLOCK_SIZE * goal.Posi[3][1] - 64;
}
//�o���Ǝ����Ƃ̓����蔻��
int JudgeGoal(Goal&goal, int playerX, int playerY)
{
    if (((goal.X      < playerX && goal.X +  64 > playerX) || (goal.X      < playerX + 54 && goal.X +  64 > playerX + 54)) &&
        ((goal.Y + 64 < playerY && goal.Y + 128 > playerY) || (goal.Y + 64 < playerY + 54 && goal.Y + 128 > playerY + 54)))
        //�S�[���n�_�Ǝ������d�Ȃ��Ă�����
	{
        return 1;
	}
	return 0;
}
//�o���ʒu�X�V
void UpdateGoal(Goal&goal, int stage)
{
	goal.X = MAP_BLOCK_SIZE * goal.Posi[stage][0];
	goal.Y = MAP_BLOCK_SIZE * goal.Posi[stage][1] - 64;
}
//�o���`��
void DrawGoal(Goal&goal, int playerX, int playerY)
{
	DrawGraph(goal.X, goal.Y, goal.Graph, TRUE);
    //if (JudgeGoal(goal, playerX, playerY))
    if (((goal.X - 50 < playerX && goal.X + 114 > playerX) || (goal.X - 50 < playerX + 54 && goal.X + 114 > playerX + 54)) &&
        ((goal.Y - 50 < playerY && goal.Y + 172 > playerY) || (goal.Y - 50 < playerY + 54 && goal.Y + 172 > playerY + 54)))
    {//�o���㕔�̕����`��
        DrawGraph(goal.X, goal.Y - 64, goal.StrGraph, TRUE);
    }
}