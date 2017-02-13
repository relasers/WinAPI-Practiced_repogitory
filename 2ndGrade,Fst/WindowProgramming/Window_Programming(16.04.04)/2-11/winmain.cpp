#include<Windows.h>
#include<Tchar.h> 
#include<time.h>

#define NUMBER_OF_SHAPE 5 // 도형 수
#define RACTANGLE_FIELD_AREA 40 // 보드 한칸 크기
#define SHAPE_SIZE 20 // 도형 사이즈
#define MAX_SIZE 16 // 최대 배율
#define SELECTED_SHAPE_LINE_SIZE 5 // 선택된 도형 선 굵기
#define SMALLER_THAN_BOARD_GRID 2 // 보드보다 쪼까 작게 그린다

typedef struct {
	int shape_type; // 1 -> 원 , 2 -> 삼각형 , 3 -> 사각형
	int left;
	int top;
	int right;
	int bottom;
	int tri_point_x; // 삼각형 그리기 x 좌표
	int tri_point_y; // 삼각형 그리기 y 좌표
	int x;
	int y;
	int size;
}Draw_Shape;


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 2-8"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
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
		1200, // 윈도우 가로크기
		850, //윈도우 세로크기
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

	srand((unsigned)time(NULL));
	PAINTSTRUCT ps;
	HDC hdc; // 항상 첫번째 인자는 hDC 다! 
	HBRUSH hBrush, oldBrush;

	static HPEN hPen, oldPen;
	static POINT point[3] = { 0 };
	static Draw_Shape shape_info[NUMBER_OF_SHAPE] =
	{ { 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	};


	wchar_t temp[40] = { 0 };
	static int i, j;
	static int x, y;
	static int ispush, shape_mode;
	static int size;
	static int number_of_data; // 지금까지 그려진 도형의 수
	static int next_draw;
	static int select_shape;
	static int data_cycle;

	srand((unsigned)time(NULL));
	//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_CREATE:
		ispush = 0; // 키가 눌러진 상태인지 확인
		shape_mode = 0; // 도형 모양 결정
		size = 1;
		break;
	case WM_KEYDOWN:
		if (wParam == VK_DELETE) {
			if ((1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0)) {
				shape_info[select_shape - 1] = { 0,0,0,0,0,0,0 };
				number_of_data--;
			}
		}
		else if (wParam == VK_LEFT) {
			if (ispush == 0 && (1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0) ) {
				if (0 < shape_info[select_shape - 1].x)
					--shape_info[select_shape - 1].x;
				else
					shape_info[select_shape - 1].x = RACTANGLE_FIELD_AREA - 1 * shape_info[select_shape - 1].size;
			}
		}
		else if (wParam == VK_RIGHT) {
			if (ispush == 0 && (1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0)) {
				if (shape_info[select_shape - 1].x < RACTANGLE_FIELD_AREA - 1 * shape_info[select_shape - 1].size)
					++shape_info[select_shape - 1].x;
				else
					shape_info[select_shape - 1].x = 0;
			}
		}
		else if (wParam == VK_UP) {
			if (ispush == 0 && (1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0)) {
				if (0 < shape_info[select_shape - 1].y)
					--shape_info[select_shape - 1].y;
				else
					shape_info[select_shape - 1].y = RACTANGLE_FIELD_AREA - 1 * shape_info[select_shape - 1].size;
			}
		}
		else if (wParam == VK_DOWN) {
			if (ispush == 0 && (1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0)) {
				if (shape_info[select_shape - 1].y < RACTANGLE_FIELD_AREA - 1 * shape_info[select_shape - 1].size)
					++shape_info[select_shape - 1].y;
				else
					shape_info[select_shape - 1].y = 0;
			}
		}
		ispush = 1;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_KEYUP:
		ispush = 0;
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
				SMALLER_THAN_BOARD_GRID,
				SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				0,0,
				rand() % RACTANGLE_FIELD_AREA,
				rand() % RACTANGLE_FIELD_AREA,
				1
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
				SMALLER_THAN_BOARD_GRID,
				SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				SMALLER_THAN_BOARD_GRID,
				SMALLER_THAN_BOARD_GRID,
				rand() % RACTANGLE_FIELD_AREA,
				rand() % RACTANGLE_FIELD_AREA,
				1
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
				SMALLER_THAN_BOARD_GRID,
				SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				0,0,
				rand() % RACTANGLE_FIELD_AREA,
				rand() % RACTANGLE_FIELD_AREA,
				1
			};
			if (number_of_data < NUMBER_OF_SHAPE) {
				number_of_data++;
				data_cycle = 0;
			}
			else
				data_cycle++;
		}
		else if ('0' <= wParam && wParam <= '9') { // 1번부터 5번까지 중에서 선택한다.
			select_shape = wParam - 48; // ascii 코드 고려해서 수치변환
		}




		else if (wParam == '+' || wParam == '-' && (1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0)) {
			if (wParam == '+' && shape_info[select_shape - 1].size <= MAX_SIZE) {

				shape_info[select_shape - 1].size *= 2;

				if (shape_info[select_shape - 1].size <= 0) {
					shape_info[select_shape - 1].size = 1;
					//shape_info[select_shape - 1].x = rand() % RACTANGLE_FIELD_AREA;
					//shape_info[select_shape - 1].y = rand() % RACTANGLE_FIELD_AREA;
					shape_info[select_shape - 1].shape_type = rand() % 3+1;
				}
			}
			else if (wParam == '-') {
				if (shape_info[select_shape - 1].size <= 1) {
					shape_info[select_shape - 1].size = 0;
				}
				shape_info[select_shape - 1].size /= 2;
			}

			if (shape_info[select_shape - 1].y > RACTANGLE_FIELD_AREA-1 - 1 * shape_info[select_shape - 1].size)
				shape_info[select_shape - 1].y = 0;
			if (shape_info[select_shape - 1].x > RACTANGLE_FIELD_AREA-1 - 1 * shape_info[select_shape - 1].size)
				shape_info[select_shape - 1].x = 0;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)

		for (i = 0; i < RACTANGLE_FIELD_AREA; ++i) {
			for (j = 0; j < RACTANGLE_FIELD_AREA; ++j) {
				Rectangle(hdc, SHAPE_SIZE*i, SHAPE_SIZE*j, SHAPE_SIZE + SHAPE_SIZE*i, SHAPE_SIZE + SHAPE_SIZE*j);
			}
		} // 보드를 그린다
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (1 <= select_shape && select_shape <= 5) {
			wsprintf(temp, TEXT("당신은 %d 번째 도형을 선택했따"), select_shape);
			TextOut(hdc, RACTANGLE_FIELD_AREA*SHAPE_SIZE, 0, temp, wcslen(temp));
			if (shape_info[select_shape - 1].shape_type == 0 || shape_info[select_shape-1].size<1) {
				wsprintf(temp, TEXT("근데 그 도형은 없거나 사라진거 같네."));
				TextOut(hdc, RACTANGLE_FIELD_AREA*SHAPE_SIZE, 20, temp, wcslen(temp));
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (ispush == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		}
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (i = 0; i < NUMBER_OF_SHAPE; ++i) {
			if (shape_info[i].shape_type == 1 && 1 <= shape_info[i].size) { // 원 그리기
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				if (select_shape - 1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 사용 선언
				}
				Ellipse(hdc, 
					shape_info[i].left + shape_info[i].x*SHAPE_SIZE,
					shape_info[i].top + shape_info[i].y*SHAPE_SIZE,
					shape_info[i].right + shape_info[i].x*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size,
					shape_info[i].bottom + shape_info[i].y*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size);
			}
			////////////////////수정할것////////////////////////////////////
			else if (shape_info[i].shape_type == 2 && 1 <= shape_info[i].size) { // 삼각형 그리기
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				point[0] = { shape_info[i].left + shape_info[i].x*SHAPE_SIZE ,
					shape_info[i].top + shape_info[i].y*SHAPE_SIZE };

				point[1] = { shape_info[i].left + shape_info[i].x*SHAPE_SIZE  ,
					shape_info[i].bottom + shape_info[i].y*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size };

				point[2] = { shape_info[i].right + shape_info[i].x*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size ,
					shape_info[i].bottom + shape_info[i].y*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size };
				if (select_shape - 1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 사용 선언
				}
				Polygon(hdc, point, 3);
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (shape_info[i].shape_type == 3 && 1<=shape_info[i].size) { // 사각형 그리기
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				if (select_shape - 1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // 새로운 펜 사용 선언
				}
				Rectangle(hdc, 
					shape_info[i].left + shape_info[i].x*SHAPE_SIZE,
					shape_info[i].top + shape_info[i].y*SHAPE_SIZE,
					shape_info[i].right + shape_info[i].x*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size,
					shape_info[i].bottom + shape_info[i].y*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size);
			}

			SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
			DeleteObject(hPen);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}