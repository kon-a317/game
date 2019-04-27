
#include "DxLib.h"
#include "player.h"
#include "enemy.h"
#include "common.h"
#include "map.h"
#include "time.h"
#include "goal.h"
#include "jewel.h"
#include "score.h"
#include "ready.h"
#include "string.h"
#include "Sound.h"




int status;						//�Q�[���̏��
int stage;						//�����X�e�[�W�߂�

bool KeyPushFlag = FALSE;		//��������̃L�[���������ςȂ����ۂ�

//Sound�X�g���N�g�̏�����
Sound sound;



//- - - - - - - - - - - - - - //
//      �Q�[������������      //
//- - - - - - - - - - - - - - //
void InitGame(Player&player,Enemy enemy[], int enemyNum)
{
	//�E�B���h�E���[�h�ɂ���
	ChangeWindowMode(TRUE);

	SetGraphMode(SCREEN_W, SCREEN_H, 16);

	status = TITLE;
	stage = 0;

	InitPlayer(player, stage);
	for (int i = 0; i < enemyNum; i++)
	{//x��y��0�̏ꍇ�A������`���Ȃ�
		InitEnemy(enemy[i], stage, i);
	}

    //�`���𗠉�ʂ�
    SetDrawScreen(DX_SCREEN_BACK);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)//���C�u��������������
	{
		return -1;//�G���[���N������I��
	}
	
	//Player�X�g���N�g�̏�����
	Player player;
	//Enemy�X�g���N�g�̏�����
	Enemy enemy[ENEMY];
    //Graph�X�g���N�g�̏�����
    Graph graph;
	//map�X�g���N�g�̏�����
	Map map;
	//Time�X�g���N�g�̏�����
	Time time;
	//Goal�X�g���N�g�̏�����
	Goal goal;
	//Jewel�X�g���N�g�̏�����
	Jewel jewel;
	//�X�R�A�X�g���N�g�̏�����
	Score score;
    //������ʃX�g���N�g�̏�����
	Ready ready;
	//String�X�g���N�g�̏�����
	Strings strings;
	//Cursou�X�g���N�g�̏�����
	Cursor cursor;
    ////Manual�X�g���N�g�̏�����
    //Manual manual;


    //�Q�[���̏�����
	InitGame(player, enemy, ENEMY);
    InitMap(map);
    InitOther(graph);
	InitTime(time);
	InitGoal(goal);
	InitJewel(jewel);
	UpdateJewel(jewel, stage);
	InitScore(score);
    InitBack(graph);
	InitReady(ready);
	ResetReady(ready,player);
	InitStrings(strings);
	InitCursor(cursor, strings);
	InitSound(sound);

	while (status != CLOSE)
	{

        //�^�C�g�����
		if (status == TITLE)
		{
			//BGM��~
			OFFBGM(sound, status);
			//BGM�Đ�
			if (CheckBGM(sound, TITLE) == FALSE)
			{
				ONBGM(sound, TITLE);
			}
			while (true)
			{
				ClearDrawScreen();
				UpdateCursor(cursor, sound);

				DrawBack(graph);                                            //�w�i�摜�`��
				DrawMap(map, stage);
				DrawRotaGraph(750, 350, 3.5f, 0, graph.Title, TRUE, 0);     //�^�C�g�������`��
				DrawStrings(strings, status);                               //�����`��
				DrawCursor(cursor);                                         //�J�[�\���`��
				//����ʂ̓��e��\��ʂɔ��f������
				ScreenFlip();

				//A�L�[�ŃQ�[���X�^�[�g
				if (CheckHitKey(KEY_INPUT_A))
				{
					if (KeyPushFlag == FALSE)
					{
						ONSound(sound, ENTER);
						switch (cursor.Count)
						{
						case 0:
						{
							//�Q�[���̏�����
							InitGame(player, enemy, ENEMY);
							InitMap(map);
							InitOther(graph);
							InitTime(time);
							InitGoal(goal);
							InitJewel(jewel);
							InitScore(score);
							InitBack(graph);
							InitReady(ready);
							ResetReady(ready, player);
							InitCursor(cursor, strings);
							stage += 3;
							UpdateJewel(jewel, stage);

							status = READY;
							break;
						}
						case 1:
						{
							stage++;
							ResetPlayer(player, stage);
							UpdateGoal(goal, stage);
							status = MANUAL;
							break;
						}
						case 2:
						{
							stage = 2;
							ResetPlayer(player, stage);
							UpdateGoal(goal, stage);
							status = CREDIT;
							break;
						}
						case 3:
						{
							status = CLOSE;
							break;
						}
						}
					}
					break;
				}
				else
				{
					KeyPushFlag = FALSE;
				}
				//ESC����������Q�[���I��
				if (CheckHitKey(KEY_INPUT_ESCAPE))
				{
					status = CLOSE;
					break;
				}
			}
		}

        //�}�j���A�����
        if (status == MANUAL)
        {
            ClearDrawScreen();
            UpdatePlayer(player, sound, stage);
            DrawBack(graph);
            DrawMap(map, stage);
            DrawStrings(strings, status);
            DrawGoal(goal, (int)player.X, (int)player.Y);
            DrawPlayer(player, status, 0);
            if (JudgeGoal(goal, (int)player.X, (int)player.Y))
            {
                if (CheckHitKey(KEY_INPUT_A))
                {
					KeyPushFlag = TRUE;		//�L�[�������ςȂ��ɂ��X�e�[�^�X�̐؂�ւ���h�~
                    stage--;
                    status = TITLE;
                }
				else
				{
					KeyPushFlag = FALSE;
				}
            }
            //����ʂ̓��e��\��ʂɔ��f������
            ScreenFlip();

            //ESC����������Q�[���I��
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                status = CLOSE;
            }
        }

        //�N���W�b�g���
        if (status == CREDIT)
        {
            ClearDrawScreen();
            UpdatePlayer(player, sound, stage);
            DrawBack(graph);
            DrawMap(map, stage);
            DrawStrings(strings, status);
            DrawGoal(goal, (int)player.X, (int)player.Y);
            DrawPlayer(player, status, 0);
            if (JudgeGoal(goal, (int)player.X, (int)player.Y))
            {
                if (CheckHitKey(KEY_INPUT_A))
                {
                    KeyPushFlag = TRUE;		//�L�[�������ςȂ��ɂ��X�e�[�^�X�̐؂�ւ���h�~
                    stage = 0;
                    status = TITLE;
                }
            }
            //����ʂ̓��e��\��ʂɔ��f������
            ScreenFlip();

            //ESC����������Q�[���I��
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                status = CLOSE;
            }
        }

		//�Q�[���J�n�O�������
		if (status == READY)
		{
			while (ready.Count < 250)
			{
				ClearDrawScreen();
				UpdateReady(ready, player);
				DrawReady(ready, player, sound);
                DrawStrings(strings,status);
				DrawTime(time,status);
				OFFBGM(sound, status);
				//����ʂ̓��e��\��ʂɔ��f������
				ScreenFlip();
				//S�������ăX�L�b�v
				if (CheckHitKey(KEY_INPUT_S))
				{
					if (KeyPushFlag == FALSE)
					{
						status = PLAY;
						break;
					}
				}
				else
				{
					KeyPushFlag = FALSE;
				}
				//ESC����������Q�[���I��
				if (CheckHitKey(KEY_INPUT_ESCAPE))
				{
					status = CLOSE;
					break;
				}
			}
			ResetPlayer(player, stage);
			for (int i = 0; i < ENEMY; i++)
			{
				ResetEnemy(enemy[i], stage, i);
			}

			status = PLAY;
		}

        //�v���C���
		if (status == PLAY)
		{
			if (CheckBGM(sound, status) == FALSE)
			{
				//BGM�Đ�
				ONBGM(sound, status);
			}

			//��ʂɂ�����̂���x�S����
            ClearDrawScreen();

			//���@����
			UpdatePlayer(player, sound, stage);
			//�G�ړ��E�G�Ƃ̓����蔻��
			for (int i = 0; i < ENEMY; i++)
			{	//�G���ݒ肳��Ă�����
				if (EnemyPosi[stage][i][0] || EnemyPosi[stage][i][1])
				{
					UpdateEnemy(enemy[i], stage, i);
					if (JudgeEnemy((int)player.X, (int)player.Y, enemy[i].X, enemy[i].Y, enemy[i].Direction))
					{
                        status = MISS;
					}
				}
			}	

			//�S�[���Ƃ̓����蔻��
			if (JudgeGoal(goal, (int)player.X, (int)player.Y))
			{
                DrawGraph(goal.X, goal.Y - 64, goal.StrGraph, TRUE);
                if (CheckHitKey(KEY_INPUT_A))
                {
                    status = CLEAR;
                }
			}

			//��΂Ƃ̓����蔻��
			if (JudgeJewel(jewel, (int)player.X, (int)player.Y, stage))
			{
				score.Number += 500;
				ONSound(sound, GET);
			}
			//�X�R�A�Έ�
			UpdateScore(score);
			//���Ԑ����Έ�
			if (UpdateTime(time, status))
			{
				status = MISS;
			}

            //�w�i�摜�`��
            DrawBack(graph);
			//�G�L�����`��
			for (int i = 0; i < ENEMY; i++)
			{
				if (EnemyPosi[stage][i][0] || EnemyPosi[stage][i][1])
				{
					DrawEnemy(enemy[i], status);
				}
			}
			//�w�i�`��
            DrawMap(map, stage);
			//�X�R�A�`��
			DrawScore(score,status);
			//�������ԕ`��
			DrawTime(time,status);
			//�o���`��
			DrawGoal(goal, (int)player.X, (int)player.Y);
			//��Ε`��
			DrawJewel(jewel, stage);
			//�v���C���[�`��
			DrawPlayer(player,status,FALSE);

            // ����ʂ̓��e��\��ʂɔ��f������
            ScreenFlip();

			//ESC����������Q�[���I��
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				status = CLOSE;
			}
		}
		
		//�~�X���
		if (status == MISS)
		{
            ONSound(sound, MISSS);
			OFFBGM(sound, status);
            int count = 0;//���u��
            while (count < 240)
            {
                if(CheckSound(sound, MISSS) == FALSE)
                {
                    if (CheckBGM(sound, MISS) == FALSE)
                    {
                        ONBGM(sound, MISS);
                    }
                }
                ClearDrawScreen();
                //�w�i�摜�`��
                DrawBack(graph);
                //�G�L�����`��
                for (int i = 0; i < ENEMY; i++)
                {
                    if (EnemyPosi[stage][i][0] || EnemyPosi[stage][i][1])
                    {
                        DrawEnemy(enemy[i], status);
                    }
                }
                //�w�i�`��
                DrawMap(map, stage);
                //�X�R�A�`��
                DrawScore(score, status);
                //�������ԕ`��
                DrawTime(time,status);
                //�o���`��
                DrawGoal(goal, (int)player.X, (int)player.Y);
                //��Ε`��
                DrawJewel(jewel, stage);
                //�v���C���[�`��
                DrawPlayer(player, status, count);
				//�����`��
                DrawStrings(strings, status);
				if (time.Limit == 0)
				{
					DrawTimeStrings(strings);
				}
                count++;
			// ����ʂ̓��e��\��ʂɔ��f������
                ScreenFlip();
            }
            player.Life--;
            if (player.Life < 1 || time.Limit == 0)
            {
                status = OVER;
            }
            else
            {
                ResetReady(ready, player);
                status = READY;
            }

			//ESC����������Q�[���I��
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				status = CLOSE;
			}
		}

		//�Q�[���I�[�o�[���
		if (status == OVER)
		{
			//BGM�Đ�
			ONBGM(sound, status);
			while (true)
			{
				ClearDrawScreen();
				DrawStrings(strings, status);
				DrawScore(score, status);
				DrawPlayer(player, status, 0);

				//����ʂ̓��e��\��ʂɔ��f������
				ScreenFlip();

				//X�L�[����������^�C�g����
				if (CheckHitKey(KEY_INPUT_S))
				{
					stage = 0;
					status = TITLE;
					break;
				}
				//ESC����������Q�[���I��
				if (CheckHitKey(KEY_INPUT_ESCAPE))
				{
					status = CLOSE;
					break;
				}
			}
		}

        //�X�e�[�W�N���A���
		if (status == CLEAR)
		{
			OFFBGM(sound, status);
            OFFSound(sound, WALK);
            OFFSound(sound, HIT);
            OFFSound(sound, JUMP);
            int count = 0;

            while (count <= 185)
            {
                ClearDrawScreen();
                //�w�i�摜�`��
                DrawBack(graph);
                //�G�L�����`��
                for (int i = 0; i < ENEMY; i++)
                {
                    if (EnemyPosi[stage][i][0] || EnemyPosi[stage][i][1])
                    {
                        DrawEnemy(enemy[i], status);
                    }
                }
                //�w�i�`��
                DrawMap(map, stage);
                //�X�R�A�`��
                DrawScore(score, status);
                //�������ԕ`��
                DrawTime(time,status);
                //�o���`��
                DrawGoal(goal, (int)player.X, (int)player.Y);
                //��Ε`��
                DrawJewel(jewel, stage);
                //�v���C���[�`��
                DrawPlayer(player, status, count);
                count++;
                // ����ʂ̓��e��\��ʂɔ��f������
                ScreenFlip();
            }
			if (CheckBGM(sound, status) == FALSE)
			{//BGM�Đ�
				ONBGM(sound, status);
			}
			DrawStrings(strings, status);
			DrawScore(score, status);
            // ����ʂ̓��e��\��ʂɔ��f������
            ScreenFlip();
            //�L�[�������܂ŉ�ʂ��̂܂�
            while(true)
            { 
			//S�L�[���������玟�̃X�e�[�W�܂��̓^�C�g����
                if (CheckHitKey(KEY_INPUT_S))
                {
                    if (KeyPushFlag == FALSE)
                    {
                        KeyPushFlag = TRUE;
                        stage++;
                        //�o�����W�̍X�V
                        UpdateGoal(goal, stage);
                        //��΂̈ʒu�X�V
                        UpdateJewel(jewel, stage);
                        if (stage == STAGE)
                        {
                            stage = 0;
                            status = CONG;
                            break;
                        }
                        else
                        {
                            ResetReady(ready, player);
                            status = READY;
                            break;
                        }
                    }
                }
                else
                {
                    KeyPushFlag = FALSE;
                }
                //ESC����������Q�[���I��
                if (CheckHitKey(KEY_INPUT_ESCAPE))
                {
                    status = CLOSE;
                    break;
                }
			}
		}

		//�Q�[���N���A���
		if (status == CONG)
		{
			OFFBGM(sound, CONG);
			int count = 0;
			while (count <= 251)
			{
				ClearDrawScreen();
				DrawStrings(strings, status);
				DrawScore(score, status);
				DrawPlayer(player, status, count);
				DrawRotaGraph(690, 600, 1.0, 0, graph.jewel, TRUE, 0);
				DrawRotaGraph(920, 600, 1.0, 0, graph.jewel, TRUE, 0);
				if (CheckBGM(sound, CONG) == FALSE)
				{
					ONBGM(sound, CONG);
				}
				if (count <= 250)
				{
					count++;
				}
				else
				{
					count = 0;
				}

				//����ʂ̓��e��\��ʂɔ��f������
				ScreenFlip();

				//X�L�[����������^�C�g����
				if (CheckHitKey(KEY_INPUT_S))
				{
					if (KeyPushFlag == FALSE)
					{
						KeyPushFlag = TRUE;
						stage = 0;
						status = TITLE;
						break;
					}
				}
				else
				{
					KeyPushFlag = FALSE;
				}
				//ESC����������Q�[���I��
				if (CheckHitKey(KEY_INPUT_ESCAPE))
				{
					status = CLOSE;
					break;
				}
			}
		}

		//�Q�[�����[�h��CLOSE�ł���΃��C�����[�v����E�o
		if (status == CLOSE)
		{
			DxLib_End();
			system("cd ..\\..\\ & Launcher.exe");
			break;
		}
	}

	return 0;
}