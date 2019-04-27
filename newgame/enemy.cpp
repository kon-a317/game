
#include "DxLib.h"
#include "enemy.h"

const int EnemyPosi[STAGE][ENEMY][2] = //�X�e�[�W���̏����ʒu�ݒ� �X�e�[�W,�̐�,xy
{
	{},
    {},
    {},
	{
		{ 14,11 },
		{ 0,0 },
		{ 0,0 },
        { 0,0 },
        { 0,0 }
	},
	{
		{ 21,11 },
		{ 19,2 },
		{ 10,5 },
        { 0,0 },
        { 0,0 }
	},
	{
		{ 12,11 },
		{ 21,7 },
		{ 3,3 },
        { 12,3 },
        { 1,7 }
	}
};

const int EnemyWait[STAGE][ENEMY] =	//�G�̕����]���̑ҋ@����
{
	{},
    {},
    {},
	{ 120,0,0,0,0 },
	{ 120,90,60,0,0 },
	{ 60,160,120,90,45 }
};

//�G�̏�����������
const int EnemyDirSave[STAGE][ENEMY] =
{
	{},
    {},
    {},
	{RIGHT,0,0},
	{RIGHT,RIGHT,LEFT,0,0},
	{LEFT,LEFT,LEFT,LEFT,RIGHT}
};

//- - - - - - - - - - - - - - //
//         Enemy����          //
//- - - - - - - - - - - - - - //
void InitEnemy(Enemy&enemy,int stage, int i)
{
	//�摜�̓ǂݍ��݁A�����ʒu�A���x�̒�`
	LoadDivGraph("texture/keikan.png", 2, 2, 1, 64, 64, enemy.Graph);
    enemy.Right = LoadGraph("texture/Right.png");
	GetGraphSize(enemy.Graph[0], &enemy.W, &enemy.H);
	(float)enemy.X = EnemyPosi[stage][i][0] * MAP_BLOCK_SIZE;
	(float)enemy.Y = EnemyPosi[stage][i][1] * MAP_BLOCK_SIZE;
	enemy.Count = EnemyWait[stage][i];
	enemy.Direction = CENTER;
	enemy.BeforeDirection = EnemyDirSave[stage][i];
}

void ResetEnemy(Enemy&enemy, int stage, int i)
{
	(float)enemy.X = EnemyPosi[stage][i][0] * MAP_BLOCK_SIZE;
	(float)enemy.Y = EnemyPosi[stage][i][1] * MAP_BLOCK_SIZE;
	enemy.Count = EnemyWait[stage][i];
	enemy.Direction = CENTER;
	enemy.BeforeDirection = EnemyDirSave[stage][i];
}

//�G�Ƃ̓����蔻��
int JudgeEnemy(int px, int py, int ex, int ey, int ed)
{
	if (((ex + 10 < px && ex + 54 > px) || (ex + 10 < px + 54 && ex + 54 > px + 54)) &&
		((ey + 10 < py && ey + 64 > py) || (ey + 10 < py + 54 && ey + 64 > py + 54)))
	{
		return 1;
	}

    if (ed == RIGHT)
    {
        if (((ex < px && ex + 246 > px) || (ex < px + 54 && ex + 246 > px + 54)) &&
            ((ey < py +10 && ey +  64 > py +10) || (ey < py + 54 && ey +  64 > py + 54)))
        {
            return 1;
        }
    }
    else if (ed == LEFT)
    {
        if (((ex - 192 < px && ex + 54 > px) || (ex - 192 < px + 54 && ex + 54 > px + 54)) &&
            ((ey       < py && ey + 64 > py) || (ey       < py + 54 && ey + 64 > py + 54)))
        {
            return 1;
        }
    }
	return 0;
}

void UpdateEnemy(Enemy&enemy, int stage, int i)
{
	if (enemy.Count)			//�J�E���g��0�łȂ�������
	{
		enemy.Count--;
	}
	else
	{
		enemy.Count = EnemyWait[stage][i];
		if (enemy.Direction == RIGHT || enemy.Direction == LEFT)
		{
			enemy.BeforeDirection = enemy.Direction;	//���O�܂łǂ���������Ă�������ۑ�
			enemy.Direction = CENTER;
		}
		else
		{
			if (enemy.BeforeDirection == RIGHT)		//���O�܂ŉE�������Ă�����
			{
				enemy.Direction = LEFT;				//���x�͍�����������
			}
			else
			{
				enemy.Direction = RIGHT;			//���x�͉E����������
			}
		}
	}
}

void DrawEnemy(Enemy&enemy,int status)
{
    if (status == PLAY)
    {
        enemy.Timer = GetNowCount();
        enemy.Frame = enemy.Timer / 450 % 2;
    }
	if (enemy.Direction == RIGHT)
	{
		DrawGraph((int)enemy.X, (int)enemy.Y, enemy.Graph[enemy.Frame], TRUE);
        SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
        DrawTurnGraph((int)enemy.X + 64, (int)enemy.Y, enemy.Right, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if(enemy.Direction == LEFT)
	{
		DrawTurnGraph((int)enemy.X, (int)enemy.Y, enemy.Graph[enemy.Frame], TRUE);
        SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
        DrawGraph((int)enemy.X - 192, (int)enemy.Y, enemy.Right, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
    else
    {
		if (enemy.BeforeDirection == RIGHT)
		{
			DrawTurnGraph((int)enemy.X, (int)enemy.Y, enemy.Graph[enemy.Frame], TRUE);
		}
		else
		{
			DrawGraph((int)enemy.X, (int)enemy.Y, enemy.Graph[enemy.Frame], TRUE);
		}
    }
}