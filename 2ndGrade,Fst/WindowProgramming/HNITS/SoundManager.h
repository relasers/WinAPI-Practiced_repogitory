#pragma once
#pragma comment (lib, "fmod_vc.lib")
#include "inc\fmod.hpp"
using namespace FMOD;

// ���ý��డ���� ����(ä��) ����.
#define Max_Channel 3000

class CSoundManager
{
public:
	///////////////// BGM ////////////////////
	typedef enum 
	{
		Logo_BGM,
		Title_BGM,
		Lobby_BGM,
		Stage_BGM,
		Boss_Stage_BGM,
		GameOver_BGM,
		GameClear_BGM,
		Count_BGM,
		Stop_BGM
	}BGM_SOUND;
	///////////////// UI /////////////////////
	typedef enum
	{
		Lobby_Menu_Select_UI,
		Potion_UI,
		Count_UI,
		Stop_UI
	}UI_SOUND;
	///////////////// PALYER /////////////////
	typedef enum
	{
		Attack_P,
		Walk_P,
		Reload_P,
		Shot_P,
		Deadly_P,
		Hit_P,
		Jump_P,
		Die_P,
		Parrying_P,
		Count_P,
		Stop_P
	}PLAYER_SOUND;
	///////////////// ENEMY //////////////////
	typedef enum
	{
		Enemy_Attack,
		Enemy_Shot,
		Enemy_Move,
		Enemy_Hit,
		Enemy_Guard,
		Enemy_Die,
		Enemy_Count,
		Enemy_Stop
	}ENEMY_SOUND;
	///////////////// BOSS ///////////////////
	typedef enum
	{
		Boss_Phase2_Shift,
		Boss_Phase2_Attack,
		Boss_Phase2_Boom,
		Boss_Phase2_Summon,
		Boss_Phase3_Shift,
		Boss_Phase3_Idle,
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

/*
FMOD::Sound        : �Ҹ��� ��� ���ҽ�
FMOD::Channel      : �Ҹ��� �ϳ��� ä�ο��� �Ҹ��� ����.
FMOD::ChannelGroup : ������ ä��(�Ҹ�)�� ��� �����Ҷ� ����Ѵ�.
������ ä�α׷��� �̿� ���Ѵ�.

ä�α׷� �����
1. result = system->createChannelGroup("Group A", &groupA);
2. result = system->getMasterChannelGroup(&masterGroup);
3. result = masterGroup->addGroup(groupA);
4. result = system->createSound("Sleep Away.mp3", FMOD_LOOP_NORMAL, 0, &sound);
5. result = system->playSound(FMOD_CHANNEL_FREE, &sound, true, &channel);
6. result = channel->setChannelGroup(groupA);
1. system���κ��� ä�α׷�A����
2. system���κ��� ������ ä�α׷� ����
3. ������ ä�α׷쿡 ä�α׷�A�߰�
4. sound��������
5. ����ϸ� ä�μ���
6. ä�ο� ä�α׷�A����
7. ä�α׷�A�� ���Ͽ� ��ϵ� �Ҹ��� �����Ѵ�.
�����, ȿ���� ���� ����
- ȿ�����׷� : �ѼҸ�, ���ڱ��Ҹ�, ���
- ������Ǳ׷� : �� ������ǵ�
- UI�׷� : UI�� ����Ҷ� ����
- ������ ä�� �׷� : ������ �Ͻ�������

*/