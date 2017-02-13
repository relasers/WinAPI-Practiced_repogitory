#include<Windows.h>
#include<Tchar.h> 
HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 2-6"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
										  // L"문자열" 문자열 앞에 대문자 L을 붙인다 아니면 유니코드에서 멀티바이트로 바꾸던가
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);

#define NUMBER_OF_LINE 10
#define NUMBER_OF_CHAR_ONE_LINE 99


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
	SIZE size;
	wchar_t temp_array[NUMBER_OF_CHAR_ONE_LINE] = { 0 };
	static wchar_t string[NUMBER_OF_LINE][NUMBER_OF_CHAR_ONE_LINE] = { 0 };
	static int count, yPos;
	int i, j, k,l;
	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd); // 빈 화면에 캐럿 표시
		count = 0; // 카운트 0으로 초기화
		yPos = 0;
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
		else { //  그 외
				if (count == NUMBER_OF_CHAR_ONE_LINE - 1) {
					if (!(yPos == NUMBER_OF_LINE - 1))
						yPos++;
					count = 0;
				}
				if (yPos <= NUMBER_OF_LINE - 1) {
					if ('0' <= wParam && wParam <= '9'&&count==0) {
						if (yPos < NUMBER_OF_LINE - 1) {
							string[yPos][count++] = wParam;
							string[yPos][count] = '\0';
							yPos++;
							count = 0;
						}
						else {
							string[yPos][count++] = wParam;
							string[yPos][count] = '\0';
						}
					}
					else {
						string[yPos][count++] = wParam;
						string[yPos][count] = '\0';
					}
					
				}

		}
		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 발생시킨다
		ReleaseDC(hWnd, hDC);
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (wParam == VK_HOME) { // 문제에선 R , 여기선 HOME 키 눌렀을때 서로 앞뒤가 바뀐다
			
			k = yPos; // 마지막 칸의 숫자를 첫번째 숫자와 맞바꾸기 위해 선언한다
			for (i = 0; i <= (yPos / 2); ++i) { // 맨 앞과 맨 뒤를 바꾸고 이후 2번째, 마지막 앞에거 바꾸고 ,,,,,
				for (j = 0; j<=NUMBER_OF_CHAR_ONE_LINE - 1; ++j) {
					temp_array[j] = '\0';
				}
				for (j = 0; j <= NUMBER_OF_CHAR_ONE_LINE - 1; ++j) {
					temp_array[j] = string[i][j];
				}
				for (j = 0; j <= NUMBER_OF_CHAR_ONE_LINE - 1; ++j) {
					string[i][j] = string[k][j];
				}
				for (j = 0; j <= NUMBER_OF_CHAR_ONE_LINE - 1; ++j) {
					string[k][j] = temp_array[j];
				}
				--k;
			}

			count = NUMBER_OF_CHAR_ONE_LINE + 1;
			while (string[yPos][count] == '\0') { count--; }; // 위에줄 마지막까지 찾아서 그자리로 간다.
			
			


			/*
			if ((yPos < NUMBER_OF_LINE - 1 ) && count!=0 ) {
				
				string[yPos][count++] = ' ';
				string[yPos][count] = '\0';
				yPos++;
				count = 0;
			}
			*/
			InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 메세지 강제 
		}
		else if (wParam ==	VK_END) { // 문제에선 Q , 여기선 END 키 눌렀을때
			HideCaret(hWnd);
			DestroyCaret();
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때, 화면이 깨졌을때 OS에서 메세지 전송 (처음 생성, 다른 윈도우 가려져있다가 다시 보일 때, 창 크기 바뀔때InvalidateRect(), InvalidateRgn()함수를 호출하여 강제로 화면을 무효화시킬 때)
		hDC = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)

		SetTextColor(hDC, RGB(0, 0, 240));

		for (j = 0; string[yPos][j] != '\0'; ++j) {
			temp_array[j] = string[yPos][j];
		}

		for (i = 0; i < NUMBER_OF_LINE; ++i) {
			if (string[i] == '\0')
				break;
			if('0' <= string[i][0] && string[i][0] <= '9')
				SetTextColor(hDC, RGB(255, 0, 0));
			else
				SetTextColor(hDC, RGB(0, 0, 0));
			GetTextExtentPoint(hDC, temp_array, wcslen(temp_array), &size); // 핸들, 측정할 문자, 몇번째까지 측정할건지, 구조체에 저장
			TextOut(hDC, 0, 20 * i, string[i], wcslen(string[i]));
			SetCaretPos(size.cx, (yPos)* 20);
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