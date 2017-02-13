#include <windows.h>
#include <TCHAR.H>
#include <atlimage.h>
#include "resource.h"
LRESULT CALLBACK FrameWndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildControlProc(HWND hDlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildViewerProc(HWND hDlg, UINT iMsg,
	WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"WindowFrame";	// 메인 윈도우의 윈도우 클래스
LPCTSTR CC_lpszClass = L"Control";	// 메인 윈도우의 윈도우 클래스
LPCTSTR CV_lpszClass = L"View";	// 메인 윈도우의 윈도우 클래스

#define NUMBER_OF_LINE 10
#define NUMBER_OF_CHAR_ONE_LINE 99
#define NUMBER_OF_WIND 2

#define CLIENT_WIDTH 800
#define CLIENT_HEIGHT 800

int ChildNum = 0;
bool isshow = false;
HWND ChildHwnd[NUMBER_OF_WIND];
CImage img;

POINT start;
POINT end;
RECT pos;
RECT ReectView[2];
RECT RectView;

typedef struct {


}POINTER;


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

	WndClass.lpfnWndProc = ChildControlProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = CC_lpszClass;
	WndClass.cbWndExtra = sizeof(int);			// 여분의 메모리
	RegisterClass(&WndClass);

	WndClass.lpfnWndProc = ChildViewerProc;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = CV_lpszClass;
	WndClass.cbWndExtra = sizeof(int);			// 여분의 메모리
	RegisterClass(&WndClass);

	hwnd = CreateWindow(_T("Window Class Name"),
		_T("Main Window Title"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CLIENT_WIDTH,
		CLIENT_HEIGHT,
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
	
	
	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &RectView);
		img.Load(TEXT("Image.PNG"));
		ChildHwnd[ChildNum] = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			CC_lpszClass,
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

		ChildNum++;


		ChildHwnd[ChildNum] = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			CV_lpszClass,
			NULL,
			WS_CHILD | WS_VISIBLE,
			RectView.right / 2,
			0,
			RectView.right,
			RectView.bottom,
			hwnd,
			NULL,
			g_hInst,
			NULL
		);


		ChildNum++;


		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

LRESULT CALLBACK ChildControlProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HBRUSH transbrush = (HBRUSH)GetStockObject(NULL_BRUSH), oldbrush;

	PAINTSTRUCT ps;
	static HBRUSH hbrBackground = NULL; // 배경브러쉬핸들
	POINT mousept;
	int ID;

	static bool drag = false;
	static bool isdraw = false;
	static int speed = 6;
	static int xvec = 1;
	static int yvec = 1;
	switch (iMessage) {
	case WM_CREATE:
		ID = ChildNum;
		SetWindowLong(hWnd, 0, ID);
		GetClientRect(hWnd, &ReectView[0]);
		//if (hbrBackground) DeleteObject(hbrBackground);
		hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);


		SetTimer(hWnd, 1, 10, NULL);
		InvalidateRect(hWnd, NULL, false); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_KEYDOWN:

		if (wParam == 'c' || wParam == 'C') {
			if (!isshow) {
				isshow = true;
				break;
			}
			if (isshow) {
				isshow = false;
				break;
			}
		}
		if (wParam == 'r' || wParam == 'R') {
			isdraw = false;
		}

		break;
	case WM_TIMER:
		//GetClientRect(hWnd, &ReectView);
		InvalidateRect(hWnd, NULL, false); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때, 화면이 깨졌을때 OS에서 메세지 전송 (처음 생성, 다른 윈도우 가려져있다가 다시 보일 때, 창 크기 바뀔때InvalidateRect(), InvalidateRgn()함수를 호출하여 강제로 화면을 무효화시킬 때)
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)

		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc); // hdc와 호환시킨다.
		HBITMAP Lay; // 레이어 생성
		Lay = CreateCompatibleBitmap(hdc, ReectView[0].right, ReectView[0].bottom); // 다블 버퍼링 ,hdc와 호환시키자.
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &ReectView[0], hbrBackground);
			SetBkMode(LayDC, TRANSPARENT);
			//////<여기다 그린다>//////////////////////////////////////////////////////////////////
			img.StretchBlt(LayDC,0,0,ReectView[0].right,ReectView[0].bottom,SRCCOPY);

			oldbrush = (HBRUSH)SelectObject(LayDC,transbrush);
			Rectangle(LayDC,pos.left,pos.top,pos.right,pos.bottom);
			SelectObject(LayDC,oldbrush);
			//////////////////////////////////////////////////////////////////////
			BitBlt(hdc, 0, 0, ReectView[0].right, ReectView[0].bottom, LayDC, 0, 0, SRCCOPY);
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
			drag = true;

			if (!isdraw) {
				start.x = end.x = LOWORD(lParam);
				start.y = end.y = HIWORD(lParam);
				pos.left = min(start.x, end.x);
				pos.right = max(start.x, end.x);
				pos.top = min(start.y, end.y);
				pos.bottom = max(start.y, end.y);
			}
			
		}
		return 0;
	case WM_MOUSEMOVE:
		if (drag) {
			if (!isdraw) {
				end.x = LOWORD(lParam);
				end.y = HIWORD(lParam);
				pos.left = min(start.x, end.x);
				pos.right = max(start.x, end.x);
				pos.top = min(start.y, end.y);
				pos.bottom = max(start.y, end.y);
			}
			if (isdraw) {
				mousept.x = LOWORD(lParam);
				mousept.y = HIWORD(lParam);

				if (PtInRect(&pos, mousept)) {
					double length_x = (pos.right - pos.left)/2;
					double length_y = (pos.bottom - pos.top)/2;
				
					pos.left = mousept.x - length_x;
					pos.right = mousept.x + length_x;

					pos.top = mousept.y - length_y;
					pos.bottom = mousept.y + length_y;
				}
			}


		}
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_LBUTTONUP:
		drag = false;
		isdraw = true;

		if (!isdraw) {
			pos.left = min(start.x, end.x);
			pos.right = max(start.x, end.x);
			pos.top = min(start.y, end.y);
			pos.bottom = max(start.y, end.y);
		}
		

		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_ACTIVATE:
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_SETFOCUS:
		break;
	case WM_KILLFOCUS:
		break;
	case WM_SIZE:
		break;
	case WM_DESTROY:
		return 0;
	} //처리할 메시지만 case문에 나열
	return DefMDIChildProc(hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK ChildViewerProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HDC memdc;
	PAINTSTRUCT ps;
	static HBITMAP bitmap = (HBITMAP)LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));
	static HBRUSH hbrBackground = NULL; // 배경브러쉬핸들
	int ID;

	static int speed = 6;
	static int xvec = 1;
	static int yvec = 1;
	switch (iMessage) {
	case WM_CREATE:
		ID = ChildNum;
		SetWindowLong(hWnd, 0, ID);
		GetClientRect(hWnd, &ReectView[1]);
		//if (hbrBackground) DeleteObject(hbrBackground);
		hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);


		SetTimer(hWnd, 1, 10, NULL);
		InvalidateRect(hWnd, NULL, false); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_KEYDOWN:
		break;
	case WM_TIMER:
		//GetClientRect(hWnd, &ReectView);


		
		InvalidateRect(hWnd, NULL, false); // WM_PAINT 메세지 강제 발생시킨다
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때, 화면이 깨졌을때 OS에서 메세지 전송 (처음 생성, 다른 윈도우 가려져있다가 다시 보일 때, 창 크기 바뀔때InvalidateRect(), InvalidateRgn()함수를 호출하여 강제로 화면을 무효화시킬 때)
		ID = GetWindowLong(hWnd, 0);
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
		GetClientRect(hWnd, &ReectView[1]);
		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc); // hdc와 호환시킨다.
		memdc = CreateCompatibleDC(hdc);
		HBITMAP Lay; // 레이어 생성
		Lay = CreateCompatibleBitmap(hdc, 400, 800); // 다블 버퍼링 ,hdc와 호환시키자.
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &ReectView[1], hbrBackground);
			SetBkMode(LayDC, TRANSPARENT);
			//////<여기다 그린다>//////////////////////////////////////////////////////////////////
			{
				double length_xx = (max(pos.right,pos.left) - min(pos.right, pos.left));
				double length_yy = (max(pos.bottom, pos.top) - min(pos.bottom, pos.top));
			
				SelectObject(memdc, bitmap);
				
				//StretchBlt(LayDC,0,0, RectView.right-RectView.left, RectView.bottom - RectView.top,
				//	memdc, 0, 0,
				//	length_xx, length_yy, SRCCOPY); // 복사된 그림을 그린다

				//img.StretchBlt(LayDC, 0, 0, length_xx, length_yy, SRCCOPY);
				if(isshow)
				img.StretchBlt(LayDC, 0, 0, 400, 800 ,
					pos.left,
					pos.top,
					length_xx,
					length_yy,
					SRCCOPY);
				
			}
			

			//////////////////////////////////////////////////////////////////////
			BitBlt(hdc, 0, 0, 400,800, LayDC, 0, 0, SRCCOPY);
		}


		DeleteObject(Lay);
		DeleteObject(hdc);

		DeleteDC(LayDC);
		DeleteDC(memdc);
		DeleteDC(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		ID = GetWindowLong(hWnd, 0);
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
	} //처리할 메시지만 case문에 나열
	return DefMDIChildProc(hWnd, iMessage, wParam, lParam);
}
