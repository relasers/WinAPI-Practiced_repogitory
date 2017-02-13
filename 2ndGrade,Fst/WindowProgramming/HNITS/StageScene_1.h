#pragma once
#include "Scene.h"
#include <atlimage.h>
#define STAGE_1_ENEMY_NUM 20

template<typename T>
class WarpList;
class CPlayer;
class CEnemy;

class CStageScene_1 :public CScene
{
protected:
	CImage	m_cimgBackground;
	CImage m_cimgControl;

	CPlayer			**m_Player;
	WarpList<CEnemy*>m_EnemyList;

	POINT m_ScenePos;
public:
	CStageScene_1();
	virtual ~CStageScene_1();

	virtual void Update(float fTimeElapsed);
	virtual void Draw(HDC hdc);

	// �Լ� ȣ�� ���Ŀ��� ó���� ���ϸ� false ��ȯ
	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFramework* pFramework, CSoundManager *pSoundManager, HWND hwnd, CurrentScene tag, CPlayer **Player);
	virtual void ReSetObjects();
	virtual void ReleaseObjects();
	virtual void Update_Scene();

	void UnitInitialize();
	bool ProcessInput();
};

