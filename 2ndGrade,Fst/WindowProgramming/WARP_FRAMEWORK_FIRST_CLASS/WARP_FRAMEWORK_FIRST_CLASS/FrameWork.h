#pragma once
class CFrameWork
{
private:
	HWND m_hwnd; // ������ �ڵ�
	RECT m_rect; // rect ����ü
	HBRUSH hbrBackground = NULL; // ���귯���ڵ�
	POINT ptmouse; // ���콺 ��ġ
	wchar_t order[TEMP_ARR_SIZE] = { 0 }; // ��ɾ �޴� �迭
	wchar_t timer[TEMP_ARR_SIZE] = {0};
	int count; // ��ɾ� �Է¿� ����
	int time; // �ð��� �ö󰣴�
public:
	bool Initial(HWND, RECT);
	void Destroy(); // posquit,destroywindow(hWnd)������ �ȵ�
	void OnCreate();
	void OnDraw(HDC);
	void OnTimer(UINT); // ������Ʈ
	void InputMouse(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�
	void InputKeyBoard(UINT, WPARAM, LPARAM); //�޼���,w�Ķ�,l�Ķ�

	void CreateBkBrush(COLORREF);
	void ClearScreen(HDC);
	LRESULT WindowMessage(HWND, UINT, WPARAM, LPARAM );//�޼���,w�Ķ�,l�Ķ�
	CFrameWork();
	~CFrameWork();
};
