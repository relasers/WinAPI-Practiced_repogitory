#pragma once
class CFrameWork
{
private:
	HWND m_hwnd; // ������ �ڵ�
	RECT m_rect; // rect ����ü
	HINSTANCE m_hInst;

	PAINTSTRUCT ps;
	HDC hdc, MemDC; // �׻� ù��° ���ڴ� hDC ��! , �ι�°�� ��Ʈ�ʿ�

	HBRUSH hbrBackground = NULL; // ���귯���ڵ�
	HWND hDlg = NULL;

	//wchar_t result[TEMP_ARR_SIZE];
	//wchar_t temp_dig[2]; // ����
	//wchar_t temp_san[2]; // ������
	//wchar_t temp[TEMP_ARR_SIZE]; //itoa�Լ��� ���
	
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
	void Destroy(); // posquit,destroywindow(hWnd)������ �ȵ�
	void OnCreate();
	void OnDraw(HDC);
	void OnTimer(UINT); // ������Ʈ
	void InputMouse(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�
	void InputKeyBoard(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�

	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);
	
	void Display(double nResult);
	void Operation();
	void Equal();

	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM );//�޼���,w�Ķ�,l�Ķ�
	LRESULT WindowMenu(HWND, UINT, WPARAM, LPARAM);
	BOOL WindowDialogProc(HWND, UINT, WPARAM, LPARAM);

	CFrameWork();
	~CFrameWork();
};
