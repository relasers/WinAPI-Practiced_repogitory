#include<Windows.h>
#include<Tchar.h> 
#include<time.h>


#define BODY_SIZE 20 // �ֹ��� ��ü�� �������
#define MORE_SIZE 8 // Ŀ�ٶ� ���� �Ӹ�

#define CLIENT_WIDTH 800 // Ŭ���̾�Ʈ ����ũ��
#define CLIENT_HEIGHT 800 // Ŭ���̾�Ʈ ����ũ��
#define MX_SPEED 10 // ���� �ִ�ӵ� / �������� ������
#define MN_SPEED 200 // ���� �ּҼӵ� / Ŭ���� ������
#define DEFAULT_SPEED 70 // ������ �ʱ� �ӵ�

#define E_SPEED 100 // �� �ֹ����� �ӵ� 

#define S_OFF 0 // ����ġ ����
#define S_ON 1 // ����ġ ����

#define JUMP_POWER 10 // ����

typedef struct {
	int hx; //�Ӹ� (head_x)
	int hy; //�Ӹ� (head_y)
	int tx; // ���� (tail_x)
	int ty; // ���� (tail_y)
}Warm;

typedef enum {
	Left, Right, Up, Down
}Direction;

typedef struct {
	int jump;
	int direction;
}Jumping;

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 3-1"; // �̰� �������� ������ �����ڵ� ���������� �׷���
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
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	static int direction = Direction::Right; // �ֹ����� �̵����� �ʱ�� �������̴�.
	static RECT rectView; // â ũ�⸦ �����ϴ� RECT ����ü

	static Warm warm; // �ֹ����� �ʱ� ��ġ
	static Warm temp; // â ���� ������� �Ӹ��� ������ �¹ٲٱ����� �ӽ� ��ġ ���� ��

	static Warm enemy;


	static int speed = DEFAULT_SPEED; // �ֹ����� �ʱ� �ӵ�

	static Jumping jumping = {0,Direction::Right}; // ���� ����ü ����

	static int enemy_created = S_OFF; // ���� �����Ǿ���


	srand((unsigned)time(NULL));
	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView);
		warm = { BODY_SIZE * 10 , BODY_SIZE * 10 , warm.hx - BODY_SIZE , warm.hy - BODY_SIZE };
		enemy = { BODY_SIZE * 2 , BODY_SIZE * 2 , enemy.hx - BODY_SIZE , enemy.hy - BODY_SIZE };
		SetTimer(hWnd, 1, speed, NULL); // ù���� �ֹ����� �ӵ�
		SetTimer(hWnd, 2, 5000, NULL); // �� �ֹ����� �����ȴ� // 5000ms �� �ڿ� ���� �����ȴ�
		return 0;
////////////////////////////////////////////////////////////////////////////////////
	case WM_TIMER:
		switch (wParam) {
		case 1: // �� ������ �����δ�
			if (0 < jumping.jump) {
				if (direction == Direction::Right || direction == Direction::Left) {
					if (JUMP_POWER/2 < jumping.jump) {
						warm.tx = warm.hx;
						warm.ty = warm.hy;
						warm.hy -= BODY_SIZE;
						enemy.tx = enemy.hx;
						enemy.ty = enemy.hy;
						enemy.hy -= BODY_SIZE;
					}
					else {
						warm.tx = warm.hx;
						warm.ty = warm.hy;
						warm.hy += BODY_SIZE;
						enemy.tx = enemy.hx;
						enemy.ty = enemy.hy;
						enemy.hy += BODY_SIZE;
					}
					jumping.jump--;

					if (warm.hy < 0)
						warm.hy = 0;
					if (enemy.hy < 0)
						enemy.hy = 0;
				}
				else if (direction == Direction::Down || direction == Direction::Up) {
					if (JUMP_POWER/2 < jumping.jump) {
						warm.tx = warm.hx;
						warm.ty = warm.hy;
						warm.hx += BODY_SIZE;
						enemy.tx = enemy.hx;
						enemy.ty = enemy.hy;
						enemy.hx += BODY_SIZE;
					}
					else {
						warm.tx = warm.hx;
						warm.ty = warm.hy;
						warm.hx -= BODY_SIZE;
						enemy.tx = enemy.hx;
						enemy.ty = enemy.hy;
						enemy.hx -= BODY_SIZE;
					}
					jumping.jump--;

					if (rectView.right < warm.hx + BODY_SIZE*2)
						warm.hx = rectView.right - BODY_SIZE;
					if (rectView.right < enemy.hx + BODY_SIZE*2)
						enemy.hx = rectView.right - BODY_SIZE;
				}
			}
			

			switch (direction) {
			case Direction::Up:
				if (warm.hy <= 0) {
					temp = { warm.hx,warm.hy,0,0 };
					warm = { warm.tx,warm.ty,temp.hx,temp.hy };
					direction = Direction::Down;
				}
				else {
					warm.tx = warm.hx;
					warm.ty = warm.hy;
					warm.hy -= BODY_SIZE;
					if (warm.hy <= 0) {
						warm.hy = 0;
						warm.ty = BODY_SIZE;
					}
				}
				break;
			case Direction::Down:
				if (rectView.bottom <= warm.hy + BODY_SIZE * 2) {
					temp = { warm.hx,warm.hy,0,0 };
					warm = { warm.tx,warm.ty,temp.hx,temp.hy };
					direction = Direction::Up;
				}
				else {
					warm.tx = warm.hx;
					warm.ty = warm.hy;
					warm.hy += BODY_SIZE;
					if (rectView.bottom <= warm.hy + BODY_SIZE) {
						warm.hy = rectView.bottom - BODY_SIZE;
						warm.ty = warm.hy - BODY_SIZE;
					}
				}

				break;
			case Direction::Left:
				if (warm.hx <= 0) {
					temp = { warm.hx,warm.hy,0,0 };
					warm = { warm.tx,warm.ty,temp.hx,temp.hy };
					direction = Direction::Right;
				}
				else {
					warm.tx = warm.hx;
					warm.ty = warm.hy;
					warm.hx -= BODY_SIZE;

					if (warm.hx < 0) { // �Ӹ��� ���� ���� �Ѿ�� 0 ���� ���������ش�
						warm.hx = 0;
						warm.tx = BODY_SIZE;
					}
				}

				break;
			case Direction::Right:
				if (rectView.right <= warm.hx + BODY_SIZE) {
					temp = { warm.hx,warm.hy,0,0 };
					warm = { warm.tx,warm.ty,temp.hx,temp.hy };
					direction = Direction::Left;
				}
				else {
					warm.tx = warm.hx;
					warm.ty = warm.hy;
					warm.hx += BODY_SIZE;
					if (rectView.right <= warm.hx + BODY_SIZE) { // �Ӹ��� ������ ���� �Ѿ�� ��-BODY_SIZE �� ��ġ�� �������Ѵ�
						warm.hx = rectView.right-BODY_SIZE;
						warm.tx = warm.hx - BODY_SIZE;
					}
				}
			}
			break;
		case 2: // Ÿ�̸� 2�� ������ �� �ֹ��� Ÿ�̸Ӹ� �ҷ��´�
			KillTimer(hWnd, 2);
			enemy_created = S_ON;
			SetTimer(hWnd, 3, E_SPEED, NULL); // �� �ֹ����� �����ȴ�
			break;
		case 3: // �� �ֹ����� �׳��� �߰��ϴ� �κ�
			enemy.tx = enemy.hx;
			enemy.ty = enemy.hy;
			if (enemy.hx < warm.hx) {
				enemy.hx += BODY_SIZE;
			}// ������ ���� �����ʿ� �ִ�!

			if (warm.hx < enemy.hx) {
				enemy.hx -= BODY_SIZE;

			}// ������ ���� ���ʿ� �ִ�!
			if (enemy.hy < warm.hy) {
				enemy.hy += BODY_SIZE;
			}// ������ ���� �Ʒ��ʿ� �ִ�!

			if (warm.hy < enemy.hy) {
				enemy.hy -= BODY_SIZE;
			}// ������ ���� ���ʿ� �ִ�!
			break;
	
		}
		
		InvalidateRect(hWnd, &rectView, TRUE);
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
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		if (wParam == '+') {
			if (MX_SPEED <= speed) {
				speed -= 10;
				KillTimer(hWnd, 1);
				SetTimer(hWnd, 1, speed, NULL); // ù���� �ֹ����� �ӵ�
				SendMessage(hWnd,WM_TIMER,1,0);
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
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
/*   --------------     �� �� �� �� �� ^ ^                 ------------   */
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� ��� ����
		hBrush = CreateSolidBrush(RGB(50, 130, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		Ellipse(hdc, warm.hx, warm.hy, warm.hx + BODY_SIZE, warm.hy + BODY_SIZE); // �Ӹ��� �׸���

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� ��� ����
		hBrush = CreateSolidBrush(RGB(150, 200, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		Ellipse(hdc, warm.tx, warm.ty, warm.tx + BODY_SIZE, warm.ty + BODY_SIZE); // ������ �׸���
		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
/*   --------------     �� �� �� �� ��  - - !              ------------   */
		if (S_OFF<enemy_created ) { // �� ���� Ʈ���Ű� �ߵ�������
			hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� ��� ����
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Ellipse(hdc, enemy.hx-MORE_SIZE, enemy.hy- MORE_SIZE, enemy.hx + BODY_SIZE+ MORE_SIZE, enemy.hy + BODY_SIZE+ MORE_SIZE); // ������ �׸���
			SelectObject(hdc, oldBrush);
			SelectObject(hdc, oldPen);

			hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
			oldPen = (HPEN)SelectObject(hdc, hPen); // ���ο� �� ��� ����
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Ellipse(hdc, enemy.tx, enemy.ty, enemy.tx + BODY_SIZE, enemy.ty + BODY_SIZE); // ������ �׸���
			SelectObject(hdc, oldBrush);
			SelectObject(hdc, oldPen);
		}


/*  ----------------------------------------------------------------------    */

		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(hPen);

		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE: // �����찡 �ٽ� �׷�����
		GetClientRect(hWnd, &rectView);
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
