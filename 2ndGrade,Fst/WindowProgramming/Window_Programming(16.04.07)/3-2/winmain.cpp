//////////////////// �ְ�� ������� 3-2 �ڵ� ///////////////////////////////

#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include<math.h> // ���� ���� ���� �����س���

#define PI 3.141592 // ���̰�

#define MN_OBJECT_SIZE 5 // �����̴� ������ �ּ�ũ��
#define MX_OBJECT_SIZE 10 // �����̴� ������ ũ��

#define CENTER_POINT 150 // ���������� ��ġ��
#define MX_FIELD_SIZE 70 //�ִ�ũ��
#define MN_FIELD_SIZE 30 //�ּ�ũ��

#define CLIENT_WIDTH 800 // Ŭ���̾�Ʈ ����ũ��
#define CLIENT_HEIGHT 800 // Ŭ���̾�Ʈ ����ũ��

#define SPEED 50 //  ������ �ӵ�

#define RADIAN_SPEED 4 // �����̴� ����

#define S_OFF 0 // ����ġ ����
#define S_ON 1 // ����ġ ����

typedef enum {
	Clock, RClock
}Direction; // �ð����, �ݽð����

typedef enum {
RECTANGLE,TRIANGLE,ELLIPSE
}Shape_Type;

typedef enum {
	LZONE,TZONE,RZONE,BZONE 
}Zone; // ��,��,��,��

typedef struct {
	int x;
	int y;
}Point; // ��ǥ ����Ʈ

typedef struct {
	Point center_point;
	int size;
	double radian; // ����
}Shape;

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 3-2"; // �̰� �������� ������ �����ڵ� ���������� �׷���
										 // L"���ڿ�" ���ڿ� �տ� �빮�� L�� ���δ� �ƴϸ� �����ڵ忡�� ��Ƽ����Ʈ�� �ٲٴ���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);



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
		CLIENT_WIDTH, // ������ ����ũ��
		CLIENT_HEIGHT, //������ ����ũ��
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	srand((unsigned)time(NULL));
	PAINTSTRUCT ps;
	HDC hdc; // �׻� ù��° ���ڴ� hDC ��! 
	HBRUSH hBrush, oldBrush;

	static RECT rectView; // â ũ�⸦ �����ϴ� RECT ����ü
	int i; // �ݺ��� ������

/////////////////// �˵� ���� ������(��浵��)///////////////////////////////////////////////////////////////
	static Shape shape[4] = { { { CENTER_POINT ,CENTER_POINT },
		MN_FIELD_SIZE + rand() % MX_FIELD_SIZE ,0 },
		{ { 3 * CENTER_POINT ,CENTER_POINT },
		MN_FIELD_SIZE + rand() % MX_FIELD_SIZE ,0 },
		{ { CENTER_POINT ,3 * CENTER_POINT },
		MN_FIELD_SIZE + rand() % MX_FIELD_SIZE ,0 },
		{ { 3 * CENTER_POINT ,3 * CENTER_POINT },
		MN_FIELD_SIZE + rand() % MX_FIELD_SIZE ,0 }
	};
	static POINT triangle[4][3]; // �ﰢ�� �׸���
	static RECT field_shape_draw[4];
	static int field_shape_type = Shape_Type::ELLIPSE; // �˵��� ���� Ÿ��
 //////////////////�����̴� ���� ������////////////////////////////////////////////////////////////////////////
	static Shape mov_shape[4] = {
		{ { shape[0].size*sin(mov_shape[0].radian) + shape[0].center_point.x , shape[0].size*cos(mov_shape[0].radian) + shape[0].center_point.y },
		MN_OBJECT_SIZE + rand() % MX_OBJECT_SIZE ,0 },
		{ { shape[1].size*sin(mov_shape[1].radian) + shape[1].center_point.x , shape[1].size*cos(mov_shape[1].radian) + shape[1].center_point.y },
		MN_OBJECT_SIZE + rand() % MX_OBJECT_SIZE ,0 },
		{ { shape[2].size*sin(mov_shape[2].radian) + shape[2].center_point.x , shape[2].size*cos(mov_shape[2].radian) + shape[2].center_point.y },
		MN_OBJECT_SIZE + rand() % MX_OBJECT_SIZE ,0 },
		{ { shape[3].size*sin(mov_shape[3].radian) + shape[3].center_point.x , shape[3].size*cos(mov_shape[3].radian) + shape[3].center_point.y },
		MN_OBJECT_SIZE + rand() % MX_OBJECT_SIZE ,0 }
	};
	static RECT mov_shape_draw[4];
	static int speed[4] = {3,5,7,9}; ////////////////////////////////<<<<<<<<<<<<<----- ���ǵ带 ����Ѵ�
	static int clockwork = Direction::Clock; // �������� ����
	static int mov_shape_type = Shape_Type::ELLIPSE; // �������� ���
	static int dir_check[4] = {
		Zone::TZONE,Zone::TZONE,Zone::TZONE,Zone::TZONE
	}; // ���������� �ִ� ��ġ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		for (i = 0; i < 4; ++i) {
			field_shape_draw[i] = {
				shape[i].center_point.x - shape[i].size,shape[i].center_point.y - shape[i].size,
				shape[i].center_point.x + shape[i].size,shape[i].center_point.y + shape[i].size
			};
		}
		for (i = 0; i < 4; ++i) {
			mov_shape_draw[i] = {
				mov_shape[i].center_point.x - mov_shape[i].size,mov_shape[i].center_point.y - mov_shape[i].size,
			mov_shape[i].center_point.x + mov_shape[i].size,mov_shape[i].center_point.y + mov_shape[i].size
			};
		}
		for (i = 0; i < 4; ++i) {
				triangle[i][0] = { field_shape_draw[i].left + shape[i].size , field_shape_draw[i].top };
				triangle[i][1] = { field_shape_draw[i].left, field_shape_draw[i].bottom};
				triangle[i][2] = { field_shape_draw[i].right , field_shape_draw[i].bottom };
			}
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView); // ������ â ũ�⸦ ���س���.
		
		SetTimer(hWnd, 1, SPEED, NULL); // ��ũ��


		return 0;
		////////////////////////////////////////////////////////////////////////////////////
	case WM_TIMER:
			for (i = 0; i < 4; ++i) {
				switch (field_shape_type) {
				case Shape_Type::ELLIPSE:
					if (clockwork == Direction::Clock) {
						mov_shape[i].radian -= speed[i];
					}
					else {
						mov_shape[i].radian += speed[i];
					}
					mov_shape[i].center_point.x = shape[i].size*sin(PI*mov_shape[i].radian / 180.0) + shape[i].center_point.x;
					mov_shape[i].center_point.y = shape[i].size*cos(PI*mov_shape[i].radian / 180.0) + shape[i].center_point.y;
					break;
				case Shape_Type::RECTANGLE:
					if (clockwork == Direction::Clock) {
						if (dir_check[i] == Zone::TZONE) {
							mov_shape[i].center_point.x += speed[i];
							if (field_shape_draw[i].right - mov_shape[i].size <= mov_shape_draw[i].left) {
								mov_shape[i].center_point.x = field_shape_draw[i].right;
								dir_check[i] = Zone::RZONE;
							}
						}
						else if (dir_check[i] == Zone::RZONE) {
							mov_shape[i].center_point.y += speed[i];
							if (field_shape_draw[i].bottom - mov_shape[i].size <= mov_shape_draw[i].top) {
								mov_shape[i].center_point.y = field_shape_draw[i].bottom;
								dir_check[i] = Zone::BZONE;
							}
						}
						else if (dir_check[i] == Zone::BZONE) {
							mov_shape[i].center_point.x -= speed[i];
							if (mov_shape_draw[i].right - mov_shape[i].size <= field_shape_draw[i].left) {
								mov_shape[i].center_point.x = field_shape_draw[i].left;
								dir_check[i] = Zone::LZONE;
							}
						}
						else if (dir_check[i] == Zone::LZONE) {
							mov_shape[i].center_point.y -= speed[i];
							if (mov_shape_draw[i].top + mov_shape[i].size <= field_shape_draw[i].top) {
								mov_shape[i].center_point.y = field_shape_draw[i].top;
								dir_check[i] = Zone::TZONE;
							}
						}
					}
					else {
						if (dir_check[i] == Zone::TZONE) {
							mov_shape[i].center_point.x -= speed[i];
							if (mov_shape_draw[i].right - mov_shape[i].size <= field_shape_draw[i].left) {
								mov_shape[i].center_point.x = field_shape_draw[i].left;
								dir_check[i] = Zone::LZONE;
							}
						}
						else if (dir_check[i] == Zone::LZONE) {
							mov_shape[i].center_point.y += speed[i];
							if (field_shape_draw[i].bottom + mov_shape[i].size <= mov_shape_draw[i].bottom) {
								mov_shape[i].center_point.y = field_shape_draw[i].bottom;
								dir_check[i] = Zone::BZONE;
							}
						}
						else if (dir_check[i] == Zone::BZONE) {
							mov_shape[i].center_point.x += speed[i];
							if (field_shape_draw[i].right + mov_shape[i].size <= mov_shape_draw[i].right) {
								mov_shape[i].center_point.x = field_shape_draw[i].right;
								dir_check[i] = Zone::RZONE;
							}
						}
						else if (dir_check[i] == Zone::RZONE) {
							mov_shape[i].center_point.y -= speed[i];
							if (mov_shape_draw[i].top <= field_shape_draw[i].top - mov_shape[i].size) {
								mov_shape[i].center_point.y = field_shape_draw[i].top;
								dir_check[i] = Zone::TZONE;
							}
						}

					}
					break;
				case Shape_Type::TRIANGLE:
					if (clockwork == Direction::Clock) {
						if (dir_check[i] == Zone::RZONE) {
							mov_shape[i].center_point.y += speed[i]*2;
							mov_shape[i].center_point.x += speed[i];
							if (field_shape_draw[i].bottom - mov_shape[i].size <= mov_shape_draw[i].bottom ) {
								mov_shape[i].center_point.x = field_shape_draw[i].right;
								mov_shape[i].center_point.y = field_shape_draw[i].bottom;
								dir_check[i] = Zone::BZONE;
							}
						}
						else if (dir_check[i] == Zone::BZONE) {
							mov_shape[i].center_point.x -= speed[i];
							if (mov_shape_draw[i].right - mov_shape[i].size <= field_shape_draw[i].left ) {
								mov_shape[i].center_point.x = field_shape_draw[i].left;
								dir_check[i] = Zone::LZONE;
							}
						}
						else if (dir_check[i] == Zone::LZONE) {
							mov_shape[i].center_point.y -= speed[i]*2;
							mov_shape[i].center_point.x += speed[i];
							if (mov_shape_draw[i].top - mov_shape[i].size <= field_shape_draw[i].top ) {
								mov_shape[i].center_point.x = field_shape_draw[i].left + shape[i].size;
								mov_shape[i].center_point.y = field_shape_draw[i].top ;
								dir_check[i] = Zone::RZONE;
							}
						}
					}
					else {
						if (dir_check[i] == Zone::RZONE) {
							mov_shape[i].center_point.y -= speed[i] * 2;
							mov_shape[i].center_point.x -= speed[i];
							if (mov_shape_draw[i].top <= field_shape_draw[i].top - mov_shape[i].size) {
								mov_shape[i].center_point.x = field_shape_draw[i].left + shape[i].size;
								mov_shape[i].center_point.y = field_shape_draw[i].top;
								dir_check[i] = Zone::LZONE;
							}
						}
						else if (dir_check[i] == Zone::LZONE) {
							mov_shape[i].center_point.y += speed[i] * 2;
							mov_shape[i].center_point.x -= speed[i];
							if (field_shape_draw[i].bottom <= mov_shape_draw[i].bottom + mov_shape[i].size ) {
								mov_shape[i].center_point.x = field_shape_draw[i].left;
								mov_shape[i].center_point.y = field_shape_draw[i].bottom;
								dir_check[i] = Zone::BZONE;
							}
						}
						else if (dir_check[i] == Zone::BZONE) {
							mov_shape[i].center_point.x += speed[i];
							if (field_shape_draw[i].right <= mov_shape_draw[i].right - mov_shape[i].size) {
								mov_shape[i].center_point.x = field_shape_draw[i].right;
								dir_check[i] = Zone::RZONE;
							}
						}
						
					}


					break;
				}
				mov_shape_draw[i] = {
					mov_shape[i].center_point.x - mov_shape[i].size,
					mov_shape[i].center_point.y - mov_shape[i].size,
					mov_shape[i].center_point.x + mov_shape[i].size,
					mov_shape[i].center_point.y + mov_shape[i].size
				};
			}
			
		InvalidateRect(hWnd, &rectView, TRUE);
		break;
		//////////////////////////////////////////////////////////////////////////////////////////
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == 'c' || wParam == 'C') { // ���������� �ٲ۴�
			if (clockwork == Direction::Clock) {
				clockwork = Direction::RClock;
			}
			else {
				clockwork = Direction::Clock;
			}
		}
		else if (wParam == 'M' || wParam == 'm') { // �������� ����� �ٲ۴�
			if (mov_shape_type == Shape_Type::ELLIPSE) {
				mov_shape_type = Shape_Type::RECTANGLE;
			}
			else {
				mov_shape_type = Shape_Type::ELLIPSE;
			}
		}
		else if (wParam == 'T' || wParam == 't') {
			if (field_shape_type != Shape_Type::TRIANGLE) {
				field_shape_type = Shape_Type::TRIANGLE;
			}
			for (i = 0; i < 4; ++i) {
				mov_shape[i].center_point.x = field_shape_draw[i].right;
				mov_shape[i].center_point.y = field_shape_draw[i].bottom;
				dir_check[i] = Zone::BZONE;
			}
		}
		else if (wParam == 'R' || wParam == 'r') {
			if (field_shape_type != Shape_Type::RECTANGLE) {
				field_shape_type = Shape_Type::RECTANGLE;
				for (i = 0; i < 4; ++i) {
					mov_shape[i].center_point.x = field_shape_draw[i].left;
					mov_shape[i].center_point.y = field_shape_draw[i].top;
					dir_check[i] = Zone::TZONE;
				}
	
			}
		}
		else if (wParam == 'E' || wParam == 'e') {
			if (field_shape_type != Shape_Type::ELLIPSE) {
				field_shape_type = Shape_Type::ELLIPSE;
				for (i = 0; i < 4; ++i) {
					mov_shape[i].center_point.x = shape[i].size*sin(PI*mov_shape[i].radian / 180.0) + shape[i].center_point.x;
					mov_shape[i].center_point.y = shape[i].size*cos(PI*mov_shape[i].radian / 180.0) + shape[i].center_point.y;
				}
			}
		}
		else if (wParam == 'Q' || wParam == 'q') { // ���α׷��� �����Ѵ�
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			return 0;
		}
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
		
		////////////////////////////// �˵��� �׸��� /////////////////////////////////////////
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		switch (field_shape_type) {
		case Shape_Type::ELLIPSE:
			for (i = 0; i < 4; ++i) {
				Ellipse(hdc, field_shape_draw[i].left, field_shape_draw[i].top, field_shape_draw[i].right, field_shape_draw[i].bottom);
			}
			break;
		case Shape_Type::RECTANGLE:
			for (i = 0; i < 4; ++i) {
				Rectangle(hdc, field_shape_draw[i].left, field_shape_draw[i].top, field_shape_draw[i].right, field_shape_draw[i].bottom);
			}
			break;
		case Shape_Type::TRIANGLE:
			for (i = 0; i < 4; ++i) {
				Polygon(hdc,triangle[i],3);
			}
			break;
		}	
		//////////////////////////////�����̴� ������ �׸���////////////////////////////////
		switch (mov_shape_type) {
		case Shape_Type::ELLIPSE:
			for (i = 0; i < 4; ++i) {
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Ellipse(hdc, mov_shape_draw[i].left, mov_shape_draw[i].top, mov_shape_draw[i].right, mov_shape_draw[i].bottom);
				SelectObject(hdc, oldBrush);
			}
			break;
		case Shape_Type::RECTANGLE:
			for (i = 0; i < 4; ++i) {
				hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, mov_shape_draw[i].left, mov_shape_draw[i].top, mov_shape_draw[i].right, mov_shape_draw[i].bottom);
				SelectObject(hdc, oldBrush);
			}
			break;
		}
		/////////////////////////////////////////////////////////////
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		///////////////////////////////////////////////������Ʈ���� �����////////////////////
		EndPaint(hWnd, &ps);

		break;
	case WM_SIZE: // �����찡 �ٽ� �׷�����
		GetClientRect(hWnd, &rectView);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}

