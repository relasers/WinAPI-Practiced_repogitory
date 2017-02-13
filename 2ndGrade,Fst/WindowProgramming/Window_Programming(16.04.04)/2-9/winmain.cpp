#include<Windows.h>
#include<Tchar.h> 
#include<time.h>

#define TEMP_ARR_SIZE 35 // 임시 문자열의 크기
#define NUMBER_OF_DATA 5 // 입력할 데이터 수
#define THICK_MAX 20 // 선 굵기 최대치
#define THICK_MIN 1 // 선 굵기 최소치
typedef struct {
	int shape_type;
	int left;
	int top;
	int right;
	int bottom;
}Draw_Shape;


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 2-9"; // 이게 빨간줄이 나오면 유니코드 문제때문에 그렇다
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

	srand((unsigned)time(NULL));
	PAINTSTRUCT ps;
	HDC hdc; // 항상 첫번째 인자는 hDC 다! 
	HPEN MyPen, OldPen;
	SIZE size;

	static Draw_Shape shape_info = { 0,0,0,0,0 };
	static wchar_t order[TEMP_ARR_SIZE] = { 0 }; // 명령어를 받는 배열
	static wchar_t temp[NUMBER_OF_DATA][TEMP_ARR_SIZE] = { 0 };
	static wchar_t show_info_temp[TEMP_ARR_SIZE] = { 0 };
	static int i, j, k;
	static int count; // 명령어 입력용 변수
	static int line_thickness = 1;

	srand((unsigned)time(NULL));
	//유니코드를 사용할 떄는 char 대신 wchar_t 를 쓰고 문자열 앞에 L를 붙인다

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리  
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 40);
		ShowCaret(hWnd); // 빈 화면에 캐럿 표시
		count = 0;
		return 0;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		if (wParam == VK_RETURN) {

			for (i = 0; i < NUMBER_OF_DATA; ++i) {
				for (j = 0; j < TEMP_ARR_SIZE; ++j) {
					temp[i][j] = '\0';
				}
			} // 임시배열 초기화

			j = 0;
			k = 0;
			for (i = 0; i < TEMP_ARR_SIZE; ++i) {
				if ('0' <= order[i] &&  order[i] <= '9') {
					temp[k][j] = order[i];
					++j;
				}
				else {
					switch (k) {
					case 0:
						shape_info.shape_type = _wtoi(temp[k]);
						j = 0;
						k++;
						break;
					case 1:
						shape_info.left = _wtoi(temp[k]);
						j = 0;
						k++;
						break;
					case 2:
						shape_info.top = _wtoi(temp[k]);
						j = 0;
						k++;
						break;
					case 3:
						shape_info.right = _wtoi(temp[k]);
						j = 0;
						k++;
						break;
					case 4:
						shape_info.bottom = _wtoi(temp[k]);
						j = 0;
						break;
					}
				}
			}

			for (i = 0; i < TEMP_ARR_SIZE; ++i) {
				order[i] = '\0';
			}
			count = 0;
		}
		else if (wParam == VK_BACK) { // 백스페이스를 눌렀을떄
			if(0<count)
			count--;
			order[count] = '\0'; 
			
		}
		else if (wParam == '+' || wParam == '-') { // + / -  키 설정
			if (wParam == '+') {
				if (line_thickness < THICK_MAX)
					line_thickness++;
			}
			else {
				if (THICK_MIN < line_thickness)
					line_thickness--;
			}
		}
		else {
			if (count < TEMP_ARR_SIZE-1) {
				order[count++] = wParam;
				order[count] = '\0';
			}
		}
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);		
		break;
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
		Rectangle(hdc,0,530,300,590);

		SetTextColor(hdc, RGB(0, 0, 240));

		GetTextExtentPoint(hdc, order, wcslen(order), &size); // 핸들, 측정할 문자, 몇번째까지 측정할건지, 구조체에 저장
		TextOut(hdc, 5, 540, order, wcslen(order));
		SetCaretPos(5+size.cx, 540);

		MyPen = CreatePen(PS_SOLID, line_thickness, RGB(rand()%240, rand() % 240, rand() % 240));
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		if (shape_info.shape_type == 1) {
			MoveToEx(hdc, shape_info.left, shape_info.top, NULL);
			LineTo(hdc, shape_info.right, shape_info.bottom);
		}
		else if (shape_info.shape_type == 2) {
			Ellipse(hdc, shape_info.left, shape_info.top, shape_info.right, shape_info.bottom);
		}
		else if (shape_info.shape_type == 3) {
			Rectangle(hdc, shape_info.left, shape_info.top, shape_info.right, shape_info.bottom);
		}
		else {
			SetTextColor(hdc,RGB(255,0,0));
			TextOut(hdc, 300, 300, L"ERROR!!!", wcslen(L"ERROR!!!"));
		}

		/////////////////////////명령어 입력한거 확인///////////////////////////////////////////
		SetTextColor(hdc, RGB(0, 0, 255));
		wsprintf(show_info_temp, TEXT("Shape Type : %d"), shape_info.shape_type);
		TextOut(hdc, 0, 0, show_info_temp, wcslen(show_info_temp));
		wsprintf(show_info_temp, TEXT("Left : %d"), shape_info.left);
		TextOut(hdc, 0, 20, show_info_temp, wcslen(show_info_temp));
		wsprintf(show_info_temp, TEXT("Top : %d"), shape_info.top);
		TextOut(hdc, 0, 40, show_info_temp, wcslen(show_info_temp));
		wsprintf(show_info_temp, TEXT("Right : %d"), shape_info.right);
		TextOut(hdc, 0, 60, show_info_temp, wcslen(show_info_temp));
		wsprintf(show_info_temp, TEXT("Bottom : %d"), shape_info.bottom);
		TextOut(hdc, 0, 80, show_info_temp, wcslen(show_info_temp));
		/////////////////////////////////////////////////////////////////////////////////////////
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}