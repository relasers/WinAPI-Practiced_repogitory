#pragma once
#pragma comment (lib, "fmod_vc.lib")
#include"inc\fmod.hpp"
using namespace FMOD;

// 동시실행가능한 사운드(채널) 갯수.
#define Max_Channel 4000

class CSoundManager
{
public:
	///////////////// BGM ////////////////////
	typedef enum 
	{
		Logo_BGM,
		Title_BGM,
		Stage_BGM,
		GameOver_BGM,
		GameClear_BGM,
		Count_BGM,
		Stop_BGM
	}BGM_SOUND;
	///////////////// UI /////////////////////
	typedef enum
	{
		BarrierCrash_UI,
		CollideBullet_UI,
		Count_UI,
		Stop_UI
	}UI_SOUND;
	///////////////// PALYER /////////////////
	typedef enum
	{
		Shot_P,
		Hit_P,
		Die_P,
		Count_P,
		Stop_P
	}PLAYER_SOUND;
	///////////////// ENEMY //////////////////
	typedef enum
	{
		Enemy_Shot,
		Enemy_Hit,
		Enemy_Die,
		Enemy_Count,
		Enemy_Stop
	}ENEMY_SOUND;
	///////////////// BOSS ///////////////////
	typedef enum
	{
		Boss_Shot,
		Boss_Die,
		Boss_Count,
		Boss_Stop
	}BOSS_SOUND;

private:
	FMOD_SYSTEM*		g_System{ nullptr };

	FMOD_SOUND*			g_BGM_Sound[BGM_SOUND::Count_BGM];
	FMOD_SOUND*			g_UI_Sound[UI_SOUND::Count_UI];
	FMOD_SOUND*			g_Player_Sound[PLAYER_SOUND::Count_P];
	FMOD_SOUND*			g_Enemy_Sound[ENEMY_SOUND::Enemy_Count];
	FMOD_SOUND*			g_Boss_Sound[BOSS_SOUND::Boss_Count];

	FMOD_CHANNELGROUP*	g_BGM_ChannelGroup{ nullptr };
	FMOD_CHANNELGROUP*	g_UI_ChannelGroup{ nullptr };
	FMOD_CHANNELGROUP*	g_Effect_ChannelGroup{ nullptr };

	FMOD_CHANNEL*		g_BGM_Channel{ nullptr };
	FMOD_CHANNEL*		g_UI_Channel{ nullptr };
	FMOD_CHANNEL*		g_Player_Channel{ nullptr };
	FMOD_CHANNEL*		g_Enemy_Channel{ nullptr };
	FMOD_CHANNEL*		g_Boss_Channel{ nullptr };
public:
	CSoundManager();
	~CSoundManager();

	void Initialize();
	
	void CreateSound_BGM();
	void CreateSound_UI();
	void CreateSound_Player();
	void CreateSound_Enemy();
	void CreateSound_Boss();

	void Update(float fTimeElapsed);

	void PlaySnd_BGM(int);
	void PlaySnd_UI(int);
	void PlaySnd_Player(int);
	void PlaySnd_Enemy(int);
	void PlaySnd_Boss(int);

	void Destroy();
};

