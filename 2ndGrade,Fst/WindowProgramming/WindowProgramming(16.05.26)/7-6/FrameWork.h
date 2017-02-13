
#pragma once
class CFrameWork
{
private:
	HWND m_hwnd; // 윈도우 핸들
	HWND c_hwnd;
	RECT m_rect; // rect 구조체
	HINSTANCE m_hInst;

	PAINTSTRUCT ps;
	HDC hdc, MemDC; // 항상 첫번째 인자는 hDC 다! , 두번째껀 비트맵용
	//HWND hDlg;
	HWND hButton;
	HWND hList;

	HWND Button[8];
	HWND Edit[4];
	HWND Button_Mak;
	HWND Button_Fil;
	HWND Button_Ext;
	HWND TheList;

	TCHAR str[30];
	POINT mapsize;
	POINT tilenum;
	POINT ptmouse;
	CTiles tile[30][30];
	COBJ obj[30][30];
	CBackGround back;

	HBITMAP bitmap1;
	HBITMAP bitmap2;
	HBITMAP bitmap3;
	HBITMAP bitmap4;
	HBITMAP bitmap5;
	HBITMAP bitmap6;

	HBITMAP O_bitmap1;
	HBITMAP O_bitmap2;

	HBITMAP B_bitmap1;
	HBITMAP B_bitmap2;
	HBITMAP B_bitmap3;

	HBRUSH hbrBackground = NULL; // 배경브러쉬핸들

	bool drag = false;
	int id = 0;
	int mode = Mode::Objecting;
	int selection = 0;
	TCHAR temp[50];
public:
	bool Initial(HWND, RECT, HINSTANCE);
	void Destroy(); // posquit,destroywindow(hWnd)넣으면 안돼
	void OnCreate();
	void OnDraw(HDC);
	void OnTimer(UINT); // 업데이트
	void InputMouse(UINT, WPARAM, LPARAM); //메세지,w파람,l파람
	void InputKeyBoard(UINT, WPARAM, LPARAM); //메세지,w파람,l파람

	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);

	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM);//메세지,w파람,l파람
	LRESULT WindowMenu(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK ChildDrawProc(HWND hWnd, UINT iMessage,WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowDialogProc(HWND, UINT, WPARAM, LPARAM);

	CFrameWork();
	~CFrameWork();
};
