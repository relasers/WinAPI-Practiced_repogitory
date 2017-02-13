#include<Windows.h>
#include<Tchar.h> 
#include<time.h>

#define RACTANGLE_FIELD_AREA 4
#define RAC_SIZE 40
#define PLAY_RAC_SIZE 20
HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 2-8"; // �̰� �������� ������ �����ڵ� ���������� �׷���
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
		800, //������ ����ũ��
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
	HBRUSH hBrush, oldBrush;

	wchar_t temp[40] = { 0 };
	static int i, j;
	static int x, y;
	static int ispush,shape_mode; 
	srand((unsigned)time(NULL));
	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		x = rand() % RACTANGLE_FIELD_AREA;
		y = rand() % RACTANGLE_FIELD_AREA;
		ispush = 0; // Ű�� ������ �������� Ȯ��
		shape_mode = 0; // ���� ��� ����
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
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)

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
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}