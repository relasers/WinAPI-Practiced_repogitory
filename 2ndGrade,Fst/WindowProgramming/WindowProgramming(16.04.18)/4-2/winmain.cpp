#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include <math.h>
#include"resource.h"

#define CLIENT_WIDTH 800 // 클라이언트 가로크기
#define CLIENT_HEIGHT 800 // 클라이언트 세로크기
typedef enum {
	normal, mul1_2, mul1_4 // 3x3,4x4,5x5,전체
}Mode;

typedef struct {
	int nXD;
	int nYD;
	int nW;
	int nH;
	int nXS;
	int nYS;
	int nWS;
	int nHS;
}CI; // copyimage

HINSTANCE hInst;
LPCTSTR IpszClass = L"Window Class 5-2"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
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
	static RECT m_glass; // 돋보기 저장 구조체
	static CI copy_image;
	static CI paste_image;

	static int screen_mode;

	static POINT start; //POINT로 변경
	static POINT old;

	static bool Drag;
	static bool isCopy;
	static float multiply;

	int endX, endY;
	//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView);
		GetWindowRect(hWnd, &rectPos); //현재 윈도우의  위치 

		screen_mode = Mode::normal;
		multiply = 1;
		hBitmap = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
			MAKEINTRESOURCE(IDB_BITMAP1));
		start.x = old.x = 50;
		start.y = old.y = 50; // 시작 좌표
		Drag = false;
		isCopy = false;

		return 0;
	case WM_LBUTTONDOWN:
		Drag = true;
		
		m_glass.left = m_glass.right = LOWORD(lParam); 
		m_glass.top = m_glass.bottom = HIWORD(lParam); // 시작 좌표
		
		  InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		
		if (Drag)
		{
			POINT local_ptstart;
			POINT local_ptend;

			local_ptstart = POINT{
				min(start.x, old.x),
				min(start.y, old.y)
			};
			local_ptend = POINT{
				max(start.x, old.x),
				max(start.y, old.y)
			};

			start = local_ptstart;
			old = local_ptend;
		}
		
		Drag = false;
		
		
		
		break;

	case WM_MOUSEMOVE:
		if (Drag == true)
		{ // 흰 바탕
																// 흰 바탕 XOR 흰 펜 = 검은색 펜
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);

			m_glass.right = endX;
			m_glass.bottom = endY; // 현 지점을 이젂 지점으로 설정
		}
		  InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_CHAR:
		if (wParam == '0') {
			screen_mode = Mode::normal;
			multiply = 1;
		}
		else if (wParam == '1') {
			screen_mode = Mode::mul1_2;
			multiply = 0.8;
		}
		else if (wParam == '2') {
			screen_mode = Mode::mul1_4;
			multiply = 0.6;
		}
		else if (wParam == 'c' || wParam == 'C') {
			copy_image.nXD = 0;
			copy_image.nYD = 0;
			copy_image.nW = (m_glass.right - m_glass.left);
			copy_image.nH = (m_glass.bottom - m_glass.top);
			copy_image.nXS = 800 * m_glass.left / rectView.right;
			copy_image.nYS = 800 * m_glass.top / rectView.bottom;
			copy_image.nWS = 800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left)*multiply;
			copy_image.nHS = 800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top)*multiply;
			
		}
		else if (wParam == 'p' || wParam == 'P') {
			isCopy = true;
			if (isCopy == true) {
				paste_image = copy_image;
			}
		}

		if (isCopy == true) {
		
			paste_image.nXD = 0;
			paste_image.nYD = 0;
			paste_image.nW = (m_glass.right - m_glass.left);
			paste_image.nH = (m_glass.bottom - m_glass.top);
			paste_image.nXS = 800 * m_glass.left / rectView.right;
			paste_image.nYS = 800 * m_glass.top / rectView.bottom;
			paste_image.nWS = 800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left)*multiply;
			paste_image.nHS = 800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top)*multiply;
		
		}
		  InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_UP || wParam == VK_DOWN || wParam == VK_RIGHT || wParam == VK_LEFT) {
			switch (wParam) {
			case VK_UP:
				OffsetRect(&m_glass, 0, -5);
				break;
			case VK_DOWN:
				OffsetRect(&m_glass, 0, 5);
				break;
			case VK_RIGHT:
				OffsetRect(&m_glass, 5, 0);
				break;
			case VK_LEFT:
				OffsetRect(&m_glass, -5, 0);
				break;
			}
		}
		if (isCopy == true) {

			paste_image.nXD = 0;
			paste_image.nYD = 0;
			paste_image.nW = (m_glass.right - m_glass.left);
			paste_image.nH = (m_glass.bottom - m_glass.top);
			paste_image.nXS = 800 * m_glass.left / rectView.right;
			paste_image.nYS = 800 * m_glass.top / rectView.bottom;
			paste_image.nWS = 800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left)*multiply;
			paste_image.nHS = 800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top)*multiply;

		}
		  InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc);
		HBITMAP Lay;
		Lay = CreateCompatibleBitmap(hdc, 800, 800);
		SelectObject(LayDC, Lay);

		{

			memdc = CreateCompatibleDC(LayDC);
			SelectObject(memdc, hBitmap);

			StretchBlt(LayDC, 0, 0, rectView.right, rectView.bottom, memdc, 0, 0, 800, 800, SRCCOPY);
			// SRCCOPY : 바탕색을 무시하고 그려라

			Rectangle(LayDC, m_glass.left - 1, m_glass.top - 1, m_glass.right + 1, m_glass.bottom + 1);



			switch (screen_mode) {
			case Mode::normal:
				StretchBlt(LayDC, m_glass.left, m_glass.top, (m_glass.right - m_glass.left), (m_glass.bottom - m_glass.top),
					memdc, 800 * m_glass.left / rectView.right, 800 * m_glass.top / rectView.bottom,
					800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left),
					800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top), SRCCOPY);
				break;
			case Mode::mul1_2:
			case Mode::mul1_4:
				StretchBlt(LayDC, m_glass.left, m_glass.top, (m_glass.right - m_glass.left), (m_glass.bottom - m_glass.top),
					memdc, 800 * m_glass.left / rectView.right, 800 * m_glass.top / rectView.bottom,
					800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left)*multiply,
					800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top)*multiply, SRCCOPY);
				break;
			}

			if (isCopy == true) {
				StretchBlt(LayDC, 0, 0, paste_image.nW, paste_image.nH,
					memdc, paste_image.nXS, paste_image.nYS,
					paste_image.nWS, paste_image.nHS, SRCCOPY);
			}

			if (Drag)
			{
				FrameRect(LayDC, &m_glass, (HBRUSH)GetStockObject(BLACK_BRUSH));
//				Rectangle(LayDC, m_glass.left, m_glass.top, endX, endY);
			}

			BitBlt(hdc, 0, 0, 800, 800, LayDC, 0, 0, SRCCOPY);
		}
		DeleteObject(Lay);
		DeleteDC(LayDC);

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

