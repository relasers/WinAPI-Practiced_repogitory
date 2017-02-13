#pragma once

#include "Car.h"
#include"Traffic_light.h"

class CFrameWork
{
private:
	HWND m_hwnd; // ������ �ڵ�
	RECT m_rect; // rect ����ü
	HINSTANCE m_hInst;

	PAINTSTRUCT ps;
	HDC hdc, MemDC; // �׻� ù��° ���ڴ� hDC ��! , �ι�°�� ��Ʈ�ʿ�

	HBRUSH hbrBackground = NULL; // ���귯���ڵ�
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
