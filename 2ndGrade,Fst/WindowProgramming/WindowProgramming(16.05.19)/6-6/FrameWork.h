
#pragma once
class CFrameWork
{
private:
	HWND m_hwnd; // ������ �ڵ�
	RECT m_rect; // rect ����ü
	HINSTANCE m_hInst;

	PAINTSTRUCT ps;
	HDC hdc, MemDC; // �׻� ù��° ���ڴ� hDC ��! , �ι�°�� ��Ʈ�ʿ�
	HWND hDlg;
	HWND hButton;
	int id;

	TCHAR str[30];
	POINT mapsize;
	POINT tilenum;
	POINT ptmouse;
	CTile tile[30][30];

	HBITMAP bitmap1;
	HBITMAP bitmap2;
	HBITMAP bitmap3;
	HBITMAP bitmap4;
	HBITMAP bitmap5;
	HBITMAP bitmap6;

	HBRUSH hbrBackground = NULL; // ���귯���ڵ�
	
	bool drag = false;
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
