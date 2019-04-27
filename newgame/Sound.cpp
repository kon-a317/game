#include "DxLib.h"
#include "Sound.h"
#include "common.h"

//音関連の初期定義
void InitSound(Sound&sound)
{
	sound.TitleBGM = LoadSoundMem("sound/TitleBGM.wav");
	sound.PlayBGM = LoadSoundMem("sound/StageBGM.mp3");
	sound.ClearBGM = LoadSoundMem("sound/StageClearBGM.mp3");
	sound.CongBGM = LoadSoundMem("sound/CongBGM.wav");
    sound.MissBGM = LoadSoundMem("sound/MissBGM.wav");
	sound.OverBGM = LoadSoundMem("sound/GameOver.mp3");
	sound.WalkSE = LoadSoundMem("sound/Walk.wav");
	sound.JumpSE = LoadSoundMem("sound/JumpSE.mp3");
	sound.HitSE = LoadSoundMem("sound/Butsukaru.mp3");
	sound.GetJewelSE = LoadSoundMem("sound/GetJewelSE.mp3");
    sound.MissSE = LoadSoundMem("sound/MissSE.wav");
    sound.KaidanSE = LoadSoundMem("sound/Kaidan-InSE.wav");
    sound.SelectSE = LoadSoundMem("sound/SelectSE.mp3");
    sound.EnterSE = LoadSoundMem("sound/EnterSE.wav");
	sound.volume = 60;
	ChangeVolumeSoundMem(255 * sound.volume / 100, sound.PlayBGM);
    ChangeVolumeSoundMem(255 * (sound.volume + 30) / 100, sound.OverBGM);
}

//音再生
void ONBGM(Sound&sound, int status)
{
	switch (status)
	{
	case TITLE:
	{
		PlaySoundMem(sound.TitleBGM, DX_PLAYTYPE_BACK);
		break;
	}
	case PLAY:
	{
		PlaySoundMem(sound.PlayBGM, DX_PLAYTYPE_LOOP);
		break;
	}
	case MISS:
	{
        PlaySoundMem(sound.MissBGM, DX_PLAYTYPE_BACK);
		break;
	}
	case OVER:
	{
		PlaySoundMem(sound.OverBGM, DX_PLAYTYPE_BACK);
		break;
	}
	case CLEAR:
	{
		PlaySoundMem(sound.ClearBGM, DX_PLAYTYPE_BACK);
		break;
	}
	case CONG:
	{
		PlaySoundMem(sound.CongBGM, DX_PLAYTYPE_BACK);
		break;
	}
	}
}

//音停止
void OFFBGM(Sound&sound, int status)
{
	switch (status)
	{
	case TITLE:
	{
		StopSoundMem(sound.OverBGM);
        StopSoundMem(sound.WalkSE);
		StopSoundMem(sound.CongBGM);
		break;
	}
	case READY:
	{
		StopSoundMem(sound.TitleBGM);
		StopSoundMem(sound.ClearBGM);
		break;
	}
	case PLAY:
	{
		break;
	}
	case MISS:
	{
		StopSoundMem(sound.PlayBGM);
        StopSoundMem(sound.WalkSE);
        StopSoundMem(sound.JumpSE);
		break;
	}
	case OVER:
	{
		break;
	}
	case CLEAR:
	{
		StopSoundMem(sound.PlayBGM);
		break;
	}
	case CONG:
	{
		StopSoundMem(sound.ClearBGM);
		break;
	}
	}
}

//BGMが再生中かどうか確認
int CheckBGM(Sound&sound, int status)
{
	switch (status)
	{
	case TITLE:
	{
		if (CheckSoundMem(sound.TitleBGM))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
	case PLAY:
	{
		if (CheckSoundMem(sound.PlayBGM))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
	case MISS:
	{
        if (CheckSoundMem(sound.MissBGM))
        {
            return 1;
        }
		return 0;
		break;
	}
	case OVER:
	{
		if(CheckSoundMem(sound.OverBGM))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
	case CLEAR:
	{
		if (CheckSoundMem(sound.ClearBGM))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
	case CONG:
	{
		if (CheckSoundMem(sound.CongBGM))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
	return 0;
	}
}


void ONSound(Sound&sound, int type)
{
    switch (type)
    {
    case JUMP:
    {
        PlaySoundMem(sound.JumpSE, DX_PLAYTYPE_BACK);
        break;
    }
    case WALK:
    {
        PlaySoundMem(sound.WalkSE, DX_PLAYTYPE_BACK);
        break;
    }
    case HIT:
    {
        PlaySoundMem(sound.HitSE, DX_PLAYTYPE_BACK);
        break;
    }
    case GET:
    {
        PlaySoundMem(sound.GetJewelSE, DX_PLAYTYPE_BACK);
        break;
    }
    case MISSS:
    {
        PlaySoundMem(sound.MissSE, DX_PLAYTYPE_BACK);
        break;
    }
    case KAIDAN:
    {
        PlaySoundMem(sound.KaidanSE, DX_PLAYTYPE_BACK);
        break;
    }
    case SELECT:
    {
        PlaySoundMem(sound.SelectSE, DX_PLAYTYPE_BACK);
        break;
    }
    case ENTER:
    {
        PlaySoundMem(sound.EnterSE, DX_PLAYTYPE_BACK);
        break;
    }
    }
}

void OFFSound(Sound&sound, int type)
{
	switch (type)
	{
	case WALK:
	{
		StopSoundMem(sound.WalkSE);
		break;
	}
	case HIT:
    {
        StopSoundMem(sound.HitSE);
        break;
    }
    break;
	}
}

int CheckSound(Sound&sound, int type)
{
    switch (type)
    {
    case SELECT:
    {
        if (CheckSoundMem(sound.SelectSE))
        {
            return 1;
        }
        return 0;
        break;
    }
    case JUMP:
    {
        if (CheckSoundMem(sound.JumpSE))
        {
            return 1;
        }
        return 0;
        break;
    }
    case WALK:
    {
        if (CheckSoundMem(sound.WalkSE))
        {
            return 1;
        }
        return 0;
        break;
    }
    case HIT:
    {
        if (CheckSoundMem(sound.HitSE))
        {
            return 1;
        }
        return 0;
        break;
    }
    case MISSS:
    {
        if (CheckSoundMem(sound.MissSE))
        {
            return 1;
        }
        return 0;
        break;
    }
    case KAIDAN:
    {
        if (CheckSoundMem(sound.KaidanSE))
        {
            return 1;
        }
        return 0;
        break;
    }
    break;
    }
}