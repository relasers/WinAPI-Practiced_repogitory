#pragma once
class CFrameWork
{
private:
	HWND m_hwnd; // 윈도우 핸들
	RECT m_rect; // rect 구조체
	HINSTANCE m_hInst;

	PAINTSTRUCT ps;
	HDC hdc, MemDC; // 항상 첫번째 인자는 hDC 다! , 두번째껀 비트맵용

	HBRUSH hbrBackground = NULL; // 배경브러쉬핸들
	HWND hDlg = NULL;

	//wchar_t result[TEMP_ARR_SIZE];
	//wchar_t temp_dig[2]; // 숫자
	//wchar_t temp_san[2]; // 연산자
	//wchar_t temp[TEMP_ARR_SIZE]; //itoa함수의 사용
	
	double Result = 0;
	double Operand = 0;
	double nMS = 0;
	int  Operator = 0;
	TCHAR Buffer[128];
	TCHAR Temp[128];
	TCHAR Show[128];
	wchar_t temp;
	float x = 0;
	float max;

	float tep = 0;
	bool bin = false;
	bool afterresult = false;
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
	
	void Display(double nResult);
	void Operation();
	void Equal();

	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM );//메세지,w파람,l파람
	LRESULT WindowMenu(HWND, UINT, WPARAM, LPARAM);
	BOOL WindowDialogProc(HWND, UINT, WPARAM, LPARAM);

	CFrameWork();
	~CFrameWork();
};
