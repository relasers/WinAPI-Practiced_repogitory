#include "stdafx.h"
#include "GLFramework.h"
#include "Scene.h"


CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::Update()
{
}


void CScene::Render()
{
}

void CScene::Reshape()
{
}

void CScene::Mouse(int button, int state, int x, int y)
{
	switch (GetMouseState(button, state))
	{
	case GLKeyStateCombine::LBUTTONDOWN:
		break;
	case GLKeyStateCombine::RBUTTONDOWN:
		break;
	case GLKeyStateCombine::LBUTTONUP:
		break;
	case GLKeyStateCombine::RBUTTONUP:
		break;

	}
}

void CScene::BuildScene(CGLFramework * pframework, int tag)
{
	m_pMasterFramework = pframework;
	m_iTag = tag;
}
