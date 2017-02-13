#pragma once

#include"Puzzle.h"

class CFrameWork
{
private:
	HWND m_hwnd; // 윈도우 핸들
	RECT m_rect; // rect 구조체
	HINSTANCE m_hinstance;
	PAINTSTRUCT ps;

	/////<그래픽 도구>//////////////////
	HBRUSH hbrBackground = NULL; // 배경브러쉬핸들

	HDC hdc, MemDC;
	HBITMAP backimage;
	////////////////////////////////
	//////<게임 도구>/////////////////
	int screenmode = 0;
	int gamestate = Game_Stat::gameset;
	CPuzzle puzzle[5][5];

	POINT ptmouse; // 마우스 포인터
	POINT temp_pos; // 임시 점

	POINT pt_left;
	POINT pt_right;
	POINT pt_up;
	POINT pt_down;

	POINT blanked_pos; // 어느칸이 비었었나
	
	RECT moved_rect;

	RECT movingrect; // 클릭한거
	RECT blankedrect; // 공백

	RECT temp_f_check; // 충돌체크

	RECT temp_rect_ud; // 상하 체크
	RECT temp_rect_lr; // 좌우 체크
	/////////////////////////////////////
public:
	bool Initial(HWND, RECT, HINSTANCE);
	void Destroy(); // posquit,destroywindow(hWnd)넣으면 안돼
	void OnCreate();
	void OnDraw(HDC);
	void OnTimer(UINT); // 업데이트
	void InputMouse(UINT, WPARAM, LPARAM); //메세지,w파람,l파람
	void InputKeyBoard(UINT, WPARAM, LPARAM); //메세지,w파람,l파람

	void createPuzzle();
	void Shuffle_image();
	void Draw_image(int,HDC,HDC);

	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);
	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM);//메세지,w파람,l파람
	CFrameWork();
	~CFrameWork();
};
