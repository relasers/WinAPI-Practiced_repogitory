#include "stdafx.h"
#include "SoundManager.h"

CSoundManager::CSoundManager()
{
}
CSoundManager::~CSoundManager()
{
}

void CSoundManager::Initialize()
{
	// 사운드 시스템을 생성하는 코드
	FMOD_System_Create(&g_System);
	// 채널수와 사운드 모드 설정
	FMOD_System_Init(g_System, Max_Channel, FMOD_INIT_NORMAL, NULL);             
	// 채널그룹 생성
	FMOD_System_CreateChannelGroup(g_System, "BGM", &g_BGM_ChannelGroup);
	FMOD_System_CreateChannelGroup(g_System, "UI", &g_UI_ChannelGroup);
	FMOD_System_CreateChannelGroup(g_System, "Effect", &g_Effect_ChannelGroup);
	// 채널그룹에 채널셋팅
	FMOD_Channel_SetChannelGroup(g_BGM_Channel, g_BGM_ChannelGroup);
	FMOD_Channel_SetChannelGroup(g_UI_Channel, g_UI_ChannelGroup);
	FMOD_Channel_SetChannelGroup(g_Enemy_Channel, g_Effect_ChannelGroup);
	FMOD_Channel_SetChannelGroup(g_Player_Channel, g_Effect_ChannelGroup);
	FMOD_Channel_SetChannelGroup(g_Boss_Channel, g_Effect_ChannelGroup);
	// 사운드 생성
	CreateSound_BGM();
	CreateSound_UI();
	CreateSound_Player();
	CreateSound_Enemy();
	CreateSound_Boss();
	// 볼륨 크기조절
	FMOD_Channel_SetVolume(g_UI_Channel, 0.3);
}

void CSoundManager::CreateSound_BGM() {

	FMOD_System_CreateSound(g_System, "Sound/Logo.wav", FMOD_LOOP_NORMAL, 0, &g_BGM_Sound[BGM_SOUND::Logo_BGM]);
	FMOD_System_CreateSound(g_System, "Sound/Title.mp3", FMOD_LOOP_NORMAL, 0, &g_BGM_Sound[BGM_SOUND::Title_BGM]);
	FMOD_System_CreateSound(g_System, "Sound/Play_BGM.ogg", FMOD_LOOP_NORMAL, 0, &g_BGM_Sound[BGM_SOUND::Stage_BGM]);
	FMOD_System_CreateSound(g_System, "Sound/GameOver.ogg", FMOD_LOOP_NORMAL, 0, &g_BGM_Sound[BGM_SOUND::GameOver_BGM]);
	FMOD_System_CreateSound(g_System, "Sound/GameClear.mp3", FMOD_LOOP_NORMAL, 0, &g_BGM_Sound[BGM_SOUND::GameClear_BGM]);
}
void CSoundManager::CreateSound_UI() {

	FMOD_System_CreateSound(g_System, "Sound/BarrierCrash.mp3", FMOD_DEFAULT, 0, &g_UI_Sound[UI_SOUND::BarrierCrash_UI]);
	FMOD_System_CreateSound(g_System, "Sound/CollideBullet.ogg", FMOD_DEFAULT, 0, &g_UI_Sound[UI_SOUND::CollideBullet_UI]);
}
void CSoundManager::CreateSound_Player() {

	FMOD_System_CreateSound(g_System, "Sound/Shot.ogg", FMOD_DEFAULT, 0, &g_Player_Sound[PLAYER_SOUND::Shot_P]);
	FMOD_System_CreateSound(g_System, "Sound/Die.mp3", FMOD_DEFAULT, 0, &g_Player_Sound[PLAYER_SOUND::Die_P]);
	FMOD_System_CreateSound(g_System, "Sound/Hit.wav", FMOD_DEFAULT, 0, &g_Player_Sound[PLAYER_SOUND::Hit_P]);
}
void CSoundManager::CreateSound_Enemy() {

	FMOD_System_CreateSound(g_System, "Sound/Shot.ogg", FMOD_DEFAULT, 0, &g_Enemy_Sound[ENEMY_SOUND::Enemy_Shot]);
	FMOD_System_CreateSound(g_System, "Sound/Hit.wav", FMOD_DEFAULT, 0, &g_Enemy_Sound[ENEMY_SOUND::Enemy_Hit]);
	FMOD_System_CreateSound(g_System, "Sound/Die.mp3", FMOD_DEFAULT, 0, &g_Enemy_Sound[ENEMY_SOUND::Enemy_Die]);
}
void CSoundManager::CreateSound_Boss() {

	FMOD_System_CreateSound(g_System, "Sound/Splash.ogg", FMOD_DEFAULT, 0, &g_Boss_Sound[BOSS_SOUND::Boss_Shot]);
	FMOD_System_CreateSound(g_System, "Sound/Boss_Crashed.ogg", FMOD_DEFAULT, 0, &g_Boss_Sound[BOSS_SOUND::Boss_Die]);
}

void CSoundManager::Update(float fTimeElapsed)
{
	FMOD_System_Update(g_System);
}

void CSoundManager::PlaySnd_BGM(int set) {
	switch (set) {
	case BGM_SOUND::Logo_BGM:
		FMOD_System_PlaySound(g_System, g_BGM_Sound[BGM_SOUND::Logo_BGM], NULL, false, &g_BGM_Channel);
		break;
	case BGM_SOUND::Title_BGM:
		FMOD_System_PlaySound(g_System, g_BGM_Sound[BGM_SOUND::Title_BGM], NULL, false, &g_BGM_Channel);
		break;
	case BGM_SOUND::Stage_BGM:
		FMOD_System_PlaySound(g_System, g_BGM_Sound[BGM_SOUND::Stage_BGM], NULL, false, &g_BGM_Channel);
		break;
	case BGM_SOUND::GameOver_BGM:
		FMOD_System_PlaySound(g_System, g_BGM_Sound[BGM_SOUND::GameOver_BGM], NULL, false, &g_BGM_Channel);
		break;
	case BGM_SOUND::GameClear_BGM:
		FMOD_System_PlaySound(g_System, g_BGM_Sound[BGM_SOUND::GameClear_BGM], NULL, false, &g_BGM_Channel);
		break;
	case BGM_SOUND::Stop_BGM:
		FMOD_Channel_Stop(g_BGM_Channel);
		break;
	}
}
void CSoundManager::PlaySnd_UI(int set) {
	switch (set) {
	case UI_SOUND::BarrierCrash_UI:
		FMOD_System_PlaySound(g_System, g_UI_Sound[UI_SOUND::BarrierCrash_UI], NULL, false, &g_UI_Channel);
		break;
	case UI_SOUND::CollideBullet_UI:
		FMOD_System_PlaySound(g_System, g_UI_Sound[UI_SOUND::CollideBullet_UI], NULL, false, &g_UI_Channel);

		break;
	case UI_SOUND::Stop_UI:
		FMOD_Channel_Stop(g_UI_Channel);
		break;
	}
}
void CSoundManager::PlaySnd_Player(int set) {
	switch (set) {
	case PLAYER_SOUND::Shot_P:
		FMOD_System_PlaySound(g_System, g_Player_Sound[PLAYER_SOUND::Shot_P], NULL, false, &g_Player_Channel);
		break;
	case PLAYER_SOUND::Hit_P:
		FMOD_System_PlaySound(g_System, g_Player_Sound[PLAYER_SOUND::Hit_P], NULL, false, &g_Player_Channel);
		break;
	case PLAYER_SOUND::Die_P:
		FMOD_System_PlaySound(g_System, g_Player_Sound[PLAYER_SOUND::Die_P], NULL, false, &g_Player_Channel);
		break;
	case PLAYER_SOUND::Stop_P:
		FMOD_Channel_Stop(g_Player_Channel);
		break;
	}
}
void CSoundManager::PlaySnd_Enemy(int set) {
	switch (set) {
	case ENEMY_SOUND::Enemy_Shot:
		FMOD_System_PlaySound(g_System, g_Enemy_Sound[ENEMY_SOUND::Enemy_Shot], NULL, false, &g_Enemy_Channel);
		break;
	case ENEMY_SOUND::Enemy_Hit:
		FMOD_System_PlaySound(g_System, g_Enemy_Sound[ENEMY_SOUND::Enemy_Hit], NULL, false, &g_Enemy_Channel);
		break;
	case ENEMY_SOUND::Enemy_Die:
		FMOD_System_PlaySound(g_System, g_Enemy_Sound[ENEMY_SOUND::Enemy_Die], NULL, false, &g_Enemy_Channel);
		break;
	case ENEMY_SOUND::Enemy_Stop:
		FMOD_Channel_Stop(g_Enemy_Channel);
		break;
	}
}
void CSoundManager::PlaySnd_Boss(int set) {
	switch (set) {
	case BOSS_SOUND::Boss_Shot:
		FMOD_System_PlaySound(g_System, g_Boss_Sound[BOSS_SOUND::Boss_Shot], NULL, false, &g_Boss_Channel);
		break;
	case BOSS_SOUND::Boss_Die:
		FMOD_System_PlaySound(g_System, g_Boss_Sound[BOSS_SOUND::Boss_Die], NULL, false, &g_Boss_Channel);
		break;
	case BOSS_SOUND::Boss_Stop:
		FMOD_Channel_Stop(g_Boss_Channel);
		break;
	}
}

void CSoundManager::Destroy() {
	for (int i = 0; i < BGM_SOUND::Count_BGM; ++i) {
		FMOD_Sound_Release(g_BGM_Sound[i]);
	}
	for (int i = 0; i < UI_SOUND::Count_UI; ++i) {
		FMOD_Sound_Release(g_UI_Sound[i]);
	}
	for (int i = 0; i < PLAYER_SOUND::Count_P; ++i) {
		FMOD_Sound_Release(g_Player_Sound[i]);
	}
	for (int i = 0; i < ENEMY_SOUND::Enemy_Count; ++i) {
		FMOD_Sound_Release(g_Enemy_Sound[i]);
	}
	for (int i = 0; i < BOSS_SOUND::Boss_Count; ++i) {
		FMOD_Sound_Release(g_Boss_Sound[i]);
	}
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}