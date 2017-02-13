#include<Windows.h>
#include<Tchar.h> 
HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 2-6"; // �̰� �������� ������ �����ڵ� ���������� �׷���
										  // L"���ڿ�" ���ڿ� �տ� �빮�� L�� ���δ� �ƴϸ� �����ڵ忡�� ��Ƽ����Ʈ�� �ٲٴ���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);

#define NUMBER_OF_LINE 10
#define NUMBER_OF_CHAR_ONE_LINE 99


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
	RECT rect; // �簢�� ����ü ����
			   //�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�
	SIZE size;
	wchar_t temp_array[NUMBER_OF_CHAR_ONE_LINE] = { 0 };
	static wchar_t string[NUMBER_OF_LINE][NUMBER_OF_CHAR_ONE_LINE] = { 0 };
	static int count, yPos;
	int i, j, k,l;
	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd); // �� ȭ�鿡 ĳ�� ǥ��
		count = 0; // ī��Ʈ 0���� �ʱ�ȭ
		yPos = 0;
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
		else { //  �� ��
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
		InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� �߻���Ų��
		ReleaseDC(hWnd, hDC);
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (wParam == VK_HOME) { // �������� R , ���⼱ HOME Ű �������� ���� �յڰ� �ٲ��
			
			k = yPos; // ������ ĭ�� ���ڸ� ù��° ���ڿ� �¹ٲٱ� ���� �����Ѵ�
			for (i = 0; i <= (yPos / 2); ++i) { // �� �հ� �� �ڸ� �ٲٰ� ���� 2��°, ������ �տ��� �ٲٰ� ,,,,,
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
			while (string[yPos][count] == '\0') { count--; }; // ������ ���������� ã�Ƽ� ���ڸ��� ����.
			
			


			/*
			if ((yPos < NUMBER_OF_LINE - 1 ) && count!=0 ) {
				
				string[yPos][count++] = ' ';
				string[yPos][count] = '\0';
				yPos++;
				count = 0;
			}
			*/
			InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT �޼��� ���� 
		}
		else if (wParam ==	VK_END) { // �������� Q , ���⼱ END Ű ��������
			HideCaret(hWnd);
			DestroyCaret();
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��, ȭ���� �������� OS���� �޼��� ���� (ó�� ����, �ٸ� ������ �������ִٰ� �ٽ� ���� ��, â ũ�� �ٲ�InvalidateRect(), InvalidateRgn()�Լ��� ȣ���Ͽ� ������ ȭ���� ��ȿȭ��ų ��)
		hDC = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)

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
			GetTextExtentPoint(hDC, temp_array, wcslen(temp_array), &size); // �ڵ�, ������ ����, ���°���� �����Ұ���, ����ü�� ����
			TextOut(hDC, 0, 20 * i, string[i], wcslen(string[i]));
			SetCaretPos(size.cx, (yPos)* 20);
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