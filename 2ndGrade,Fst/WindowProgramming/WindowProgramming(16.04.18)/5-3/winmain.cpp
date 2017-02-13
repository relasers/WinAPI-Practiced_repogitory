#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include <math.h>
#include"resource.h"

#define CLIENT_WIDTH 800 // 클라이언트 가로크기
#define CLIENT_HEIGHT 800 // 클라이언트 세로크기

typedef enum {
	jayu,full,by2,by3,by4,by5
}Screen;

typedef struct {
	RECT posit;
	bool select;
}Board;

typedef struct {
	int nXD;
	int nYD;
	int nW;
	int nH;
	int nXS;
	int nYS;
	int nWS;
	int nHS;
	int selX;
	int selY;
	bool copied;
}CI; // copyimage

bool isPointinRect(RECT rc,int x,int y) {
	if ((rc.left <= x&&x <= rc.right) && (rc.top <= y && y <= rc.bottom)) {
		return true;
	}
	return false;
} // 점과 사각형의 충돌쳌


HINSTANCE hInst;
LPCTSTR IpszClass = L"Window Class 5-3"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
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
	HBRUSH nullBrush,oldBrush;
	HPEN selectPen,normalPen, oldPen;
	static HBITMAP hBitmap;

	static RECT rectView;
	static RECT m_glass; // 돋보기 저장 구조체

	static CI paste_image[5][5];

	static Board board[3][3];
	static int sel_X=-1; //선택가로
	static int sel_Y=-1; //선택세로

	static float screen_mode;

	static int startX, startY, oldX, oldY;
	static int mx = 0, my = 0; // 마우스
	static bool Drag;
	static bool isCopy;
	static float multiply;
	int i, j;
	int endX, endY;
	//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView);

		multiply = 1;
		hBitmap = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
			MAKEINTRESOURCE(IDB_BITMAP2));
		startX = oldX = 50; startY = oldY = 50; // 시작 좌표
		Drag = false;
		isCopy = false;

		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; ++j) {
				board[i][j].posit = { i*rectView.right / 6, j*rectView.bottom / 3,
					(i + 1)*rectView.right / 6, (j + 1)*rectView.bottom / 3 };
				board[i][j].select = false;
			}
		} // 보드 그리기
		for (i = 0; i < 5; ++i) {
			for (j = 0; j < 5; ++j) {
				paste_image[i][j].copied = false;
			}
		}
		return 0;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);

		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; ++j) {
				if (0 <= mx&&mx <= rectView.right / 2) {
					board[i][j].select = false;
					if (isPointinRect(board[i][j].posit, mx, my)) {
						board[i][j].select = true;
						sel_X = i;
						sel_Y = j;
					}
				}
			}
		}
		if (sel_X != -1 && sel_Y != -1) {
			if (screen_mode == Screen::jayu) {
				if (rectView.right / 2 <= mx&&mx <= rectView.right) {
					Drag = true;
					m_glass.left = m_glass.right = LOWORD(lParam); m_glass.top = m_glass.bottom = HIWORD(lParam); // 시작 좌표
					ReleaseDC(hWnd, hdc);
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
			else {
				for (i = 0; i < screen_mode; ++i) {
					for (j = 0; j < screen_mode; ++j) {
						if ((rectView.right / 2 + rectView.right / 2 / screen_mode*j
							<= mx&&mx <= rectView.right / 2 + rectView.right / 2 / screen_mode*(j + 1)) &&
							(rectView.bottom / screen_mode*i <= my && my <= rectView.bottom / screen_mode*(i + 1))) {
							paste_image[i][j].nXD = rectView.right / 2 + rectView.right / 2 / screen_mode*j;
							paste_image[i][j].nYD = (rectView.bottom / screen_mode)*i;
							paste_image[i][j].nW = rectView.right / 2 / screen_mode;
							paste_image[i][j].nH = rectView.bottom / screen_mode;
							paste_image[i][j].selX = sel_X;
							paste_image[i][j].selY = sel_Y;
							paste_image[i][j].copied = true;
						}
					}
				}
			}
		}
		

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		Drag = false;
		if (screen_mode == Screen::jayu) {
			paste_image[0][0].nXD = m_glass.left;
			paste_image[0][0].nYD = m_glass.top;
			paste_image[0][0].nW = (m_glass.right - m_glass.left);
			paste_image[0][0].nH = (m_glass.bottom - m_glass.top);
			paste_image[0][0].nXS = 800 * m_glass.left / rectView.right;
			paste_image[0][0].nYS = 800 * m_glass.top / rectView.bottom;
			paste_image[0][0].nWS = 800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left)*multiply;
			paste_image[0][0].nHS = 800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top)*multiply;
			paste_image[0][0].selX = sel_X;
			paste_image[0][0].selY = sel_Y;
			paste_image[0][0].copied = true;
		}
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hWnd);
		if (Drag == true)
		{ // 흰 바탕
			SetROP2(hdc, R2_XORPEN); // 펜의 XOR 연산
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN)); // 흰 펜
																// 흰 바탕 XOR 흰 펜 = 검은색 펜
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);
			Rectangle(hdc, m_glass.left, m_glass.top, m_glass.right, m_glass.bottom);
			Rectangle(hdc, m_glass.left, m_glass.top, endX, endY);
			m_glass.right = endX; m_glass.bottom = endY; // 현 지점을 이젂 지점으로 설정
		}
		InvalidateRect(hWnd, NULL, FALSE);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		if (wParam == '0') {
			screen_mode = Screen::jayu;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		else if (wParam == '1') {
			screen_mode = Screen::full;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		else if (wParam == '2') {
			screen_mode = Screen::by2;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		else if (wParam == '3') {
			screen_mode = Screen::by3;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		else if (wParam == '4') {
			screen_mode = Screen::by4;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		else if (wParam == '5') {
			screen_mode = Screen::by5;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
		memdc = CreateCompatibleDC(hdc);
		nullBrush = (HBRUSH)GetStockObject(NULL_BRUSH); // 빈브러쉬
		selectPen = (HPEN)CreatePen(PS_SOLID,2,RGB(255,0,0)); // 선택 펜
		normalPen = (HPEN)CreatePen(PS_DASH, 1, RGB(255, 255, 0)); // 선택 펜

		SelectObject(memdc, hBitmap);

		StretchBlt(hdc, 0, 0, rectView.right/2, rectView.bottom, memdc, 0, 0, 400, 800, SRCCOPY);
		
		// SRCCOPY : 바탕색을 무시하고 그려라
		
		
		if (screen_mode == Screen::jayu) {
			Rectangle(hdc, m_glass.left - 1, m_glass.top - 1, m_glass.right + 1, m_glass.bottom + 1);
			if (paste_image[0][0].copied == true) {
				StretchBlt(hdc, paste_image[0][0].nXD, paste_image[0][0].nYD,
					paste_image[0][0].nW, paste_image[0][0].nH,
					memdc, paste_image[0][0].selX*(400 / 3), paste_image[0][0].selY*(800 / 3),
					400 / 3, 800 / 3, SRCCOPY); // 복사된 그림을 그린다
			}
			
		}

		else {
			for (i = 0; i < screen_mode; ++i) {
				for (j = 0; j < screen_mode; ++j) {
					Rectangle(hdc, rectView.right/2+rectView.right/2/(screen_mode)*j
						, rectView.bottom/screen_mode*i,
						rectView.right / 2 + rectView.right / 2 / (screen_mode)*(j+1),
						rectView.bottom / screen_mode*(i+1));
					if (paste_image[i][j].copied == true) {
						StretchBlt(hdc, paste_image[i][j].nXD, paste_image[i][j].nYD,
							paste_image[i][j].nW, paste_image[i][j].nH,
							memdc, paste_image[i][j].selX*(400 / 3), paste_image[i][j].selY*(800 / 3),
							400 / 3, 800 / 3, SRCCOPY);
					}
				}
			}
		}


		oldBrush = (HBRUSH)SelectObject(hdc, nullBrush);
		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; ++j) {
				oldPen = (HPEN)SelectObject(hdc,normalPen);
				if (board[i][j].select == true) {
					SelectObject(hdc, oldPen);
					oldPen = (HPEN)SelectObject(hdc, selectPen);
				}
				Rectangle(hdc, board[i][j].posit.left, board[i][j].posit.top,
					board[i][j].posit.right, board[i][j].posit.bottom);
				SelectObject(hdc, oldPen);
			}
		} // 왼쪽 그림판 // 칸을 나눈다
		SelectObject(hdc, oldBrush);

		DeleteDC(memdc);
		DeleteObject(selectPen);
		DeleteObject(normalPen);
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE: // 윈도우가 다시 그려질때
		GetClientRect(hWnd, &rectView);

		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; ++j) {
				board[i][j].posit = { i*rectView.right / 6, j*rectView.bottom / 3,
					(i + 1)*rectView.right / 6, (j + 1)*rectView.bottom / 3 };
				board[i][j].select = false;
			}
		} // 보드 그리기
		for (i = 0; i < screen_mode; ++i) {
			for (j = 0; j < screen_mode; ++j) {
				paste_image[i][j].nXD = rectView.right / 2 + rectView.right / 2 / screen_mode*j;
				paste_image[i][j].nYD = (rectView.bottom / screen_mode)*i;
				paste_image[i][j].nW = rectView.right / 2 / screen_mode;
				paste_image[i][j].nH = rectView.bottom / screen_mode;
			}
		}
		
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}

