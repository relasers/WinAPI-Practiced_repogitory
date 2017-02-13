#pragma once
#include <iostream>
#include <gl/glut.h>
#include "GLFramework.h"

class CGLFramework; // 선언만 시켜 놓자

class CScene
{
public:
	CScene();
	~CScene();

	enum class CurrentScene : int {
		None = 0
		, Title
		, Lobby
		, Count
	};

public:
	virtual void Update();
	virtual void Rander();
	
	virtual void InputKeyboard(unsigned char key, int x, int y);
	virtual void InputMouse(int button, int state, int x, int y);
	
	virtual void BuildScene(CGLFramework* pFramework,
	CurrentScene tag
	);
	CGLFramework* GetMyFramework() { return m_pMasterFramework; }

	bool IsMyTag(CurrentScene tag) const { return (tag == m_iTag); }
	CurrentScene GetMyTag() const { return m_iTag; };

protected:

	CGLFramework*	m_pMasterFramework;
	CurrentScene	m_iTag;
};