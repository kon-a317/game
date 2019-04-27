#pragma once
#include "common.h"
#include "Map.h"

//��Ί֘A�̃X�g���N�g
struct Jewel
{
	int Graph;
	int X[STAGE][JEWEL];
	int Y[STAGE][JEWEL];
	//��΂̔�������
	int Flag[STAGE][JEWEL] =
	{
		{},
        {},
        {},
		{ TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE },
		{ TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE },
		{ TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE }
	};
	//��΂̈ʒu�ݒ�
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
//�֐��v���g�^�C�v�錾
//
//��Β�`
void InitJewel(Jewel&jewel);
//��΂Ƃ̓����蔻��
int JudgeJewel(Jewel&jewel, int x, int y, int stage);
//��΂̈ʒu�X�V
void UpdateJewel(Jewel&jewel, int stage);
//��Ε`��
void DrawJewel(Jewel&jewel, int stage);