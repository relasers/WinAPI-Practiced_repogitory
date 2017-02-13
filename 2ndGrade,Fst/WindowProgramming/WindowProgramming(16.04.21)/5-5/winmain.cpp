#include <Windows.h>
#include <Tchar.h> 
#include <time.h>
#include <math.h>
#include"resource.h"

#define CLIENT_WIDTH 800 // 클라이언트 가로크기
#define CLIENT_HEIGHT 800 // 클라이언트 세로크기

#define WT_ANIMATION 1
#define WT_UPDATE 2
#define WT_BACKGROUND 3

#define GRAVITY 0.5
#define GRAVITY_ACCEL 0.15

//bool keydown[255] = { 0, };

typedef struct {
	RECT pos;
	bool moving;
	int dir;
	double vec_y;
}Player;

typedef struct {
	RECT pos;
	bool exist;
}Explode;

typedef enum {
	left,right
}player_dir;

HINSTANCE hInst;
LPCTSTR IpszClass = L"Window Class 5-5"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
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
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, //윈도우 스타일
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

	static HDC hdc, memdc;
	static HBITMAP Bit_Back1;
	static HBITMAP Bit_Back2;
	static HBITMAP Bit_Explosion;
	static HBITMAP Bit_Obstacle;
	static HBITMAP Bit_Player;

	static RECT rectView;
	static RECT rectPos;

	static RECT back_1;
	static RECT back_2;
	static RECT platform;
	static RECT obstacle;
	static Explode explode;

	static Player player;

	static unsigned int mainframe;
	static int playerframe;
	static int obstacleframe;
	static int explosionframe;
	int randomposobs;
	static RECT temp; //사각형 구조체 충돌 체크용

	//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView);
		GetWindowRect(hWnd, &rectPos); //현재 윈도우의  위치 

		back_1 = { 0,0,800,800 };
		back_2 = { 0,400,800,800 };
		platform = { 0,700,800,800 };


		randomposobs = 620 + rand() % 30;
		obstacle = { 0,randomposobs,64,randomposobs+64 };

		player = { {500,500,532,548},false,player_dir::left,0 };

		explode = { {0,0,64,64}, false };

		Bit_Back1 = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
			MAKEINTRESOURCE(IDB_BITMAP1));
		Bit_Back2 = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
			MAKEINTRESOURCE(IDB_BITMAP2));
		Bit_Explosion = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
			MAKEINTRESOURCE(IDB_BITMAP3));
		Bit_Obstacle = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
			MAKEINTRESOURCE(IDB_BITMAP4));
		Bit_Player = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
			MAKEINTRESOURCE(IDB_BITMAP5));

		mainframe = 0;
		playerframe = 0;
		explosionframe = 0;

		SetTimer(hWnd, WT_BACKGROUND, 10, NULL);
		SetTimer(hWnd, WT_ANIMATION, 60, NULL);
		SetTimer(hWnd, WT_UPDATE, 10, NULL);
		return 0;

	case WM_TIMER:
		randomposobs = 620 + rand() % 30;
		switch (wParam) {
		case WT_BACKGROUND:
			OffsetRect(&back_1, 2, 0);

			OffsetRect(&back_2, 5, 0);
			if (rectView.right < back_1.left) {
				back_1 = { 0,0,800,800 };
			}
			if (rectView.right < back_2.left) {
				back_2 = { 0,400,800,800 };
			}
			break;
		case WT_ANIMATION:
			(++mainframe) %= 21000;
			playerframe = mainframe % 10;
			obstacleframe = mainframe % 4;

			if (explode.exist == true) {
				explosionframe++;
				if (explosionframe > 6) {
					explode.exist = false;
					explosionframe = 0;
				}
			}

			break;
		case WT_UPDATE:

			if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
				player.dir = player_dir::left;
				player.moving = true;
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
				player.dir = player_dir::right;
				player.moving = true;
			}
			if (GetAsyncKeyState(VK_UP) & 0x8000) {
				player.vec_y = -10;
			}
			// 참조! 이렇게하면 키 충돌이 없다!

			OffsetRect(&obstacle, 5, 0);
			if (rectView.right < obstacle.left) {
				obstacle = { -64,randomposobs,0,randomposobs+64 };
			}


			if (player.vec_y > 0) {
				player.vec_y += GRAVITY;
			}
			else
				player.vec_y += GRAVITY+GRAVITY_ACCEL;


			OffsetRect(&player.pos, 0, player.vec_y);

			if (IntersectRect(&temp, &platform, &player.pos)) {
				player.pos.top = platform.top - 49;
				player.pos.bottom = platform.top - 1;
				player.vec_y = 0;
			}

			if (IntersectRect(&temp, &obstacle, &player.pos)) {

				explode.pos = {
					player.pos.left,
					player.pos.top,
					player.pos.left + 64,
					player.pos.top + 64,
				};

				explode.exist = true;
				explosionframe = 0;
			}

			if (player.moving) {
				switch (player.dir) {
				case player_dir::left:
					OffsetRect(&player.pos, -5, 0);
					break;
				case player_dir::right:
					OffsetRect(&player.pos, 5, 0);
					break;
				}
			}

			

			break;
		}
	
		InvalidateRgn(hWnd, NULL, false);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		break;
	case WM_KEYDOWN:
		
		//key[wParam] = true;
		switch (wParam) {
		case VK_LEFT:
			player.dir = player_dir::left;
			player.moving = true;
			break;
		case VK_RIGHT:
			player.dir = player_dir::right;
			player.moving = true;
			break;
		case VK_UP:
			player.vec_y = -10;
			break;
		}
		
		
		InvalidateRect(hWnd,NULL,false);
		break;
	case WM_KEYUP:
		if(player.moving)
		player.moving = false;
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
		memdc = CreateCompatibleDC(hdc);

		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc);
		HBITMAP Lay;
		Lay = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
		SelectObject(LayDC, Lay);
		{

			SelectObject(memdc, Bit_Back1);

			BitBlt(LayDC, back_1.left, back_1.top, back_1.right - back_1.left, back_1.bottom - back_1.top
				, memdc, 0, 0, SRCCOPY); // 산을 그린다 // SRCCOPY : 바탕색을 무시하고 그려라
			if (rectView.right < back_1.right) {
				BitBlt(LayDC, 0, back_1.top, back_1.left, back_1.bottom - back_1.top
					, memdc, 800 - back_1.left, 0, SRCCOPY); // 산을 그린다 // SRCCOPY : 바탕색을 무시하고 그려라
			}
			SelectObject(memdc, Bit_Back2);

			TransparentBlt(LayDC, back_2.left, back_2.top, back_2.right - back_2.left, back_2.bottom - back_2.top
				, memdc, 0, 0,800,200, RGB(255,255,255)); // 땅을 그린다
			if (rectView.right < back_2.right) {

				TransparentBlt(LayDC, 0, back_2.top, back_2.left, back_2.bottom - back_2.top
					, memdc, 800 - back_2.left, 0, back_2.left ,200, RGB(255, 255, 255)); // 땅을 그린다

			}

			SelectObject(memdc, Bit_Obstacle);
			TransparentBlt(LayDC, obstacle.left, obstacle.top, 64, 64
				, memdc, obstacleframe*64, 0, 64, 64, RGB(255, 255, 255)); // 장애물을 그린다

			SelectObject(memdc, Bit_Player);
			TransparentBlt(LayDC, player.pos.left, player.pos.top, 32, 48
				, memdc, playerframe * 32, 0, 32, 48, RGB(255, 255, 255)); // 플레이어를 그린다

			if (explode.exist == true) {
				SelectObject(memdc, Bit_Explosion);
				TransparentBlt(LayDC, explode.pos.left, explode.pos.top, 64, 64
					, memdc, explosionframe * 64, 0, 64, 64, RGB(255, 255, 255)); // 폭8을 그린다
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

