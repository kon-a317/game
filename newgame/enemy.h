#pragma once
#include"common.h"
#include"map.h"

struct Enemy
{
	float X;					//X���W
	float Y;					//Y���W
	int W;					//����
	int H;					//�c��
	int Graph[2];				//�摜
    int Right;				//���̉摜
	int Speed;				//���x
	int HP;					//�̗�
	int Count;
	int Direction;			//�����ۑ��p�֐�
	int BeforeDirection;	//�����ۑ��p�֐�(���O�܂łǂ���������Ă�����)
	int Timer;				//�A�j���[�V�����p
	int Frame;				//�A�j���[�V�����p
};

enum { LEFT, RIGHT, CENTER };	//�E�������A�������e
extern const int EnemyPosi[STAGE][ENEMY][2];//�X�e�[�W���̏����ʒu�ݒ� �X�e�[�W,�̐�,xy
extern const int EnemyWait[STAGE][ENEMY];//�G�̕����]���̑ҋ@����
extern const int EnemyDirSave[STAGE][ENEMY];

//- - - - - - - - - - - - - - - //
//    enemy�v���g�^�C�v�錾     //
//- - - - - - - - - - - - - - - //
void InitEnemy(Enemy&enemy, int stage, int i);
void ResetEnemy(Enemy&enemy, int stage, int i);
int JudgeEnemy(int px, int py, int ex, int ey, int ed);
void UpdateEnemy(Enemy&enemy, int stage, int i);
void DrawEnemy(Enemy&enemy, int status);

