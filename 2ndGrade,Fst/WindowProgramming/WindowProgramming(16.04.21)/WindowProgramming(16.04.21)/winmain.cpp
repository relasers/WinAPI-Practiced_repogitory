#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include <math.h>
#include"resource.h"

#define CLIENT_WIDTH 800 // 클라이언트 가로크기
#define CLIENT_HEIGHT 800 // 클라이언트 세로크기
#define WT_ANIMATION 1 // 애니메이션 메세지
#define WT_MOVE 2 // 움직인다

#define GRAVITY 0.05 // 뉴턴파워
#define GRAVITY_ACCEL 0.15 // 중력가속도

typedef struct {
	POINT pos; // 현 좌표
	int z_pos;// z 좌표
	int stat; // 현 상태
	int dir; // 방향
	int speed; // 속도
	float vec_y; // 상하벡터
}Pone; // 폰

typedef enum {
	stand,move,jump,clmoving // 서있다,움직인다,점프한다,클릭후이동한다
}Pone_Stat;

typedef enum {
left,right,down,up
}Direction;

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

		static POINT mouse;

		static HDC hdc, memdc;// 항상 첫번째 인자는 hDC 다! 

		static HBITMAP Bit_Back;
		static HBITMAP Bit_move;
		static HBITMAP Bit_moveto;
		static HBITMAP Bit_stand;
		static HBRUSH brush_shadow;
		HBRUSH oldbrush;
		static RECT ponerect;
		static RECT rectView;
		static RECT rectPos;

		static Pone pone; // 폰
		static bool moving; // 키가 눌려저서 움직이는가?
		static bool jumping;
		static int movedist;

		static unsigned int mainframe;
		static int poneframe;

		//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다

		switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
		case WM_CREATE:
			rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
			GetClientRect(hWnd, &rectView);

			Bit_Back = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
				MAKEINTRESOURCE(IDB_BACK));
			Bit_stand = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
				MAKEINTRESOURCE(IDB_STAND));
			Bit_move = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
				MAKEINTRESOURCE(IDB_MOVE));
			Bit_moveto = (HBITMAP)LoadBitmap(hInst, // hinstance 인수는 맨위에 선언한 HINSTANCE 값으로..
				MAKEINTRESOURCE(IDB_MOVETO));

			pone = {
				{rectView.right / 2,rectView.bottom / 2},0,Pone_Stat::stand,Direction::left,5,0
			}; // 좌표,z축,상태,방향,속도
			brush_shadow = (HBRUSH)GetStockObject(BLACK_BRUSH);
			moving = false;
			jumping = false;
			movedist =0;
			SetTimer(hWnd, WT_ANIMATION, 60, NULL);
			SetTimer(hWnd, WT_MOVE, 60, NULL);
			return 0;

		case WM_TIMER:
			switch (wParam) {
			case WT_ANIMATION:
				mainframe++;
				poneframe = mainframe % 4;
				break;
			case WT_MOVE:
				
				if (movedist <= 0) {
					if (moving == true) {
						switch (pone.dir) {
						case Direction::left:
							pone.pos.x -= pone.speed;
							break;
						case Direction::right:
							pone.pos.x += pone.speed;
							break;
						case Direction::up:
							pone.pos.y -= pone.speed;
							break;
						case Direction::down:
							pone.pos.y += pone.speed;
							break;
						}
					}
				}
				else {
					movedist--;
					switch (pone.dir) {
					case Direction::left:
						pone.pos.x -= pone.speed;
						break;
					case Direction::right:
						pone.pos.x += pone.speed;
						break;
					case Direction::up:
						pone.pos.y -= pone.speed;
						break;
					case Direction::down:
						pone.pos.y += pone.speed;
						break;
					}
					if (movedist <= 0) {
						pone.stat = Pone_Stat::stand;
					}
				}
				

				if (pone.vec_y >= 0) {
					pone.vec_y += GRAVITY_ACCEL;
				}
				else {
					pone.vec_y += GRAVITY_ACCEL + GRAVITY;
				}
				if (jumping == true) {
					pone.z_pos -= pone.vec_y;
				}
				
				if (jumping == true && pone.z_pos <= 0) {
					pone.stat = Pone_Stat::stand;
					jumping = false;
					pone.vec_y = 0;
					pone.z_pos = 0;
				}
					


				break;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case WM_KEYDOWN:
			if (movedist <= 0) {
				switch (wParam) {
				case VK_LEFT:
					moving = true;
					if (jumping == false) {
						pone.stat = Pone_Stat::move;
					}
					pone.dir = Direction::left;
					break;
				case VK_RIGHT:
					moving = true;
					if (jumping == false) {
						pone.stat = Pone_Stat::move;
					}
					pone.dir = Direction::right;
					break;
				case VK_UP:
					moving = true;
					if (jumping == false) {
						pone.stat = Pone_Stat::move;
					}
					pone.dir = Direction::up;
					break;
				case VK_DOWN:
					moving = true;
					if (jumping == false) {
						pone.stat = Pone_Stat::move;
					}

					pone.dir = Direction::down;
					break;
				case 'j':
				case 'J':
					pone.stat = Pone_Stat::jump;
					jumping = true;
					pone.vec_y = -4.5;
				}
			}
				
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case WM_KEYUP:
			moving = false;
			if (pone.z_pos == 0) {
				pone.stat = Pone_Stat::stand;
			}
			
			break;
		case WM_LBUTTONDOWN:
			ponerect = { pone.pos.x,pone.pos.y,
			pone.pos.x + 32,pone.pos.y + 64
			};
			mouse.x = LOWORD(lParam);
			mouse.y = HIWORD(lParam);
			if (PtInRect(&ponerect, mouse)) {
				pone.stat = Pone_Stat::clmoving;
				movedist = 10;
				pone.dir = rand() % 4;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case WM_PAINT: //윈도우 다시 그려줘야 할 때
			hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
			memdc = CreateCompatibleDC(hdc);

			HDC LayDC;
			LayDC = CreateCompatibleDC(hdc);
			HBITMAP Lay;
			HBRUSH block_brush;
			int block_color; // 블럭 색깔 바꾸기용 변수
			Lay = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
			SelectObject(LayDC, Lay);
			{

				SelectObject(memdc, Bit_Back);

				// mem1dc에 있는 내용을 hdc에 뿌려준다.
				BitBlt(LayDC, 0, 0, 800, 800
					, memdc, 0, 0, SRCCOPY); // 산을 그린다 // SRCCOPY : 바탕색을 무시하고 그려라

				switch (pone.stat) {
				case Pone_Stat::stand:
					SelectObject(memdc, Bit_stand);
					break;
				case Pone_Stat::move:
					SelectObject(memdc, Bit_move);
					break;
				case Pone_Stat::jump:
					SelectObject(memdc, Bit_moveto);
					break;
				case Pone_Stat::clmoving:
					SelectObject(memdc, Bit_moveto);
					break;
				}
				oldbrush = (HBRUSH)SelectObject(LayDC,brush_shadow);
				Ellipse(LayDC, pone.pos.x, pone.pos.y + 58, pone.pos.x + 32, pone.pos.y + 68);
				TransparentBlt(LayDC,pone.pos.x,pone.pos.y-pone.z_pos,
					32,64,memdc,poneframe*32,0,32,64,RGB(255,255,0));
				

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

