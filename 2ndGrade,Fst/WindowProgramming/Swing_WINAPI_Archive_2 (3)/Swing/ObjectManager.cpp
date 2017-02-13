#include "stdafx.h"
#include "ObjectManager.h"


void CObjectManager::init(RECT m_rect)
{
	RECT groundinit = {0,m_rect.bottom-THICK_OF_GROUND,m_rect.right,m_rect.bottom}; // µû¾Ó ÃÊ±âÈ­
	POINT settingpt = {30,30};
	ground.setpos(groundinit);
	player.setpos(settingpt);
}

void CObjectManager::Play_Obj_Sprite()
{
	player.play_spr();
}

void CObjectManager::Obj_Updater()
{
	player.Updater();
	player.collisioncheck(player.getpos(),ground.getpos());
}

void CObjectManager::Obj_RT_Key_Input(bool iskeydown) {
	player.ActonKey(iskeydown);
}

bool CObjectManager::InputKeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam, bool iskeydown)
{
	switch (iMessage) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
		case VK_RIGHT:
			if (iskeydown == false)
				player.reset_spr();
		}
		return true;
		break;
	case WM_KEYUP:
		iskeydown = false;
		switch (wParam) {
		case VK_LEFT:
		case VK_RIGHT:
			player.reset_spr();
			player.setstance(PStance::stand);
		}
		break;
	}
}

void CObjectManager::Draw(HDC hdc,RECT m_rect) {
	player.draw(hdc,m_rect);
	ground.draw(hdc);
}

CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
}
