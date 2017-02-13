#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 2-7"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
										 // L"문자열" 문자열 앞에 대문자 L을 붙인다 아니면 유니코드에서 멀티바이트로 바꾸던가
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);

#define NUMBER_OF_LINE 10
#define NUMBER_OF_CHAR_ONE_LINE 99
#define PDMODE_NUMBER_OF_LINE 99
#define PDMODE_NUMBER_OF_CHAR_ONE_LINE 11


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
	SIZE size;
	static wchar_t temp_array[NUMBER_OF_LINE][NUMBER_OF_CHAR_ONE_LINE] = { 0 }; //  
	static wchar_t temp_array_for_cerat[NUMBER_OF_CHAR_ONE_LINE] = { 0 }; // 캐럿 위치 계산용
	static wchar_t string[NUMBER_OF_LINE][NUMBER_OF_CHAR_ONE_LINE] = { 0 };
	static wchar_t page_down_string[PDMODE_NUMBER_OF_LINE][PDMODE_NUMBER_OF_CHAR_ONE_LINE] = { 0 }; // 페이지 다운 표기위한 배열
	static wchar_t temp_page_down_string[PDMODE_NUMBER_OF_LINE][PDMODE_NUMBER_OF_CHAR_ONE_LINE] = { 0 }; // 페이지 다운 표기위한 배열
	static int count, yPos;
	static int secret_mode,page_down_mode; // F1 키 눌렀을때 * 표시로 바뀌는걸 표현하기 위한 트리거 변수, 한줄에 10개 문자만 입력하는 트리거 변수
	static int x, y, pd_caret; // page-down 모드 삽입용
	int i, j;
	srand((unsigned)time(NULL));

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd); // 빈 화면에 캐럿 표시
		count = 0; // 카운트 0으로 초기화
		yPos = 0;
		pd_caret = 0;
		secret_mode = 0;
		page_down_mode = 0;
		x = 0, y = 0;
		return 0;

	case WM_CHAR:
		hDC = GetDC(hWnd);
		if (wParam == VK_BACK) { // 백스페이스 키 눌렀을경우
			if (count == 0) {
				if (0 < yPos) {
					--yPos;
					count = NUMBER_OF_CHAR_ONE_LINE + 1;
					while (string[yPos][count] == '\0') { count--; }; // 위에줄 마지막까지 찾아서 그자리로 간다.
				}
			}
			else 
				count--;
			
			for (i = 0; i <= count; ++i) { // 맨 앞에서부터 삭제한다
				string[yPos][i] = string[yPos][i + 1];
			}
			string[yPos][i] = '\0';
			string[yPos][count] = '\0';
		}

		else if (wParam == VK_RETURN) // 엔터 눌렸을때
		{
			if (yPos < NUMBER_OF_LINE - 1) {
				string[yPos][count++] = ' ';
				string[yPos][count] = '\0';
				yPos++;
				count = 0;
			}
		}
		else if (wParam == VK_ESCAPE) { // esc 눌렀을때
			yPos = 0;
			count = 0;
			for (i = 0; i < NUMBER_OF_LINE; ++i) {
				for (j = 0; j < NUMBER_OF_CHAR_ONE_LINE; ++j) {
					string[i][j] = '\0'; //NULL로 초기화
				}
			}
		}
		else if (wParam == VK_TAB) {
			for (i = 0; i < 4; ++i) {
				if (count == NUMBER_OF_CHAR_ONE_LINE - 1) {
					if (!(yPos == NUMBER_OF_LINE - 1))
						yPos++;
					count = 0;
				}
				if (yPos <= NUMBER_OF_LINE - 1) {
					string[yPos][count++] = ' ';
					string[yPos][count] = '\0';
				}
			}
		}
		
		else {
			if (count == NUMBER_OF_CHAR_ONE_LINE - 1) {
				if (!(yPos == NUMBER_OF_LINE - 1))
					yPos++;
				count = 0;
			}
			if (yPos <= NUMBER_OF_LINE - 1) {
				string[yPos][count++] = wParam;
				string[yPos][count] = '\0';
			}
		}

		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 발생시킨다
		ReleaseDC(hWnd, hDC);
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (wParam == VK_HOME) { // Home 키 눌렀을때, 랜덤한 위치에서 입력을 시작한다.
			yPos = rand() % NUMBER_OF_LINE;
			count = rand() % NUMBER_OF_CHAR_ONE_LINE;
			for (i = 0; i <= yPos; ++i) {
				for (j = 0; j <= count; ++j) {
					if (string[i][j] == '\0')
						string[i][j] = ' ';
				}
			}

			InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 
		}
		else if (wParam == VK_CONTROL) { //ctrl 눌렀을때 대문자는 소문자로, 소문자는 대문자로 바꿔서 출력한다.
			for (i = 0; i <= yPos; ++i) {
				for (j = 0; j <= NUMBER_OF_CHAR_ONE_LINE - 1; ++j) {
					if (97 <= string[i][j] && string[i][j] <= 122)
						string[i][j] -= 32; // a~z 사이일시 32를 빼서 A~Z 로 만든다 (ASCII CODE)
					else if (65 <= string[i][j] && string[i][j] <= 90)
						string[i][j] += 32; // A~Z 사이일시 32를 더해 a~z 로 만든다 (ASCII CODE)
				}
			}
			InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 
		}
		else if (wParam == VK_F1) { // F1 스위치 전환
			if (secret_mode == 0) {
				secret_mode = 1;
				InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 
			}
			else {
				secret_mode = 0;
				InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 
			}
		}
		else if (wParam == VK_NEXT) { // Page-down Key 눌렀을때
			if (page_down_mode == 0) {
				page_down_mode = 1;
				InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 
			}
			else {
				page_down_mode = 0;
				InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 
			}
		}
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때, 화면이 깨졌을때 OS에서 메세지 전송 (처음 생성, 다른 윈도우 가려져있다가 다시 보일 때, 창 크기 바뀔때InvalidateRect(), InvalidateRgn()함수를 호출하여 강제로 화면을 무효화시킬 때)
		hDC = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)

		SetTextColor(hDC, RGB(0, 0, 240));
		///////////그리기 전 초기화/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (j = 0; j<NUMBER_OF_CHAR_ONE_LINE; ++j) {
			temp_array_for_cerat[j] = '\0';
		}
		for (i = 0; i < NUMBER_OF_LINE; ++i) {
			for (j = 0; j < NUMBER_OF_CHAR_ONE_LINE; ++j) {
				temp_array[i][j] = '\0';
			}
		}
		for (i = 0; i < PDMODE_NUMBER_OF_LINE; ++i) {
			for (j = 0; j < PDMODE_NUMBER_OF_CHAR_ONE_LINE; ++j) {
				page_down_string[i][j] = '\0';
			}	
		}
		for (i = 0; i < PDMODE_NUMBER_OF_LINE; ++i) {
			for (j = 0; j < PDMODE_NUMBER_OF_CHAR_ONE_LINE; ++j) {
				temp_page_down_string[i][j] = '\0';
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (page_down_mode == 1) {
			x = 0, y = 0, pd_caret = 0;
			for (i = 0; i < NUMBER_OF_LINE; ++i) {
				for (j = 0; string[i][j] != '\0'; ++j) {
					page_down_string[y][x] = string[i][j];
					++x;
					if (!(x < PDMODE_NUMBER_OF_CHAR_ONE_LINE-1)) {
						y++;
						x=0;
					}
				}
			}
			for (j = 0; page_down_string[y][j] != '\0'; ++j) {
				temp_array_for_cerat[j] = page_down_string[y][j];
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (secret_mode == 1) { //별표로 바꾸는 동작
			if (page_down_mode == 0) {
				for (i = 0; i < NUMBER_OF_LINE; ++i) {
					for (j = 0; string[i][j] != '\0'; ++j) {
						if (('a' <= string[i][j] && string[i][j] <= 'z') || ('A' <= string[i][j] && string[i][j] <= 'Z') || ('0' <= string[i][j] && string[i][j] <= '9'))
							temp_array[i][j] = '*';
						else
							temp_array[i][j] = ' ';
					}
				}
				for (j = 0; string[yPos][j] != '\0'; ++j) {
					temp_array_for_cerat[j] = temp_array[yPos][j];
				}
			}
			else {
				for (i = 0; i < PDMODE_NUMBER_OF_LINE; ++i) {
					for (j = 0; page_down_string[i][j] != '\0'; ++j) {
						if (('a' <= page_down_string[i][j] && page_down_string[i][j] <= 'z') || ('A' <= page_down_string[i][j] && page_down_string[i][j] <= 'Z') || ('0' <= page_down_string[i][j] && page_down_string[i][j] <= '9'))
							temp_page_down_string[i][j] = '*';
						else
							temp_page_down_string[i][j] = ' ';
					}
				}
				for (j = 0; page_down_string[y][j] != '\0'; ++j) {
					temp_array_for_cerat[j] = temp_page_down_string[y][j];
				}
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (page_down_mode == 0 && secret_mode == 0) { // 모드 두개 둘다 켜지 않았다면
			for (j = 0; string[yPos][j] != '\0'; ++j) {
				temp_array_for_cerat[j] = string[yPos][j];
			}
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (page_down_mode == 1) {
			for (i = 0; i < PDMODE_NUMBER_OF_LINE; ++i) {
				if (string[i] == '\0')
					break;
				if (secret_mode == 1) {
					GetTextExtentPoint(hDC, temp_array_for_cerat, wcslen(temp_array_for_cerat), &size); // 핸들, 측정할 문자, 몇번째까지 측정할건지, 구조체에 저장
					TextOut(hDC, 0, 20 * i, temp_page_down_string[i], wcslen(temp_page_down_string[i]));
					SetCaretPos(size.cx, (y) * 20);
				}
				else {
					GetTextExtentPoint(hDC, temp_array_for_cerat, wcslen(temp_array_for_cerat), &size); // 핸들, 측정할 문자, 몇번째까지 측정할건지, 구조체에 저장
					TextOut(hDC, 0, 20 * i, page_down_string[i], wcslen(page_down_string[i]));
					SetCaretPos(size.cx, (y) * 20);
				}
				
			}
		}
		else {
			for (i = 0; i < NUMBER_OF_LINE; ++i) {
				if (string[i] == '\0')
					break;
				if (secret_mode == 1) {
					GetTextExtentPoint(hDC, temp_array_for_cerat, wcslen(temp_array_for_cerat), &size); // 핸들, 측정할 문자, 몇번째까지 측정할건지, 구조체에 저장
					TextOut(hDC, 0, 20 * i, temp_array[i], wcslen(temp_array[i]));
					SetCaretPos(size.cx, (yPos)* 20);
				}
				else {
					GetTextExtentPoint(hDC, temp_array_for_cerat, wcslen(temp_array_for_cerat), &size); // 핸들, 측정할 문자, 몇번째까지 측정할건지, 구조체에 저장
					TextOut(hDC, 0, 20 * i, string[i], wcslen(string[i]));
					SetCaretPos(size.cx, (yPos)* 20);
				}
			}
		}

		// strlen(temp) 는 멀티바이트에서만 지원한다
		// 유니코드에서 쓸수있는 함수는 wcslen 이 있다!!!
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}