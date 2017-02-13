#pragma once
#include "Scene.h"
#define ObstarcleNum 40
#define InitEnemyNum 10
#define ImmuneTime 5

class CM_Sky;

class CMainScene :public CScene
{
private:
	CSoundManager			*m_SoundManager;

	CCamera_OpenGL			*m_pCamera;
	CCamera_OpenGL			*m_MiniMapCamera;

	CLight					*m_pLight;
	CTextureLibraray		*m_TextureLib;

	CSurface				*m_Bottom;
	CM_Sky					*m_Sky;

	std::list<CCube *>		m_ObstarcleList;
	std::list<Cbullet*>		m_bullets;
	std::list<Cbullet*>		m_ally_bullets;
	std::list<CEnergyBolt*> m_energybolts;
	std::list<CParticle*>	m_particles;

	CPlayer					*m_Player;
	CBoss					*m_Boss;
	std::list<CEnemy*>		m_EnemyList;

	float					m_Immune = 0.0f;

	bool					m_bFront = false;
	bool					m_bBack = false;
	bool					m_bLeft = false;
	bool					m_bRight = false;

	bool					m_bGameOver = false;
	bool					m_bGameClear = false;
public:
	CMainScene();
	~CMainScene();

	void DrawAxis();
	void SettingLight();
	void SettingObjects();

	bool CollideCheck(CCube& a, CCube& b);
	void Reset();

	virtual void Update(float fTimeElapsed);
	virtual void Rendering();
	virtual void RendMiniMap();

	virtual bool OnProcessingKeyboardMessage	(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingWindowMessage		(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void BuildObjects(CFramework* pFramework, HWND hwnd, CurrentScene tag);
	virtual void ReleaseObjects();

	CCamera_OpenGL* GetCamera() { return m_pFramework->GetCamera(); }
	CLight* GetLight() { return m_pFramework->GetLight(); }

	bool ProcessInput();
};
