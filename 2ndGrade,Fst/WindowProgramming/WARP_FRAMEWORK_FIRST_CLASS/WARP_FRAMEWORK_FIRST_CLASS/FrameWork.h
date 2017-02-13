#pragma once
class CFrameWork
{
private:
	HWND m_hwnd; // 윈도우 핸들
	RECT m_rect; // rect 구조체
	HBRUSH hbrBackground = NULL; // 배경브러쉬핸들
	POINT ptmouse; // 마우스 위치
	wchar_t order[TEMP_ARR_SIZE] = { 0 }; // 명령어를 받는 배열
	wchar_t timer[TEMP_ARR_SIZE] = {0};
	int count; // 명령어 입력용 변수
	int time; // 시간이 올라간다
public:
	bool Initial(HWND, RECT);
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
