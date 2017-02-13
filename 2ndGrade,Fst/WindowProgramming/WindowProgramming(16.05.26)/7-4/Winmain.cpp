#include <windows.h>
#include <TCHAR.H>
#include <math.h>
#include <time.h>
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildBallProc(HWND hDlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"WindowFrame";	// 메인 윈도우의 윈도우 클래스
LPCTSTR CB_lpszClass = L"Ball";	// 메인 윈도우의 윈도우 클래스

#define IDC_BUTTON_EXIT 1000
#define IDC_BUTTON_DIR 1001
#define ID_SCR1 1002
#define ID_SCR2 1003
#define ID_RAD1 1004
#define ID_RAD2 1005
#define ID_RAD3 1006

#define NUMBER_OF_WIND 100
#define PI 3.141592
#define BALL_SIZE 30

int ChildNum = 0;
int size = 0;
HWND ChildHwnd[NUMBER_OF_WIND];
HWND hButton_Exit;
HWND hButton_Dir;
HWND hScroll_spd1;
HWND hScroll_spd2;
HWND hRadio1;
HWND hRadio2;
HWND hRadio3;
RECT circ_big;
RECT circ_mid;

typedef struct BALL{
	RECT pos;
	bool ismove = false;
	double speed = 1;
	int degree = 0;
	int direction = 1;
}BALL;

BALL ball_1;
BALL ball_2;

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
	WndClass.cbWndExtra = sizeof(int);			// 여분의 메모리
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


		ball_1.speed = rand()%10;
		ball_2.speed = rand() % 10;
		ChildHwnd[ChildNum] = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			CB_lpszClass,
			NULL,
			WS_CHILD | WS_VISIBLE,
			0,
			0,
			RectView.right / 2 - 1,
			RectView.bottom,
			hwnd,
			NULL,
			g_hInst,
			NULL
		);
		hButton_Dir = CreateWindow(L"button", L"나가",
			// 버튺의 윈도우 클래스 이름은 “button”
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			// 차일드 윈도우이고 누르는 형태의 버튺 스타일
			600, 500, 70, 25, hwnd,
			(HMENU)IDC_BUTTON_EXIT, g_hInst, NULL);
		hButton_Dir = CreateWindow(L"button", L"방향반대로",
			// 버튺의 윈도우 클래스 이름은 “button”
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			// 차일드 윈도우이고 누르는 형태의 버튺 스타일
			700, 500, 70, 25, hwnd,
			(HMENU)IDC_BUTTON_DIR, g_hInst, NULL);

		hScroll_spd1 = CreateWindow(L"scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			600, 10, 200, 20, hwnd, (HMENU)ID_SCR1, g_hInst, NULL);
		hScroll_spd2 = CreateWindow(L"scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			600, 30, 200, 20, hwnd, (HMENU)ID_SCR2, g_hInst, NULL);

		SetScrollRange(hScroll_spd1, SB_CTL, 0, 15, TRUE);
		SetScrollPos(hScroll_spd1, SB_CTL, ball_1.speed, TRUE);

		SetScrollRange(hScroll_spd2, SB_CTL, 0, 15, TRUE);
		SetScrollPos(hScroll_spd2, SB_CTL, ball_2.speed, TRUE);

		//CreateWindow(L"button", L"Size", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 600, 50, 300, 50, hwnd, (HMENU)0, g_hInst, NULL);

		hRadio1 = CreateWindow(L"button", L"Big",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			600, 50, 100, 30, hwnd, (HMENU)ID_RAD1, g_hInst, NULL);
		hRadio2 = CreateWindow(L"button", L"Mid",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			600, 80, 100, 30, hwnd, (HMENU)ID_RAD2, g_hInst, NULL);
		hRadio3 = CreateWindow(L"button", L"Smll",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			600, 110, 100, 30, hwnd, (HMENU)ID_RAD3, g_hInst, NULL);
		CheckRadioButton(hwnd, ID_RAD1, ID_RAD3, ID_RAD1);



		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)

		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc); // hdc와 호환시킨다.
		HBITMAP Lay; // 레이어 생성
		Lay = CreateCompatibleBitmap(hdc, RectView.right, RectView.bottom); // 다블 버퍼링 ,hdc와 호환시키자.
		static HBRUSH oldbrush;
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &RectView, hbrBackground);
			SetBkMode(LayDC, TRANSPARENT);
			//////<여기다 그린다>//////////////////////////////////////////////////////////////////
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
	case WM_HSCROLL: 
	{
		double TempPos;

		if ((HWND)lParam == hScroll_spd1) TempPos = ball_1.speed;
		if ((HWND)lParam == hScroll_spd2) TempPos = ball_2.speed;

		switch (LOWORD(wParam)) {
		case SB_LINELEFT: TempPos = max(0, TempPos - 1); break;
		case SB_LINERIGHT: TempPos = min(15, TempPos + 1); break;
		case SB_PAGELEFT: TempPos = max(0, TempPos - 1); break;
		case SB_PAGERIGHT: TempPos = min(15, TempPos + 1); break;
		case SB_THUMBTRACK: TempPos = HIWORD(wParam); break;
		}
	
		if ((HWND)lParam == hScroll_spd1) ball_1.speed = TempPos;
		if ((HWND)lParam == hScroll_spd2) ball_2.speed = TempPos;

		SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
		
	}
			



	InvalidateRect(hwnd, NULL, FALSE);
			break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_DIR:
			ball_1.direction *= -1;
			ball_2.direction *= -1;
			return 0;
		case IDC_BUTTON_EXIT:
			PostQuitMessage(0);
			return 0;
		case ID_RAD1:
			size = 0;
			return 0;
		case ID_RAD2:
			size = 1;
			return 0;
		case ID_RAD3:
			size = 2;
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
	static HBRUSH hbrBackground = NULL; // 배경브러쉬핸들
	static RECT RectView;
	static HBRUSH transbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	static HBRUSH oldbrush;

	int ID;

	
	switch (iMessage) {
	case WM_CREATE:
		ID = ChildNum;
		SetWindowLong(hWnd, 0, ID);
		GetClientRect(hWnd, &RectView);

		circ_big = { RectView.right / 5, RectView.bottom / 5,
			RectView.right - RectView.right / 5 ,RectView.bottom - RectView.bottom / 5 };
		circ_mid = { RectView.right / 3, RectView.bottom / 3,
			RectView.right - RectView.right/3 ,RectView.bottom - RectView.bottom/3 };

		//if (hbrBackground) DeleteObject(hbrBackground);
		hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

		{
			POINT Centerpt;
			
			Centerpt.x = (circ_big.right - circ_big.left)/2*sin(PI*ball_1.degree/180.0) + RectView.right/2;
			Centerpt.y = (circ_big.bottom - circ_big.top)/2*cos(PI*ball_1.degree / 180.0) + RectView.bottom / 2;
			ball_1.pos = { Centerpt.x - BALL_SIZE,
				Centerpt.y - BALL_SIZE,
				Centerpt.x + BALL_SIZE,
				Centerpt.y + BALL_SIZE,
			};

			Centerpt.x = (circ_mid.right - circ_mid.left)/2*sin(PI*ball_2.degree / 180.0) + RectView.right / 2;
			Centerpt.y = (circ_mid.bottom - circ_mid.top)/2*cos(PI*ball_2.degree / 180.0) + RectView.bottom / 2;
			ball_2.pos = { Centerpt.x - BALL_SIZE,
				Centerpt.y - BALL_SIZE,
				Centerpt.x + BALL_SIZE,
				Centerpt.y + BALL_SIZE,
			};


		}
		

		SetTimer(hWnd, 1, 10, NULL);
		InvalidateRect(hWnd, NULL, false); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_KEYDOWN:
		break;
	case WM_TIMER:

	{

		if (ball_2.direction == 1) {
			for (int i = 0; i<ball_2.speed; ++i) (--ball_2.degree) %= 360;
		}
		else
			for (int i = 0; i<ball_2.speed; ++i) (++ball_2.degree) %= 360;

		if (ball_1.direction == 1) {
			for (int i = 0; i<ball_1.speed; ++i) (--ball_1.degree) %= 360;
		}
		else {
			for (int i = 0; i<ball_1.speed; ++i) (++ball_1.degree) %= 360;
		}

		POINT Centerpt;

		Centerpt.x = (circ_big.right - circ_big.left)/2*sin(PI*ball_1.degree / 180.0) + RectView.right / 2;
		Centerpt.y = (circ_big.bottom - circ_big.top)/2*cos(PI*ball_1.degree / 180.0) + RectView.bottom / 2;
		ball_1.pos = { Centerpt.x - BALL_SIZE,
			Centerpt.y - BALL_SIZE,
			Centerpt.x + BALL_SIZE,
			Centerpt.y + BALL_SIZE,
		};

		Centerpt.x = (circ_mid.right - circ_mid.left)/2*sin(PI*ball_2.degree / 180.0) + RectView.right / 2;
		Centerpt.y = (circ_mid.bottom - circ_mid.top)/2*cos(PI*ball_2.degree / 180.0) + RectView.bottom / 2;
		ball_2.pos = { Centerpt.x - BALL_SIZE,
			Centerpt.y - BALL_SIZE,
			Centerpt.x + BALL_SIZE,
			Centerpt.y + BALL_SIZE,
		};
	}





		InvalidateRect(hWnd, NULL, false); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때, 화면이 깨졌을때 OS에서 메세지 전송 (처음 생성, 다른 윈도우 가려져있다가 다시 보일 때, 창 크기 바뀔때InvalidateRect(), InvalidateRgn()함수를 호출하여 강제로 화면을 무효화시킬 때)
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)

		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc); // hdc와 호환시킨다.
		HBITMAP Lay; // 레이어 생성
		Lay = CreateCompatibleBitmap(hdc, RectView.right, RectView.bottom); // 다블 버퍼링 ,hdc와 호환시키자.
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &RectView, hbrBackground);
			SetBkMode(LayDC, TRANSPARENT);
			//////<여기다 그린다>//////////////////////////////////////////////////////////////////
			oldbrush = (HBRUSH)SelectObject(LayDC,transbrush);
			
			MoveToEx(LayDC, 0, RectView.bottom/2, NULL);
			LineTo(LayDC, RectView.right, RectView.bottom / 2);

			MoveToEx(LayDC, RectView.right / 2, 0, NULL);
			LineTo(LayDC, RectView.right / 2, RectView.bottom);

			Ellipse(LayDC, circ_big.left,
				circ_big.top,
				circ_big.right,
				circ_big.bottom
			);


			Ellipse(LayDC, circ_mid.left,
				circ_mid.top,
				circ_mid.right,
				circ_mid.bottom
			);


			switch (size) {
			case 0:
				Ellipse(LayDC, ball_1.pos.left,
					ball_1.pos.top,
					ball_1.pos.right,
					ball_1.pos.bottom
				);

				Ellipse(LayDC, ball_2.pos.left,
					ball_2.pos.top,
					ball_2.pos.right,
					ball_2.pos.bottom
				);
				break;
			case 1:
				Ellipse(LayDC, ball_1.pos.left + 10,
					ball_1.pos.top + 10,
					ball_1.pos.right - 10,
					ball_1.pos.bottom - 10
				);

				Ellipse(LayDC, ball_2.pos.left + 10,
					ball_2.pos.top + 10,
					ball_2.pos.right - 10,
					ball_2.pos.bottom - 10
				);
				break;

			case 2:
				Ellipse(LayDC, ball_1.pos.left + 20,
					ball_1.pos.top + 20,
					ball_1.pos.right - 20,
					ball_1.pos.bottom - 20
				);

				Ellipse(LayDC, ball_2.pos.left + 20,
					ball_2.pos.top + 20,
					ball_2.pos.right - 20,
					ball_2.pos.bottom - 20
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