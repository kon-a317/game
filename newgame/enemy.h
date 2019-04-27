#pragma once
#include"common.h"
#include"map.h"

struct Enemy
{
	float X;					//X座標
	float Y;					//Y座標
	int W;					//横幅
	int H;					//縦幅
	int Graph[2];				//画像
    int Right;				//光の画像
	int Speed;				//速度
	int HP;					//体力
	int Count;
	int Direction;			//向き保存用関数
	int BeforeDirection;	//向き保存用関数(直前までどちらを向いていたか)
	int Timer;				//アニメーション用
	int Frame;				//アニメーション用
};

enum { LEFT, RIGHT, CENTER };	//右左中央、向き内容
extern const int EnemyPosi[STAGE][ENEMY][2];//ステージ毎の初期位置設定 ステージ,個体数,xy
extern const int EnemyWait[STAGE][ENEMY];//敵の方向転換の待機時間
extern const int EnemyDirSave[STAGE][ENEMY];

//- - - - - - - - - - - - - - - //
//    enemyプロトタイプ宣言     //
//- - - - - - - - - - - - - - - //
void InitEnemy(Enemy&enemy, int stage, int i);
void ResetEnemy(Enemy&enemy, int stage, int i);
int JudgeEnemy(int px, int py, int ex, int ey, int ed);
void UpdateEnemy(Enemy&enemy, int stage, int i);
void DrawEnemy(Enemy&enemy, int status);

