#pragma once
#include "stdafx.h"
class CObjectManager
{
public:
	CPlayer player;
	CPlatform ground;
	CPlatform platform[NUM_PLATFORM+2];
	CBasket basket[2];
	CPortal portal;
	CItem * item_head;

	int score = 0;
	TCHAR temp[100];

	void init(RECT);
	void Play_Obj_Sprite(); // ������Ʈ ��������Ʈ ���
	void Obj_Updater(RECT); // ������Ʈ ���� ������Ʈ
	void Obj_RT_Key_Input(bool); // ������Ʈ �ǽð� Ű �Է¿� ���� ������
	void Obj_NORM_Key_Input(WPARAM);
	bool InputKeyBoard(UINT iMessage,WPARAM wParam,LPARAM lParam,bool iskeydown);
	void Draw(HDC,RECT m_rect);

	CObjectManager();
	~CObjectManager();
};

