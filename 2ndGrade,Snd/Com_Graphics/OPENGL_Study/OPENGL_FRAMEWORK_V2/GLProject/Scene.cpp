#include "Scene.h" // 자기 자신은 제일 마지막에 인클루드한다.
CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::Update()
{
}

void CScene::Rander()
{
}

void CScene::InputKeyboard(unsigned char key, int x, int y)
{
}

void CScene::InputMouse(int button, int state, int x, int y)
{
}

void CScene::BuildScene(CGLFramework * pFramework, CurrentScene tag)
{
	m_pMasterFramework = pFramework;
	m_iTag = tag;
}
