#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 2-7"; // �̰� �������� ������ �����ڵ� ���������� �׷���
										 // L"���ڿ�" ���ڿ� �տ� �빮�� L�� ���δ� �ƴϸ� �����ڵ忡�� ��Ƽ����Ʈ�� �ٲٴ���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);

#define NUMBER_OF_LINE 10
#define NUMBER_OF_CHAR_ONE_LINE 99
#define PDMODE_NUMBER_OF_LINE 99
#define PDMODE_NUMBER_OF_CHAR_ONE_LINE 11


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow) { // WinMain ��ҹ��� �ؼ��� ��!
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass; // EX �� �ٿ��� �ǰ� �Ⱥٿ��� �ȴ�.
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // ������ ��� ��Ÿ��
	WndClass.lpfnWndProc = (WNDPROC)WndProc; // �ظ��ؼ� �̸��� �״�� ����
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //  �⺻������ ��,ȸ,ȭ ���� ���� �̷��� ������� ���� ���� ��������
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = IpszClass; // �̷��� ���س����� ���Ŀ��� �Ȱ��� �̸�, �̰ŷ� ���
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Ŭ���� 12��// �ݵ�� 12�� �� ����Ѵ�
	RegisterClassEx(&WndClass);
	// API�� �������ִ� �Լ�
	hWnd = CreateWindow( //������ �ڵ鰪 ��ȯ
		IpszClass, //������ Ŭ���� �̸�
		IpszClass, //������ Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW, //������ ��Ÿ��
		CW_USEDEFAULT, //������ ��ġ x
		CW_USEDEFAULT, //������ ��ġ y
		800, // ������ ����ũ��
		600, //������ ����ũ��
		NULL, //�θ� ������ �ڵ�
		(HMENU)NULL, //�޴��ڵ�
		hInstance,//�������α׷� �ν��Ͻ�
		NULL);//���������� ����

	ShowWindow(hWnd, nCmdShow); // ������ ȭ�� ���
	UpdateWindow(hWnd); // O/S�� WM_PAINT  �޽��� ���� 

	while (GetMessage(&Message, 0, 0, 0)) { // ������ ���ν������� PostQuitMessage() ȣ�� ������ ó�� 
		TranslateMessage(&Message);  // ex) Shift ��a���� �빮�� ��A�� 
		DispatchMessage(&Message);  // WinMain �� WinProc 
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT ps;
	HDC hDC; // �׻� ù��° ���ڴ� hDC ��! 
	SIZE size;
	static wchar_t temp_array[NUMBER_OF_LINE][NUMBER_OF_CHAR_ONE_LINE] = { 0 }; //  
	static wchar_t temp_array_for_cerat[NUMBER_OF_CHAR_ONE_LINE] = { 0 }; // ĳ�� ��ġ ����
	static wchar_t string[NUMBER_OF_LINE][NUMBER_OF_CHAR_ONE_LINE] = { 0 };
	static wchar_t page_down_string[PDMODE_NUMBER_OF_LINE][PDMODE_NUMBER_OF_CHAR_ONE_LINE] = { 0 }; // ������ �ٿ� ǥ������ �迭
	static wchar_t temp_page_down_string[PDMODE_NUMBER_OF_LINE][PDMODE_NUMBER_OF_CHAR_ONE_LINE] = { 0 }; // ������ �ٿ� ǥ������ �迭
	static int count, yPos;
	static int secret_mode,page_down_mode; // F1 Ű �������� * ǥ�÷� �ٲ�°� ǥ���ϱ� ���� Ʈ���� ����, ���ٿ� 10�� ���ڸ� �Է��ϴ� Ʈ���� ����
	static int x, y, pd_caret; // page-down ��� ���Կ�
	int i, j;
	srand((unsigned)time(NULL));

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd); // �� ȭ�鿡 ĳ�� ǥ��
		count = 0; // ī��Ʈ 0���� �ʱ�ȭ
		yPos = 0;
		pd_caret = 0;
		secret_mode = 0;
		page_down_mode = 0;
		x = 0, y = 0;
		return 0;

	case WM_CHAR:
		hDC = GetDC(hWnd);
		if (wParam == VK_BACK) { // �齺���̽� Ű ���������
			if (count == 0) {
				if (0 < yPos) {
					--yPos;
					count = NUMBER_OF_CHAR_ONE_LINE + 1;
					while (string[yPos][count] == '\0') { count--; }; // ������ ���������� ã�Ƽ� ���ڸ��� ����.
				}
			}
			else 
				count--;
			
			for (i = 0; i <= count; ++i) { // �� �տ������� �����Ѵ�
				string[yPos][i] = string[yPos][i + 1];
			}
			string[yPos][i] = '\0';
			string[yPos][count] = '\0';
		}

		else if (wParam == VK_RETURN) // ���� ��������
		{
			if (yPos < NUMBER_OF_LINE - 1) {
				string[yPos][count++] = ' ';
				string[yPos][count] = '\0';
				yPos++;
				count = 0;
			}
		}
		else if (wParam == VK_ESCAPE) { // esc ��������
			yPos = 0;
			count = 0;
			for (i = 0; i < NUMBER_OF_LINE; ++i) {
				for (j = 0; j < NUMBER_OF_CHAR_ONE_LINE; ++j) {
					string[i][j] = '\0'; //NULL�� �ʱ�ȭ
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

		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� �߻���Ų��
		ReleaseDC(hWnd, hDC);
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (wParam == VK_HOME) { // Home Ű ��������, ������ ��ġ���� �Է��� �����Ѵ�.
			yPos = rand() % NUMBER_OF_LINE;
			count = rand() % NUMBER_OF_CHAR_ONE_LINE;
			for (i = 0; i <= yPos; ++i) {
				for (j = 0; j <= count; ++j) {
					if (string[i][j] == '\0')
						string[i][j] = ' ';
				}
			}

			InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� 
		}
		else if (wParam == VK_CONTROL) { //ctrl �������� �빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� �ٲ㼭 ����Ѵ�.
			for (i = 0; i <= yPos; ++i) {
				for (j = 0; j <= NUMBER_OF_CHAR_ONE_LINE - 1; ++j) {
					if (97 <= string[i][j] && string[i][j] <= 122)
						string[i][j] -= 32; // a~z �����Ͻ� 32�� ���� A~Z �� ����� (ASCII CODE)
					else if (65 <= string[i][j] && string[i][j] <= 90)
						string[i][j] += 32; // A~Z �����Ͻ� 32�� ���� a~z �� ����� (ASCII CODE)
				}
			}
			InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� 
		}
		else if (wParam == VK_F1) { // F1 ����ġ ��ȯ
			if (secret_mode == 0) {
				secret_mode = 1;
				InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� 
			}
			else {
				secret_mode = 0;
				InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� 
			}
		}
		else if (wParam == VK_NEXT) { // Page-down Key ��������
			if (page_down_mode == 0) {
				page_down_mode = 1;
				InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� 
			}
			else {
				page_down_mode = 0;
				InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� 
			}
		}
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��, ȭ���� �������� OS���� �޼��� ���� (ó�� ����, �ٸ� ������ �������ִٰ� �ٽ� ���� ��, â ũ�� �ٲ�InvalidateRect(), InvalidateRgn()�Լ��� ȣ���Ͽ� ������ ȭ���� ��ȿȭ��ų ��)
		hDC = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)

		SetTextColor(hDC, RGB(0, 0, 240));
		///////////�׸��� �� �ʱ�ȭ/////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		if (secret_mode == 1) { //��ǥ�� �ٲٴ� ����
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
		if (page_down_mode == 0 && secret_mode == 0) { // ��� �ΰ� �Ѵ� ���� �ʾҴٸ�
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
					GetTextExtentPoint(hDC, temp_array_for_cerat, wcslen(temp_array_for_cerat), &size); // �ڵ�, ������ ����, ���°���� �����Ұ���, ����ü�� ����
					TextOut(hDC, 0, 20 * i, temp_page_down_string[i], wcslen(temp_page_down_string[i]));
					SetCaretPos(size.cx, (y) * 20);
				}
				else {
					GetTextExtentPoint(hDC, temp_array_for_cerat, wcslen(temp_array_for_cerat), &size); // �ڵ�, ������ ����, ���°���� �����Ұ���, ����ü�� ����
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
					GetTextExtentPoint(hDC, temp_array_for_cerat, wcslen(temp_array_for_cerat), &size); // �ڵ�, ������ ����, ���°���� �����Ұ���, ����ü�� ����
					TextOut(hDC, 0, 20 * i, temp_array[i], wcslen(temp_array[i]));
					SetCaretPos(size.cx, (yPos)* 20);
				}
				else {
					GetTextExtentPoint(hDC, temp_array_for_cerat, wcslen(temp_array_for_cerat), &size); // �ڵ�, ������ ����, ���°���� �����Ұ���, ����ü�� ����
					TextOut(hDC, 0, 20 * i, string[i], wcslen(string[i]));
					SetCaretPos(size.cx, (yPos)* 20);
				}
			}
		}

		// strlen(temp) �� ��Ƽ����Ʈ������ �����Ѵ�
		// �����ڵ忡�� �����ִ� �Լ��� wcslen �� �ִ�!!!
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}