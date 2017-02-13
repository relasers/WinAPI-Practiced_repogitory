#pragma once
#include "Scene.h"
#include "SpriteImage.h"

class CGameOverScene :public CScene
{
protected:

	CSpriteImage	*m_cimgBackground;

public:
	CGameOverScene();
	virtual ~CGameOverScene();

	virtual void Update(float fTimeElapsed);
	virtual void Draw(HDC hdc);

	// �Լ� ȣ�� ���Ŀ��� ó���� ���ϸ� false ��ȯ
	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFramework* pFramework, CSoundManager *pSoundManager, HWND hwnd, CurrentScene tag, CPlayer **Player);
	virtual void ReSetObjects() {};
	virtual void ReleaseObjects();
	virtual void Update_Scene() {}
};

