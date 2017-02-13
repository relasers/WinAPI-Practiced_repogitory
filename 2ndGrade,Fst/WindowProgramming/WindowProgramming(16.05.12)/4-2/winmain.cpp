#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include<math.h>
#include "resource.h"
#define BODY_SIZE 30 // �ֹ��� ��ü�� �������
#define MORE_SIZE 8 // Ŀ�ٶ� ���� �Ӹ�
#define WARM_LENGTH 20 // �ֹ����� ����
#define MX_NUM_FOOD 30 // �ִ� ���� ����
#define MX_NUM_BOMB 30 // �ִ� ��ź ����
#define PI 3.141592

#define MX_MOUSE 10
#define MOUTH_FRAME 4
#define FEVERTIME 20

#define ITEM_SIZE 10 // ������ ũ��

#define CLIENT_WIDTH 800 // Ŭ���̾�Ʈ ����ũ��
#define CLIENT_HEIGHT 800 // Ŭ���̾�Ʈ ����ũ��
#define MX_SPEED 10 // ���� �ִ�ӵ� / �������� ������
#define MN_SPEED 200 // ���� �ּҼӵ� / Ŭ���� ������
#define DEFAULT_SPEED 70 // ������ �ʱ� �ӵ�

#define E_SPEED 100 // �� �ֹ����� �ӵ� 

#define S_OFF 0 // ����ġ ����
#define S_ON 1 // ����ġ ����

#define JUMP_POWER 10 // ����
typedef enum {
	cyan,magenta,yellow,random

}Color;
typedef enum {
	Left, Right, Up, Down
}Direction;

typedef struct {
	int jump;
	int direction;
}Jumping;

typedef struct{
	RECT pos;
	bool exist;
}ITEM;

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 4-2"; // �̰� �������� ������ �����ڵ� ���������� �׷���
										 // L"���ڿ�" ���ڿ� �տ� �빮�� L�� ���δ� �ƴϸ� �����ڵ忡�� ��Ƽ����Ʈ�� �ٲٴ���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


bool collisionEllipseCheck(RECT rc, RECT rc2)
{
	float rc_R = (rc.right - rc.left) / 2;
	float rc2_R = (rc2.right - rc2.left) / 2;

	float rX = (rc.left + (rc.right - rc.left) / 2) - (rc2.left + (rc2.right - rc2.left) / 2);
	float rY = (rc.top + (rc.bottom - rc.top) / 2) - (rc2.top + (rc2.bottom - rc2.top) / 2);

	float length = (rc_R + rc2_R)  * (rc_R + rc2_R);

	if (length >= (rX * rX + rY * rY))
	{
		return true;
	}

	return false;
}

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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
	HPEN hPen, oldPen;
	static HBRUSH hbrBackground = NULL; // ���귯���ڵ�

	static HBRUSH hBrush[5], oldBrush;

	static int direction = Direction::Right; // �ֹ����� �̵����� �ʱ�� �������̴�.
	static int e_direction = Direction::Right;

	static RECT rectView; // â ũ�⸦ �����ϴ� RECT ����ü
	static RECT temp;
	static RECT collcheck_temp;
	//static Warm warm; // �ֹ����� �ʱ� ��ġ
	//static Warm temp; // â ���� ������� �Ӹ��� ������ �¹ٲٱ����� �ӽ� ��ġ ���� ��
	static int length = 3;
	static int e_length = 2; // �� ����

	static RECT warm[WARM_LENGTH] = { 0 };
	static RECT enemy_warm[WARM_LENGTH] = { 0 };

	static ITEM food[MX_NUM_FOOD] = { 0 };
	static ITEM bomb[MX_NUM_BOMB] = { 0 };
	static int wx, wy, mx, my;
	static int num_bomb = 0;
	static int num_food = 0;

	static int playermouth = 0;
	static int enemymouth = 0;

	static bool messageon = false;


	static bool creating = false; // ������ ���ġ?
	static bool gameon = false;
	static int head_color = Color::magenta;
	static int speed = DEFAULT_SPEED; // �ֹ����� �ʱ� �ӵ�

	static Jumping jumping = { 0,Direction::Right }; // ���� ����ü ����

	static int enemy_created = S_OFF; // ���� �����Ǿ���
	int i;
	int x, y;
	int x1, x2, y1, y2;
	static int mx_food = 1+rand()% (MX_NUM_FOOD-1);
	static int mx_bomb = 1+rand() % (MX_NUM_BOMB-1);

	static int fever = 0;
	static int mouseani = 0;
	static int moremouth = 0;


	static bool grid = false;
	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView);
		warm[0] = { BODY_SIZE * 10 ,BODY_SIZE * 10, BODY_SIZE * 10 +BODY_SIZE,BODY_SIZE * 10 + BODY_SIZE };
		warm[1] = { BODY_SIZE * 9 ,BODY_SIZE * 10, BODY_SIZE * 9 + BODY_SIZE,BODY_SIZE * 10 + BODY_SIZE };
		enemy_warm[0] = { BODY_SIZE * 2 ,BODY_SIZE * 2, BODY_SIZE * 2 + BODY_SIZE,BODY_SIZE * 2 + BODY_SIZE };
		enemy_warm[1] = { BODY_SIZE * 1 ,BODY_SIZE * 2, BODY_SIZE * 1 + BODY_SIZE,BODY_SIZE * 2 + BODY_SIZE };

		for (i = 0; i <mx_food; ++i) {
			x = rand() % rectView.right- ITEM_SIZE;
			y = rand() % rectView.bottom- ITEM_SIZE;
			food[i] = { {x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
			num_food++;
		}
		for (i = 0; i <mx_bomb; ++i) {
			x = rand() % rectView.right;
			y = rand() % rectView.bottom;
			bomb[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
			num_bomb++;
		}

		SetTimer(hWnd, 1, speed, NULL); // ù���� �ֹ����� �ӵ�
		SetTimer(hWnd, 2, 5000, NULL); // �� �ֹ����� �����ȴ� // 5000ms �� �ڿ� ���� �����ȴ�
		SetTimer(hWnd, 4, 100000, NULL); // ���� ���� ����
		SetTimer(hWnd,5, 300, NULL); // �� �Դٰ���
		return 0;
		////////////////////////////////////////////////////////////////////////////////////
	case WM_LBUTTONDOWN:
		
		wx = warm[0].left + (warm[0].right - warm[0].left) / 2;
		wy = warm[0].top + (warm[0].bottom - warm[0].right) / 2;
		mx = LOWORD(lParam);
		my = HIWORD(lParam);


			if ((mx - wx)*(mx - wx) < (my - wy)*(my - wy)) {
				if (my < wy) {
					direction = Direction::Up;
				}
				else {
					direction = Direction::Down;
				}
			}
			else {
				if (mx < wx) {
					direction = Direction::Left;
				}
				else {
					direction = Direction::Right;
				}
			
			}

		break;
		///////////////////////////////////////////////////////////////////////////////
	case WM_TIMER:
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (i = 0; i < MX_NUM_FOOD; ++i) {
			if (collisionEllipseCheck(warm[0], food[i].pos) == true && food[i].exist == true) {
				length++;
				num_food--;
				fever = FEVERTIME;
				food[i].exist = false;
			}
		}
		for (i = 0; i < MX_NUM_BOMB; ++i) {
			if (collisionEllipseCheck(warm[0], bomb[i].pos) == true && bomb[i].exist == true) {
				warm[length - 1] = { '\0','\0' ,'\0' ,'\0' };
				length--;
				num_bomb--;
				bomb[i].exist = false;
			}
		}
		if(creating == false)
		if (length == 0 || num_bomb == 0 || num_food == 0) { // ����
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);
			if (num_food == 0) {
				if (messageon == false) {
					messageon = true;
					MessageBoxW(hWnd, TEXT("�ٸԾ���!"), TEXT("����޼���"), MB_OK);
					Sleep(100000);
					
				}
			}
			PostQuitMessage(0);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(gameon)
		switch (wParam) {
		case 1: // �� ������ �����δ�
			(++mouseani) %= MOUTH_FRAME;
			if (0 < fever) {
				fever--;
				moremouth = 20;
			}
			
			if(fever<=0){
				moremouth = 0;
			}
				
			if (0 < jumping.jump) {
				if (direction == Direction::Right || direction == Direction::Left) {
					if (JUMP_POWER / 2 < jumping.jump) {
						for (i = length-1; 0 < i; --i) {
							warm[i] = warm[i - 1];
						}
						for (i = e_length - 1; 0 < i; --i) {
							enemy_warm[i] = enemy_warm[i - 1];
						}
						OffsetRect(&warm[0], 0, -BODY_SIZE);
						OffsetRect(&enemy_warm[0], 0, -BODY_SIZE);
					}
					else {
						for (i = length - 1; 0 < i; --i) {
							warm[i] = warm[i - 1];
						}
						for (i = e_length - 1; 0 < i; --i) {
							enemy_warm[i] = enemy_warm[i - 1];
						}
						OffsetRect(&warm[0],0, BODY_SIZE);
						OffsetRect(&enemy_warm[0], 0, BODY_SIZE);
					}
					jumping.jump--;

					if (warm[0].top < 0) {
						warm[0].top = 0;
						warm[0].bottom = BODY_SIZE;
					}
					if (enemy_warm[0].top < 0) {
						enemy_warm[0].top = 0;
						enemy_warm[0].bottom = enemy_warm[0].top+BODY_SIZE;
					}
				}
				else if (direction == Direction::Down || direction == Direction::Up) {
					if (JUMP_POWER / 2 < jumping.jump) {
						for (i = length - 1; 0 < i; --i) {
							warm[i] = warm[i - 1];
						}
						for (i = e_length - 1; 0 < i; --i) {
							enemy_warm[i] = enemy_warm[i - 1];
						}
						OffsetRect(&warm[0], BODY_SIZE,0 );
						OffsetRect(&enemy_warm[0], BODY_SIZE, 0);
					}
					else {
						for (i = length - 1; 0 < i; --i) {
							warm[i] = warm[i - 1];
						}
						for (i = e_length - 1; 0 < i; --i) {
							enemy_warm[i] = enemy_warm[i - 1];
						}
						OffsetRect(&warm[0], -BODY_SIZE, 0);
						OffsetRect(&enemy_warm[0], -BODY_SIZE, 0);
					}
					jumping.jump--;

					if (rectView.right < warm[0].right) {
						warm[0].right = rectView.right;
						warm[0].left = warm[0].right - BODY_SIZE;
					}
						
					if (rectView.right < enemy_warm[0].right) {
						enemy_warm[0].left = rectView.right - BODY_SIZE;
						enemy_warm[0].right = enemy_warm[0].left - BODY_SIZE;
					}
						
				}
			}


			switch (direction) {
			case Direction::Up:
				if (warm[0].top <= 0) {
					if (length != 1) {
						for (i = 0; i < length / 2; i++) {
							temp = warm[i];
							warm[i] = warm[(length - 1) - i];
							warm[(length - 1) - i] = temp;
						}
					}
					
					direction = Direction::Down;
				}
				else {
					for (i = length - 1; 0 < i; --i) {
						warm[i] = warm[i - 1];
					}
					OffsetRect(&warm[0], 0, -BODY_SIZE);
					if (warm[0].top < 0) {
						warm[0].top = 0;
						warm[0].bottom = BODY_SIZE;
					}
				}
				break;
			case Direction::Down:
				if (rectView.bottom <= warm[0].bottom) {
					if (length != 1) {
						for (i = 0; i < length / 2; i++) {
							temp = warm[i];
							warm[i] = warm[(length - 1) - i];
							warm[(length - 1) - i] = temp;
						}
					}
					
					direction = Direction::Up;
				}
				else {
					for (i = length - 1; 0 < i; --i) {
						warm[i] = warm[i - 1];
					}
					OffsetRect(&warm[0], 0, BODY_SIZE);
					if (rectView.bottom < warm[0].bottom) {
						warm[0].top = rectView.bottom - BODY_SIZE;
						warm[0].bottom = warm[0].top + BODY_SIZE;
					}
				}

				break;
			case Direction::Left:
				if (warm[0].left <= 0) {
					if (length != 1) {
						for (i = 0; i < length / 2; i++) {
							temp = warm[i];
							warm[i] = warm[(length - 1) - i];
							warm[(length - 1) - i] = temp;
						}
					}
					
					direction = Direction::Right;
				}
				else {
					for (i = length - 1; 0 < i; --i) {
						warm[i] = warm[i - 1];
					}
					OffsetRect(&warm[0], -BODY_SIZE, 0);
					if (warm[0].left < 0) { // �Ӹ��� ���� ���� �Ѿ�� 0 ���� ���������ش�
						warm[0].left = 0;
						warm[0].right = warm[0].left+BODY_SIZE;
					}
				}

				break;
			case Direction::Right:
				if (rectView.right <= warm[0].right) {
					if (length != 1) {
						for (i = 0; i < length / 2; i++) {
							temp = warm[i];
							warm[i] = warm[(length - 1) - i];
							warm[(length - 1) - i] = temp;
						}
					}
					
					direction = Direction::Left;
				}
				else {
					for (i = length - 1; 0 < i; --i) {
						warm[i] = warm[i - 1];
					}
					OffsetRect(&warm[0], BODY_SIZE, 0);
					if (rectView.right < warm[0].right) {
						warm[0].right = rectView.right;
						warm[0].left = warm[0].right - BODY_SIZE;
					}

				}
				break;
			}


			////////////////////////////////////////////////////////////
			break;
		case 2: // Ÿ�̸� 2�� ������ �� �ֹ��� Ÿ�̸Ӹ� �ҷ��´�
			KillTimer(hWnd, 2);
			enemy_created = S_ON;
			SetTimer(hWnd, 3, E_SPEED, NULL); // �� �ֹ����� �����ȴ�
			break;
		case 3: // �� �ֹ����� �׳��� �߰��ϴ� �κ�
			for (i = e_length - 1; 0 < i; --i) {
				enemy_warm[i] = enemy_warm[i - 1];
			}
			if (enemy_warm[0].left < warm[0].left) {
				OffsetRect(&enemy_warm[0], BODY_SIZE, 0);
				e_direction = Direction::Right;
			}// ������ ���� �����ʿ� �ִ�!

			if (warm[0].left < enemy_warm[0].left) {
				OffsetRect(&enemy_warm[0], -BODY_SIZE, 0);
				e_direction = Direction::Left;

			}// ������ ���� ���ʿ� �ִ�!
			if (enemy_warm[0].top < warm[0].top) {
				OffsetRect(&enemy_warm[0], 0, BODY_SIZE);
				e_direction = Direction::Down;
			}// ������ ���� �Ʒ��ʿ� �ִ�!

			if (warm[0].top <enemy_warm[0].top) {
				OffsetRect(&enemy_warm[0], 0, -BODY_SIZE);
				e_direction = Direction::Up;
			}// ������ ���� ���ʿ� �ִ�!
			break;
		case 4: // ���� ����

			if(gameon)
			{
			
				for (i = 0; i < 30; ++i) {
				
					if (food[i].exist == false) {
						x = rand() % rectView.right - ITEM_SIZE;
						y = rand() % rectView.bottom - ITEM_SIZE;
						food[i].exist = true;
						food[i].pos = { x,y,x + ITEM_SIZE,y + ITEM_SIZE };
						num_food++;
						break;
					}
				
				}
			
			
			}


			break;
		}

		InvalidateRect(hWnd, &rectView, FALSE);
		break;
		//////////////////////////////////////////////////////////////////////////////////////////
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == VK_UP) {
			direction = Direction::Up;
		}
		else if (wParam == VK_DOWN) {
			direction = Direction::Down;
		}
		else if (wParam == VK_LEFT) {
			direction = Direction::Left;
		}
		else if (wParam == VK_RIGHT) {
			direction = Direction::Right;
		}

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		if (wParam == '+') {
			if (MX_SPEED <= speed) {
				speed -= 10;
				KillTimer(hWnd, 1);
				SetTimer(hWnd, 1, speed, NULL); // ù���� �ֹ����� �ӵ�
				SendMessage(hWnd, WM_TIMER, 1, 0);
			}
		}
		else if (wParam == '-') {
			if (speed <= MN_SPEED) {
				speed += 10;
				KillTimer(hWnd, 1);
				SetTimer(hWnd, 1, speed, NULL); // ù���� �ֹ����� �ӵ�
				SendMessage(hWnd, WM_TIMER, 1, 0);
			}
		}
		else if (wParam == VK_SPACE && jumping.jump == 0) {
			jumping.jump = JUMP_POWER;
			jumping.direction = direction;
		}
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
									 /*   --------------     �� �� �� �� �� ^ ^                 ------------   */
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hBrush[0] = CreateSolidBrush(RGB(255, 0, 0)); // ����
		

		switch (head_color) {
		case Color::magenta:
			hBrush[1] = CreateSolidBrush(RGB(255, 150, 255)); // �Ķ�
			hBrush[2] = CreateSolidBrush(RGB(255,0, 255)); // ���κ�
			break;
		case Color::cyan:
			hBrush[1] = CreateSolidBrush(RGB(150, 255, 255)); // �Ķ�
			hBrush[2] = CreateSolidBrush(RGB(0, 255, 255)); // ���κ�
			break;
		case Color::yellow:
			hBrush[1] = CreateSolidBrush(RGB(255, 255, 150)); // �Ķ�
			hBrush[2] = CreateSolidBrush(RGB(255, 255, 0)); // ���κ�
			break;
		case Color::random:
			hBrush[1] = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)); // �Ķ�
			hBrush[2] = CreateSolidBrush(RGB(rand()%255, rand() % 255, rand() % 255)); // ���κ�
			break;
			
		}
		
		hBrush[3] = CreateSolidBrush(RGB(255, 255 ,0)); // �ʷ�

		
		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc); // hdc�� ȣȯ��Ų��.
		HBITMAP Lay; // ���̾� ����
		Lay = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); // �ٺ� ���۸� ,hdc�� ȣȯ��Ű��.
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &rectView, hbrBackground);
			SetBkMode(LayDC, TRANSPARENT);
			//////<����� �׸���>//////////////////////////////////////////////////////////////////

			if (grid) {
				for (int i = 0; i < 40; ++i) {
					for (int j = 0; j < 40; ++j) {
						Rectangle(LayDC, j * 40, i * 40, (j + 1) * 40, (i + 1) * 40);
					}
				}
			}

			oldPen = (HPEN)SelectObject(LayDC, hPen); // ���ο� �� ��� ����

			for (i = 0; i < WARM_LENGTH; ++i) {
				if (i<length) {
					if (i == 0) {
						oldBrush = (HBRUSH)SelectObject(LayDC, hBrush[2]);
					}
					else {
						oldBrush = (HBRUSH)SelectObject(LayDC, hBrush[1]);
					}

					if (i == 0) {
					
						switch (direction) {
						case Direction::Left:
						
							x1 = (warm[i].right - warm[i].left) / 2 * sin(PI*(270 + mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							x2 = (warm[i].right - warm[i].left) / 2 * sin(PI*(270 - mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							y1 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(270 + mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							y2 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(270 - mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							Pie(LayDC, warm[i].left, warm[i].top, warm[i].right, warm[i].bottom, x1, y1, x2, y2); // �Ӹ��� �׸���
							break;
						case Direction::Right:
							x1 = (warm[i].right - warm[i].left) / 2 *sin(PI*(90+mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							x2 = (warm[i].right - warm[i].left) / 2 *sin(PI*(90-mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							y1 = (warm[i].bottom - warm[i].top) / 2 *cos(PI*(90+mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							y2 = (warm[i].bottom - warm[i].top) / 2 *cos(PI*(90-mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							Pie(LayDC, warm[i].left, warm[i].top, warm[i].right, warm[i].bottom, x1, y1, x2, y2); // �Ӹ��� �׸���
							break;
						case Direction::Up:
							x1 = (warm[i].right - warm[i].left) / 2 * sin(PI*(mouseani*(MX_MOUSE + moremouth) + 180) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							x2 = (warm[i].right - warm[i].left) / 2 * sin(PI*(-mouseani*(MX_MOUSE + moremouth) + 180) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							y1 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(mouseani*(MX_MOUSE + moremouth) + 180) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							y2 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(-mouseani*(MX_MOUSE + moremouth) + 180) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							Pie(LayDC, warm[i].left, warm[i].top, warm[i].right, warm[i].bottom, x1, y1, x2, y2); // �Ӹ��� �׸���
							break;
						case Direction::Down:
							x1 = (warm[i].right - warm[i].left) / 2 * sin(PI*(mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							x2 = (warm[i].right - warm[i].left) / 2 * sin(PI*(-mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].left + (warm[i].right - warm[i].left) / 2;
							y1 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							y2 = (warm[i].bottom - warm[i].top) / 2 * cos(PI*(-mouseani*(MX_MOUSE + moremouth)) / 180) + warm[i].top + (warm[i].bottom - warm[i].top) / 2;
							Pie(LayDC, warm[i].left, warm[i].top, warm[i].right, warm[i].bottom, x1, y1, x2, y2); // �Ӹ��� �׸���
							break;


						}
					
					
					
					
					}
					
					else {
						Ellipse(LayDC, warm[i].left, warm[i].top, warm[i].right, warm[i].bottom); // �Ӹ��� �׸���
					}
					SelectObject(LayDC, oldBrush);
				}
			}
			oldBrush = (HBRUSH)SelectObject(LayDC, hBrush[3]);
			for (i = 0; i < MX_NUM_FOOD; ++i) {
				if (food[i].exist == true) {
					Ellipse(LayDC, food[i].pos.left, food[i].pos.top, food[i].pos.right, food[i].pos.bottom); // �Ӹ��� �׸���
				}
			}
			SelectObject(LayDC, oldBrush);

			oldBrush = (HBRUSH)SelectObject(LayDC, hBrush[0]);
			for (i = 0; i < MX_NUM_FOOD; ++i) {
				if (bomb[i].exist == true) {
					Rectangle(LayDC, bomb[i].pos.left, bomb[i].pos.top, bomb[i].pos.right, bomb[i].pos.bottom); // �Ӹ��� �׸���
				}
			}
			SelectObject(LayDC, oldBrush);

			/*   --------------     �� �� �� �� ��  - - !              ------------   */
			if (S_OFF<enemy_created) { // �� ���� Ʈ���Ű� �ߵ�������
				oldBrush = (HBRUSH)SelectObject(LayDC, hBrush[0]);
				for (i = 0; i < WARM_LENGTH; ++i) {
					if (enemy_warm[i].left != '\0') {
						if(i!=0)
						Ellipse(LayDC, enemy_warm[i].left, enemy_warm[i].top, enemy_warm[i].right, enemy_warm[i].bottom); // �Ӹ��� �׸���
						else {
							switch (e_direction) {
							
							case Direction::Left:

								x1 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(270 + mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								x2 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(270 - mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								y1 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(270 + mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								y2 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(270 - mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								Pie(LayDC, enemy_warm[i].left, enemy_warm[i].top, enemy_warm[i].right, enemy_warm[i].bottom, x1, y1, x2, y2); // �Ӹ��� �׸���
								break;
							case Direction::Right:
								x1 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(90 + mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								x2 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(90 - mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								y1 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(90 + mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								y2 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(90 - mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								Pie(LayDC, enemy_warm[i].left, enemy_warm[i].top, enemy_warm[i].right, enemy_warm[i].bottom, x1, y1, x2, y2); // �Ӹ��� �׸���
								break;
							case Direction::Up:
								x1 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(mouseani*MX_MOUSE + 180) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								x2 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(-mouseani*MX_MOUSE + 180) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								y1 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(mouseani*MX_MOUSE + 180) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								y2 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(-mouseani*MX_MOUSE + 180) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								Pie(LayDC, enemy_warm[i].left, enemy_warm[i].top, enemy_warm[i].right, enemy_warm[i].bottom, x1, y1, x2, y2); // �Ӹ��� �׸���
								break;
							case Direction::Down:
								x1 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								x2 = (enemy_warm[i].right - enemy_warm[i].left) / 2 * sin(PI*(-mouseani*MX_MOUSE) / 180) + enemy_warm[i].left + (enemy_warm[i].right - enemy_warm[i].left) / 2;
								y1 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								y2 = (enemy_warm[i].bottom - enemy_warm[i].top) / 2 * cos(PI*(-mouseani*MX_MOUSE) / 180) + enemy_warm[i].top + (enemy_warm[i].bottom - enemy_warm[i].top) / 2;
								Pie(LayDC, enemy_warm[i].left, enemy_warm[i].top, enemy_warm[i].right, enemy_warm[i].bottom, x1, y1, x2, y2); // �Ӹ��� �׸���
								break;
							
							
							
							
							
							
							}
						
						
						
						
						}
					}
				}

			}


			/*  ----------------------------------------------------------------------    */





			SelectObject(LayDC, oldBrush);
			SelectObject(LayDC, oldPen);
			DeleteObject(hBrush[0]);
			DeleteObject(hBrush[1]);
			DeleteObject(hBrush[2]);
			DeleteObject(hBrush[3]);
			DeleteObject(hPen);






			//////////////////////////////////////////////////////////////////////
			BitBlt(hdc, 0, 0, rectView.right,rectView.bottom, LayDC, 0, 0, SRCCOPY);
		}


		DeleteObject(Lay);
		DeleteObject(hdc);

		DeleteDC(LayDC);
		DeleteDC(hdc);




		

		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE: // �����찡 �ٽ� �׷�����
		GetClientRect(hWnd, &rectView);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_GAME_START:
			gameon = true;
			break;
		case ID_GAME_END:
			gameon = false;
			break;
		case ID_COLOR_CYAN:
			head_color = Color::cyan;
			break;
		case ID_COLOR_MAGENTA:
			head_color = Color::magenta;
			break;
		case ID_COLOR_YELLOW:
			head_color = Color::yellow;
			break;
		case ID_COLOR_RANDOM:
			head_color = Color::random;
			break;
		case ID_FOODBOMB_10:
			creating = true;
			num_food = 0;
			num_bomb = 0;

			for (i = 0; i < 30; ++i) {
				food[i] = { {0,0,0,0},false };
				bomb[i] = { { 0,0,0,0 },false };
			}
			

			for (i = 0; i <10; ++i) {
				x = rand() % rectView.right - ITEM_SIZE + 20;
				y = rand() % rectView.bottom - ITEM_SIZE + 20;
				food[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_food++;
			}
			for (i = 0; i <10; ++i) {
				x = rand() % rectView.right + 20;
				y = rand() % rectView.bottom + 20;
				bomb[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_bomb++;
			}

			creating = false;
			break;
		case ID_FOODBOMB_20:
			creating = true;
			num_food = 0;
			num_bomb = 0;

			for (i = 0; i < 30; ++i) {
				food[i] = { { 0,0,0,0 },false };
				bomb[i] = { { 0,0,0,0 },false };
			}

			for (i = 0; i <20; ++i) {
				x = rand() % rectView.right - ITEM_SIZE + 20;
				y = rand() % rectView.bottom - ITEM_SIZE + 20;
				food[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_food++;
			}
			for (i = 0; i <20; ++i) {
				x = rand() % rectView.right + 20;
				y = rand() % rectView.bottom + 20;
				bomb[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_bomb++;
			}

			creating = false;
			break;
		case ID_FOODBOMB_30:
			creating = true;
			num_food = 0;
			num_bomb = 0;

			for (i = 0; i < 30; ++i) {
				food[i] = { { 0,0,0,0 },false };
				bomb[i] = { { 0,0,0,0 },false };
			}

			for (i = 0; i < 30; ++i) {
				x = rand() % rectView.right - ITEM_SIZE;
				y = rand() % rectView.bottom - ITEM_SIZE;
				food[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_food++;
			}
			for (i = 0; i < 30; ++i) {
				x = rand() % rectView.right + 20;
				y = rand() % rectView.bottom + 20;
				bomb[i] = { { x,y,x + ITEM_SIZE,y + ITEM_SIZE },true };
				num_bomb++;
			}

			creating = false;

			break;
		case ID_GRID_ON:
			grid = true;
			break;
		case ID_GRID_OFF:
			grid = false;
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		PostQuitMessage(0);
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}

