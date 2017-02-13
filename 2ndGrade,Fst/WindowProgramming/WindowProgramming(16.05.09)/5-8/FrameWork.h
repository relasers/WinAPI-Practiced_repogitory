#pragma once

#include "Car.h"
#include"Traffic_light.h"

class CFrameWork
{
private:
	HWND m_hwnd; // 윈도우 핸들
	RECT m_rect; // rect 구조체
	HINSTANCE m_hInst;

	PAINTSTRUCT ps;
	HDC hdc, MemDC; // 항상 첫번째 인자는 hDC 다! , 두번째껀 비트맵용

	HBRUSH hbrBackground = NULL; // 배경브러쉬핸들
	HBRUSH old_brush;

	HBITMAP bit_back;
	HBITMAP bit_truck;
	HBITMAP bit_rev_truck;

	HBITMAP bit_crossline;
	RECT crossline = {
	250 ,100,
	550 ,300
	};

	CCar car[8];
	CTraffic_light light[3];
	RECT col_check;
	wchar_t temp_str[40];

	POINT ptmouse;
	int counter = 0;

	bool red = false;
	bool yellow = false;
	bool green = true;

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
