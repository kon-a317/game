#pragma once
#include "map.h"
#include "common.h"
#include "Sound.h"

struct Player
{
	float Posi[STAGE][2] = 
	{
		{},
        {200,590},
        {200,590},
		{100,680},
		{700,680},
		{400,680}
	};
	float X;				//X���W
	float Y;				//Y���W
	int W;					//����
	int H;					//�c��
	int Graph[4];			//�摜
    int HashigoGraph[4];    //��q�o��r���̉摜
    int JumpGraph[2];       //�W�����v���̉摜
	int LaughGraph[2];      //�΂��摜(������ʂŎg�p)
    int MissGraph[3];       //�~�X�����摜
    int EscapeGraph[2];     //�E�o���̃L�����L��������摜
	int GladGraph;			//�N���A���̔�ђ��˂�摜
	float Speed;			//���x
	bool AtariFlag;			//�G�ɓ����������ۂ�
	int AtariCount;			//���ɓG�ɓ�����܂ł̃J�E���g
    int Life;               //�c�@
	float JumpVelocity;		//�W�����v���̏d��
	bool JumpFlag;			//�W�����v���Ă��邩�ۂ�
    bool PrevJumpFlag;      //�W�����v�L�[��������Ă��邩�ۂ�
	bool HashigoFlag;		//�͂����̂Ƃ���ɂ��邩�ۂ�
    bool ContactFlag;       //�}�b�v�`�b�v�ƐڐG���Ă��邩�ۂ�
    bool GroundFlag;        //�ڒn���Ă��邩�ۂ�����
	bool Left;				//���������ۂ�
    bool WalkFlag;          //�n�ʂɂ��ĕ����Ă��邩���Ȃ���
	int Frame;
	int Timer;				//�A�j���[�V�����ɂ�������
    int KeepGraph;          //���݂̉摜��ێ�
};

//
//�֐��v���g�^�C�v�錾
//
void InitPlayer(Player&player, int stage);
void ResetPlayer(Player&player, int stage);
void UpdatePlayer(Player&player, Sound&sound, int stage);
void DrawPlayer(Player&player, int status, int count);
void DrawPlayPlayer(Player&player);
void DrawMissPlayer(Player&player, int count);
void DrawOverPlayer(Player&player);
void DrawClearPlayer(Player&player, int count);
void DrawCongPlayer(Player&player, int count);

