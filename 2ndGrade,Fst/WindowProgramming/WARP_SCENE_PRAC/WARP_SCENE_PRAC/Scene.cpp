#include "stdafx.h"
#include <atlimage.h>
#include "FrameWork.h"
#include "Scene.h"

CScene::CScene()
{
}


CScene::~CScene()
{
	ReleaseObjects();
}

bool CScene::InputMouse(UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

bool CScene::InputKeyBoard(UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

void CScene::BuildObjects(CFrameWork * F, HWND hwnd, int tag)
{
	m_pframework = F;
	m_hwnd = hwnd;
	m_tag = tag;
}

void CScene::ReleaseObjects()
{
}

CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
	ReleaseObjects();
}

void CTitleScene::Update(float fTimeElapsed)
{
}

void CTitleScene::Draw(HDC hdc)
{
	img.StretchBlt(hdc, 0, 0,1000, 800);
}

bool CTitleScene::InputMouse(UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg) {
	case WM_LBUTTONDOWN:
		m_pframework->ChangeScene(Scene_State::Lobby);

		break;
	}
	return false;
	
}

bool CTitleScene::InputKeyBoard(UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg) {
	case WM_KEYDOWN:
		switch (wParam) {

		}
		break;
	}
	return false;
}

void CTitleScene::BuildObjects(CFrameWork * F, HWND hwnd, int tag)
{
	CScene::BuildObjects(F,hwnd,tag);
	img.Load(TEXT("RES\\IMG\\Pistol.PNG"));
}

void CTitleScene::ReleaseObjects()
{
}

CLobbyScene::CLobbyScene()
{
}

CLobbyScene::~CLobbyScene()
{
	ReleaseObjects();
}

void CLobbyScene::Update(float fTimeElapsed)
{
}

void CLobbyScene::Draw(HDC hdc)
{
	img.StretchBlt(hdc, 0, 0, 1000, 800);
}

bool CLobbyScene::InputMouse(UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg) {
	case WM_RBUTTONDOWN:
		m_pframework->ChangeScene(Scene_State::Title);

		break;
	}
	return false;
}

bool CLobbyScene::InputKeyBoard(UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg) {
	case WM_KEYDOWN:
		switch (wParam) {

		}
		break;
	}
	return false;
}

void CLobbyScene::BuildObjects(CFrameWork * F, HWND hwnd, int tag)
{
	CScene::BuildObjects(F, hwnd, tag);
	img.Load(TEXT("RES\\IMG\\Death.PNG"));
}

void CLobbyScene::ReleaseObjects()
{
}
