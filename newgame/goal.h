#pragma once
#include "map.h"

//�o���֘A�̃X�g���N�g
struct Goal
{
	int X;
	int Y;
	int Graph;
    int StrGraph;
	//�S�[���̈ʒu�ݒ�
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

//�o����`
void InitGoal(Goal&goal);
//�S�[���Ƃ̓����蔻��
int JudgeGoal(Goal&goal, int playerX, int playerY);
//�o���ʒu�X�V
void UpdateGoal(Goal&goal, int stage);
//�o���`��
void DrawGoal(Goal&goal, int playerX, int playerY);
