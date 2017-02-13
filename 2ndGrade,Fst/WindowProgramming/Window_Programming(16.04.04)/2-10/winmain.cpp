#include<Windows.h>
#include<Tchar.h> 
#include<time.h>

#define NUMBER_OF_SHAPE 5 // ���� ��
#define MAX_SIZE 200 // �ִ� ������
#define MAX_RANDOM_POSIT 100 // �ִ� ��ġ ��
#define SELECTED_SHAPE_LINE_SIZE 50 // ���õ� ���� �� ����
typedef struct {
	int shape_type; // 1 -> �� , 2 -> �ﰢ�� , 3 -> �簢��
	int left;
	int top;
	int right;
	int bottom;
	int tri_point_x; // �ﰢ�� �׸��� x ��ǥ
	int tri_point_y; // �ﰢ�� �׸��� y ��ǥ
}Draw_Shape;


HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 2-10"; // �̰� �������� ������ �����ڵ� ���������� �׷���
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

	
	PAINTSTRUCT ps;
	HDC hdc; // �׻� ù��° ���ڴ� hDC ��! 
	static HBRUSH hBrush, oldBrush;
	static HPEN hPen, oldPen;
	static POINT point[3] = { 0 };
	static Draw_Shape shape_info[NUMBER_OF_SHAPE] = 
	{ { 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },
	};
	srand((unsigned)time(NULL)+ GetCurrentProcessId());
	static wchar_t temp[40] = { 0 }; // �� ��° ������ �����ߴ��� �����ִ� ���ڿ�
	static int i, j;
	static int number_of_data; // ���ݱ��� �׷��� ������ ��
	static int next_draw;
	static int select_shape;
	static int data_cycle;

	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�
	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		next_draw = 0;
		number_of_data = 0;
		data_cycle = 0; // �ڸ� �� ���� �ٽ� ù��° �����ڸ��� �����
		return 0;
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == VK_DELETE) {
			if ((1 <= select_shape && select_shape <= 5)&& (shape_info[select_shape-1].shape_type != 0)) {
				shape_info[select_shape-1] = {0,0,0,0,0,0,0};
				number_of_data--;
			}
		}
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:

		hdc = GetDC(hWnd);
		if (number_of_data < NUMBER_OF_SHAPE) {
			for (i = 0; i < NUMBER_OF_SHAPE; ++i) {
				if (shape_info[i].shape_type == 0) {
					next_draw = i;
					break;
				}
			}
		}
		else {
			next_draw = data_cycle % NUMBER_OF_SHAPE;
		}

		if (wParam == 'E' || wParam == 'e') {
			shape_info[next_draw] = {
				1,
				rand() % MAX_RANDOM_POSIT,
				rand() % MAX_RANDOM_POSIT,
				MAX_RANDOM_POSIT + rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				MAX_RANDOM_POSIT + rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				0,0
			};
			if (number_of_data < NUMBER_OF_SHAPE) {
				number_of_data++;
				data_cycle = 0;
			}
			else
				data_cycle++;
		}
		else if (wParam == 'T' || wParam == 't') {
			shape_info[next_draw] = {
				2,
				rand() % MAX_RANDOM_POSIT,
				rand() % MAX_RANDOM_POSIT,
				rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				rand() % MAX_RANDOM_POSIT,
				MAX_RANDOM_POSIT + rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
			};
			if (number_of_data < NUMBER_OF_SHAPE) {
				number_of_data++;
				data_cycle = 0;
			}
			else
				data_cycle++;
		}
		else if (wParam == 'R' || wParam == 'r') {
			shape_info[next_draw] = {
				3,
				rand() % MAX_RANDOM_POSIT,
				rand() % MAX_RANDOM_POSIT,
				MAX_RANDOM_POSIT + rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				MAX_RANDOM_POSIT + rand() % MAX_RANDOM_POSIT + rand() % MAX_SIZE,
				0,0
			};
			if (number_of_data < NUMBER_OF_SHAPE) {
				number_of_data++;
				data_cycle = 0;
			}
			else
				data_cycle++;
		}
		else if ('0' <= wParam && wParam <= '9') {
			select_shape = wParam-48; // ascii �ڵ� ����ؼ� ��ġ��ȯ
		}

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)

		if (1 <= select_shape && select_shape <= 5) {
			wsprintf(temp,TEXT("����� %d ��° ������ �����ߵ�"),select_shape);
			TextOut(hdc,0,0,temp,wcslen(temp));
			if (shape_info[select_shape-1].shape_type == 0) {
				wsprintf(temp, TEXT("�ٵ� �� ������ ���ų� ������� ����."));
				TextOut(hdc, 0, 20, temp, wcslen(temp));
			}
		}

		for (i = 0; i < NUMBER_OF_SHAPE; ++i) {
			if (shape_info[i].shape_type == 1) { // �� �׸���
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				if (select_shape - 1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� ��� ����
				}
				Ellipse(hdc,shape_info[i].left, shape_info[i].top, shape_info[i].right, shape_info[i].bottom);
			}
			else if (shape_info[i].shape_type == 2) { // �ﰢ�� �׸���
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				point[0] = { shape_info[i].left , shape_info[i].top };
				point[1] = { shape_info[i].right , shape_info[i].bottom };
				point[2] = { shape_info[i].tri_point_x , shape_info[i].tri_point_y };
				if (select_shape-1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� ��� ����
				}
				Polygon(hdc,point,3);
			}
			else if (shape_info[i].shape_type == 3) { // �簢�� �׸���
				hBrush = CreateSolidBrush(RGB(rand()%255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				if (select_shape - 1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� ��� ����
				}
				Rectangle(hdc, shape_info[i].left, shape_info[i].top, shape_info[i].right, shape_info[i].bottom);
			}

			SelectObject(hdc, oldPen); // ������ ������ ���ư�
			DeleteObject(hPen);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}



