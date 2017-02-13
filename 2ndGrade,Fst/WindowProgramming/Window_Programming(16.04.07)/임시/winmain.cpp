#include <Windows.h>
#include <Tchar.h>
#include <time.h>

#define LENGTH_CHAR 10
#define WIDTH 1200
#define HIGHT 800
#define Cell_W 80
#define Cell_H 60
#define TYPE 4
#define COUNT 5

	//typedef struct {};

	HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	// 윈도우 클래스 구조체 값 설정
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = IpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	// 윈도우 생성
	hWnd = CreateWindow(
		IpszClass,
		IpszClass,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WIDTH,
		HIGHT,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	// 윈도우 출력
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// 이벤트 루프 처리
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {

	srand((unsigned)time(NULL));
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	PAINTSTRUCT ps;
	HDC hdc;
	static POINT pointT[3];
	static POINT pointR[4];
	static POINT pointE[2];
	//
	static wchar_t buffur;
	static int i, j;


	switch (iMessage)
	{
	case WM_CREATE:
		buffur = 0;
		return 0;

	case WM_CHAR:
		//e, t, r 의 세가지 명령어에 대한 조건을 만든다.
		if (wParam == 'r' || wParam == 'R') {
			buffur = wParam;
			for (i = 0; i < TYPE - 1; ++i) {
				pointR[i].x = rand() % WIDTH;
				pointR[i].y = rand() % HIGHT;
			}
		}
		else if (wParam == 'e' || wParam == 'E') {
			buffur = wParam;
			for (i = 0; i < TYPE - 3; ++i) {
				pointE[i].x = rand() % WIDTH;
				pointE[i].y = rand() % HIGHT;
			}
		}
		else if (wParam == 't' || wParam == 'T') {
			buffur = wParam;
			for (i = 0; i < TYPE - 2; ++i) {
				pointT[i].x = rand() % WIDTH;
				pointT[i].y = rand() % HIGHT;
			}
		}

		else if (wParam == VK_DELETE) {}
		InvalidateRect(hwnd, NULL, true);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hPen = CreatePen(PS_SOLID, 1, RGB(rand() % 240, rand() % 240, rand() % 240));
		oldPen = (HPEN)SelectObject(hdc, hPen);

		if (buffur == 'r') {
			Polygon(hdc, pointR, 4);
		}
		else if (buffur == 'e') {
			Ellipse(hdc, pointE[0].x, pointE[0].y, pointE[1].x, pointE[1].y);
		}
		else if (buffur == 't') {
			Polygon(hdc, pointT, 3);
		}
		else
			TextOut(hdc, WIDTH / 2, HIGHT / 2, L"NOTHING", 7);

		SelectObject(hdc, oldPen);
		DeleteObject(hPen);

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hwnd, iMessage, wParam, IParam));
}
