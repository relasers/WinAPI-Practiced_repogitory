#pragma once

#include"Puzzle.h"

class CFrameWork
{
private:
	HWND m_hwnd; // ������ �ڵ�
	RECT m_rect; // rect ����ü
	HINSTANCE m_hinstance;
	PAINTSTRUCT ps;

	/////<�׷��� ����>//////////////////
	HBRUSH hbrBackground = NULL; // ���귯���ڵ�

	HDC hdc, MemDC;
	HBITMAP backimage;
	////////////////////////////////
	//////<���� ����>/////////////////
	int screenmode = 0;
	int gamestate = Game_Stat::gameset;
	CPuzzle puzzle[5][5];

	POINT ptmouse; // ���콺 ������
	POINT temp_pos; // �ӽ� ��

	POINT pt_left;
	POINT pt_right;
	POINT pt_up;
	POINT pt_down;

	POINT blanked_pos; // ���ĭ�� �������
	
	RECT moved_rect;

	RECT movingrect; // Ŭ���Ѱ�
	RECT blankedrect; // ����

	RECT temp_f_check; // �浹üũ

	RECT temp_rect_ud; // ���� üũ
	RECT temp_rect_lr; // �¿� üũ
	/////////////////////////////////////
public:
	bool Initial(HWND, RECT, HINSTANCE);
	void Destroy(); // posquit,destroywindow(hWnd)������ �ȵ�
	void OnCreate();
	void OnDraw(HDC);
	void OnTimer(UINT); // ������Ʈ
	void InputMouse(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�
	void InputKeyBoard(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�

	void createPuzzle();
	void Shuffle_image();
	void Draw_image(int,HDC,HDC);

	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);
	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM);//�޼���,w�Ķ�,l�Ķ�
	CFrameWork();
	~CFrameWork();
};
