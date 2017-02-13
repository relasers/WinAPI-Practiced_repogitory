#include <windows.h>
#include <TCHAR.H>
#include <math.h>
#include <time.h>
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildBallProc(HWND hDlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"WindowFrame";	// ���� �������� ������ Ŭ����
LPCTSTR CB_lpszClass = L"Ball";	// ���� �������� ������ Ŭ����

#define IDC_BUTTON_EXIT 1000
#define IDC_BUTTON_1XDIR 1001
#define IDC_BUTTON_1YDIR 1002
#define IDC_BUTTON_1JMP 1003
#define IDC_BUTTON_2XDIR 1004
#define IDC_BUTTON_2YDIR 1005
#define IDC_BUTTON_2JMP 1006
#define IDC_BUTTON_STOP 1007
#define IDC_BUTTON_CHNGE 1008

#define NUMBER_OF_WIND 100
#define PI 3.141592
#define BALL_SIZE 30
#define MX_JMP 30
int ChildNum = 0;
int size = 0;
HWND ChildHwnd[NUMBER_OF_WIND];

HWND hButton[9];

typedef struct BALL {
	RECT pos;
	double speed = 5;
	bool x_ismove = false;
	bool y_ismove = false;
	int shapetype = 0;
	int x_direction = 1;
	int y_direction = 1;
	int jmp_guage=0;
}BALL;

BALL ball[2];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
	HWND 	 hwnd;
	MSG 	 msg;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = FrameWndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildBallProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = CB_lpszClass;
	WndClass.cbWndExtra = sizeof(int);			// ������ �޸�
	RegisterClass(&WndClass);


	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Main Window Title"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam)
{
	static RECT RectView;
	static HBRUSH hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	static HBRUSH transbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	srand((unsigned)time(NULL));
	HDC hdc;
	PAINTSTRUCT ps;
	RECT drawText;
	switch (iMsg)
	{
	case WM_CREATE:

		GetClientRect(hwnd, &RectView);

		ChildHwnd[ChildNum] = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			CB_lpszClass,
			NULL,
			WS_CHILD | WS_VISIBLE,
			0,
			0,
			RectView.right / 2 - 1,
			RectView.bottom /2 - 1,
			hwnd,
			NULL,
			g_hInst,
			NULL
		);
		ChildNum++;
		ChildHwnd[ChildNum] = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			CB_lpszClass,
			NULL,
			WS_CHILD | WS_VISIBLE,
			RectView.right / 2 - 1,
			0,
			RectView.right,
			RectView.bottom / 2 - 1,
			hwnd,
			NULL,
			g_hInst,
			NULL
		);

		hButton[0] = CreateWindow(L"button", L"�����¿�",
			// ���j�� ������ Ŭ���� �̸��� ��button��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
			0, 500, 70, 25, hwnd,
			(HMENU)IDC_BUTTON_1XDIR, g_hInst, NULL);

		hButton[1] = CreateWindow(L"button", L"���ʻ���",
			// ���j�� ������ Ŭ���� �̸��� ��button��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
			100, 500, 70, 25, hwnd,
			(HMENU)IDC_BUTTON_1YDIR, g_hInst, NULL);

		hButton[2] = CreateWindow(L"button", L"����«��",
			// ���j�� ������ Ŭ���� �̸��� ��button��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
			200, 500, 70, 25, hwnd,
			(HMENU)IDC_BUTTON_1JMP, g_hInst, NULL);

		hButton[3] = CreateWindow(L"button", L"�������¿�",
			// ���j�� ������ Ŭ���� �̸��� ��button��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
			300, 500, 70, 25, hwnd,
			(HMENU)IDC_BUTTON_2XDIR, g_hInst, NULL);

		hButton[4] = CreateWindow(L"button", L"�����ʻ���",
			// ���j�� ������ Ŭ���� �̸��� ��button��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
			400, 500, 70, 25, hwnd,
			(HMENU)IDC_BUTTON_2YDIR, g_hInst, NULL);

		hButton[5] = CreateWindow(L"button", L"������«��",
			// ���j�� ������ Ŭ���� �̸��� ��button��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
			500, 500, 70, 25, hwnd,
			(HMENU)IDC_BUTTON_2JMP, g_hInst, NULL);

		hButton[6] = CreateWindow(L"button", L"����",
			// ���j�� ������ Ŭ���� �̸��� ��button��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
			600, 500, 70, 25, hwnd,
			(HMENU)IDC_BUTTON_STOP, g_hInst, NULL);

		hButton[7] = CreateWindow(L"button", L"�ٲ�",
			// ���j�� ������ Ŭ���� �̸��� ��button��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
			700, 500, 70, 25, hwnd,
			(HMENU)IDC_BUTTON_CHNGE, g_hInst, NULL);

		hButton[8] = CreateWindow(L"button", L"����",
			// ���j�� ������ Ŭ���� �̸��� ��button��
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
			800, 500, 70, 25, hwnd,
			(HMENU)IDC_BUTTON_EXIT, g_hInst, NULL);

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)

		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc); // hdc�� ȣȯ��Ų��.
		HBITMAP Lay; // ���̾� ����
		Lay = CreateCompatibleBitmap(hdc, RectView.right, RectView.bottom); // �ٺ� ���۸� ,hdc�� ȣȯ��Ű��.
		static HBRUSH oldbrush;
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &RectView, hbrBackground);
			SetBkMode(LayDC, TRANSPARENT);
			//////<����� �׸���>//////////////////////////////////////////////////////////////////
			oldbrush = (HBRUSH)SelectObject(LayDC, transbrush);
			//////////////////////////////////////////////////////////////////////
			BitBlt(hdc, 0, 0, RectView.right, RectView.bottom, LayDC, 0, 0, SRCCOPY);
		}


		DeleteObject(Lay);
		DeleteObject(hdc);

		DeleteDC(LayDC);
		DeleteDC(hdc);

		EndPaint(hwnd, &ps);


		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_1XDIR:
			if (ball[0].x_ismove) {
				ball[0].x_ismove = false;
				return 0;
			}
			if (!ball[0].x_ismove) {
				ball[0].x_ismove = true;
				return 0;
			}
			
			return 0;
		case IDC_BUTTON_1YDIR:
			if (ball[0].y_ismove) {
				ball[0].y_ismove = false;
				return 0;
			}
			if (!ball[0].y_ismove) {
				ball[0].y_ismove = true;
				return 0;
			}
			return 0;
		case IDC_BUTTON_1JMP:
			ball[0].jmp_guage = MX_JMP;
			return 0;
		case IDC_BUTTON_2XDIR:
			if (ball[1].x_ismove) {
				ball[1].x_ismove = false;
				return 0;
			}
			if (!ball[1].x_ismove) {
				ball[1].x_ismove = true;
				return 0;
			}
			return 0;
		case IDC_BUTTON_2YDIR:
			if (ball[1].y_ismove) {
				ball[1].y_ismove = false;
				return 0;
			}
			if (!ball[1].y_ismove) {
				ball[1].y_ismove = true;
				return 0;
			}
			return 0;
		case IDC_BUTTON_2JMP:
			ball[1].jmp_guage = MX_JMP;
			return 0;
		case IDC_BUTTON_CHNGE:
			ball[0].shapetype = 1 - ball[0].shapetype;
			ball[1].shapetype = 1 - ball[1].shapetype;
			return 0;
		case IDC_BUTTON_STOP:
			ball[0].x_ismove = false;
			ball[0].y_ismove = false;
			ball[1].x_ismove = false;
			ball[1].y_ismove = false;
			return 0;
		case IDC_BUTTON_EXIT:
			PostQuitMessage(0);
			return 0;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

LRESULT CALLBACK ChildBallProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HBRUSH hbrBackground = NULL; // ���귯���ڵ�
	static RECT RectView;
	static HBRUSH transbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	static HBRUSH oldbrush;

	int ID;


	switch (iMessage) {
	case WM_CREATE:
		ID = ChildNum;
		SetWindowLong(hWnd, 0, ID);
		GetClientRect(hWnd, &RectView);

		

		//if (hbrBackground) DeleteObject(hbrBackground);
		hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

		{
			ball[ID].pos = {10,10,30,30};
			ball[ID].shapetype = ID;

		}
		SetTimer(hWnd, 1, 10, NULL);
		InvalidateRect(hWnd, NULL, false); // WM_PAINT �޼��� ���� �߻���Ų��
		break;
	case WM_KEYDOWN:
		break;
	case WM_TIMER:

	{
		ID = GetWindowLong(hWnd, 0);

		if(ball[ID].x_ismove)
		OffsetRect(&ball[ID].pos,5* ball[ID].x_direction,0);
		if (ball[ID].y_ismove)
		OffsetRect(&ball[ID].pos,0, 5 * ball[ID].y_direction);

		if (ball[ID].pos.left <= 0) {
			ball[ID].x_direction *= -1;
		}
		if (ball[ID].pos.top <= 0) {
			ball[ID].pos.top = 0;
			ball[ID].pos.bottom = 20;
			ball[ID].y_direction *= -1;
		}
		if (ball[ID].pos.right >= RectView.right/2) {
			ball[ID].x_direction *= -1;
		}
		if (ball[ID].pos.bottom >= RectView.bottom) {
			ball[ID].pos.top = RectView.bottom-20;
			ball[ID].pos.bottom = RectView.bottom;
			ball[ID].y_direction *= -1;
		}
		


		if (ball[ID].jmp_guage > 0)


			if (ball[ID].jmp_guage > MX_JMP / 2) {
				OffsetRect(&ball[ID].pos, 0, -10);
			}
			else {
				OffsetRect(&ball[ID].pos, 0, 10);
			}
			ball[ID].jmp_guage--;
	}


	InvalidateRect(hWnd, NULL, false); // WM_PAINT �޼��� ���� �߻���Ų��
	break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��, ȭ���� �������� OS���� �޼��� ���� (ó�� ����, �ٸ� ������ �������ִٰ� �ٽ� ���� ��, â ũ�� �ٲ�InvalidateRect(), InvalidateRgn()�Լ��� ȣ���Ͽ� ������ ȭ���� ��ȿȭ��ų ��)
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)

		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc); // hdc�� ȣȯ��Ų��.
		HBITMAP Lay; // ���̾� ����
		Lay = CreateCompatibleBitmap(hdc, RectView.right, RectView.bottom); // �ٺ� ���۸� ,hdc�� ȣȯ��Ű��.
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &RectView, hbrBackground);
			SetBkMode(LayDC, TRANSPARENT);
			//////<����� �׸���>//////////////////////////////////////////////////////////////////
			oldbrush = (HBRUSH)SelectObject(LayDC, transbrush);

			ID = GetWindowLong(hWnd, 0);

			switch (ball[ID].shapetype) {
			case 0:
				Ellipse(LayDC,
					ball[ID].pos.left,
					ball[ID].pos.top,
					ball[ID].pos.right,
					ball[ID].pos.bottom
				);
				break;

			case 1:
				Rectangle(LayDC,
					ball[ID].pos.left,
					ball[ID].pos.top,
					ball[ID].pos.right,
					ball[ID].pos.bottom
				);


				break;
			
			
			}
			
			
			//////////////////////////////////////////////////////////////////////
			BitBlt(hdc, 0, 0, RectView.right, RectView.bottom, LayDC, 0, 0, SRCCOPY);
		}


		DeleteObject(Lay);
		DeleteObject(hdc);

		DeleteDC(LayDC);
		DeleteDC(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		ID = GetWindowLong(hWnd, 0);
		if ((hWnd == ChildHwnd[ID])) {
			SetFocus(hWnd);
			//ismove = true;
		}
		return 0;
	case WM_LBUTTONUP:
		return 0;
	case WM_ACTIVATE:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_SETFOCUS:
		break;
	case WM_KILLFOCUS:
		break;
	case WM_SIZE:
		break;
	case WM_DESTROY:
		return 0;
	}
	return DefMDIChildProc(hWnd, iMessage, wParam, lParam);
}