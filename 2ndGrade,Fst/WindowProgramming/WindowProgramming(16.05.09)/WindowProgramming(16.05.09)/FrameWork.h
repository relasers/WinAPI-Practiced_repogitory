#pragma once

#include "Obj_Cat.h"
#include "Obj_Mouse.h"
#include "Obj_Obstacle.h"

class CFrameWork
{
private:
	HWND m_hwnd; // 윈도우 핸들
	RECT m_rect; // rect 구조체
	HINSTANCE m_hInst;

	PAINTSTRUCT ps;
	HDC hdc, MemDC; // 항상 첫번째 인자는 hDC 다! , 두번째껀 비트맵용

	HBRUSH hbrBackground = NULL; // 배경브러쉬핸들
	
	HBITMAP bit_back;
	HBITMAP bit_cat;
	HBITMAP bit_mouse;

	CObj_Cat cat;
	CObj_Mouse mouse;
	CObj_Obstacle obstacle[MAX_OBSTACLE];

	POINT ptmouse;
	RECT col_check; // 충돌체크용

	int direction = left;
	bool drag = false;
public:
	bool Initial(HWND, RECT,HINSTANCE);
	void Destroy(); // posquit,destroywindow(hWnd)넣으면 안돼
	void OnCreate();
	void OnDraw(HDC);
	void OnTimer(UINT); // 업데이트
	void InputMouse(UINT, WPARAM, LPARAM); //메세지,w파람,l파람
	void InputKeyBoard(UINT, WPARAM, LPARAM); //메세지,w파람,l파람

	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);
	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM );//메세지,w파람,l파람
	CFrameWork();
	~CFrameWork();
};
