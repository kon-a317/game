#include "DxLib.h"
#include "jewel.h"

//��Β�`
void InitJewel(Jewel&jewel)
{
	jewel.Graph = LoadGraph("texture/jewel.png");
    //�S�X�e�[�W�̕�΂̔����t���O�����Z�b�g(TRUE��)
    for (int i = 0; i < STAGE; i++)
    {
        for (int j = 0; j < JEWEL; j++)
        {
            jewel.Flag[i][j] = TRUE;
        }
    }
}

//��΂Ǝ����Ƃ̓����蔻��
int JudgeJewel(Jewel&jewel, int x, int y, int stage)
{
    for (int i = 0; i < JEWEL; i++)
    {
        if (jewel.Posi[stage][i][0] || jewel.Posi[stage][i][1])
        {
            if (jewel.Flag[stage][i])//�t���O��TRUE�̎��̂ݔ���
            {
                if (((jewel.X[stage][i] < x && jewel.X[stage][i] + 64 > x) || (jewel.X[stage][i] < x + 54 && jewel.X[stage][i] + 64 > x + 54)) &&
                    ((jewel.Y[stage][i] < y && jewel.Y[stage][i] + 54 > y) || (jewel.Y[stage][i] < y + 54 && jewel.Y[stage][i] + 64 > y + 54)))
                {
                    jewel.Flag[stage][i] = FALSE;
                    return 1;
                }
            }
        }
    }
	return 0;
}

//��Έʒu���X�V(�X�e�[�W�ύX���Ƃɍ��W��ǂݍ���)
void UpdateJewel(Jewel&jewel, int stage)
{
	for (int i = 0; i < JEWEL; i++)
	{
		jewel.X[stage][i] = jewel.Posi[stage][i][0] * MAP_BLOCK_SIZE;
		jewel.Y[stage][i] = jewel.Posi[stage][i][1] * MAP_BLOCK_SIZE;
	}
}

//��Ε`��
void DrawJewel(Jewel&jewel, int stage)
{
	for (int i = 0; i < JEWEL; i++)
	{
		//X��Y��0�̏ꍇ�͕`�悵�Ȃ�
		if (jewel.Posi[stage][i][0] || jewel.Posi[stage][i][1])
		{	//�������Ă邩���ĂȂ���
			if (jewel.Flag[stage][i])
			{
				DrawGraph(jewel.Posi[stage][i][0] * 64, jewel.Posi[stage][i][1] * 64, jewel.Graph, TRUE);
			}
		}
	}
}