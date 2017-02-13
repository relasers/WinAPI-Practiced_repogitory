#include "stdafx.h"
#include "SoundManager.h"


CSoundManager::CSoundManager()
{
}


CSoundManager::~CSoundManager()
{
}

void CSoundManager::Init() {
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System,32,FMOD_INIT_NORMAL,NULL);
}
void CSoundManager::CreateSound() {
	FMOD_System_Create(&g_System);         //사운드 시스템을 생성하는 코드
	FMOD_System_Init(g_System,32, FMOD_INIT_NORMAL, NULL);             //채널수와 사운드 모드 설정하는부분이다.
	
	FMOD_System_CreateSound(g_System,"RES\\SND\\BackGroundSound.mp3", FMOD_LOOP_NORMAL, 0, &g_Sound[SD_Back]);
	FMOD_System_CreateSound(g_System, "RES\\SND\\Scream_1.wav", FMOD_DEFAULT, 0, &g_Sound[SD_SCR1]);
	FMOD_System_CreateSound(g_System, "RES\\SND\\Scream_2.wav", FMOD_DEFAULT, 0, &g_Sound[SD_SCR2]);
	FMOD_System_CreateSound(g_System, "RES\\SND\\electriczap.wav", FMOD_DEFAULT, 0, &g_Sound[SD_PORTAL]);
	FMOD_System_CreateSound(g_System, "RES\\SND\\Get_Item.wav", FMOD_DEFAULT, 0, &g_Sound[SD_GETITEM]);
}
void CSoundManager::PlaySnd(int set) {
	switch (set) {
	case SD_Back:
		FMOD_System_PlaySound(g_System, g_Sound[SD_Back], NULL, false, &g_Channel);
		break;
	case SD_SCR1:
		FMOD_System_PlaySound(g_System, g_Sound[SD_SCR1], NULL, false, &g_Channel);
		break;
	case SD_SCR2:
		FMOD_System_PlaySound(g_System, g_Sound[SD_SCR2], NULL, false, &g_Channel);
		break;
	case SD_PORTAL:
		FMOD_System_PlaySound(g_System, g_Sound[SD_PORTAL], NULL, false, &g_Channel);
		break;
	case SD_GETITEM:
		FMOD_System_PlaySound(g_System, g_Sound[SD_GETITEM], NULL, false, &g_Channel);
		break;
	}
	
}
void CSoundManager::Destroy() {
//	for (int i = 0; i < SD_END; ++i) {
//		FMOD_Sound_Release(g_Sound[i]);
//	}
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}