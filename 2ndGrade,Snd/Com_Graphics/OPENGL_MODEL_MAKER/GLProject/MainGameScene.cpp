#pragma once
#include "stdafx.h"
#include "GLFramework.h"
#include "MainGameScene.h"



CMainGameScene::CMainGameScene()
{
}


CMainGameScene::~CMainGameScene()
{
}

void CMainGameScene::Update()
{

}

void CMainGameScene::Render()
{
	glColor3ub(100,100,100);
	glutSolidCube(1.f);
}

void CMainGameScene::Reshape()
{
	auto sz = m_pMasterFramework->GetWindowSize();
	m_camera.SetAspect(static_cast<float>(sz.x) / static_cast<float>(sz.y));

	m_camera.LookAt();
}

void CMainGameScene::Mouse(int button, int state, int x, int y)
{
	switch (GetMouseState(button, state))
	{
	case GLKeyStateCombine::LBUTTONDOWN:
		m_camera.Move({ 0, 0, 1 });
		break;
	case GLKeyStateCombine::RBUTTONDOWN:
		break;
	case GLKeyStateCombine::LBUTTONUP:
		break;
	case GLKeyStateCombine::RBUTTONUP:
		break;

	}
}

void CMainGameScene::KeyBoard(unsigned char key, int x, int y)
{
	if (key == 'j' || key == 'J') {
		m_camera.Rotate(10, 0);
	}
}

void CMainGameScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	glClearColor(0.5, 0.5, 0.8, 1);
}
