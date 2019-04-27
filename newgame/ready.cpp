#include "DxLib.h"
#include "ready.h"
#include "common.h"
#include "player.h"

//������ʏ�����`
void InitReady(Ready&ready)
{
    //�摜�ǂݍ���
	ready.Steps = LoadGraph("texture/kaidan.png");
}

//������ʍX�V
void UpdateReady(Ready & ready, Player&player)
{
	ready.Count++;
	player.Timer = GetNowCount();
	if (ready.Count < 125)
	{
		player.X += 5;
		player.Frame = player.Timer / 200 % 4;
	}
	else if (ready.Count >= 125)
	{
		player.Frame = player.Timer / 100 % 4;
	}
}

//������ʂ̃A�j���[�V�����ɂ������āA���l�̃��Z�b�g
void ResetReady(Ready&ready, Player&player)
{
	ready.Count = 0;
	player.X = 300;
	player.Y = 600;
}

//������ʕ`��(�v���C���[�A�K�i�`��)&SE
void DrawReady(Ready & ready, Player&player, Sound&sound)
{
	if (ready.Count < 125)
	{
		DrawGraph(player.X, player.Y, player.Graph[player.Frame], TRUE);
        if (CheckSound(sound, WALK) == FALSE)
        {
            ONSound(sound, WALK);
        }
	}
	else if (125 <= ready.Count && ready.Count < 200)
	{
        OFFSound(sound, WALK);
		DrawGraph(player.X, player.Y, player.LaughGraph[player.Frame % 2], TRUE);
	}
    else if(ready.Count >= 200)
    {
        if (CheckSound(sound, KAIDAN) == FALSE)
        {
            ONSound(sound, KAIDAN);
        }
    }
    DrawGraph(1000, 600, ready.Steps, TRUE);
}