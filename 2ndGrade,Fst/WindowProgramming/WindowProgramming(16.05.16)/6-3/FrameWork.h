#pragma once
class CFrameWork
{
private:
	HWND m_hwnd; // 윈도우 핸들
	RECT m_rect; // rect 구조체
	HINSTANCE m_hInst;

	PAINTSTRUCT ps;
	HDC hdc, MemDC; // 항상 첫번째 인자는 hDC 다! , 두번째껀 비트맵용


	HBRUSH shapebr = (HBRUSH)CreateSolidBrush(RGB(255,0,0));
	HBRUSH oldbr;
	HBRUSH hbrBackground = NULL; // 배경브러쉬핸들
	
	int Radiostat = TriFun::sa;
	int Checkstat[END] = {0};
	bool movleft = false;
	bool movupdown = false;

	int udstat = CTSTAT::Inc;

	double f;
	double y;
	double h = 50;
	double xpos = 0;
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
	LRESULT WindowMenu(HWND, UINT, WPARAM, LPARAM);
	BOOL WindowDialogProc(HWND, UINT, WPARAM, LPARAM);

	CFrameWork();
	~CFrameWork();
};
