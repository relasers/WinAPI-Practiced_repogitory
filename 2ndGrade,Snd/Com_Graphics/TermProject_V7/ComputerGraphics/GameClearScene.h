#pragma once
#include "Scene.h"
class CGameClearScene :public CScene
{
private:
	CSoundManager			*m_SoundManager;

	CCamera_OpenGL			*m_pCamera;
	CLight					*m_pLight;
	CTextureLibraray		*m_TextureLib;

	float					m_timer = 0.0f;
	bool					m_Input = false;

public:
	CGameClearScene();
	~CGameClearScene();
	virtual void Update(float fTimeElapsed);
	virtual void Rendering();
	virtual void RendMiniMap();

	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFramework* pFramework, HWND hwnd, CurrentScene tag);
	virtual void ReleaseObjects();
};

