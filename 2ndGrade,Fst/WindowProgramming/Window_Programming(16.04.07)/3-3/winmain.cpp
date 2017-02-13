//////////////////// 최고로 쓸모없는 3-2 코드 ///////////////////////////////

#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include<math.h> // 사인 라디안 값을 도출해낸다

#define T_LIGHT 50 // 신호등 사이즈
#define T_LIGHT_POSIT 150 // 산호등 위치

#define CLIENT_WIDTH 800 // 클라이언트 가로크기
#define CLIENT_HEIGHT 400 // 클라이언트 세로크기

#define CAR_SIZE 200
#define CAR_H_SIZE 40
#define CAR_INTERVAL 70
#define S_OFF 0 // 스위치 꺼짐
#define S_ON 1 // 스위치 켜짐

#define N_CAR 3 // 자동차 수

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 3-3"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
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
	HBRUSH hBrush[5], oldBrush;

	static RECT rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) }; // 창 크기를 저장하는 RECT 구조체
	static RECT traffic_light[3];
	static RECT car[N_CAR];
	static bool red_on = false;
	static bool yellow_on = false;
	static bool green_on = true;
	static wchar_t temp[2];
	int i; // 반복문 돌리게
	static int counter=0;
	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView); // 윈도우 창 크기를 구해낸다.
		for (i = 0; i < 3; ++i) {
			traffic_light[i] = { rectView.right - (3-i) * T_LIGHT,0,rectView.right - (2-i) * T_LIGHT,T_LIGHT };
			car[i] = {(i+1)*CAR_INTERVAL,(i+1)*CAR_INTERVAL,(i + 1)*CAR_INTERVAL+CAR_SIZE,(i + 1)*CAR_INTERVAL + CAR_H_SIZE };
		}

		SetTimer(hWnd, 1, 50, NULL); // 소크도
		return 0;
		////////////////////////////////////////////////////////////////////////////////////
	case WM_TIMER:
		switch (wParam) {
		case 1:
			if (green_on == true||yellow_on == true) {
				OffsetRect(&car[0], 10, 0);
				OffsetRect(&car[1], -20, 0);
				OffsetRect(&car[2], 30, 0);
			}
			for (i = 0; i < N_CAR; ++i) {
				if (rectView.right <= car[i].left) {
					car[i].left = 0;
					car[i].right = CAR_SIZE;
				}
				if (i == 1 && car[i].left <= 0) {
					car[i].left = rectView.right;
					car[i].right = rectView.right+CAR_SIZE;
				}
			}
			break;
		case 2:
			counter--;
			MessageBeep(MB_OK);
			if (counter == 0) {
				KillTimer(hWnd, 2);
				red_on = true;
				yellow_on = false;
				green_on = false;
			}
			break;
		}
		
		InvalidateRect(hWnd, &rectView, TRUE);
		break;
		//////////////////////////////////////////////////////////////////////////////////////////
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == 'B' || wParam == 'b') { // 파란불
			red_on = false;
			yellow_on = false;
			green_on = true;
		}
		else if (wParam == 'Y' || wParam == 'y') { // 노란불
			red_on = false;
			yellow_on = true;
			green_on = false;
			counter = 4;
			SetTimer(hWnd, 2, 1000, NULL);
			SendMessage(hWnd,WM_TIMER,2,NULL);
		}
		else if (wParam == 'R' || wParam == 'r') { // 빨간불
			red_on = true;
			yellow_on = false;
			green_on = false;
		}

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
		hBrush[0] = (HBRUSH)GetStockObject(NULL_BRUSH);
		hBrush[1] = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		hBrush[2] = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
		hBrush[3] = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
		hBrush[4] = (HBRUSH)CreateSolidBrush(RGB(20, 150, 255));

		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, traffic_light[0].left, traffic_light[0].top, traffic_light[2].right, traffic_light[2].bottom);
		for (i = 0; i < 3; ++i) {
			SelectObject(hdc, oldBrush);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[0]);
			if (i == 0 && red_on == true) {
				SelectObject(hdc, oldBrush);
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush[i + 1]);
			}
			if (i == 1 && yellow_on == true) {
				SelectObject(hdc, oldBrush);
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush[i + 1]);
				if (0 < counter) {
					wsprintf(temp,TEXT("%d..."),counter);
					DrawText(hdc,temp,-1,&rectView,DT_VCENTER|DT_CENTER);
				}
			}
			if (i == 2 && green_on == true) {
				SelectObject(hdc, oldBrush);
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush[i + 1]);
			}
			Ellipse(hdc, traffic_light[i].left,traffic_light[i].top, traffic_light[i].right, traffic_light[i].bottom);
			SelectObject(hdc, oldBrush);
		}

		for (i = 0; i < 3; ++i) {
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[4]);
			Rectangle(hdc, car[i].left, car[i].top, car[i].right, car[i].bottom);
			if (rectView.right <= car[i].right) {
				Rectangle(hdc, 0, car[i].top, car[i].right-rectView.right, car[i].bottom);
			}
			if (i == 1 && car[i].left <= 0) {
				Rectangle(hdc, car[i].right - rectView.right, car[i].top, rectView.right, car[i].bottom);
			}
			SelectObject(hdc, oldBrush);
		}

		///////////////////////////////////////////////오브젝트들을 지운다////////////////////
		DeleteObject(hBrush[0]);
		DeleteObject(hBrush[1]);
		DeleteObject(hBrush[2]);
		DeleteObject(hBrush[3]);
		DeleteObject(hBrush[4]);
		EndPaint(hWnd, &ps);

		break;
	case WM_SIZE: // 윈도우가 다시 그려질때
		GetClientRect(hWnd, &rectView);
		for (i = 0; i < 3; ++i) {
			traffic_light[i] = { rectView.right - (3 - i) * T_LIGHT,0,rectView.right - (2 - i) * T_LIGHT,T_LIGHT };
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}

