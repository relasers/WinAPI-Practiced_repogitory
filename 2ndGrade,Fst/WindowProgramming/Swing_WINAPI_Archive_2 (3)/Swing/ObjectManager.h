#pragma once
#include "stdafx.h"
class CObjectManager
{
public:
	CPlayer player;
	CPlatform ground;

	void init(RECT);
	void Play_Obj_Sprite(); // ������Ʈ ��������Ʈ ���
	void Obj_Updater(); // ������Ʈ ���� ������Ʈ
	void Obj_RT_Key_Input(bool); // ������Ʈ �ǽð� Ű �Է¿� ���� ������
	bool InputKeyBoard(UINT iMessage,WPARAM wParam,LPARAM lParam,bool iskeydown);
	void Draw(HDC,RECT m_rect);

	CObjectManager();
	~CObjectManager();
};

