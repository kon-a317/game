#pragma once
#include "Sound.h"

struct Player;

//������ʂ̃X�g���N�g
struct Ready
{
	int Steps;              //�K�i�摜
	int Count;              //������ʂ�\�������鎞�Ԃ��J�E���g
};


//
//�֐��v���g�^�C�v�錾
//
void InitReady(Ready&ready);
void UpdateReady(Ready&ready, Player&player);
void ResetReady(Ready&ready, Player&player);
void DrawReady(Ready&ready, Player&player, Sound&sound);