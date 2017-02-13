// ������ MDI ����
#include <windows.h>
#include "resource.h"

// �Լ� ���� �� ���� ����
LRESULT CALLBACK MDIWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MDIChildProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;					// �ν��Ͻ� �ڵ�
HWND g_hFrameWnd;					// ���� ������ ������ �ڵ�
HWND g_hMDIClient;					// Ŭ���̾�Ʈ ������ �ڵ�
#define NUMBER_OF_LINE 10
#define NUMBER_OF_CHAR_ONE_LINE 99
#define NUMBER_OF_WIND 100

typedef struct {
	wchar_t string[NUMBER_OF_LINE][NUMBER_OF_CHAR_ONE_LINE] = { 0 };
	int count, yPos;
	int home_input;
	bool flag;
	RECT rectView;
	SIZE size;
}Data;

LPCTSTR lpszClass = L"WindowFrame";	// ���� �������� ������ Ŭ����
LPCTSTR C_lpszClass = L"Note";	// ���� �������� ������ Ŭ����
int ChildNum = 0;

Data data[NUMBER_OF_WIND];
HWND hwndChild[NUMBER_OF_WIND];


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	// MDI Frame ������ Ŭ���� ���
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = MDIWndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = 0;
	RegisterClass(&WndClass);

	// MDI Frame ������ ����
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	g_hFrameWnd = hWnd;

	// MDI Child ������ Ŭ���� ���
	WndClass.lpszClassName = C_lpszClass;
	WndClass.lpfnWndProc = MDIChildProc;
	WndClass.hIcon = LoadIcon(NULL, IDI_ASTERISK);
	WndClass.lpszMenuName = NULL;
	WndClass.cbWndExtra = sizeof(DWORD);			// ������ �޸�
	RegisterClass(&WndClass);

	// MDI�� �޽��� ����
	while (GetMessage(&Message, NULL, 0, 0)) {
		if (!TranslateMDISysAccel(g_hMDIClient, &Message)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;
}

// ������ �������� �޽��� ���ν���
LRESULT CALLBACK MDIWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	CLIENTCREATESTRUCT ccs;
	MDICREATESTRUCT mcs;
	switch (iMessage) {
	case WM_CREATE:
		// MDI Client ������ ����
		ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 1);
		ccs.idFirstChild = ID_FIRSTCHILD;
		g_hMDIClient = CreateWindow(L"MDICLIENT", NULL, WS_CHILD | WS_VSCROLL |
			WS_HSCROLL | WS_CLIPCHILDREN,
			0, 0, 0, 0, hWnd, (HMENU)NULL, g_hInst, (LPSTR)&ccs);
		ShowWindow(g_hMDIClient, SW_SHOW);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			// ���ο� ���ϵ� �����츦 �����.
		case ID_NEW:
			mcs.szClass = C_lpszClass;
			mcs.szTitle = L"Child";
			mcs.hOwner = g_hInst;
			mcs.x = mcs.y = CW_USEDEFAULT;
			mcs.cx = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;
			hwndChild[ChildNum] = (HWND)SendMessage(g_hMDIClient, WM_MDICREATE,
				0, (LPARAM)(LPMDICREATESTRUCT)&mcs);
			ChildNum++;
			break;
		}
		break;		// ���⼭ "return 0"�ϸ� �ȵȴ�. �ݵ�� break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefFrameProc(hWnd, g_hMDIClient, iMessage, wParam, lParam));
}

// ���ϵ� �������� �޽��� ���ν���
LRESULT CALLBACK MDIChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	TCHAR str[128];
	wchar_t temp_array[NUMBER_OF_CHAR_ONE_LINE] = { 0 };
	POINT mousept;
	int i, j;
	int ID;
	switch (iMessage) {
	case WM_CREATE:
		wsprintf(str, TEXT("Child %d"), ChildNum);
		
		ID = ChildNum;
		SetWindowLong(hWnd, 0, ID);
		data[ID].count = 0; // ī��Ʈ 0���� �ʱ�ȭ
		data[ID].yPos = 0;
		data[ID].home_input = 0;
		data[ID].flag = false;
		GetClientRect(hWnd, &data[ID].rectView);
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd); // �� ȭ�鿡 ĳ�� ǥ��
		
		SetWindowText(hWnd, str);
		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� �߻���Ų��
		break;
	case WM_CHAR:
		ID = GetWindowLong(hWnd, 0);
		if (data[ID].flag) {
			data[ID].home_input = 0;
			if (wParam == VK_BACK) { // �齺���̽� Ű ���������
				if (data[ID].count == 0) {
					if (0 < data[ID].yPos) {
						--data[ID].yPos;
						data[ID].count = NUMBER_OF_CHAR_ONE_LINE + 1;
						while (data[ID].string[data[ID].yPos][data[ID].count] == '\0') { data[ID].count--; }; // ������ ���������� ã�Ƽ� ���ڸ��� ����.
					}
				}
				else
					data[ID].count--;
				data[ID].string[data[ID].yPos][data[ID].count] = '\0';

			}

			else if (wParam == VK_RETURN) // ���� ��������
			{
				if (data[ID].yPos < NUMBER_OF_LINE - 1) {
					data[ID].string[data[ID].yPos][data[ID].count++] = ' ';
					data[ID].string[data[ID].yPos][data[ID].count] = '\0';
					data[ID].yPos++;
					data[ID].count = 0;
				}
			}
			else if (wParam == VK_ESCAPE) { // esc ��������
				data[ID].yPos = 0;
				data[ID].count = 0;
				for (i = 0; i < NUMBER_OF_LINE; ++i) {
					for (j = 0; j < NUMBER_OF_CHAR_ONE_LINE; ++j) {
						data[ID].string[i][j] = '\0'; //NULL�� �ʱ�ȭ
					}
				}
			}
			else if (wParam == VK_TAB) {
				for (i = 0; i < 4; ++i) {
					if (data[ID].count == NUMBER_OF_CHAR_ONE_LINE - 1) {
						if (!(data[ID].yPos == NUMBER_OF_LINE - 1))
							data[ID].yPos++;
						data[ID].count = 0;
					}
					if (data[ID].yPos <= NUMBER_OF_LINE - 1) {
						data[ID].string[data[ID].yPos][data[ID].count++] = ' ';
						data[ID].string[data[ID].yPos][data[ID].count] = '\0';
					}
				}
			}
			else {
				if (data[ID].count == NUMBER_OF_CHAR_ONE_LINE - 1) {
					if (!(data[ID].yPos == NUMBER_OF_LINE - 1))
						data[ID].yPos++;
					data[ID].count = 0;
				}
				if (data[ID].yPos <= NUMBER_OF_LINE - 1) {
					data[ID].string[data[ID].yPos][data[ID].count++] = wParam;
					data[ID].string[data[ID].yPos][data[ID].count] = '\0';
				}
			}
		}
		


		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� �߻���Ų��
		break;
	case WM_KEYDOWN:
		ID = GetWindowLong(hWnd, 0);
		if (data[ID].flag) {
			data[ID].home_input = 0;
			if (wParam == VK_HOME) { // delete Ű ��������
				data[ID].count = 0;
				data[ID].home_input = 1;
			}
		}
			InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� 
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��, ȭ���� �������� OS���� �޼��� ���� (ó�� ����, �ٸ� ������ �������ִٰ� �ٽ� ���� ��, â ũ�� �ٲ�InvalidateRect(), InvalidateRgn()�Լ��� ȣ���Ͽ� ������ ȭ���� ��ȿȭ��ų ��)
		hDC = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
		ID = GetWindowLong(hWnd, 0);
		SetTextColor(hDC, RGB(0, 0, 240));
		//temp_array[NUMBER_OF_CHAR_ONE_LINE] = { 0 };
		for (j = 0; data[ID].string[data[ID].yPos][j] != '\0'; ++j) {
			temp_array[j] = data[ID].string[data[ID].yPos][j];
		}

		for (i = 0; i < NUMBER_OF_LINE; ++i) {
			if (data[ID].string[i] == '\0')
				break;
			GetTextExtentPoint(hDC, temp_array, wcslen(temp_array), &data[ID].size); // �ڵ�, ������ ����, ���°���� �����Ұ���, ����ü�� ����
			TextOut(hDC, 0, 20 * i, data[ID].string[i], wcslen(data[ID].string[i]));
			if (data[ID].home_input > 0) {
				SetCaretPos(0, (data[ID].yPos) * 20);
			}
			else
				SetCaretPos(data[ID].size.cx, (data[ID].yPos) * 20);
		}
		// strlen(temp) �� ��Ƽ����Ʈ������ �����Ѵ�
		// �����ڵ忡�� �����ִ� �Լ��� wcslen �� �ִ�!!!
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		mousept.x = LOWORD(lParam);
		mousept.y = HIWORD(lParam);
		/*
		if (PtInRect(&data[ID].rectView, mousept)) {
			data[ID].flag = true;
		}
		else {
			data[ID].flag = false;
		}
		*/
		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� �߻���Ų��
		break;
	case WM_ACTIVATE:
		ID = GetWindowLong(hWnd, 0);
		if (LOWORD(wParam) == WA_INACTIVE) {
			data[ID].flag = false;
		}
		else {
			data[ID].flag = true;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_SETFOCUS:
		ID = GetWindowLong(hWnd, 0);
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd); // �� ȭ�鿡 ĳ�� ǥ��
		data[ID].flag = true;
		break;
	case WM_KILLFOCUS:
		ID = GetWindowLong(hWnd, 0);
		data[ID].flag = false;
		break;
	case WM_SIZE:
		ID = GetWindowLong(hWnd, 0);
		GetClientRect(hWnd, &data[ID].rectView);
		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� 
		break;
	case WM_DESTROY:
		ID = GetWindowLong(hWnd, 0);
		SendMessage(g_hMDIClient, WM_MDIDESTROY,
			(WPARAM)hwndChild[ID], 0);
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefMDIChildProc(hWnd, iMessage, wParam, lParam));
}