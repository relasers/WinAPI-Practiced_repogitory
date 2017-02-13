#pragma once
#include "Scene.h"
#include "SpriteImage.h"

class CTitleScene :public CScene
{
protected:

	CSpriteImage *m_cimgBackground{ nullptr };

	CImage m_Logo;

	int m_Alpha{ 0 };
	
	bool m_Sound{ false };

public:
	CTitleScene();
	virtual ~CTitleScene();

	virtual void Update(float fTimeElapsed); // "=0" -> ���� �����Լ�
	virtual void Draw(HDC hdc);

	// �Լ� ȣ�� ���Ŀ��� ó���� ���ϸ� false ��ȯ
	virtual bool OnProcessingKeyboardMessage	(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFramework* pFramework, CSoundManager *pSoundManager, HWND hwnd, CurrentScene tag, CPlayer**Player);
	virtual void ReSetObjects() {};
	virtual void ReleaseObjects();
	virtual void Update_Scene() {}
};
