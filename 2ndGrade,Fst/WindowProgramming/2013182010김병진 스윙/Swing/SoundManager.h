#pragma once
class CSoundManager
{
private:
	FMOD_SYSTEM*   g_System;
	FMOD_SOUND*    g_Sound[SD_END];
	FMOD_CHANNEL* g_Channel;
public:
	CSoundManager();
	~CSoundManager();

	void Init();
	void CreateSound();
	void PlaySnd(int);
	void Destroy();
};

