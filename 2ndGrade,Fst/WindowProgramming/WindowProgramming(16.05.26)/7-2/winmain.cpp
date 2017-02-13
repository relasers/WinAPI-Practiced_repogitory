#include <windows.h>
#include <TCHAR.H>
#include "resource.h"
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildTextProc(HWND hDlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildDrawProc(HWND hDlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildBallProc(HWND hDlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"WindowFrame";	// 메인 윈도우의 윈도우 클래스
LPCTSTR CT_lpszClass = L"Note";	// 메인 윈도우의 윈도우 클래스
LPCTSTR CD_lpszClass = L"Draw";	// 메인 윈도우의 윈도우 클래스
LPCTSTR CB_lpszClass = L"Ball";	// 메인 윈도우의 윈도우 클래스

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

int ChildNum = 0;
Data data[NUMBER_OF_WIND];
HWND ChildHwnd[NUMBER_OF_WIND];


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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildTextProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = CT_lpszClass;
	WndClass.cbWndExtra = sizeof(int);			// 여분의 메모리
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildDrawProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = CD_lpszClass;
	WndClass.cbWndExtra = sizeof(int);			// 여분의 메모리
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
	RECT RectView;

	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &RectView);


		ChildHwnd[ChildNum] = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			CT_lpszClass,
			NULL,
			WS_CHILD | WS_VISIBLE,
			0,
			0,
			RectView.right / 2 - 1,
			RectView.bottom / 2 - 1,
			hwnd,
			NULL,
			g_hInst,
			NULL
		);

		ChildNum++;


		ChildHwnd[ChildNum] = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			CT_lpszClass,
			NULL,
			WS_CHILD | WS_VISIBLE,
			RectView.right / 2,
			RectView.bottom / 2 + 1,
			RectView.right,
			RectView.bottom,
			hwnd,
			NULL,
			g_hInst,
			NULL
		);


		ChildNum++;


		ChildHwnd[ChildNum] = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			CD_lpszClass,
			NULL,
			WS_CHILD | WS_VISIBLE,
			RectView.right / 2,
			0,
			RectView.right,
			RectView.bottom / 2 - 1,
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
			0,
			RectView.bottom / 2 - 1,
			RectView.right /2 - 1,
			RectView.bottom,
			hwnd,
			NULL,
			g_hInst,
			NULL
		);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

LRESULT CALLBACK ChildTextProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
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
		data[ID].count = 0; // 카운트 0으로 초기화
		data[ID].yPos = 0;
		data[ID].home_input = 0;
		data[ID].flag = true;
		GetClientRect(hWnd, &data[ID].rectView);
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd); // 빈 화면에 캐럿 표시

		SetWindowText(hWnd, str);
		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_CHAR:
		ID = GetWindowLong(hWnd, 0);
		if (data[ID].flag) {
			data[ID].home_input = 0;
			if (wParam == VK_BACK) { // 백스페이스 키 눌렀을경우
				if (data[ID].count == 0) {
					if (0 < data[ID].yPos) {
						--data[ID].yPos;
						data[ID].count = NUMBER_OF_CHAR_ONE_LINE + 1;
						while (data[ID].string[data[ID].yPos][data[ID].count] == '\0') { data[ID].count--; }; // 위에줄 마지막까지 찾아서 그자리로 간다.
					}
				}
				else
					data[ID].count--;
				data[ID].string[data[ID].yPos][data[ID].count] = '\0';

			}

			else if (wParam == VK_RETURN) // 엔터 눌렸을때
			{
				if (data[ID].yPos < NUMBER_OF_LINE - 1) {
					data[ID].string[data[ID].yPos][data[ID].count++] = ' ';
					data[ID].string[data[ID].yPos][data[ID].count] = '\0';
					data[ID].yPos++;
					data[ID].count = 0;
				}
			}
			else if (wParam == VK_ESCAPE) { // esc 눌렀을때
				data[ID].yPos = 0;
				data[ID].count = 0;
				for (i = 0; i < NUMBER_OF_LINE; ++i) {
					for (j = 0; j < NUMBER_OF_CHAR_ONE_LINE; ++j) {
						data[ID].string[i][j] = '\0'; //NULL로 초기화
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
		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_KEYDOWN:
		ID = GetWindowLong(hWnd, 0);
		if (data[ID].flag) {
			data[ID].home_input = 0;
			if (wParam == VK_HOME) { // delete 키 눌렀을때
				data[ID].count = 0;
				data[ID].home_input = 1;
			}
		}
		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때, 화면이 깨졌을때 OS에서 메세지 전송 (처음 생성, 다른 윈도우 가려져있다가 다시 보일 때, 창 크기 바뀔때InvalidateRect(), InvalidateRgn()함수를 호출하여 강제로 화면을 무효화시킬 때)
		hDC = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
		ID = GetWindowLong(hWnd, 0);
		SetTextColor(hDC, RGB(0, 0, 240));
		//temp_array[NUMBER_OF_CHAR_ONE_LINE] = { 0 };
		for (j = 0; data[ID].string[data[ID].yPos][j] != '\0'; ++j) {
			temp_array[j] = data[ID].string[data[ID].yPos][j];
		}

		for (i = 0; i < NUMBER_OF_LINE; ++i) {
			if (data[ID].string[i] == '\0')
				break;
			GetTextExtentPoint(hDC, temp_array, wcslen(temp_array), &data[ID].size); // 핸들, 측정할 문자, 몇번째까지 측정할건지, 구조체에 저장
			TextOut(hDC, 0, 20 * i, data[ID].string[i], wcslen(data[ID].string[i]));
			if (data[ID].home_input > 0) {
				SetCaretPos(0, (data[ID].yPos) * 20);
			}
			else
				SetCaretPos(data[ID].size.cx, (data[ID].yPos) * 20);
		}
		// strlen(temp) 는 멀티바이트에서만 지원한다
		// 유니코드에서 쓸수있는 함수는 wcslen 이 있다!!!
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		ID = GetWindowLong(hWnd, 0);
		mousept.x = LOWORD(lParam);
		mousept.y = HIWORD(lParam);
		
		if ((hWnd == ChildHwnd[ID])) {
			SetFocus(hWnd);
			data[ID].flag = true;
			CreateCaret(hWnd, NULL, 5, 15);
			ShowCaret(hWnd); // 빈 화면에 캐럿 표시
		}
		else {
			data[ID].flag = false;
		}
		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_ACTIVATE:
		ID = GetWindowLong(hWnd, 0);
		/*
		if (LOWORD(wParam) == WA_INACTIVE) {
			data[ID].flag = false;
		}
		else {
			data[ID].flag = true;
		}
		*/
		
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_SETFOCUS:
		//ID = GetWindowLong(hWnd, 0);
		
		//data[ID].flag = true;
		break;
	case WM_KILLFOCUS:
		//ID = GetWindowLong(hWnd, 0);
		//data[ID].flag = false;
		break;
	case WM_SIZE:
		//ID = GetWindowLong(hWnd, 0);
		//GetClientRect(hWnd, &data[ID].rectView);
		//InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 
		break;
	case WM_DESTROY:
		ID = GetWindowLong(hWnd, 0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return DefMDIChildProc(hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK ChildDrawProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	int ID;
	static int x;
	static int y;
	static bool drag = false;
	switch (iMessage) {
	case WM_CREATE:
		ID = ChildNum;
		SetWindowLong(hWnd, 0, ID);
		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_KEYDOWN:
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때, 화면이 깨졌을때 OS에서 메세지 전송 (처음 생성, 다른 윈도우 가려져있다가 다시 보일 때, 창 크기 바뀔때InvalidateRect(), InvalidateRgn()함수를 호출하여 강제로 화면을 무효화시킬 때)
		break;
	case WM_LBUTTONDOWN:
		x=LOWORD(lParam);
		y=HIWORD(lParam);
		ID = GetWindowLong(hWnd, 0);
		if ((hWnd == ChildHwnd[ID])) {
			SetFocus(hWnd);
			drag = true;
		}
		return 0;
	case WM_MOUSEMOVE:
		if (drag) {
			hdc=GetDC(hWnd);
			MoveToEx(hdc,x,y,NULL);
			x=LOWORD(lParam);
			y=HIWORD(lParam);
			LineTo(hdc,x,y);
			ReleaseDC(hWnd,hdc);
		}
		return 0;
	case WM_LBUTTONUP:
		drag=false;
		return 0;
	case WM_ACTIVATE:
		/*
		if (LOWORD(wParam) == WA_INACTIVE) {
		data[ID].flag = false;
		}
		else {
		data[ID].flag = true;
		}
		*/
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_SETFOCUS:
		//ID = GetWindowLong(hWnd, 0);

		//data[ID].flag = true;
		break;
	case WM_KILLFOCUS:
		//ID = GetWindowLong(hWnd, 0);
		//data[ID].flag = false;
		break;
	case WM_SIZE:
		//ID = GetWindowLong(hWnd, 0);
		//GetClientRect(hWnd, &data[ID].rectView);
		//InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 
		break;
	case WM_DESTROY:
		return 0;
	} //처리할 메시지만 case문에 나열
	return DefMDIChildProc(hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK ChildBallProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HBRUSH hbrBackground = NULL; // 배경브러쉬핸들
	static RECT ReectView;
	int ID;

	static RECT pos = { 5,5,36,36 };
	static bool ismove = false;
	static int speed = 6;
	static int xvec = 1;
	static int yvec = 1;
	switch (iMessage) {
	case WM_CREATE:
		ID = ChildNum;
		SetWindowLong(hWnd, 0, ID);
		GetClientRect(hWnd,&ReectView);
		//if (hbrBackground) DeleteObject(hbrBackground);
		hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);


		SetTimer(hWnd,1,10,NULL);
		InvalidateRect(hWnd, NULL, false); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_KEYDOWN:
		break;
	case WM_TIMER:
		//GetClientRect(hWnd, &ReectView);
		if (ismove)
			OffsetRect(&pos, speed*xvec, speed*yvec);

		if (pos.left <= 0) {
			xvec *= -1;
		}
		if (pos.top <= 0) {
			yvec *= -1;
		}
		if (pos.right >= ReectView.right) {
			xvec *= -1;
		}
		if (pos.bottom >= ReectView.bottom/2) {
			yvec *= -1;
		}

		InvalidateRect(hWnd, NULL, false); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때, 화면이 깨졌을때 OS에서 메세지 전송 (처음 생성, 다른 윈도우 가려져있다가 다시 보일 때, 창 크기 바뀔때InvalidateRect(), InvalidateRgn()함수를 호출하여 강제로 화면을 무효화시킬 때)
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)

		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc); // hdc와 호환시킨다.
		HBITMAP Lay; // 레이어 생성
		Lay = CreateCompatibleBitmap(hdc, ReectView.right, ReectView.bottom); // 다블 버퍼링 ,hdc와 호환시키자.
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &ReectView, hbrBackground);
			SetBkMode(LayDC, TRANSPARENT);
			//////<여기다 그린다>//////////////////////////////////////////////////////////////////
				Ellipse(LayDC, pos.left,
					pos.top,
					pos.right,
					pos.bottom
				);

			//////////////////////////////////////////////////////////////////////
			BitBlt(hdc, 0, 0, ReectView.right, ReectView.bottom, LayDC, 0, 0, SRCCOPY);
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
			ismove = true;
		}
		return 0;
	case WM_LBUTTONUP:
		return 0;
	case WM_ACTIVATE:
		/*
		if (LOWORD(wParam) == WA_INACTIVE) {
		data[ID].flag = false;
		}
		else {
		data[ID].flag = true;
		}
		*/
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_SETFOCUS:
		//ID = GetWindowLong(hWnd, 0);

		//data[ID].flag = true;
		break;
	case WM_KILLFOCUS:
		//ID = GetWindowLong(hWnd, 0);
		//data[ID].flag = false;
		break;
	case WM_SIZE:
		//ID = GetWindowLong(hWnd, 0);
		//GetClientRect(hWnd, &data[ID].rectView);
		//InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 
		break;
	case WM_DESTROY:
		return 0;
	} //처리할 메시지만 case문에 나열
	return DefMDIChildProc(hWnd, iMessage, wParam, lParam);
}