#pragma once

//���Ԋ֘A
struct Time
{
	int Now;
	int Frame;
	int Limit;
	int Display[3] = { 0,0,0 };
	int Graph[96];
    int WatchGraph;
};

//
//�֐��v���g�^�C�v�錾
//
//���Ԓ�`
void InitTime(Time&time);
//���Ԃ̍X�V���
int UpdateTime(Time&time, int status);
//���ԕ`��
void DrawTime(Time&time,int status);