#include<Windows.h>
#include<Tchar.h> 
#include<time.h>

#define RACTANGLE_FIELD_AREA 4
#define RAC_SIZE 40
#define PLAY_RAC_SIZE 20
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

	srand((unsigned)time(NULL));
	PAINTSTRUCT ps;
	HDC hdc; // 항상 첫번째 인자는 hDC 다! 
	HBRUSH hBrush, oldBrush;

	wchar_t temp[40] = { 0 };
	static int i, j;
	static int x, y;
	static int ispush,shape_mode; 
	srand((unsigned)time(NULL));
	//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_CREATE:
		x = rand() % RACTANGLE_FIELD_AREA;
		y = rand() % RACTANGLE_FIELD_AREA;
		ispush = 0; // 키가 눌러진 상태인지 확인
		shape_mode = 0; // 도형 모양 결정
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			if (ispush == 0) {
				if (0 < x)
					--x;
				else
					x = RACTANGLE_FIELD_AREA - 1;
			}
		}
		else if (wParam == VK_RIGHT) {
			if (ispush == 0) {
				if (x < RACTANGLE_FIELD_AREA - 1)
					++x;
				else
					x = 0;
			}
		}
		else if (wParam == VK_UP) {
			if (ispush == 0) {
				if (0 < y)
					--y;
				else
					y = RACTANGLE_FIELD_AREA - 1;
			}
		}
		else if (wParam == VK_DOWN) {
			if (ispush == 0) {
			if (y < RACTANGLE_FIELD_AREA - 1)
				++y;
			else
				y = 0;
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
		if (wParam == 'R' || wParam == 'r') {
			if (shape_mode == 0)
				shape_mode = 1;
			else
				shape_mode = 0;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)

		for (i = 0; i < RACTANGLE_FIELD_AREA; ++i) {
			for (j = 0; j < RACTANGLE_FIELD_AREA; ++j) {
				Rectangle(hdc, RAC_SIZE*i, RAC_SIZE*j, RAC_SIZE + RAC_SIZE*i, RAC_SIZE + RAC_SIZE*j);
			}
		}
		if (ispush == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		}
		else {
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		}
		if (shape_mode == 0) {
			Rectangle(hdc, RAC_SIZE*x + 5, RAC_SIZE*y + 5, RAC_SIZE + RAC_SIZE*x - 5, RAC_SIZE + RAC_SIZE*y - 5);
		}
		else {
			Ellipse(hdc, RAC_SIZE*x + 5, RAC_SIZE*y + 5, RAC_SIZE + RAC_SIZE*x - 5, RAC_SIZE + RAC_SIZE*y - 5);
		}
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