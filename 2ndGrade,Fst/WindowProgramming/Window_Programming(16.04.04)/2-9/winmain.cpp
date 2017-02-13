#include<Windows.h>
#include<Tchar.h> 
#include<time.h>

#define TEMP_ARR_SIZE 35 // �ӽ� ���ڿ��� ũ��
#define NUMBER_OF_DATA 5 // �Է��� ������ ��
#define THICK_MAX 20 // �� ���� �ִ�ġ
#define THICK_MIN 1 // �� ���� �ּ�ġ
typedef struct {
	int shape_type;
	int left;
	int top;
	int right;
	int bottom;
}Draw_Shape;


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 2-9"; // �̰� �������� ������ �����ڵ� ���������� �׷���
										  // L"���ڿ�" ���ڿ� �տ� �빮�� L�� ���δ� �ƴϸ� �����ڵ忡�� ��Ƽ����Ʈ�� �ٲٴ���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);

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

	srand((unsigned)time(NULL));
	PAINTSTRUCT ps;
	HDC hdc; // �׻� ù��° ���ڴ� hDC ��! 
	HPEN MyPen, OldPen;
	SIZE size;

	static Draw_Shape shape_info = { 0,0,0,0,0 };
	static wchar_t order[TEMP_ARR_SIZE] = { 0 }; // ��ɾ �޴� �迭
	static wchar_t temp[NUMBER_OF_DATA][TEMP_ARR_SIZE] = { 0 };
	static wchar_t show_info_temp[TEMP_ARR_SIZE] = { 0 };
	static int i, j, k;
	static int count; // ��ɾ� �Է¿� ����
	static int line_thickness = 1;

	srand((unsigned)time(NULL));
	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 40);
		ShowCaret(hWnd); // �� ȭ�鿡 ĳ�� ǥ��
		count = 0;
		return 0;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		if (wParam == VK_RETURN) {

			for (i = 0; i < NUMBER_OF_DATA; ++i) {
				for (j = 0; j < TEMP_ARR_SIZE; ++j) {
					temp[i][j] = '\0';
				}
			} // �ӽù迭 �ʱ�ȭ

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
		else if (wParam == VK_BACK) { // �齺���̽��� ��������
			if(0<count)
			count--;
			order[count] = '\0'; 
			
		}
		else if (wParam == '+' || wParam == '-') { // + / -  Ű ����
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
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
		Rectangle(hdc,0,530,300,590);

		SetTextColor(hdc, RGB(0, 0, 240));

		GetTextExtentPoint(hdc, order, wcslen(order), &size); // �ڵ�, ������ ����, ���°���� �����Ұ���, ����ü�� ����
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

		/////////////////////////��ɾ� �Է��Ѱ� Ȯ��///////////////////////////////////////////
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
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}