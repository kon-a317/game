#include "DxLib.h"
#include "player.h"
#include "map.h"




//- - - - - - - - - - - - - - //
//         Player処理         //
//- - - - - - - - - - - - - - //
void InitPlayer(Player&player, int stage)
{
	//自機画像読み込み、初期座標、速度、ジャンプフラグ定義
	LoadDivGraph("texture/hage2.png", 4, 4, 1, 64, 64, player.Graph);
    LoadDivGraph("texture/noboru-hage.png", 4, 4, 1, 64, 64, player.HashigoGraph);
    LoadDivGraph("texture/haneru-hage.png", 2, 2, 1, 64, 64, player.JumpGraph);
	LoadDivGraph("texture/warau-hage.png", 2, 2, 1, 64, 64, player.LaughGraph);
    LoadDivGraph("texture/misuru-hage.png", 3, 3, 1, 64, 64, player.MissGraph);
    LoadDivGraph("texture/kyororu-hage.png", 2, 2, 1, 64, 64, player.EscapeGraph);
	player.GladGraph = LoadGraph("texture/haneru-hage2.png");
	GetGraphSize(player.Graph[0], &player.W, &player.H);
	player.X = player.Posi[stage][0];
    player.Y = player.Posi[stage][1];
	player.Speed = 5;
	player.JumpFlag = FALSE;
    player.PrevJumpFlag = FALSE;
    player.GroundFlag = FALSE;
	player.AtariCount = 0;
	player.AtariFlag = FALSE;
    player.Life = 3;
	player.HashigoFlag = FALSE;
    player.JumpVelocity = 0;
    player.Left = TRUE;
}

void ResetPlayer(Player&player, int stage)
{
	//ステージ変更時の位置・当たり判定リセット
    player.X = player.Posi[stage][0];
    player.Y = player.Posi[stage][1];
    player.JumpFlag = FALSE;
	player.JumpVelocity = 0;
    player.AtariCount = 0;
    player.PrevJumpFlag = FALSE;
    player.AtariFlag = FALSE;
    player.HashigoFlag = FALSE;
    player.Left = TRUE;
}

void UpdatePlayer(Player&player, Sound&sound, int stage)
{
	//キーが押されていたら自機を動かす
    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        player.X -= player.Speed;
        player.Left = TRUE;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        player.X += player.Speed;
        player.Left = FALSE;
    }

	//はしごのところにいたら上り降りできる
	if (player.HashigoFlag == TRUE)
	{
		if (CheckHitKey(KEY_INPUT_UP))
		{
			player.Y -= player.Speed;
			player.JumpFlag = FALSE;
		}
        if (CheckHitKey(KEY_INPUT_DOWN))
        {
            player.Y += player.Speed;
            player.JumpFlag = FALSE;
        }
	}

    //重力について
    if (player.HashigoFlag == TRUE)
    { //梯子を上り下りしてるときは重力オフ
        if (player.JumpFlag == TRUE)
        {
            player.JumpFlag = FALSE;
        }
    }
    else
    {
        //上に向かう力を重力に従って減少させる
        player.JumpVelocity -= GRAVITY;
        if (player.JumpVelocity <= MIN_GRAVITY)
        {
            player.JumpVelocity = MIN_GRAVITY;
        }
        //向かう力に従ってプレイヤーを移動させる
        player.Y -= player.JumpVelocity;
        player.GroundFlag = FALSE;              //接地判定オフ
    }

	//画面から出ないようにする
	if (player.X < 0)
	{
		player.X = 0;
	}
	if (player.X >(SCREEN_W - player.W))
	{
		player.X = ((float)(SCREEN_W - player.W));
	}
	if (player.Y < 0)
	{
		player.Y = 0;
	}

    //左へ移動
    if ((GetMapType(player.X + (player.W -1), player.Y, stage) ==2) && 
        (GetMapType(player.X + (player.W -1), player.Y + (player.H -1), stage) == 2))
    {
        int i = GetMapIndexX(player.X);
        player.X = ((float)(i)*MAP_BLOCK_SIZE);
        if (CheckSound(sound, HIT) == FALSE)
        {
            ONSound(sound, HIT);
        }
    }
    //右へ移動
    if ((GetMapType(player.X, player.Y, stage) == 2) && 
        (GetMapType(player.X, player.Y + (player.H -1), stage) == 2))
    {
        int i = GetMapIndexX(player.X);
        player.X = ((float)(i + 1)*MAP_BLOCK_SIZE);
        if (CheckSound(sound, HIT) == FALSE)
        {
            ONSound(sound, HIT);
        }
    }
    //上へ修正
    if ((GetMapType(player.X, player.Y + (player.H -1), stage) == 2 )
        ||(GetMapType(player.X, player.Y + (player.H -1), stage) == 2 )
        &&(GetMapType(player.X + (player.W -1), player.Y + (player.H -1), stage) == 2)
        ||(GetMapType(player.X + (player.W -1), player.Y + (player.H -1), stage) == 2))
    {
        int i = GetMapIndexY(player.Y);
        player.Y = ((float)(i)*MAP_BLOCK_SIZE);
        player.GroundFlag = TRUE;               //接地している
        if (player.JumpFlag == TRUE)
        {
            player.JumpFlag = FALSE;
        }
    }
    //下に修正する
    if ((GetMapType(player.X, player.Y, stage) == 2)
        ||(GetMapType(player.X, player.Y, stage) == 2)
        &&(GetMapType(player.X + (player.W -1), player.Y, stage) == 2)
        ||(GetMapType(player.X + (player.W -1), player.Y, stage) == 2))
    {
        int i = GetMapIndexY(player.Y);
        player.Y = ((float)(i + 1)*MAP_BLOCK_SIZE);
        player.JumpVelocity = 0;        //ジャンプ中の場合、天井に頭を打ったら自由落下に切り替える
        ONSound(sound, HIT);
    }

    //ジャンプ処理
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
		if (player.PrevJumpFlag == FALSE && player.GroundFlag == TRUE)//キーが押しっぱじゃなかったら実行
        {
            if (player.JumpFlag == FALSE)
            {
                player.JumpFlag = TRUE;
                player.JumpVelocity = 15;
                ONSound(sound, JUMP);
            }
        }
        player.PrevJumpFlag = TRUE;//キーが押されている
    }
    else
    {
        player.PrevJumpFlag = FALSE;//キーが押されていない
    }


    //自分のいる場所が梯子のあるもしくは梯子のある床だったら梯子フラグをオン
    if ((GetMapType(player.X + (player.W / 2), player.Y , stage) == 1 && GetMapType(player.X + (player.W / 2), player.Y + (player.H), stage) == 2) ||
        (GetMapType(player.X + (player.W / 2), player.Y , stage) == 1 && GetMapType(player.X + (player.W / 2), player.Y + (player.H), stage) == 1) ||
        (GetMapType(player.X + (player.W / 2), player.Y , stage) == 4 && GetMapType(player.X + (player.W / 2), player.Y + (player.H), stage) == 1) ||
        (GetMapType(player.X + (player.W / 2), player.Y , stage) == 0 && GetMapType(player.X + (player.W / 2), player.Y + (player.H), stage) == 4))
    {
        player.HashigoFlag = TRUE;
		player.GroundFlag = TRUE;		//設置判定もオン
    }
    else
    {
        player.HashigoFlag = FALSE;
    }

    //歩きSEを再生するためのフラグ管理
    if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_RIGHT) ||
        CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN))
    {
        player.WalkFlag = TRUE;
    }
    else
    {
        player.WalkFlag = FALSE;
    }
    //歩きSE再生
    if (player.GroundFlag == TRUE && player.WalkFlag == TRUE)
    {
        if (CheckSound(sound, WALK) == FALSE)
        {
            ONSound(sound, WALK);
        }
    }
    else
    {
        OFFSound(sound, WALK);
    }
}

void DrawPlayer(Player&player, int status, int count)
{
	player.Timer = GetNowCount();//現在時刻取得
	player.Frame = player.Timer / 200 % 4;

    switch (status)
    {
    case READY:
    {
        break;
    }
    case MANUAL:
    {
        DrawPlayPlayer(player);
        break;
    }
    case CREDIT:
    {
        DrawPlayPlayer(player);
        break;
    }
    case PLAY:
    {
        DrawPlayPlayer(player);
        break;
    }
    case MISS:
    {
        DrawMissPlayer(player, count);
        break;
    }
    case OVER:
    {
        DrawOverPlayer(player);
        break;
    }
    case CLEAR:
    {
        DrawClearPlayer(player, count);
        break;
    }
	case CONG:
	{
		DrawCongPlayer(player, count);
		break;
	}
    }
    
    if (status == PLAY || status == MISS || status == CLEAR)
    {
        //ライフ描画
        for (int i = 0; i < player.Life; i++)
        {
            DrawRotaGraph(700 + (i * 45) + 16, 50, 0.7, 0, player.Graph[0], TRUE, 0);
        }
    }
}

void DrawPlayPlayer(Player&player)
{
    if (player.JumpFlag || (player.GroundFlag == FALSE))
    {//ジャンプ中の描画
        if (player.JumpVelocity > 0)
        {
            if (player.Left)
            {
                DrawTurnGraph((int)player.X, (int)player.Y, player.JumpGraph[0], TRUE);
            }
            else
            {
                DrawGraph((int)player.X, (int)player.Y, player.JumpGraph[0], TRUE);
            }
        }
        else
        {
            if (player.Left)
            {
                DrawTurnGraph((int)player.X, (int)player.Y, player.JumpGraph[1], TRUE);
            }
            else
            {
                DrawGraph((int)player.X, (int)player.Y, player.JumpGraph[1], TRUE);
            }
        }
    }
    else
    {
        if (player.HashigoFlag)
        {//梯子上下中の描画
            if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_RIGHT) ||
                CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN))
            {
                DrawGraph((int)player.X, (int)player.Y, player.HashigoGraph[player.Frame], TRUE);
                player.KeepGraph = player.HashigoGraph[player.Frame];
            }
            else
            {
                DrawGraph((int)player.X, (int)player.Y, player.KeepGraph, TRUE);
            }
        }
        else
        {
            //通常状態の描画
            if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_RIGHT))
            {
                if (player.Left)
                {
                    DrawTurnGraph((int)player.X, (int)player.Y, player.Graph[player.Frame], TRUE);
                }
                else
                {
                    DrawGraph((int)player.X, (int)player.Y, player.Graph[player.Frame], TRUE);
                }
            }
            else
            {
                if (player.Left)
                {
                    DrawTurnGraph((int)player.X, (int)player.Y, player.Graph[0], TRUE);
                }
                else
                {
                    DrawGraph((int)player.X, (int)player.Y, player.Graph[0], TRUE);
                }
            }
        }
    }
}

void DrawMissPlayer(Player&player, int count)
{
    player.Frame = player.Timer / 400 % 2;
    if (player.Left)
    {
        if (count > 0 && count <= 25)
        {
            DrawRotaGraph(player.X + 32, player.Y + 15, 1.0, PI * 0, player.MissGraph[0], TRUE, TRUE);
        }
        else if (count > 25 && count <= 50)
        {
            DrawRotaGraph(player.X + 32, player.Y + 15, 1.0, PI * 0.5, player.MissGraph[0], TRUE, TRUE);
        }
        else if (count > 50 && count <= 75)
        {
            DrawRotaGraph(player.X + 32, player.Y + 15, 1.0, PI * 1, player.MissGraph[0], TRUE, TRUE);
        }
        else if (count > 75 && count <= 100)
        {
            DrawRotaGraph(player.X + 32, player.Y + 15, 1.0, PI * 1.5, player.MissGraph[0], TRUE, TRUE);
        }
        else if (count <= 125)
        {
            DrawRotaGraph(player.X + 32, player.Y + 15, 1.0, PI * 0, player.MissGraph[0], TRUE, TRUE);
        }
        else
        {
            DrawRotaGraph(player.X + 32, player.Y + 45, 1.0, 0, player.MissGraph[player.Frame + 1], TRUE, TRUE);
        }
    }
    else
    {
        if (count > 0 && count <= 25)
        {
            DrawRotaGraph(player.X + 32, player.Y + 15, 1.0, PI * 0, player.MissGraph[0], TRUE, 0);
        }
        else if (count > 25 && count <= 50)
        {
            DrawRotaGraph(player.X + 32, player.Y + 15, 1.0, PI * 1.5, player.MissGraph[0], TRUE, 0);
        }
        else if (count > 50 && count <= 75)
        {
            DrawRotaGraph(player.X + 32, player.Y + 15, 1.0, PI * 1, player.MissGraph[0], TRUE, 0);
        }
        else if (count > 75 && count <= 100)
        {
            DrawRotaGraph(player.X + 32, player.Y + 15, 1.0, PI * 0.5, player.MissGraph[0], TRUE, 0);
        }
        else if (count <= 125)
        {
            DrawRotaGraph(player.X + 32, player.Y + 15, 1.0, PI * 0, player.MissGraph[0], TRUE, 0);
        }
        else
        {
            DrawRotaGraph(player.X + 32, player.Y + 35, 1.0, 0, player.MissGraph[player.Frame + 1], TRUE, 0);
        }
    }
}

void DrawOverPlayer(Player&player)
{
    player.Frame = player.Timer / 400 % 2;
    DrawGraph(770, 600, player.MissGraph[player.Frame + 1], TRUE);
}

void DrawClearPlayer(Player&player, int count)
{
    if (count >= 0 && count <= 80)
    {
        player.Frame = player.Timer / 400 % 2;
        if (player.Left == TRUE)
        {
            DrawRotaGraph(player.X+32, player.Y+32, 1.0, 0, player.EscapeGraph[player.Frame], TRUE, TRUE);
        }
        else
        {
            DrawRotaGraph(player.X+32, player.Y+32, 1.0, 0, player.EscapeGraph[player.Frame], TRUE);
        }
    }
    else if (count > 80 && count <= 170)
    {
        player.Frame = player.Timer / 100 % 4;
        if (player.Left == TRUE)
        {
            DrawRotaGraph(player.X+32, player.Y+32, 1.0, 0, player.LaughGraph[player.Frame % 2], TRUE, TRUE);
        }
        else
        {
            DrawRotaGraph(player.X+32, player.Y+32, 1.0, 0, player.LaughGraph[player.Frame % 2], TRUE);
        }
    }
}

void DrawCongPlayer(Player&player, int count)
{
	player.Frame = player.Timer / 400 % 2;
	if (count < 125)
	{
		if ((count / 25) % 2 == 0)
		{
			DrawRotaGraph(770 + 32, 600 + 32, 1.0, 0, player.Graph[0], TRUE, 0);
		}
		else
		{
			DrawRotaGraph(770 + 32, 560, 1.0, 0, player.GladGraph, TRUE, 0);
		}
	}
	else
	{
		if (count >= 125 && count <= 150)
		{
			DrawRotaGraph(770 + 32, 560, 1.0, PI * 0, player.GladGraph, TRUE, 0);
		}
		else if (count > 150 && count <= 175)
		{
			DrawRotaGraph(770 + 32, 560, 1.0, PI * 1.5, player.GladGraph, TRUE, 0);
		}
		else if (count > 175 && count <= 200)
		{
			DrawRotaGraph(770 + 32, 560, 1.0, PI * 1, player.GladGraph, TRUE, 0);
		}
		else if (count > 200 && count <= 225)
		{
			DrawRotaGraph(770 + 32, 560, 1.0, PI * 0.5, player.GladGraph, TRUE, 0);
		}
		else if (count <= 250)
		{
			DrawRotaGraph(770 + 32, 560, 1.0, PI * 0, player.GladGraph, TRUE, 0);
		}
	}
}
