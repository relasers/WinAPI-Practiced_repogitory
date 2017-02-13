#include<Windows.h>
#include<Tchar.h> 
#include<time.h>

#define NUMBER_OF_SHAPE 5 // 도형 수
#define MAX_SIZE 200 // 최대 사이즈
#define MAX_RANDOM_POSIT 100 // 최대 위치 값
#define SELECTED_SHAPE_LINE_SIZE 50 // 선택된 도형 선 굵기
typedef struct {
	int shape_type; // 1 -> 원 , 2 -> 삼각형 , 3 -> 사각형
	int left;
	int top;
	int right;
	int bottom;
	int tri_point_x; // 삼각형 그리기 x 좌표
	int tri_point_y; // 삼각형 그리기 y 좌표
}Draw_Shape;


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 2-10"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
										 // L"문자열" 문자열 앞에 대문자 L을 붙인다 아니면 유니코드에서 멀티바이트로 바꾸던가
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);

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
		800, // 윈도우 가로크기
		800, //윈도우 세로크기
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {

	
	PAINTSTRUCT ps;
	HDC hdc; // 항상 첫번째 인자는 hDC 다! 
	static HBRUSH hBrush, oldBrush;
	static HPEN hPen, oldPen;
	static POINT point[3] = { 0 };
	static Draw_Shape shape_info[NUMBER_OF_SHAPE] = 
	{ { 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },
	};
	srand((unsigned)time(NULL)+ GetCurrentProcessId());
	static wchar_t temp[40] = { 0 }; // 몇 번째 도형을 선택했는지 보여주는 문자열
	static int i, j;
	static int number_of_data; // 지금까지 그려진 도형의 수
	static int next_draw;
	static int select_shape;
	static int data_cycle;

	//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다
	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_CREATE:
		next_draw = 0;
		number_of_data = 0;
		data_cycle = 0; // 자리 다 차면 다시 첫번째 도형자리에 덮어쓴다
		return 0;
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == VK_DELETE) {
			if ((1 <= select_shape && select_shape <= 5)&& (shape_info[select_shape-1].shape_type != 0)) {
				shape_info[select_shape-1] = {0,0,0,0,0,0,0};
				number_of_data--;
			}
		}
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:

		hdc = GetDC(hWnd);
		if (number_of_data < NUMBER_OF_SHAPE) {
			for (i = 0; i < NUMBER_OF_SHAPE; ++i) {
				if (shape_info[i].shape_type == 0) {
					next_draw = i;
					break;
				}
			}
		}
		else {
			next_draw = data_cycle % NUMBER_OF_SHAPE;
		}

		if (wParam == 'E' || wParam == 'e') {
			shape_info[next_draw] = {
				1,
				rand() % MAX_RANDOM_POSIT,
				rand() % MAX_RANDOM_POSIT,
				MAX_RANDOM_POSIT + rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				MAX_RANDOM_POSIT + rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				0,0
			};
			if (number_of_data < NUMBER_OF_SHAPE) {
				number_of_data++;
				data_cycle = 0;
			}
			else
				data_cycle++;
		}
		else if (wParam == 'T' || wParam == 't') {
			shape_info[next_draw] = {
				2,
				rand() % MAX_RANDOM_POSIT,
				rand() % MAX_RANDOM_POSIT,
				rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				rand() % MAX_RANDOM_POSIT,
				MAX_RANDOM_POSIT + rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
			};
			if (number_of_data < NUMBER_OF_SHAPE) {
				number_of_data++;
				data_cycle = 0;
			}
			else
				data_cycle++;
		}
		else if (wParam == 'R' || wParam == 'r') {
			shape_info[next_draw] = {
				3,
				rand() % MAX_RANDOM_POSIT,
				rand() % MAX_RANDOM_POSIT,
				MAX_RANDOM_POSIT + rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				MAX_RANDOM_POSIT + rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				0,0
			};
			if (number_of_data < NUMBER_OF_SHAPE) {
				number_of_data++;
				data_cycle = 0;
			}
			else
				data_cycle++;
		}
		else if ('0' <= wParam && wParam <= '9') {
			select_shape = wParam-48; // ascii 코드 고려해서 수치변환
		}

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)

		if (1 <= select_shape && select_shape <= 5) {
			wsprintf(temp,TEXT("당신은 %d 번째 도형을 선택했따"),select_shape);
			TextOut(hdc,0,0,temp,wcslen(temp));
			if (shape_info[select_shape-1].shape_type == 0) {
				wsprintf(temp, TEXT("근데 그 도형은 없거나 사라진거 같네."));
				TextOut(hdc, 0, 20, temp, wcslen(temp));
			}
		}

		for (i = 0; i < NUMBER_OF_SHAPE; ++i) {
			if (shape_info[i].shape_type == 1) { // 원 그리기
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				if (select_shape - 1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 사용 선언
				}
				Ellipse(hdc,shape_info[i].left, shape_info[i].top, shape_info[i].right, shape_info[i].bottom);
			}
			else if (shape_info[i].shape_type == 2) { // 삼각형 그리기
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				point[0] = { shape_info[i].left , shape_info[i].top };
				point[1] = { shape_info[i].right , shape_info[i].bottom };
				point[2] = { shape_info[i].tri_point_x , shape_info[i].tri_point_y };
				if (select_shape-1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 사용 선언
				}
				Polygon(hdc,point,3);
			}
			else if (shape_info[i].shape_type == 3) { // 사각형 그리기
				hBrush = CreateSolidBrush(RGB(rand()%255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				if (select_shape - 1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 사용 선언
				}
				Rectangle(hdc, shape_info[i].left, shape_info[i].top, shape_info[i].right, shape_info[i].bottom);
			}

			SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
			DeleteObject(hPen);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}



