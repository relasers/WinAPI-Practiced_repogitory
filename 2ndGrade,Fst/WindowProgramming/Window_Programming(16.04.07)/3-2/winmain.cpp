//////////////////// 최고로 쓸모없는 3-2 코드 ///////////////////////////////

#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include<math.h> // 사인 라디안 값을 도출해낸다

#define PI 3.141592 // 파이값

#define MN_OBJECT_SIZE 5 // 움직이는 도형의 최소크기
#define MX_OBJECT_SIZE 10 // 움직이는 도형의 크기

#define CENTER_POINT 150 // 도형중점의 위치값
#define MX_FIELD_SIZE 70 //최대크기
#define MN_FIELD_SIZE 30 //최소크기

#define CLIENT_WIDTH 800 // 클라이언트 가로크기
#define CLIENT_HEIGHT 800 // 클라이언트 세로크기

#define SPEED 50 //  스핀의 속도

#define RADIAN_SPEED 4 // 움직이는 각도

#define S_OFF 0 // 스위치 꺼짐
#define S_ON 1 // 스위치 켜짐

typedef enum {
	Clock, RClock
}Direction; // 시계방향, 반시계방향

typedef enum {
RECTANGLE,TRIANGLE,ELLIPSE
}Shape_Type;

typedef enum {
	LZONE,TZONE,RZONE,BZONE 
}Zone; // 좌,상,우,하

typedef struct {
	int x;
	int y;
}Point; // 좌표 포인트

typedef struct {
	Point center_point;
	int size;
	double radian; // 각도
}Shape;

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 3-2"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
										 // L"문자열" 문자열 앞에 대문자 L을 붙인다 아니면 유니코드에서 멀티바이트로 바꾸던가
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);



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
	HDC hdc; // 항상 첫번째 인자는 hDC 다! 
	HBRUSH hBrush, oldBrush;

	static RECT rectView; // 창 크기를 저장하는 RECT 구조체
	int i; // 반복문 돌리게

/////////////////// 궤도 도형 데이터(배경도형)///////////////////////////////////////////////////////////////
	static Shape shape[4] = { { { CENTER_POINT ,CENTER_POINT },
		MN_FIELD_SIZE + rand() % MX_FIELD_SIZE ,0 },
		{ { 3 * CENTER_POINT ,CENTER_POINT },
		MN_FIELD_SIZE + rand() % MX_FIELD_SIZE ,0 },
		{ { CENTER_POINT ,3 * CENTER_POINT },
		MN_FIELD_SIZE + rand() % MX_FIELD_SIZE ,0 },
		{ { 3 * CENTER_POINT ,3 * CENTER_POINT },
		MN_FIELD_SIZE + rand() % MX_FIELD_SIZE ,0 }
	};
	static POINT triangle[4][3]; // 삼각형 그리기
	static RECT field_shape_draw[4];
	static int field_shape_type = Shape_Type::ELLIPSE; // 궤도의 도형 타입
 //////////////////움직이는 도형 데이터////////////////////////////////////////////////////////////////////////
	static Shape mov_shape[4] = {
		{ { shape[0].size*sin(mov_shape[0].radian) + shape[0].center_point.x , shape[0].size*cos(mov_shape[0].radian) + shape[0].center_point.y },
		MN_OBJECT_SIZE + rand() % MX_OBJECT_SIZE ,0 },
		{ { shape[1].size*sin(mov_shape[1].radian) + shape[1].center_point.x , shape[1].size*cos(mov_shape[1].radian) + shape[1].center_point.y },
		MN_OBJECT_SIZE + rand() % MX_OBJECT_SIZE ,0 },
		{ { shape[2].size*sin(mov_shape[2].radian) + shape[2].center_point.x , shape[2].size*cos(mov_shape[2].radian) + shape[2].center_point.y },
		MN_OBJECT_SIZE + rand() % MX_OBJECT_SIZE ,0 },
		{ { shape[3].size*sin(mov_shape[3].radian) + shape[3].center_point.x , shape[3].size*cos(mov_shape[3].radian) + shape[3].center_point.y },
		MN_OBJECT_SIZE + rand() % MX_OBJECT_SIZE ,0 }
	};
	static RECT mov_shape_draw[4];
	static int speed[4] = {3,5,7,9}; ////////////////////////////////<<<<<<<<<<<<<----- 스피드를 담당한다
	static int clockwork = Direction::Clock; // 공전방향 결정
	static int mov_shape_type = Shape_Type::ELLIPSE; // 공전도형 모양
	static int dir_check[4] = {
		Zone::TZONE,Zone::TZONE,Zone::TZONE,Zone::TZONE
	}; // 공전도형이 있는 위치
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_CREATE:
		for (i = 0; i < 4; ++i) {
			field_shape_draw[i] = {
				shape[i].center_point.x - shape[i].size,shape[i].center_point.y - shape[i].size,
				shape[i].center_point.x + shape[i].size,shape[i].center_point.y + shape[i].size
			};
		}
		for (i = 0; i < 4; ++i) {
			mov_shape_draw[i] = {
				mov_shape[i].center_point.x - mov_shape[i].size,mov_shape[i].center_point.y - mov_shape[i].size,
			mov_shape[i].center_point.x + mov_shape[i].size,mov_shape[i].center_point.y + mov_shape[i].size
			};
		}
		for (i = 0; i < 4; ++i) {
				triangle[i][0] = { field_shape_draw[i].left + shape[i].size , field_shape_draw[i].top };
				triangle[i][1] = { field_shape_draw[i].left, field_shape_draw[i].bottom};
				triangle[i][2] = { field_shape_draw[i].right , field_shape_draw[i].bottom };
			}
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView); // 윈도우 창 크기를 구해낸다.
		
		SetTimer(hWnd, 1, SPEED, NULL); // 소크도


		return 0;
		////////////////////////////////////////////////////////////////////////////////////
	case WM_TIMER:
			for (i = 0; i < 4; ++i) {
				switch (field_shape_type) {
				case Shape_Type::ELLIPSE:
					if (clockwork == Direction::Clock) {
						mov_shape[i].radian -= speed[i];
					}
					else {
						mov_shape[i].radian += speed[i];
					}
					mov_shape[i].center_point.x = shape[i].size*sin(PI*mov_shape[i].radian / 180.0) + shape[i].center_point.x;
					mov_shape[i].center_point.y = shape[i].size*cos(PI*mov_shape[i].radian / 180.0) + shape[i].center_point.y;
					break;
				case Shape_Type::RECTANGLE:
					if (clockwork == Direction::Clock) {
						if (dir_check[i] == Zone::TZONE) {
							mov_shape[i].center_point.x += speed[i];
							if (field_shape_draw[i].right - mov_shape[i].size <= mov_shape_draw[i].left) {
								mov_shape[i].center_point.x = field_shape_draw[i].right;
								dir_check[i] = Zone::RZONE;
							}
						}
						else if (dir_check[i] == Zone::RZONE) {
							mov_shape[i].center_point.y += speed[i];
							if (field_shape_draw[i].bottom - mov_shape[i].size <= mov_shape_draw[i].top) {
								mov_shape[i].center_point.y = field_shape_draw[i].bottom;
								dir_check[i] = Zone::BZONE;
							}
						}
						else if (dir_check[i] == Zone::BZONE) {
							mov_shape[i].center_point.x -= speed[i];
							if (mov_shape_draw[i].right - mov_shape[i].size <= field_shape_draw[i].left) {
								mov_shape[i].center_point.x = field_shape_draw[i].left;
								dir_check[i] = Zone::LZONE;
							}
						}
						else if (dir_check[i] == Zone::LZONE) {
							mov_shape[i].center_point.y -= speed[i];
							if (mov_shape_draw[i].top + mov_shape[i].size <= field_shape_draw[i].top) {
								mov_shape[i].center_point.y = field_shape_draw[i].top;
								dir_check[i] = Zone::TZONE;
							}
						}
					}
					else {
						if (dir_check[i] == Zone::TZONE) {
							mov_shape[i].center_point.x -= speed[i];
							if (mov_shape_draw[i].right - mov_shape[i].size <= field_shape_draw[i].left) {
								mov_shape[i].center_point.x = field_shape_draw[i].left;
								dir_check[i] = Zone::LZONE;
							}
						}
						else if (dir_check[i] == Zone::LZONE) {
							mov_shape[i].center_point.y += speed[i];
							if (field_shape_draw[i].bottom + mov_shape[i].size <= mov_shape_draw[i].bottom) {
								mov_shape[i].center_point.y = field_shape_draw[i].bottom;
								dir_check[i] = Zone::BZONE;
							}
						}
						else if (dir_check[i] == Zone::BZONE) {
							mov_shape[i].center_point.x += speed[i];
							if (field_shape_draw[i].right + mov_shape[i].size <= mov_shape_draw[i].right) {
								mov_shape[i].center_point.x = field_shape_draw[i].right;
								dir_check[i] = Zone::RZONE;
							}
						}
						else if (dir_check[i] == Zone::RZONE) {
							mov_shape[i].center_point.y -= speed[i];
							if (mov_shape_draw[i].top <= field_shape_draw[i].top - mov_shape[i].size) {
								mov_shape[i].center_point.y = field_shape_draw[i].top;
								dir_check[i] = Zone::TZONE;
							}
						}

					}
					break;
				case Shape_Type::TRIANGLE:
					if (clockwork == Direction::Clock) {
						if (dir_check[i] == Zone::RZONE) {
							mov_shape[i].center_point.y += speed[i]*2;
							mov_shape[i].center_point.x += speed[i];
							if (field_shape_draw[i].bottom - mov_shape[i].size <= mov_shape_draw[i].bottom ) {
								mov_shape[i].center_point.x = field_shape_draw[i].right;
								mov_shape[i].center_point.y = field_shape_draw[i].bottom;
								dir_check[i] = Zone::BZONE;
							}
						}
						else if (dir_check[i] == Zone::BZONE) {
							mov_shape[i].center_point.x -= speed[i];
							if (mov_shape_draw[i].right - mov_shape[i].size <= field_shape_draw[i].left ) {
								mov_shape[i].center_point.x = field_shape_draw[i].left;
								dir_check[i] = Zone::LZONE;
							}
						}
						else if (dir_check[i] == Zone::LZONE) {
							mov_shape[i].center_point.y -= speed[i]*2;
							mov_shape[i].center_point.x += speed[i];
							if (mov_shape_draw[i].top - mov_shape[i].size <= field_shape_draw[i].top ) {
								mov_shape[i].center_point.x = field_shape_draw[i].left + shape[i].size;
								mov_shape[i].center_point.y = field_shape_draw[i].top ;
								dir_check[i] = Zone::RZONE;
							}
						}
					}
					else {
						if (dir_check[i] == Zone::RZONE) {
							mov_shape[i].center_point.y -= speed[i] * 2;
							mov_shape[i].center_point.x -= speed[i];
							if (mov_shape_draw[i].top <= field_shape_draw[i].top - mov_shape[i].size) {
								mov_shape[i].center_point.x = field_shape_draw[i].left + shape[i].size;
								mov_shape[i].center_point.y = field_shape_draw[i].top;
								dir_check[i] = Zone::LZONE;
							}
						}
						else if (dir_check[i] == Zone::LZONE) {
							mov_shape[i].center_point.y += speed[i] * 2;
							mov_shape[i].center_point.x -= speed[i];
							if (field_shape_draw[i].bottom <= mov_shape_draw[i].bottom + mov_shape[i].size ) {
								mov_shape[i].center_point.x = field_shape_draw[i].left;
								mov_shape[i].center_point.y = field_shape_draw[i].bottom;
								dir_check[i] = Zone::BZONE;
							}
						}
						else if (dir_check[i] == Zone::BZONE) {
							mov_shape[i].center_point.x += speed[i];
							if (field_shape_draw[i].right <= mov_shape_draw[i].right - mov_shape[i].size) {
								mov_shape[i].center_point.x = field_shape_draw[i].right;
								dir_check[i] = Zone::RZONE;
							}
						}
						
					}


					break;
				}
				mov_shape_draw[i] = {
					mov_shape[i].center_point.x - mov_shape[i].size,
					mov_shape[i].center_point.y - mov_shape[i].size,
					mov_shape[i].center_point.x + mov_shape[i].size,
					mov_shape[i].center_point.y + mov_shape[i].size
				};
			}
			
		InvalidateRect(hWnd, &rectView, TRUE);
		break;
		//////////////////////////////////////////////////////////////////////////////////////////
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == 'c' || wParam == 'C') { // 공전방향을 바꾼다
			if (clockwork == Direction::Clock) {
				clockwork = Direction::RClock;
			}
			else {
				clockwork = Direction::Clock;
			}
		}
		else if (wParam == 'M' || wParam == 'm') { // 공전도형 모양을 바꾼다
			if (mov_shape_type == Shape_Type::ELLIPSE) {
				mov_shape_type = Shape_Type::RECTANGLE;
			}
			else {
				mov_shape_type = Shape_Type::ELLIPSE;
			}
		}
		else if (wParam == 'T' || wParam == 't') {
			if (field_shape_type != Shape_Type::TRIANGLE) {
				field_shape_type = Shape_Type::TRIANGLE;
			}
			for (i = 0; i < 4; ++i) {
				mov_shape[i].center_point.x = field_shape_draw[i].right;
				mov_shape[i].center_point.y = field_shape_draw[i].bottom;
				dir_check[i] = Zone::BZONE;
			}
		}
		else if (wParam == 'R' || wParam == 'r') {
			if (field_shape_type != Shape_Type::RECTANGLE) {
				field_shape_type = Shape_Type::RECTANGLE;
				for (i = 0; i < 4; ++i) {
					mov_shape[i].center_point.x = field_shape_draw[i].left;
					mov_shape[i].center_point.y = field_shape_draw[i].top;
					dir_check[i] = Zone::TZONE;
				}
	
			}
		}
		else if (wParam == 'E' || wParam == 'e') {
			if (field_shape_type != Shape_Type::ELLIPSE) {
				field_shape_type = Shape_Type::ELLIPSE;
				for (i = 0; i < 4; ++i) {
					mov_shape[i].center_point.x = shape[i].size*sin(PI*mov_shape[i].radian / 180.0) + shape[i].center_point.x;
					mov_shape[i].center_point.y = shape[i].size*cos(PI*mov_shape[i].radian / 180.0) + shape[i].center_point.y;
				}
			}
		}
		else if (wParam == 'Q' || wParam == 'q') { // 프로그램을 종료한다
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			return 0;
		}
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
		
		////////////////////////////// 궤도를 그린다 /////////////////////////////////////////
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		switch (field_shape_type) {
		case Shape_Type::ELLIPSE:
			for (i = 0; i < 4; ++i) {
				Ellipse(hdc, field_shape_draw[i].left, field_shape_draw[i].top, field_shape_draw[i].right, field_shape_draw[i].bottom);
			}
			break;
		case Shape_Type::RECTANGLE:
			for (i = 0; i < 4; ++i) {
				Rectangle(hdc, field_shape_draw[i].left, field_shape_draw[i].top, field_shape_draw[i].right, field_shape_draw[i].bottom);
			}
			break;
		case Shape_Type::TRIANGLE:
			for (i = 0; i < 4; ++i) {
				Polygon(hdc,triangle[i],3);
			}
			break;
		}	
		//////////////////////////////움직이는 도형을 그린다////////////////////////////////
		switch (mov_shape_type) {
		case Shape_Type::ELLIPSE:
			for (i = 0; i < 4; ++i) {
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Ellipse(hdc, mov_shape_draw[i].left, mov_shape_draw[i].top, mov_shape_draw[i].right, mov_shape_draw[i].bottom);
				SelectObject(hdc, oldBrush);
			}
			break;
		case Shape_Type::RECTANGLE:
			for (i = 0; i < 4; ++i) {
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, mov_shape_draw[i].left, mov_shape_draw[i].top, mov_shape_draw[i].right, mov_shape_draw[i].bottom);
				SelectObject(hdc, oldBrush);
			}
			break;
		}
		/////////////////////////////////////////////////////////////
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		///////////////////////////////////////////////오브젝트들을 지운다////////////////////
		EndPaint(hWnd, &ps);

		break;
	case WM_SIZE: // 윈도우가 다시 그려질때
		GetClientRect(hWnd, &rectView);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}

