#include<Windows.h>
#include<Tchar.h> 
HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
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
		600, //윈도우 세로크기
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
	HDC hDC; // 항상 첫번째 인자는 hDC 다! 
	RECT rect; // 사각형 구조체 선언
	//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_PAINT: //윈도우 다시 그려줘야 할 때, 화면이 깨졌을때 OS에서 메세지 전송 (처음 생성, 다른 윈도우 가려져있다가 다시 보일 때, 창 크기 바뀔때InvalidateRect(), InvalidateRgn()함수를 호출하여 강제로 화면을 무효화시킬 때)
		hDC = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
		rect.left = 0; // 사각형 정의
		rect.top = 0;
		rect.right = 780;  // 왜 줄였나 -> 문자열 기니까 잘림
		rect.bottom = 560; // 왜 줄였나 -> 윈도우 생성때 크기가 타이틀바 포함이라서 이거 안줄이면 잘려
		SetTextColor(hDC, RGB(77, 255, 240));
		SetBkColor(hDC, RGB(178, 0, 15));
		DrawText(hDC, L"LeftTop (0, 0)", -1, &rect, DT_SINGLELINE | DT_TOP | DT_LEFT); // 3번째 인자 -1 : NULL 값이 나올때까지로 길이를 정한다는거
		SetTextColor(hDC, RGB(0, 255, 104));
		SetBkColor(hDC, RGB(255, 0, 151));
		DrawText(hDC, L"RightTop (800, 0)", -1, &rect, DT_SINGLELINE | DT_TOP | DT_RIGHT );
		SetTextColor(hDC, RGB(0, 0, 255));
		SetBkColor(hDC, RGB(255, 255, 0));
		DrawText(hDC, L"Center (300, 400)", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		SetTextColor(hDC, RGB(255, 85, 0));
		SetBkColor(hDC, RGB(0, 175, 255));
		DrawText(hDC, L"LeftBottom (0, 800)", -1, &rect, DT_SINGLELINE | DT_BOTTOM | DT_LEFT);
		SetTextColor(hDC, RGB(0,0,178));
		SetBkColor(hDC, RGB(255, 255, 77));
		DrawText(hDC, L"RightBottom (600, 800)", -1, &rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);
		// strlen(temp) 는 멀티바이트에서만 지원한다
		// 유니코드에서 쓸수있는 함수는 wcslen 이 있다!!!
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}