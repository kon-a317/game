#include "DxLib.h"
#include "string.h"
#include "common.h"

char character;
int characterGraph;

//�����𐔒l�ɕϊ�����
void ConfigStrings(Strings & strings, char *str, int num)
{
    for (int i = 0; i < num; i++)
    {
		switch (str[i])
		{
		case '!':
		{
			str[i] = 26;
			break;
		}
		case '?':
		{
			str[i] = 27;
			break;
		}
		case '.':
		{
			str[i] = 29;
			break;
		}
		default :
		{
			str[i] = str[i] - 65;
			break;
		}
		}
    }
}

//������`
void InitStrings(Strings&strings)
{
    LoadDivGraph("texture/font-org.png", 33, 11, 3, 29, 24, strings.Graph);
	//�e�������w��
    strings.EnterNum = 13;
    strings.GameStartNum = 10;
    strings.ManualNum = 6;
    strings.CreditNum = 6;
    strings.PlessNum = 5;
    strings.WalkNum = 4;
	strings.SpaseNum = 5;
    strings.JumpNum = 4;
    strings.HashigoNum = 7;
    strings.ExitNum = 4;
    strings.ReadyNum = 7;
	strings.TimeLimitNum = 10;
    strings.SkipNum = 4;
	strings.NextNum = 4;
    strings.MissNum = 5;
	strings.TimeOverNum = 9;
    strings.GameOverNum = 9;
    strings.StageClearNum = 11;
    strings.GameClearNum = 10;
	strings.CongratulationsNum = 16;
    strings.SEUseNum = 13;
    strings.SEUse2Num = 12;
    strings.BGMUseNum = 17;
	strings.BGMUse2Num = 15;
	strings.BGMUse3Num = 12;
    //�e������̕ϊ�
    ConfigStrings(strings, strings.Enter, strings.EnterNum);
    ConfigStrings(strings, strings.GameStart, strings.GameStartNum);
    ConfigStrings(strings, strings.Manual, strings.ManualNum);
    ConfigStrings(strings, strings.Credit, strings.CreditNum);
    ConfigStrings(strings, strings.Pless, strings.PlessNum);
    ConfigStrings(strings, strings.Walk, strings.WalkNum);
	ConfigStrings(strings, strings.Spase, strings.SpaseNum);
    ConfigStrings(strings, strings.Jump, strings.JumpNum);
    ConfigStrings(strings, strings.Hashigo, strings.HashigoNum);
    ConfigStrings(strings, strings.Exit, strings.ExitNum);
    ConfigStrings(strings, strings.Ready, strings.ReadyNum);
	ConfigStrings(strings, strings.TimeLimit, strings.TimeLimitNum);
    ConfigStrings(strings, strings.Skip, strings.SkipNum);
	ConfigStrings(strings, strings.Next, strings.NextNum);
    ConfigStrings(strings, strings.Miss, strings.MissNum);
	ConfigStrings(strings, strings.TimeOver, strings.TimeOverNum);
    ConfigStrings(strings, strings.GameOver, strings.GameOverNum);
    ConfigStrings(strings, strings.StageClear, strings.StageClearNum);
    ConfigStrings(strings, strings.GameClear, strings.GameClearNum);
	ConfigStrings(strings, strings.Congratulations, strings.CongratulationsNum);
    ConfigStrings(strings, strings.SEUse, strings.SEUseNum);
    ConfigStrings(strings, strings.SEUse2, strings.SEUse2Num);
    ConfigStrings(strings, strings.BGMUse, strings.BGMUseNum);
	ConfigStrings(strings, strings.BGMUse2, strings.BGMUse2Num);
	ConfigStrings(strings, strings.BGMUse3, strings.BGMUse3Num);
}


//�����\���֐�
void DrawStrings(Strings&strings, int status)
{
	switch (status)
	{
	case TITLE:
	{
        DrawTitleStrings(strings);
		break;
	}
    case MANUAL:
    {
        DrawManualStrings(strings);
        break;
    }
    case CREDIT:
    {
        DrawCreditStrings(strings);
        break;
    }
	case READY:
	{
        DrawReadyStrings(strings);
		break;
	}
	case MISS:
	{
        DrawMissStrings(strings);
		break;
	}
	case OVER:
	{
        DrawOverStrings(strings);
		break;
	}
    case CLEAR:
    {
        DrawClearStrings(strings);
        break;
    }
	case CONG:
	{
		DrawCongStrings(strings);
	}
	break;
	}
}

//�����`��֐�
void DrawALLStrings(Strings&strings, char str[], int num, int X, int Y, float ExRate)
{
	for (int i = 0; i < num; i++)
	{
		character = str[i];
		characterGraph = strings.Graph[character];
		DrawRotaGraph(X + ((STRINGS_W * ExRate) * i), Y, ExRate, 0, characterGraph, TRUE);
	}
}

//���`��
void DrawArrow(Strings&strings, int X, int Y, int div)
{
	switch (div)
	{
	case ARIGHT:
	{
		DrawRotaGraph(X, Y, 1.0, PI * 0.5, strings.Graph[30], TRUE);
		break;
	}
	case ALEFT:
	{
		DrawRotaGraph(X, Y, 1.0, PI * 1.5, strings.Graph[30], TRUE);
		break;
	}
	case AUP:
	{
		DrawRotaGraph(X, Y, 1.0, 0, strings.Graph[30], TRUE);
		break;
	}
	case ADOWN:
	{
		DrawRotaGraph(X, Y, 1.0, PI, strings.Graph[30], TRUE);
		break;
	}
	}
}

//�^�C�g����ʕ����`��
void DrawTitleStrings(Strings & strings)
{
	DrawALLStrings(strings, strings.GameStart, strings.GameStartNum, 645, 600, 1.0);
	DrawALLStrings(strings, strings.Manual, strings.ManualNum, 705, 650, 1.0);
    DrawALLStrings(strings, strings.Credit, strings.CreditNum, 705, 700, 1.0);
	DrawALLStrings(strings, strings.Exit, strings.ExitNum, 730, 750, 1.0);
	DrawALLStrings(strings, strings.Enter, strings.EnterNum, 640, 800, 0.8);

}

//�}�j���A����ʕ����`��
void DrawManualStrings(Strings&strings)
{
	//�����������
	DrawALLStrings(strings, strings.Pless, strings.PlessNum, 180, 440, 1.0);
	DrawALLStrings(strings, strings.Walk, strings.WalkNum, 200, 500, 1.0);
	DrawArrow(strings, 225, 470, ALEFT);
	DrawArrow(strings, 265, 470, ARIGHT);
	//�W�����v�������
	DrawALLStrings(strings, strings.Pless, strings.PlessNum, 460, 340, 1.0);
	DrawALLStrings(strings, strings.Jump, strings.JumpNum, 475, 400, 1.0);
	DrawALLStrings(strings, strings.Spase, strings.SpaseNum, 460, 370, 1.0);
	//��q�������
	DrawALLStrings(strings, strings.Pless, strings.PlessNum, 1020, 540, 1.0);
	DrawALLStrings(strings, strings.Hashigo, strings.HashigoNum, 1000, 600, 1.0);
	DrawArrow(strings, 1045, 570, AUP);
	DrawArrow(strings, 1085, 570, ADOWN);
}

//�N���W�b�g��ʕ����\��
void DrawCreditStrings(Strings&strings)

{
    DrawALLStrings(strings, strings.SEUse, strings.SEUseNum, 450, 200, 1.5);
    DrawALLStrings(strings, strings.SEUse2, strings.SEUse2Num, 670, 280, 1.5);
    DrawALLStrings(strings, strings.BGMUse, strings.BGMUseNum, 450, 360, 1.5);
	DrawALLStrings(strings, strings.BGMUse2, strings.BGMUse2Num, 670, 440, 1.5);
	DrawALLStrings(strings, strings.BGMUse3, strings.BGMUse3Num, 670, 520, 1.5);
}

//������ʕ����`��
void DrawReadyStrings(Strings & strings)
{
	DrawALLStrings(strings, strings.Ready, strings.ReadyNum, 630, 350, 2.3);
	DrawALLStrings(strings, strings.Pless, strings.PlessNum, 800, 700, 0.8);
	DrawRotaGraph(950, 700, 0.8, 0, strings.Graph[18], TRUE);
	DrawALLStrings(strings, strings.Skip, strings.SkipNum, 1000, 700, 0.8);
	DrawALLStrings(strings, strings.TimeLimit, strings.TimeLimitNum, 640, 450, 1.0);
}

//�~�X��ʕ����`��
void DrawMissStrings(Strings & strings)
{
	DrawALLStrings(strings, strings.Miss, strings.MissNum, 680, 450, 2.0);
}

//�^�C���I�[�o�[�����`��
void DrawTimeStrings(Strings&strings)
{
	DrawALLStrings(strings, strings.TimeOver, strings.TimeOverNum, 540, 380, 2.0);
}

//�Q�[���I�[�o�[��ʕ����`��
void DrawOverStrings(Strings & strings)
{
	DrawALLStrings(strings, strings.GameOver, strings.GameOverNum, 500, 400, 2.3);
	DrawALLStrings(strings, strings.Pless, strings.PlessNum, 800, 700, 0.8);
	DrawRotaGraph(950, 700, 0.8, 0, strings.Graph[18], TRUE);
	DrawALLStrings(strings, strings.Skip, strings.SkipNum, 1000, 700, 0.8);
}

//�X�e�[�W�N���A��ʕ����`��
void DrawClearStrings(Strings & strings)
{
	DrawALLStrings(strings, strings.StageClear, strings.StageClearNum, 500, 450, 2.0);
	DrawALLStrings(strings, strings.Pless, strings.PlessNum, 800, 550, 0.8);
	DrawRotaGraph(950, 550, 0.8, 0, strings.Graph[18], TRUE);
	DrawALLStrings(strings, strings.Next, strings.NextNum, 1000, 550, 0.8);
}

//�Q�[���N���A��ʕ����\��
void DrawCongStrings(Strings & strings)
{
	DrawALLStrings(strings, strings.GameClear, strings.GameClearNum, 550, 350, 2.0);
	DrawALLStrings(strings, strings.Congratulations, strings.CongratulationsNum, 370, 420, 2.0);
}


//�^�C�g����ʃJ�[�\����`
void InitCursor(Cursor&cursor, Strings&strings)
{
	cursor.Graph = strings.Graph[28];
	cursor.Count = 0;
    cursor.AgainCount = 10;             //�J�[�\�����������������Ȃ��悤�ɃJ�E���g�Œx�߂�
}

//�J�[�\���ɂ��Ă̍X�V���
void UpdateCursor(Cursor&cursor, Sound&sound)
{
    if (cursor.AgainCount)//�J�[�\���̃J�E���g����������
    {
        cursor.AgainCount--;
    }
    else
    {
        if (CheckHitKey(KEY_INPUT_UP))
        {//��L�[�������ꂽ��J�[�\�������܂��͈�ԉ���
            cursor.Count--;
            ONSound(sound, SELECT);
            if (cursor.Count == -1)
            {
                cursor.Count = 3;
            }
            cursor.AgainCount = 10;
        }
        if (CheckHitKey(KEY_INPUT_DOWN))
        {//���L�[�������ꂽ���L���l
            cursor.Count++;
            ONSound(sound, SELECT);
            if (cursor.Count == 4)
            {
                cursor.Count = 0;
            }
            cursor.AgainCount = 10;
        }
    }
}

//�J�[�\���`��
void DrawCursor(Cursor&cursor)
{
	DrawRotaGraph(600, 600 + (cursor.Count * 50), 1.0f, 0, cursor.Graph, TRUE);
}