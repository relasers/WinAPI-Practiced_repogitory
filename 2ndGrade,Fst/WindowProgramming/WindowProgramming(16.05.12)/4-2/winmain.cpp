#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include<math.h>
#include "resource.h"
#define BODY_SIZE 30 // 애벌레 몸체의 사이즈다
#define MORE_SIZE 8 // 커다란 적의 머리
#define WARM_LENGTH 20 // 애벌레의 길이
#define MX_NUM_FOOD 30 // 최대 먹이 갯수
#define MX_NUM_BOMB 30 // 최대 폭탄 갯수
#define PI 3.141592

#define MX_MOUSE 10
#define MOUTH_FRAME 4
#define FEVERTIME 20

#define ITEM_SIZE 10 // 아이템 크기

#define CLIENT_WIDTH 800 // 클라이언트 가로크기
#define CLIENT_HEIGHT 800 // 클라이언트 세로크기
#define MX_SPEED 10 // 벌레 최대속도 / 작을수록 빠르다
#define MN_SPEED 200 // 벌레 최소속도 / 클수록 느리다
#define DEFAULT_SPEED 70 // 벌레의 초기 속도

#define E_SPEED 100 // 적 애벌레의 속도 

#define S_OFF 0 // 스위치 꺼짐
#define S_ON 1 // 스위치 켜짐

#define JUMP_POWER 10 // 점프
typedef enum {
	cyan,magenta,yellow,random

}Color;
typedef enum {
	Left, Right, Up, Down
}Direction;

typedef struct {
	int jump;
	int direction;
}Jumping;

typedef struct{
	RECT pos;
	bool exist;
}ITEM;

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 4-2"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
										 // L"문자열" 문자열 앞에 대문자 L을 붙인다 아니면 유니코드에서 멀티바이트로 바꾸던가
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


bool collisionEllipseCheck(RECT rc, RECT rc2)
{
	float rc_R = (rc.right - rc.left) / 2;
	float rc2_R = (rc2.right - rc2.left) / 2;

	float rX = (rc.left + (rc.right - rc.left) / 2) - (rc2.left + (rc2.right - rc2.left) / 2);
	float rY = (rc.top + (rc.bottom - rc.top) / 2) - (rc2.top + (rc2.bottom - rc2.top) / 2);

	float length = (rc_R + rc2_R)  * (rc_R + rc2_R);

	if (length >= (rX * rX + rY * rY))
	{
		return true;
	}

	return false;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow) { // WinMain 대소문자 준수할 것!
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass; // EX 는 붙여도 되고 안붙여도 된다.
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 출력 스타일
	WndClass.lpfnWndProc = (WNDPROC)WndProc; // 왠만해선 이름은 그대로 쓰자
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //  기본적으로 흑,회,화 지원 빨강 이런거 만들려면 색깔 직접 만들어아함
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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
	HDC hdc; // 항상 첫번째 인자는 hDC 다! 
	HPEN hPen, oldPen;
	static HBRUSH hbrBackground = NULL; // 배경브러쉬핸들

	static HBRUSH hBrush[5], oldBrush;

	static int direction = Direction::Right; // 애벌레의 이동방향 초기는 오른쪽이다.
	static int e_direction = Direction::Right;

	static RECT rectView; // 창 크기를 저장하는 RECT 구조체
	static RECT temp;
	static RECT collcheck_temp;
	//static Warm warm; // 애벌레의 초기 위치
	//static Warm temp; // 창 끝에 닿았을때 머리와 꼬리를 맞바꾸기위한 임시 위치 저장 값
	static int length = 3;
	static int e_length = 2; // 적 길이

	static RECT warm[WARM_LENGTH] = { 0 };
	static RECT enemy_warm[WARM_LENGTH] = { 0 };

	static ITEM food[MX_NUM_FOOD] = { 0 };
	static ITEM bomb[MX_NUM_BOMB] = { 0 };
	static int wx, wy, mx, my;
	static int num_bomb = 0;
	static int num_food = 0;

	static int playermouth = 0;
	static int enemymouth = 0;

	static bool messageon = false;


	static bool creating = false; // 아이템 재배치?
	static bool gameon = false;
	static int head_color = Color::magenta;
	static int speed = DEFAULT_SPEED; // 애벌레의 초기 속도

	static Jumping jumping = { 0,Direction::Right }; // 점프 구조체 선언

	static int enemy_created = S_OFF; // 적이 생성되었다
	int i;
	int x, y;
	int x1, x2, y1, y2;
	static int mx_food = 1+rand()% (MX_NUM_FOOD-1);
	static int mx_bomb = 1+rand() % (MX_NUM_BOMB-1);

	static int fever = 0;
	static int mouseani = 0;
	static int moremouth = 0;


	static bool grid = false;
	//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView);
		warm[0] = { BODY_SIZE * 10 ,BODY_SIZE * 10, BODY_SIZE * 10 +BODY_SIZE,BODY_SIZE * 10 + BODY_SIZE };
		warm[1] = { BODY_SIZE * 9 ,BODY_SIZE * 10, BODY_SIZE * 9 + BODY_SIZE,BODY_SIZE * 10 + BODY_SIZE };
		enemy_warm[0] = { BODY_SIZE * 2 ,BODY_SIZE * 2, BODY_SIZE * 2 + BODY_SIZE,BODY_SIZE * 2 + BODY_SIZE };
		enemy_warm[1] = { BODY_SIZE * 1 ,BODY_SIZE * 2, BODY_SIZE * 1 + BODY_SIZE,BODY_SIZE * 2 + BODY_SIZE };

		for (i = 0; i <mx_food; ++i) {
			x = rand() % rectView.right- ITEM_SIZE;
			y = rand() % rectView.bottom- ITEM_SIZE;
			food[i] = { {x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
			num_food++;
		}
		for (i = 0; i <mx_bomb; ++i) {
			x = rand() % rectView.right;
			y = rand() % rectView.bottom;
			bomb[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
			num_bomb++;
		}

		SetTimer(hWnd, 1, speed, NULL); // 첫번쨰 애벌레의 속도
		SetTimer(hWnd, 2, 5000, NULL); // 적 애벌레가 생성된다 // 5000ms 초 뒤에 적이 생성된다
		SetTimer(hWnd, 4, 100000, NULL); // 먹의 임의 생성
		SetTimer(hWnd,5, 300, NULL); // 입 왔다갔다
		return 0;
		////////////////////////////////////////////////////////////////////////////////////
	case WM_LBUTTONDOWN:
		
		wx = warm[0].left + (warm[0].right - warm[0].left) / 2;
		wy = warm[0].top + (warm[0].bottom - warm[0].right) / 2;
		mx = LOWORD(lParam);
		my = HIWORD(lParam);


			if ((mx - wx)*(mx - wx) < (my - wy)*(my - wy)) {
				if (my < wy) {
					direction = Direction::Up;
				}
				else {
					direction = Direction::Down;
				}
			}
			else {
				if (mx < wx) {
					direction = Direction::Left;
				}
				else {
					direction = Direction::Right;
				}
			
			}

		break;
		///////////////////////////////////////////////////////////////////////////////
	case WM_TIMER:
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (i = 0; i < MX_NUM_FOOD; ++i) {
			if (collisionEllipseCheck(warm[0], food[i].pos) == true && food[i].exist == true) {
				length++;
				num_food--;
				fever = FEVERTIME;
				food[i].exist = false;
			}
		}
		for (i = 0; i < MX_NUM_BOMB; ++i) {
			if (collisionEllipseCheck(warm[0], bomb[i].pos) == true && bomb[i].exist == true) {
				warm[length - 1] = { '\0','\0' ,'\0' ,'\0' };
				length--;
				num_bomb--;
				bomb[i].exist = false;
			}
		}
		if(creating == false)
		if (length == 0 || num_bomb == 0 || num_food == 0) { // 종료
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
			if (num_food == 0) {
				if (messageon == false) {
					messageon = true;
					MessageBoxW(hWnd, TEXT("다먹었다!"), TEXT("종료메세지"), MB_OK);
					Sleep(100000);
					
				}
			}
			PostQuitMessage(0);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(gameon)
		switch (wParam) {
		case 1: // 내 벌레가 움직인다
			(++mouseani) %= MOUTH_FRAME;
			if (0 < fever) {
				fever--;
				moremouth = 20;
			}
			
			if(fever<=0){
				moremouth = 0;
			}
				
			if (0 < jumping.jump) {
				if (direction == Direction::Right || direction == Direction::Left) {
					if (JUMP_POWER / 2 < jumping.jump) {
						for (i = length-1; 0 < i; --i) {
							warm[i] = warm[i - 1];
						}
						for (i = e_length - 1; 0 < i; --i) {
							enemy_warm[i] = enemy_warm[i - 1];
						}
						OffsetRect(&warm[0], 0, -BODY_SIZE);
						OffsetRect(&enemy_warm[0], 0, -BODY_SIZE);
					}
					else {
						for (i = length - 1; 0 < i; --i) {
							warm[i] = warm[i - 1];
						}
						for (i = e_length - 1; 0 < i; --i) {
							enemy_warm[i] = enemy_warm[i - 1];
						}
						OffsetRect(&warm[0],0, BODY_SIZE);
						OffsetRect(&enemy_warm[0], 0, BODY_SIZE);
					}
					jumping.jump--;

					if (warm[0].top < 0) {
						warm[0].top = 0;
						warm[0].bottom = BODY_SIZE;
					}
					if (enemy_warm[0].top < 0) {
						enemy_warm[0].top = 0;
						enemy_warm[0].bottom = enemy_warm[0].top+BODY_SIZE;
					}
				}
				else if (direction == Direction::Down || direction == Direction::Up) {
					if (JUMP_POWER / 2 < jumping.jump) {
						for (i = length - 1; 0 < i; --i) {
							warm[i] = warm[i - 1];
						}
						for (i = e_length - 1; 0 < i; --i) {
							enemy_warm[i] = enemy_warm[i - 1];
						}
						OffsetRect(&warm[0], BODY_SIZE,0 );
						OffsetRect(&enemy_warm[0], BODY_SIZE, 0);
					}
					else {
						for (i = length - 1; 0 < i; --i) {
							warm[i] = warm[i - 1];
						}
						for (i = e_length - 1; 0 < i; --i) {
							enemy_warm[i] = enemy_warm[i - 1];
						}
						OffsetRect(&warm[0], -BODY_SIZE, 0);
						OffsetRect(&enemy_warm[0], -BODY_SIZE, 0);
					}
					jumping.jump--;

					if (rectView.right < warm[0].right) {
						warm[0].right = rectView.right;
						warm[0].left = warm[0].right - BODY_SIZE;
					}
						
					if (rectView.right < enemy_warm[0].right) {
						enemy_warm[0].left = rectView.right - BODY_SIZE;
						enemy_warm[0].right = enemy_warm[0].left - BODY_SIZE;
					}
						
				}
			}


			switch (direction) {
			case Direction::Up:
				if (warm[0].top <= 0) {
					if (length != 1) {
						for (i = 0; i < length / 2; i++) {
							temp = warm[i];
							warm[i] = warm[(length - 1) - i];
							warm[(length - 1) - i] = temp;
						}
					}
					
					direction = Direction::Down;
				}
				else {
					for (i = length - 1; 0 < i; --i) {
						warm[i] = warm[i - 1];
					}
					OffsetRect(&warm[0], 0, -BODY_SIZE);
					if (warm[0].top < 0) {
						warm[0].top = 0;
						warm[0].bottom = BODY_SIZE;
					}
				}
				break;
			case Direction::Down:
				if (rectView.bottom <= warm[0].bottom) {
					if (length != 1) {
						for (i = 0; i < length / 2; i++) {
							temp = warm[i];
							warm[i] = warm[(length - 1) - i];
							warm[(length - 1) - i] = temp;
						}
					}
					
					direction = Direction::Up;
				}
				else {
					for (i = length - 1; 0 < i; --i) {
						warm[i] = warm[i - 1];
					}
					OffsetRect(&warm[0], 0, BODY_SIZE);
					if (rectView.bottom < warm[0].bottom) {
						warm[0].top = rectView.bottom - BODY_SIZE;
						warm[0].bottom = warm[0].top + BODY_SIZE;
					}
				}

				break;
			case Direction::Left:
				if (warm[0].left <= 0) {
					if (length != 1) {
						for (i = 0; i < length / 2; i++) {
							temp = warm[i];
							warm[i] = warm[(length - 1) - i];
							warm[(length - 1) - i] = temp;
						}
					}
					
					direction = Direction::Right;
				}
				else {
					for (i = length - 1; 0 < i; --i) {
						warm[i] = warm[i - 1];
					}
					OffsetRect(&warm[0], -BODY_SIZE, 0);
					if (warm[0].left < 0) { // 머리가 왼쪽 벽을 넘어가면 0 으로 재조정해준다
						warm[0].left = 0;
						warm[0].right = warm[0].left+BODY_SIZE;
					}
				}

				break;
			case Direction::Right:
				if (rectView.right <= warm[0].right) {
					if (length != 1) {
						for (i = 0; i < length / 2; i++) {
							temp = warm[i];
							warm[i] = warm[(length - 1) - i];
							warm[(length - 1) - i] = temp;
						}
					}
					
					direction = Direction::Left;
				}
				else {
					for (i = length - 1; 0 < i; --i) {
						warm[i] = warm[i - 1];
					}
					OffsetRect(&warm[0], BODY_SIZE, 0);
					if (rectView.right < warm[0].right) {
						warm[0].right = rectView.right;
						warm[0].left = warm[0].right - BODY_SIZE;
					}

				}
				break;
			}


			////////////////////////////////////////////////////////////
			break;
		case 2: // 타이머 2를 죽인후 적 애벌레 타이머를 불러온다
			KillTimer(hWnd, 2);
			enemy_created = S_ON;
			SetTimer(hWnd, 3, E_SPEED, NULL); // 적 애벌레가 생성된다
			break;
		case 3: // 적 애벌레가 네놈을 추격하는 부분
			for (i = e_length - 1; 0 < i; --i) {
				enemy_warm[i] = enemy_warm[i - 1];
			}
			if (enemy_warm[0].left < warm[0].left) {
				OffsetRect(&enemy_warm[0], BODY_SIZE, 0);
				e_direction = Direction::Right;
			}// 적보다 내가 오른쪽에 있다!

			if (warm[0].left < enemy_warm[0].left) {
				OffsetRect(&enemy_warm[0], -BODY_SIZE, 0);
				e_direction = Direction::Left;

			}// 적보다 내가 왼쪽에 있다!
			if (enemy_warm[0].top < warm[0].top) {
				OffsetRect(&enemy_warm[0], 0, BODY_SIZE);
				e_direction = Direction::Down;
			}// 적보다 내가 아래쪽에 있다!

			if (warm[0].top <enemy_warm[0].top) {
				OffsetRect(&enemy_warm[0], 0, -BODY_SIZE);
				e_direction = Direction::Up;
			}// 적보다 내가 위쪽에 있다!
			break;
		case 4: // 먹이 생성

			if(gameon)
			{
			
				for (i = 0; i < 30; ++i) {
				
					if (food[i].exist == false) {
						x = rand() % rectView.right - ITEM_SIZE;
						y = rand() % rectView.bottom - ITEM_SIZE;
						food[i].exist = true;
						food[i].pos = { x,y,x + ITEM_SIZE,y + ITEM_SIZE };
						num_food++;
						break;
					}
				
				}
			
			
			}


			break;
		}

		InvalidateRect(hWnd, &rectView, FALSE);
		break;
		//////////////////////////////////////////////////////////////////////////////////////////
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == VK_UP) {
			direction = Direction::Up;
		}
		else if (wParam == VK_DOWN) {
			direction = Direction::Down;
		}
		else if (wParam == VK_LEFT) {
			direction = Direction::Left;
		}
		else if (wParam == VK_RIGHT) {
			direction = Direction::Right;
		}

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		if (wParam == '+') {
			if (MX_SPEED <= speed) {
				speed -= 10;
				KillTimer(hWnd, 1);
				SetTimer(hWnd, 1, speed, NULL); // 첫번쨰 애벌레의 속도
				SendMessage(hWnd, WM_TIMER, 1, 0);
			}
		}
		else if (wParam == '-') {
			if (speed <= MN_SPEED) {
				speed += 10;
				KillTimer(hWnd, 1);
				SetTimer(hWnd, 1, speed, NULL); // 첫번쨰 애벌레의 속도
				SendMessage(hWnd, WM_TIMER, 1, 0);
			}
		}
		else if (wParam == VK_SPACE && jumping.jump == 0) {
			jumping.jump = JUMP_POWER;
			jumping.direction = direction;
		}
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
									 /*   --------------     나 의 에 벌 레 ^ ^                 ------------   */
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hBrush[0] = CreateSolidBrush(RGB(255, 0, 0)); // 빨강
		

		switch (head_color) {
		case Color::magenta:
			hBrush[1] = CreateSolidBrush(RGB(255, 150, 255)); // 파랑
			hBrush[2] = CreateSolidBrush(RGB(255,0, 255)); // 헤드부분
			break;
		case Color::cyan:
			hBrush[1] = CreateSolidBrush(RGB(150, 255, 255)); // 파랑
			hBrush[2] = CreateSolidBrush(RGB(0, 255, 255)); // 헤드부분
			break;
		case Color::yellow:
			hBrush[1] = CreateSolidBrush(RGB(255, 255, 150)); // 파랑
			hBrush[2] = CreateSolidBrush(RGB(255, 255, 0)); // 헤드부분
			break;
		case Color::random:
			hBrush[1] = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)); // 파랑
			hBrush[2] = CreateSolidBrush(RGB(rand()%255, rand() % 255, rand() % 255)); // 헤드부분
			break;
			
		}
		
		hBrush[3] = CreateSolidBrush(RGB(255, 255 ,0)); // 초록

		
		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc); // hdc와 호환시킨다.
		HBITMAP Lay; // 레이어 생성
		Lay = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); // 다블 버퍼링 ,hdc와 호환시키자.
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &rectView, hbrBackground);
			SetBkMode(LayDC, TRANSPARENT);
			//////<여기다 그린다>//////////////////////////////////////////////////////////////////

			if (grid) {
				for (int i = 0; i < 40; ++i) {
					for (int j = 0; j < 40; ++j) {
						Rectangle(LayDC, j * 40, i * 40, (j + 1) * 40, (i + 1) * 40);
					}
				}
			}

			oldPen = (HPEN)SelectObject(LayDC, hPen); // 새로운 펜 사용 선언

			for (i = 0; i < WARM_LENGTH; ++i) {
				if (i<length) {
					if (i == 0) {
						oldBrush = (HBRUSH)SelectObject(LayDC, hBrush[2]);
					}
					else {
						oldBrush = (HBRUSH)SelectObject(LayDC, hBrush[1]);
					}

					if (i == 0) {
					
						switch (direction) {
						case Direction::Left:
						
							x1 = (warm[i].right - warm[i].left) / 2 * sin(PI*(270 + mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							x2 = (warm[i].right - warm[i].left) / 2 * sin(PI*(270 - mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							y1 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(270 + mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							y2 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(270 - mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							Pie(LayDC, warm[i].left, warm[i].top, warm[i].right, warm[i].bottom, x1, y1, x2, y2); // 머리를 그린다
							break;
						case Direction::Right:
							x1 = (warm[i].right - warm[i].left) / 2 *sin(PI*(90+mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							x2 = (warm[i].right - warm[i].left) / 2 *sin(PI*(90-mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							y1 = (warm[i].bottom - warm[i].top) / 2 *cos(PI*(90+mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							y2 = (warm[i].bottom - warm[i].top) / 2 *cos(PI*(90-mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							Pie(LayDC, warm[i].left, warm[i].top, warm[i].right, warm[i].bottom, x1, y1, x2, y2); // 머리를 그린다
							break;
						case Direction::Up:
							x1 = (warm[i].right - warm[i].left) / 2 * sin(PI*(mouseani*(MX_MOUSE + moremouth) + 180) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							x2 = (warm[i].right - warm[i].left) / 2 * sin(PI*(-mouseani*(MX_MOUSE + moremouth) + 180) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							y1 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(mouseani*(MX_MOUSE + moremouth) + 180) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							y2 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(-mouseani*(MX_MOUSE + moremouth) + 180) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							Pie(LayDC, warm[i].left, warm[i].top, warm[i].right, warm[i].bottom, x1, y1, x2, y2); // 머리를 그린다
							break;
						case Direction::Down:
							x1 = (warm[i].right - warm[i].left) / 2 * sin(PI*(mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							x2 = (warm[i].right - warm[i].left) / 2 * sin(PI*(-mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							y1 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							y2 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(-mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							Pie(LayDC, warm[i].left, warm[i].top, warm[i].right, warm[i].bottom, x1, y1, x2, y2); // 머리를 그린다
							break;


						}
					
					
					
					
					}
					
					else {
						Ellipse(LayDC, warm[i].left, warm[i].top, warm[i].right, warm[i].bottom); // 머리를 그린다
					}
					SelectObject(LayDC, oldBrush);
				}
			}
			oldBrush = (HBRUSH)SelectObject(LayDC, hBrush[3]);
			for (i = 0; i < MX_NUM_FOOD; ++i) {
				if (food[i].exist == true) {
					Ellipse(LayDC, food[i].pos.left, food[i].pos.top, food[i].pos.right, food[i].pos.bottom); // 머리를 그린다
				}
			}
			SelectObject(LayDC, oldBrush);

			oldBrush = (HBRUSH)SelectObject(LayDC, hBrush[0]);
			for (i = 0; i < MX_NUM_FOOD; ++i) {
				if (bomb[i].exist == true) {
					Rectangle(LayDC, bomb[i].pos.left, bomb[i].pos.top, bomb[i].pos.right, bomb[i].pos.bottom); // 머리를 그린다
				}
			}
			SelectObject(LayDC, oldBrush);

			/*   --------------     적 의 에 벌 레  - - !              ------------   */
			if (S_OFF<enemy_created) { // 적 생성 트리거가 발동했을때
				oldBrush = (HBRUSH)SelectObject(LayDC, hBrush[0]);
				for (i = 0; i < WARM_LENGTH; ++i) {
					if (enemy_warm[i].left != '\0') {
						if(i!=0)
						Ellipse(LayDC, enemy_warm[i].left, enemy_warm[i].top, enemy_warm[i].right, enemy_warm[i].bottom); // 머리를 그린다
						else {
							switch (e_direction) {
							
							case Direction::Left:

								x1 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(270 + mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								x2 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(270 - mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								y1 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(270 + mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								y2 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(270 - mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								Pie(LayDC, enemy_warm[i].left, enemy_warm[i].top, enemy_warm[i].right, enemy_warm[i].bottom, x1, y1, x2, y2); // 머리를 그린다
								break;
							case Direction::Right:
								x1 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(90 + mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								x2 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(90 - mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								y1 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(90 + mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								y2 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(90 - mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								Pie(LayDC, enemy_warm[i].left, enemy_warm[i].top, enemy_warm[i].right, enemy_warm[i].bottom, x1, y1, x2, y2); // 머리를 그린다
								break;
							case Direction::Up:
								x1 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(mouseani*MX_MOUSE + 180) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								x2 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(-mouseani*MX_MOUSE + 180) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								y1 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(mouseani*MX_MOUSE + 180) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								y2 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(-mouseani*MX_MOUSE + 180) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								Pie(LayDC, enemy_warm[i].left, enemy_warm[i].top, enemy_warm[i].right, enemy_warm[i].bottom, x1, y1, x2, y2); // 머리를 그린다
								break;
							case Direction::Down:
								x1 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								x2 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(-mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								y1 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								y2 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(-mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								Pie(LayDC, enemy_warm[i].left, enemy_warm[i].top, enemy_warm[i].right, enemy_warm[i].bottom, x1, y1, x2, y2); // 머리를 그린다
								break;
							
							
							
							
							
							
							}
						
						
						
						
						}
					}
				}

			}


			/*  ----------------------------------------------------------------------    */





			SelectObject(LayDC, oldBrush);
			SelectObject(LayDC, oldPen);
			DeleteObject(hBrush[0]);
			DeleteObject(hBrush[1]);
			DeleteObject(hBrush[2]);
			DeleteObject(hBrush[3]);
			DeleteObject(hPen);






			//////////////////////////////////////////////////////////////////////
			BitBlt(hdc, 0, 0, rectView.right,rectView.bottom, LayDC, 0, 0, SRCCOPY);
		}


		DeleteObject(Lay);
		DeleteObject(hdc);

		DeleteDC(LayDC);
		DeleteDC(hdc);




		

		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE: // 윈도우가 다시 그려질때
		GetClientRect(hWnd, &rectView);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_GAME_START:
			gameon = true;
			break;
		case ID_GAME_END:
			gameon = false;
			break;
		case ID_COLOR_CYAN:
			head_color = Color::cyan;
			break;
		case ID_COLOR_MAGENTA:
			head_color = Color::magenta;
			break;
		case ID_COLOR_YELLOW:
			head_color = Color::yellow;
			break;
		case ID_COLOR_RANDOM:
			head_color = Color::random;
			break;
		case ID_FOODBOMB_10:
			creating = true;
			num_food = 0;
			num_bomb = 0;

			for (i = 0; i < 30; ++i) {
				food[i] = { {0,0,0,0},false };
				bomb[i] = { { 0,0,0,0 },false };
			}
			

			for (i = 0; i <10; ++i) {
				x = rand() % rectView.right - ITEM_SIZE + 20;
				y = rand() % rectView.bottom - ITEM_SIZE + 20;
				food[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_food++;
			}
			for (i = 0; i <10; ++i) {
				x = rand() % rectView.right + 20;
				y = rand() % rectView.bottom + 20;
				bomb[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_bomb++;
			}

			creating = false;
			break;
		case ID_FOODBOMB_20:
			creating = true;
			num_food = 0;
			num_bomb = 0;

			for (i = 0; i < 30; ++i) {
				food[i] = { { 0,0,0,0 },false };
				bomb[i] = { { 0,0,0,0 },false };
			}

			for (i = 0; i <20; ++i) {
				x = rand() % rectView.right - ITEM_SIZE + 20;
				y = rand() % rectView.bottom - ITEM_SIZE + 20;
				food[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_food++;
			}
			for (i = 0; i <20; ++i) {
				x = rand() % rectView.right + 20;
				y = rand() % rectView.bottom + 20;
				bomb[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_bomb++;
			}

			creating = false;
			break;
		case ID_FOODBOMB_30:
			creating = true;
			num_food = 0;
			num_bomb = 0;

			for (i = 0; i < 30; ++i) {
				food[i] = { { 0,0,0,0 },false };
				bomb[i] = { { 0,0,0,0 },false };
			}

			for (i = 0; i < 30; ++i) {
				x = rand() % rectView.right - ITEM_SIZE;
				y = rand() % rectView.bottom - ITEM_SIZE;
				food[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_food++;
			}
			for (i = 0; i < 30; ++i) {
				x = rand() % rectView.right + 20;
				y = rand() % rectView.bottom + 20;
				bomb[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_bomb++;
			}

			creating = false;

			break;
		case ID_GRID_ON:
			grid = true;
			break;
		case ID_GRID_OFF:
			grid = false;
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}

