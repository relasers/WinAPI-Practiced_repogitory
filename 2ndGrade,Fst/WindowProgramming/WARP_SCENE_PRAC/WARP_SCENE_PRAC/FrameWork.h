#pragma once
#include "Scene.h"
#define TITLE_MX_LENGTH 64
class CFrameWork
{
private:
	HWND m_hwnd; // ������ �ڵ�
	RECT m_rect; // rect ����ü
	HINSTANCE m_hInst;

	HBRUSH hbrBackground = NULL; // ���귯���ڵ�
	HDC m_hdcBackGround;
	HBITMAP m_BackGroundBitmap;

	CScene* m_currentScene;
	CScene* m_ArrayScene[Scene_State::Count];

	chrono::system_clock::time_point m_current_time;
	chrono::duration<double> m_timeElapsed; // �ð��� �󸶳� ������
	double m_fps;

	TCHAR m_CaptionTitle[TITLE_MX_LENGTH];
	int m_TitleLength;
	chrono::system_clock::time_point m_LastUpdate_time;
	chrono::duration<double> m_UpdateElapsed; // �ð��� �󸶳� ������


public:
	bool Initial(HWND, RECT,HINSTANCE);
	void Destroy(); // posquit,destroywindow(hWnd)������ �ȵ�
	void OnCreate();

	void OnDraw(HDC);
	void PreprocessingDraw();

	void CreateBackBuffer();
	void DestroyBackBuffer();

	void OnTimer(float fTimeElapsed); // ������Ʈ
	void InputMouse(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�
	void InputKeyBoard(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�

	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);

	void FrameAdvance();

	void ChangeScene(int tag,bool bDestroy = false);
	

	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM );//�޼���,w�Ķ�,l�Ķ�
	LRESULT WindowMenu(HWND, UINT, WPARAM, LPARAM);
	CFrameWork();
	~CFrameWork();
};
