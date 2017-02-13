#pragma once
#include "Scene.h"
#include "SpriteImage.h"

class CLobbyScene :public CScene
{
protected:

	CSpriteImage	*m_cimgBackground;
	CSpriteImage	*m_cimgMenu;
	CSpriteImage	*m_cimgMenuCusser;

	int m_CusserMove;

public:
	CLobbyScene();
	virtual ~CLobbyScene();

	virtual void Update(float fTimeElapsed); 
	virtual void Draw(HDC hdc);

	// �Լ� ȣ�� ���Ŀ��� ó���� ���ϸ� false ��ȯ
	virtual bool OnProcessingKeyboardMessage	(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFramework* pFramework, CSoundManager *pSoundManager, HWND hwnd, CurrentScene tag, CPlayer **Player);
	virtual void ReSetObjects() {};
	virtual void ReleaseObjects();
	virtual void Update_Scene() {}
};
