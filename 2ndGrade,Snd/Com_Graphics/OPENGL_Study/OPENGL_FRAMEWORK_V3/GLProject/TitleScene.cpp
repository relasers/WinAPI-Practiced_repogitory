#include "stdafx.h"
#include "GLFramework.h"
#include "MainGameScene.h"
#include "TitleScene.h"


CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Update()
{
}

void CTitleScene::Render()
{
}

void CTitleScene::Reshape()
{
	auto sz = m_pMasterFramework->GetWindowSize();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,sz.x,sz.y,0,-1,1);

	glMatrixMode(GL_MODELVIEW);

}

void CTitleScene::Mouse(int button, int state, int x, int y)
{
	switch (GetMouseState(button, state))
	{
	case GLKeyStateCombine::LBUTTONDOWN:
		m_pMasterFramework->BuildScene<CMainGameScene>();
		break;
	case GLKeyStateCombine::RBUTTONDOWN:
		break;
	case GLKeyStateCombine::LBUTTONUP:
		break;
	case GLKeyStateCombine::RBUTTONUP:
		break;

	}
}

void CTitleScene::BuildScene(CGLFramework * pframework, int tag)
{
	CScene::BuildScene(pframework, tag);
	glClearColor(0.7, 0.7, 0.8, 1);

}
