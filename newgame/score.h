#pragma once

//�Q�[���X�R�A�֘A�̃X�g���N�g
struct Score
{
	int Number;
	int String[6] = { 51,35,47,50,37,26 };
	int Digit[5] = { 0,0,0,0,0 };
	int Graph[96];
};

//
//�֐��v���g�^�C�v�錾
//
//�Q�[���X�R�A��`
void InitScore(Score&score);
//�X�R�A�̍X�V���
void UpdateScore(Score&score);
//�X�R�A�`��
void DrawScore(Score&score,int status);