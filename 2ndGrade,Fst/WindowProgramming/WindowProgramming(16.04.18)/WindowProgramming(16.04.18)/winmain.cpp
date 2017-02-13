#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include <math.h>
#include"resource.h"

#define CLIENT_WIDTH 800 // 클라이언트 가로크기
#define CLIENT_HEIGHT 800 // 클라이언트 세로크기

typedef enum {
	by3,by4,by5,full // 3x3,4x4,5x5,전체
}Mode;

HINSTANCE hInst;
LPCTSTR IpszClass = L"Window Class 5-1"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
										 // L"문자열" 문자열 앞에 대문자 L을 붙인다 아니면 유니코드에서 멀티바이트로 바꾸던가
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow) { // WinMain 대소문자 준수할 것!
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass; // EX 는 붙여도 되고 안붙여도 된다.
	hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 출력 스타일
	WndClass.lpfnWndProc = (WNDPROC)WndProc; // 왠만해선 이름은 그대로 쓰자
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //  기본적으로 흑,회,화 지원 빨강 이런거 만들려면 색깔 직접 만들어아함
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = IpszClass; // 이렇게 정해놨으면 이후에도 똑같은 이름, 이거로 써라
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // 클래스 12개// 반드시 12개 다 써야한다
	RegisterClassEx(&WndClass);
	// API가 지원해주는 함수
	hWnd = CreateWindow( //윈도우 핸들값 반환
		IpszClass, //윈도우 클래스 이름
		IpszClass, //윈도우 타이틀 이름
		WS_OVERLAPPEDWINDOW, //윈도우 스타일
		CW_USEDEFAULT, //윈도우 위치 x
		CW_USEDEFAULT, //윈도우 위치 y
		CLIENT_WIDTH, // 윈도우 가로크기
		CLIENT_HEIGHT, //윈도우 세로크기
		NULL, //부모 윈도우 핸들
		(HMENU)NULL, //메뉴핸들
		hInstance,//응용프로그램 인스턴스
		NULL);//생성윈도우 정보

	ShowWindow(hWnd, nCmdShow); // 윈도우 화면 출력
	UpdateWindow(hWnd); // O/S에 WM_PAINT  메시지 전송 

	while (GetMessage(&Message, 0, 0, 0)) { // 윈도우 프로시져에서 PostQuitMessage() 호출 때까지 처리 
		TranslateMessage(&Message);  // ex) Shift ‘a’→ 대문자 ‘A’ 
		DispatchMessage(&Message);  // WinMain → WinProc 
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	srand((unsigned)time(NULL));
	PAINTSTRUCT ps;

	HDC hdc, memdc;; // 항상 첫번째 인자는 hDC 다! 
	static HBITMAP hBitmap;

	static RECT rectView;
	static RECT rectPos;
	RECT temp; //사각형 구조체 충돌 체크용
	int i,j;
	static int screen_mode;
	//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView);
		GetWindowRect(hWnd, &rectPos); //현재 윈도우의  위치 

		screen_mode = Mode::full;

		hBitmap = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
			MAKEINTRESOURCE(IDB_BITMAP1));

		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd, &rectView, TRUE);
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hWnd);
		InvalidateRect(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		if (wParam == 'A' || wParam == 'a') {
			screen_mode = Mode::full;
		}
		else if (wParam == '3'){
			screen_mode = Mode::by3;
		}
		else if (wParam == '4') {
			screen_mode = Mode::by4;
		}
		else if (wParam == '5') {
			screen_mode = Mode::by5;
		}

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
		memdc = CreateCompatibleDC(hdc);
		SelectObject(memdc, hBitmap);
		switch (screen_mode) {
		case Mode::by3:
			for (i = 0;i<3;++i) {
				for (j = 0; j < 3; ++j) {
					StretchBlt(hdc, rectView.right / 3 * i, rectView.bottom / 3 * j, rectView.right / 3, rectView.bottom / 3, memdc,
						0,0,800,800, SRCCOPY);
				}
			}
			
			break;
		case Mode::by4:
			for (i = 0; i<4; ++i) {
				for (j = 0; j < 4; ++j) {
					StretchBlt(hdc, rectView.right / 4 * i, rectView.bottom / 4 * j, rectView.right / 4, rectView.bottom / 4, memdc,
						0, 0, 800, 800, SRCCOPY);
				}
			}
			break;
		case Mode::by5:
			for (i = 0; i<5; ++i) {
				for (j = 0; j < 5; ++j) {
					StretchBlt(hdc, rectView.right / 5 * i, rectView.bottom / 5 * j, rectView.right / 5, rectView.bottom / 5, memdc,
						0, 0, 800, 800, SRCCOPY);
				}
			}
			break;
		case Mode::full:
			StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc, 0, 0, 800, 800, SRCCOPY);
			break;
		}
		// SRCCOPY : 바탕색을 무시하고 그려라
		DeleteDC(memdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE: // 윈도우가 다시 그려질때
		GetClientRect(hWnd, &rectView);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}

