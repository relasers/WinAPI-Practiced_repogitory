#pragma once

#include <Windows.h>
#include <iostream>

#define WT_COUNTING		0x0001

class CSpriteImage;

class CFramework
{
private:
	HWND			m_hWnd{ NULL };
	RECT			m_rcClient{ 0,0,0,0 };

	TCHAR			m_strTest[100]{ NULL };

	HBITMAP			m_hBitmapBackBuffer = NULL;
	HDC				m_hDC = NULL;

	COLORREF		m_clrBackBuffer = 0x000000;
	HBRUSH			m_hbrBackground = NULL;

	CSpriteImage	*m_SpriteImage;

public:
	CFramework();
	~CFramework();

	bool OnCreate(HWND hWnd, const RECT& rc);
	void CreatebackBuffer();

	bool OnDestroy();
	
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	HRESULT OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void Update(WPARAM wParam);
	
	void SetBKColor(COLORREF color);
	void ClearBackgroundColor();
	void PreproccessingForDraw();
	void OnDraw(HDC hDC);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

