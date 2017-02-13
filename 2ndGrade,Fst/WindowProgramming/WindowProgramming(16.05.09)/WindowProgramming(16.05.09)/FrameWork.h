#pragma once

#include "Obj_Cat.h"
#include "Obj_Mouse.h"
#include "Obj_Obstacle.h"

class CFrameWork
{
private:
	HWND m_hwnd; // ������ �ڵ�
	RECT m_rect; // rect ����ü
	HINSTANCE m_hInst;

	PAINTSTRUCT ps;
	HDC hdc, MemDC; // �׻� ù��° ���ڴ� hDC ��! , �ι�°�� ��Ʈ�ʿ�

	HBRUSH hbrBackground = NULL; // ���귯���ڵ�
	
	HBITMAP bit_back;
	HBITMAP bit_cat;
	HBITMAP bit_mouse;

	CObj_Cat cat;
	CObj_Mouse mouse;
	CObj_Obstacle obstacle[MAX_OBSTACLE];

	POINT ptmouse;
	RECT col_check; // �浹üũ��

	int direction = left;
	bool drag = false;
public:
	bool Initial(HWND, RECT,HINSTANCE);
	void Destroy(); // posquit,destroywindow(hWnd)������ �ȵ�
	void OnCreate();
	void OnDraw(HDC);
	void OnTimer(UINT); // ������Ʈ
	void InputMouse(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�
	void InputKeyBoard(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�

	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);
	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM );//�޼���,w�Ķ�,l�Ķ�
	CFrameWork();
	~CFrameWork();
};
