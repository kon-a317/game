#pragma once

#define SCREEN_W 1600
#define SCREEN_H 900

#define GRAVITY 0.8f
#define MIN_GRAVITY -10.0f

#define PI 3.1415926535897932384626433832795f

#define ENEMY 5
#define JEWEL 7


enum { TITLE, READY, PLAY, MISS, OVER, CLEAR, CONG, MANUAL, CREDIT, CLOSE };

//���̑��C���X�g�֘A�̃X�g���N�g
struct Graph
{
    int Back;
    int Title;
	int jewel;
};

//
//�֐��v���g�^�C�v�錾
//
//���̑��摜�̓ǂݍ���
void InitOther(Graph&graph);
//�w�i�摜�ǂݍ���
void InitBack(Graph&graph);
//�w�i�摜�`��
void DrawBack(Graph&graph);