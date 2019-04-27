
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




int status;						//ゲームの状態
int stage;						//今何ステージめか

bool KeyPushFlag = FALSE;		//何かしらのキーが押しっぱなしか否か

//Soundストラクトの初期化
Sound sound;



//- - - - - - - - - - - - - - //
//      ゲーム初期化処理      //
//- - - - - - - - - - - - - - //
void InitGame(Player&player,Enemy enemy[], int enemyNum)
{
	//ウィンドウモードにする
	ChangeWindowMode(TRUE);

	SetGraphMode(SCREEN_W, SCREEN_H, 16);

	status = TITLE;
	stage = 0;

	InitPlayer(player, stage);
	for (int i = 0; i < enemyNum; i++)
	{//xもyも0の場合、初期定義しない
		InitEnemy(enemy[i], stage, i);
	}

    //描画先を裏画面に
    SetDrawScreen(DX_SCREEN_BACK);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)//ライブラリ初期化処理
	{
		return -1;//エラーが起きたら終了
	}
	
	//Playerストラクトの初期化
	Player player;
	//Enemyストラクトの初期化
	Enemy enemy[ENEMY];
    //Graphストラクトの初期化
    Graph graph;
	//mapストラクトの初期化
	Map map;
	//Timeストラクトの初期化
	Time time;
	//Goalストラクトの初期化
	Goal goal;
	//Jewelストラクトの初期化
	Jewel jewel;
	//スコアストラクトの初期化
	Score score;
    //準備画面ストラクトの初期化
	Ready ready;
	//Stringストラクトの初期化
	Strings strings;
	//Cursouストラクトの初期化
	Cursor cursor;
    ////Manualストラクトの初期化
    //Manual manual;


    //ゲームの初期化
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

        //タイトル画面
		if (status == TITLE)
		{
			//BGM停止
			OFFBGM(sound, status);
			//BGM再生
			if (CheckBGM(sound, TITLE) == FALSE)
			{
				ONBGM(sound, TITLE);
			}
			while (true)
			{
				ClearDrawScreen();
				UpdateCursor(cursor, sound);

				DrawBack(graph);                                            //背景画像描画
				DrawMap(map, stage);
				DrawRotaGraph(750, 350, 3.5f, 0, graph.Title, TRUE, 0);     //タイトル文字描画
				DrawStrings(strings, status);                               //文字描画
				DrawCursor(cursor);                                         //カーソル描画
				//裏画面の内容を表画面に反映させる
				ScreenFlip();

				//Aキーでゲームスタート
				if (CheckHitKey(KEY_INPUT_A))
				{
					if (KeyPushFlag == FALSE)
					{
						ONSound(sound, ENTER);
						switch (cursor.Count)
						{
						case 0:
						{
							//ゲームの初期化
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
				//ESCを押したらゲーム終了
				if (CheckHitKey(KEY_INPUT_ESCAPE))
				{
					status = CLOSE;
					break;
				}
			}
		}

        //マニュアル画面
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
					KeyPushFlag = TRUE;		//キー押しっぱなしによるステータスの切り替えを防止
                    stage--;
                    status = TITLE;
                }
				else
				{
					KeyPushFlag = FALSE;
				}
            }
            //裏画面の内容を表画面に反映させる
            ScreenFlip();

            //ESCを押したらゲーム終了
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                status = CLOSE;
            }
        }

        //クレジット画面
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
                    KeyPushFlag = TRUE;		//キー押しっぱなしによるステータスの切り替えを防止
                    stage = 0;
                    status = TITLE;
                }
            }
            //裏画面の内容を表画面に反映させる
            ScreenFlip();

            //ESCを押したらゲーム終了
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                status = CLOSE;
            }
        }

		//ゲーム開始前準備画面
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
				//裏画面の内容を表画面に反映させる
				ScreenFlip();
				//Sを押してスキップ
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
				//ESCを押したらゲーム終了
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

        //プレイ画面
		if (status == PLAY)
		{
			if (CheckBGM(sound, status) == FALSE)
			{
				//BGM再生
				ONBGM(sound, status);
			}

			//画面にあるものを一度全消去
            ClearDrawScreen();

			//自機操作
			UpdatePlayer(player, sound, stage);
			//敵移動・敵との当たり判定
			for (int i = 0; i < ENEMY; i++)
			{	//敵が設定されていたら
				if (EnemyPosi[stage][i][0] || EnemyPosi[stage][i][1])
				{
					UpdateEnemy(enemy[i], stage, i);
					if (JudgeEnemy((int)player.X, (int)player.Y, enemy[i].X, enemy[i].Y, enemy[i].Direction))
					{
                        status = MISS;
					}
				}
			}	

			//ゴールとの当たり判定
			if (JudgeGoal(goal, (int)player.X, (int)player.Y))
			{
                DrawGraph(goal.X, goal.Y - 64, goal.StrGraph, TRUE);
                if (CheckHitKey(KEY_INPUT_A))
                {
                    status = CLEAR;
                }
			}

			//宝石との当たり判定
			if (JudgeJewel(jewel, (int)player.X, (int)player.Y, stage))
			{
				score.Number += 500;
				ONSound(sound, GET);
			}
			//スコア偏移
			UpdateScore(score);
			//時間制限偏移
			if (UpdateTime(time, status))
			{
				status = MISS;
			}

            //背景画像描画
            DrawBack(graph);
			//敵キャラ描画
			for (int i = 0; i < ENEMY; i++)
			{
				if (EnemyPosi[stage][i][0] || EnemyPosi[stage][i][1])
				{
					DrawEnemy(enemy[i], status);
				}
			}
			//背景描画
            DrawMap(map, stage);
			//スコア描画
			DrawScore(score,status);
			//制限時間描画
			DrawTime(time,status);
			//出口描画
			DrawGoal(goal, (int)player.X, (int)player.Y);
			//宝石描画
			DrawJewel(jewel, stage);
			//プレイヤー描画
			DrawPlayer(player,status,FALSE);

            // 裏画面の内容を表画面に反映させる
            ScreenFlip();

			//ESCを押したらゲーム終了
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				status = CLOSE;
			}
		}
		
		//ミス画面
		if (status == MISS)
		{
            ONSound(sound, MISSS);
			OFFBGM(sound, status);
            int count = 0;//仮置き
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
                //背景画像描画
                DrawBack(graph);
                //敵キャラ描画
                for (int i = 0; i < ENEMY; i++)
                {
                    if (EnemyPosi[stage][i][0] || EnemyPosi[stage][i][1])
                    {
                        DrawEnemy(enemy[i], status);
                    }
                }
                //背景描画
                DrawMap(map, stage);
                //スコア描画
                DrawScore(score, status);
                //制限時間描画
                DrawTime(time,status);
                //出口描画
                DrawGoal(goal, (int)player.X, (int)player.Y);
                //宝石描画
                DrawJewel(jewel, stage);
                //プレイヤー描画
                DrawPlayer(player, status, count);
				//文字描画
                DrawStrings(strings, status);
				if (time.Limit == 0)
				{
					DrawTimeStrings(strings);
				}
                count++;
			// 裏画面の内容を表画面に反映させる
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

			//ESCを押したらゲーム終了
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				status = CLOSE;
			}
		}

		//ゲームオーバー画面
		if (status == OVER)
		{
			//BGM再生
			ONBGM(sound, status);
			while (true)
			{
				ClearDrawScreen();
				DrawStrings(strings, status);
				DrawScore(score, status);
				DrawPlayer(player, status, 0);

				//裏画面の内容を表画面に反映させる
				ScreenFlip();

				//Xキーを押したらタイトルへ
				if (CheckHitKey(KEY_INPUT_S))
				{
					stage = 0;
					status = TITLE;
					break;
				}
				//ESCを押したらゲーム終了
				if (CheckHitKey(KEY_INPUT_ESCAPE))
				{
					status = CLOSE;
					break;
				}
			}
		}

        //ステージクリア画面
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
                //背景画像描画
                DrawBack(graph);
                //敵キャラ描画
                for (int i = 0; i < ENEMY; i++)
                {
                    if (EnemyPosi[stage][i][0] || EnemyPosi[stage][i][1])
                    {
                        DrawEnemy(enemy[i], status);
                    }
                }
                //背景描画
                DrawMap(map, stage);
                //スコア描画
                DrawScore(score, status);
                //制限時間描画
                DrawTime(time,status);
                //出口描画
                DrawGoal(goal, (int)player.X, (int)player.Y);
                //宝石描画
                DrawJewel(jewel, stage);
                //プレイヤー描画
                DrawPlayer(player, status, count);
                count++;
                // 裏画面の内容を表画面に反映させる
                ScreenFlip();
            }
			if (CheckBGM(sound, status) == FALSE)
			{//BGM再生
				ONBGM(sound, status);
			}
			DrawStrings(strings, status);
			DrawScore(score, status);
            // 裏画面の内容を表画面に反映させる
            ScreenFlip();
            //キー押されるまで画面そのまま
            while(true)
            { 
			//Sキーを押したら次のステージまたはタイトルへ
                if (CheckHitKey(KEY_INPUT_S))
                {
                    if (KeyPushFlag == FALSE)
                    {
                        KeyPushFlag = TRUE;
                        stage++;
                        //出口座標の更新
                        UpdateGoal(goal, stage);
                        //宝石の位置更新
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
                //ESCを押したらゲーム終了
                if (CheckHitKey(KEY_INPUT_ESCAPE))
                {
                    status = CLOSE;
                    break;
                }
			}
		}

		//ゲームクリア画面
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

				//裏画面の内容を表画面に反映させる
				ScreenFlip();

				//Xキーを押したらタイトルへ
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
				//ESCを押したらゲーム終了
				if (CheckHitKey(KEY_INPUT_ESCAPE))
				{
					status = CLOSE;
					break;
				}
			}
		}

		//ゲームモードがCLOSEであればメインループから脱出
		if (status == CLOSE)
		{
			DxLib_End();
			system("cd ..\\..\\ & Launcher.exe");
			break;
		}
	}

	return 0;
}