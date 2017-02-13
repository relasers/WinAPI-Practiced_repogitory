#pragma once

#include"Ball.h"
class CFrameWork
{
private:
	HWND m_hwnd; // ������ �ڵ�

	RECT m_rect; // rect ����ü
	RECT m_diarect;

	HINSTANCE m_hInst;

	PAINTSTRUCT ps;
	PAINTSTRUCT dia_ps;

	HBRUSH shapebr = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldbr;

	HDC hdc, MemDC, windc; // �׻� ù��° ���ڴ� hDC ��! , �ι�°�� ��Ʈ�ʿ�

	HBRUSH hbrBackground = NULL; // ���귯���ڵ�
	
	CBall winball;
	CBall diaball;

	int Radio;
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
	LRESULT WindowMenu(HWND, UINT, WPARAM, LPARAM);
	BOOL WindowDialogProc(HWND, UINT, WPARAM, LPARAM);

	CFrameWork();
	~CFrameWork();
};
