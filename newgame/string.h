#pragma once
#include"Sound.h"

#define STRINGS_W 30
#define STRINGS_H 35


//文字関連のストラクト
struct Strings
{
	int  Graph[145];                                    //画像用
	int  EnterNum;                                      //PLESS Aの文字数
    char Enter[64] = { "PLESSaAaENTER"};                //文字列保存
    int  GameStartNum;                                  //GAME STARTの文字数
    char GameStart[64] = { "GAMEaSTART" };
    int  ManualNum;                                     //MANUALの文字数
	char Manual[64] = {"MANUAL"};
    int  CreditNum;
    char Credit[64] = { "CREDIT" };
    int  PlessNum;
    char Pless[64] = { "PRESS" };
    int  WalkNum;
    char Walk[64] = { "WALK" };
	int  SpaseNum;
	char Spase[64] = { "SPASE" };
    int  JumpNum;
    char Jump[64] = { "JUMP" };
    int  HashigoNum;
    char Hashigo[64] = { "UPaDOWN" };
    int  ExitNum;
    char Exit[64] = { "EXIT" };
    int  ReadyNum;
    char Ready[64] = { "READY.?" };
	int  TimeLimitNum;
	char TimeLimit[64] = { "TIMELIMIT." };
    int  SkipNum;
    char Skip[64] = { "SKIP" };
	int  NextNum;
	char Next[64] = { "NEXT" };
    int  StageClearNum;
    char StageClear[64] = { "STAGECLEAR!" };
    int  GameClearNum;
    char GameClear[64] = { "GAMECLEAR!" };
    int  CongratulationsNum;
	char Congratulations[64] = {"CONGRATULATIONS!"};
    int  MissNum;
    char Miss[64] = { "MISS." };
	int  TimeOverNum;
	char TimeOver[64] = { "TIMEOVER!" };
    int  GameOverNum;
    char GameOver[64] = { "GAMEOVER." };
	int  SEUseNum;
	char SEUse[64] = { "SEaaaSKIPMORE" };
	int  SEUse2Num;
	char SEUse2[64] = { "MUSICaISaVFR" };
	int  BGMUseNum;
	char BGMUse[64] = { "BGMaaMAOUDAMASHII" };
	int  BGMUse2Num;
	char BGMUse2[64] = { "HINATAaHARUHANA" };
	int  BGMUse3Num;
	char BGMUse3[64] = { "PANICPUMPKIN" };
};

//カーソル関連のストラクト
struct Cursor
{
	int Graph;          //カーソル画像
	int Count;          //カーソルがどこにあるかのカウント
    int AgainCount;     //カーソル変動が出来るようになるまでのカウント
};

enum {START, MANU, EXIT};
enum { ARIGHT, ALEFT, AUP, ADOWN };

//
//関数のプロトタイプ宣言
//
//文字関連
void InitStrings(Strings&strings);
void ConfigStrings(Strings&strings, char *str, int num);
void DrawStrings(Strings&strings, int status);
void DrawTitleStrings(Strings&strings);
void DrawManualStrings(Strings&strings);
void DrawCreditStrings(Strings&strings);
void DrawReadyStrings(Strings&strings);
void DrawMissStrings(Strings&strings);
void DrawTimeStrings(Strings&strings);
void DrawOverStrings(Strings&strings);
void DrawClearStrings(Strings&strings);
void DrawCongStrings(Strings&strings);
void DrawALLStrings(Strings&strings, char str[], int num, int X, int Y, float ExRate);
//カーソル関連
void InitCursor(Cursor&cursor, Strings&strings);
void UpdateCursor(Cursor&cursor, Sound&sound);
void DrawCursor(Cursor&cursor);