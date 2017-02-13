#include<Windows.h>
#include<Tchar.h> 
#include<time.h>

#define NUMBER_OF_SHAPE 5 // ���� ��
#define RACTANGLE_FIELD_AREA 40 // ���� ��ĭ ũ��
#define SHAPE_SIZE 20 // ���� ������
#define MAX_SIZE 16 // �ִ� ����
#define SELECTED_SHAPE_LINE_SIZE 5 // ���õ� ���� �� ����
#define SMALLER_THAN_BOARD_GRID 2 // ���庸�� �ɱ� �۰� �׸���

typedef struct {
	int shape_type; // 1 -> �� , 2 -> �ﰢ�� , 3 -> �簢��
	int left;
	int top;
	int right;
	int bottom;
	int tri_point_x; // �ﰢ�� �׸��� x ��ǥ
	int tri_point_y; // �ﰢ�� �׸��� y ��ǥ
	int x;
	int y;
	int size;
}Draw_Shape;


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
		1200, // ������ ����ũ��
		850, //������ ����ũ��
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

	static HPEN hPen, oldPen;
	static POINT point[3] = { 0 };
	static Draw_Shape shape_info[NUMBER_OF_SHAPE] =
	{ { 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	};


	wchar_t temp[40] = { 0 };
	static int i, j;
	static int x, y;
	static int ispush, shape_mode;
	static int size;
	static int number_of_data; // ���ݱ��� �׷��� ������ ��
	static int next_draw;
	static int select_shape;
	static int data_cycle;

	srand((unsigned)time(NULL));
	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		ispush = 0; // Ű�� ������ �������� Ȯ��
		shape_mode = 0; // ���� ��� ����
		size = 1;
		break;
	case WM_KEYDOWN:
		if (wParam == VK_DELETE) {
			if ((1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0)) {
				shape_info[select_shape - 1] = { 0,0,0,0,0,0,0 };
				number_of_data--;
			}
		}
		else if (wParam == VK_LEFT) {
			if (ispush == 0 && (1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0) ) {
				if (0 < shape_info[select_shape - 1].x)
					--shape_info[select_shape - 1].x;
				else
					shape_info[select_shape - 1].x = RACTANGLE_FIELD_AREA - 1 * shape_info[select_shape - 1].size;
			}
		}
		else if (wParam == VK_RIGHT) {
			if (ispush == 0 && (1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0)) {
				if (shape_info[select_shape - 1].x < RACTANGLE_FIELD_AREA - 1 * shape_info[select_shape - 1].size)
					++shape_info[select_shape - 1].x;
				else
					shape_info[select_shape - 1].x = 0;
			}
		}
		else if (wParam == VK_UP) {
			if (ispush == 0 && (1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0)) {
				if (0 < shape_info[select_shape - 1].y)
					--shape_info[select_shape - 1].y;
				else
					shape_info[select_shape - 1].y = RACTANGLE_FIELD_AREA - 1 * shape_info[select_shape - 1].size;
			}
		}
		else if (wParam == VK_DOWN) {
			if (ispush == 0 && (1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0)) {
				if (shape_info[select_shape - 1].y < RACTANGLE_FIELD_AREA - 1 * shape_info[select_shape - 1].size)
					++shape_info[select_shape - 1].y;
				else
					shape_info[select_shape - 1].y = 0;
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
				SMALLER_THAN_BOARD_GRID,
				SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				0,0,
				rand() % RACTANGLE_FIELD_AREA,
				rand() % RACTANGLE_FIELD_AREA,
				1
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
				SMALLER_THAN_BOARD_GRID,
				SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				SMALLER_THAN_BOARD_GRID,
				SMALLER_THAN_BOARD_GRID,
				rand() % RACTANGLE_FIELD_AREA,
				rand() % RACTANGLE_FIELD_AREA,
				1
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
				SMALLER_THAN_BOARD_GRID,
				SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				- SMALLER_THAN_BOARD_GRID,
				0,0,
				rand() % RACTANGLE_FIELD_AREA,
				rand() % RACTANGLE_FIELD_AREA,
				1
			};
			if (number_of_data < NUMBER_OF_SHAPE) {
				number_of_data++;
				data_cycle = 0;
			}
			else
				data_cycle++;
		}
		else if ('0' <= wParam && wParam <= '9') { // 1������ 5������ �߿��� �����Ѵ�.
			select_shape = wParam - 48; // ascii �ڵ� ����ؼ� ��ġ��ȯ
		}




		else if (wParam == '+' || wParam == '-' && (1 <= select_shape && select_shape <= 5) && (shape_info[select_shape - 1].shape_type != 0)) {
			if (wParam == '+' && shape_info[select_shape - 1].size <= MAX_SIZE) {

				shape_info[select_shape - 1].size *= 2;

				if (shape_info[select_shape - 1].size <= 0) {
					shape_info[select_shape - 1].size = 1;
					//shape_info[select_shape - 1].x = rand() % RACTANGLE_FIELD_AREA;
					//shape_info[select_shape - 1].y = rand() % RACTANGLE_FIELD_AREA;
					shape_info[select_shape - 1].shape_type = rand() % 3+1;
				}
			}
			else if (wParam == '-') {
				if (shape_info[select_shape - 1].size <= 1) {
					shape_info[select_shape - 1].size = 0;
				}
				shape_info[select_shape - 1].size /= 2;
			}

			if (shape_info[select_shape - 1].y > RACTANGLE_FIELD_AREA-1 - 1 * shape_info[select_shape - 1].size)
				shape_info[select_shape - 1].y = 0;
			if (shape_info[select_shape - 1].x > RACTANGLE_FIELD_AREA-1 - 1 * shape_info[select_shape - 1].size)
				shape_info[select_shape - 1].x = 0;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)

		for (i = 0; i < RACTANGLE_FIELD_AREA; ++i) {
			for (j = 0; j < RACTANGLE_FIELD_AREA; ++j) {
				Rectangle(hdc, SHAPE_SIZE*i, SHAPE_SIZE*j, SHAPE_SIZE + SHAPE_SIZE*i, SHAPE_SIZE + SHAPE_SIZE*j);
			}
		} // ���带 �׸���
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (1 <= select_shape && select_shape <= 5) {
			wsprintf(temp, TEXT("����� %d ��° ������ �����ߵ�"), select_shape);
			TextOut(hdc, RACTANGLE_FIELD_AREA*SHAPE_SIZE, 0, temp, wcslen(temp));
			if (shape_info[select_shape - 1].shape_type == 0 || shape_info[select_shape-1].size<1) {
				wsprintf(temp, TEXT("�ٵ� �� ������ ���ų� ������� ����."));
				TextOut(hdc, RACTANGLE_FIELD_AREA*SHAPE_SIZE, 20, temp, wcslen(temp));
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (ispush == 1) {
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		}
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (i = 0; i < NUMBER_OF_SHAPE; ++i) {
			if (shape_info[i].shape_type == 1 && 1 <= shape_info[i].size) { // �� �׸���
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				if (select_shape - 1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� ��� ����
				}
				Ellipse(hdc, 
					shape_info[i].left + shape_info[i].x*SHAPE_SIZE,
					shape_info[i].top + shape_info[i].y*SHAPE_SIZE,
					shape_info[i].right + shape_info[i].x*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size,
					shape_info[i].bottom + shape_info[i].y*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size);
			}
			////////////////////�����Ұ�////////////////////////////////////
			else if (shape_info[i].shape_type == 2 && 1 <= shape_info[i].size) { // �ﰢ�� �׸���
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				point[0] = { shape_info[i].left + shape_info[i].x*SHAPE_SIZE ,
					shape_info[i].top + shape_info[i].y*SHAPE_SIZE };

				point[1] = { shape_info[i].left + shape_info[i].x*SHAPE_SIZE  ,
					shape_info[i].bottom + shape_info[i].y*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size };

				point[2] = { shape_info[i].right + shape_info[i].x*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size ,
					shape_info[i].bottom + shape_info[i].y*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size };
				if (select_shape - 1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� ��� ����
				}
				Polygon(hdc, point, 3);
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else if (shape_info[i].shape_type == 3 && 1<=shape_info[i].size) { // �簢�� �׸���
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				if (select_shape - 1 == i) {
					hPen = CreatePen(PS_DOT, SELECTED_SHAPE_LINE_SIZE, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� ��� ����
				}
				Rectangle(hdc, 
					shape_info[i].left + shape_info[i].x*SHAPE_SIZE,
					shape_info[i].top + shape_info[i].y*SHAPE_SIZE,
					shape_info[i].right + shape_info[i].x*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size,
					shape_info[i].bottom + shape_info[i].y*SHAPE_SIZE + SHAPE_SIZE*shape_info[i].size);
			}

			SelectObject(hdc, oldPen); // ������ ������ ���ư�
			DeleteObject(hPen);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
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