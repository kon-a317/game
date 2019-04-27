#pragma once
#include"DxLib.h"


//���֘A�̃X�g���N�g
struct Sound
{
	int TitleBGM;
	int PlayBGM;
	int ClearBGM;
	int CongBGM;
	int MissBGM;
	int OverBGM;
	int WalkSE;
	int JumpSE;
	int HitSE;
	int GetJewelSE;
    int MissSE;
    int KaidanSE;
    int SelectSE;
    int EnterSE;

	int volume;
};

enum { JUMP, WALK, HIT, GET, MISSS, KAIDAN, SELECT, ENTER};		//SE�̎��

//
//�֐��v���g�^�C�v�錾
//
void InitSound(Sound&sound);
void ONBGM(Sound&sound, int status);
void OFFBGM(Sound&sound, int status);
int  CheckBGM(Sound&sound, int status);
void ONSound(Sound&sound, int type);
void OFFSound(Sound&sound, int type);
int  CheckSound(Sound&sound, int type);