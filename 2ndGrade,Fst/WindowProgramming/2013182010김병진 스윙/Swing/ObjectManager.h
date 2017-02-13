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
	void Play_Obj_Sprite(); // 오브젝트 스프라이트 재생
	void Obj_Updater(RECT); // 오브젝트 상태 업데이트
	void Obj_RT_Key_Input(bool); // 오브젝트 실시간 키 입력에 따른 움직임
	void Obj_NORM_Key_Input(WPARAM);
	bool InputKeyBoard(UINT iMessage,WPARAM wParam,LPARAM lParam,bool iskeydown);
	void Draw(HDC,RECT m_rect);

	CObjectManager();
	~CObjectManager();
};

