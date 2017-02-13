#pragma once
#include "Scene.h"
#define TITLE_MX_LENGTH 64
class CFrameWork
{
private:
	HWND m_hwnd; // 윈도우 핸들
	RECT m_rect; // rect 구조체
	HINSTANCE m_hInst;

	HBRUSH hbrBackground = NULL; // 배경브러쉬핸들
	HDC m_hdcBackGround;
	HBITMAP m_BackGroundBitmap;

	CScene* m_currentScene;
	CScene* m_ArrayScene[Scene_State::Count];

	chrono::system_clock::time_point m_current_time;
	chrono::duration<double> m_timeElapsed; // 시간이 얼마나 지났나
	double m_fps;

	TCHAR m_CaptionTitle[TITLE_MX_LENGTH];
	int m_TitleLength;
	chrono::system_clock::time_point m_LastUpdate_time;
	chrono::duration<double> m_UpdateElapsed; // 시간이 얼마나 지났나


public:
	bool Initial(HWND, RECT,HINSTANCE);
	void Destroy(); // posquit,destroywindow(hWnd)넣으면 안돼
	void OnCreate();

	void OnDraw(HDC);
	void PreprocessingDraw();

	void CreateBackBuffer();
	void DestroyBackBuffer();

	void OnTimer(float fTimeElapsed); // 업데이트
	void InputMouse(UINT, WPARAM, LPARAM); //메세지,w파람,l파람
	void InputKeyBoard(UINT, WPARAM, LPARAM); //메세지,w파람,l파람

	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);

	void FrameAdvance();

	void ChangeScene(int tag,bool bDestroy = false);
	

	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM );//메세지,w파람,l파람
	LRESULT WindowMenu(HWND, UINT, WPARAM, LPARAM);
	CFrameWork();
	~CFrameWork();
};
