#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include <math.h>
#include"resource.h"

#define CLIENT_WIDTH 800 // Ŭ���̾�Ʈ ����ũ��
#define CLIENT_HEIGHT 800 // Ŭ���̾�Ʈ ����ũ��
#define WT_ANIMATION 1 // �ִϸ��̼� �޼���
#define WT_MOVE 2 // �����δ�

#define GRAVITY 0.05 // �����Ŀ�
#define GRAVITY_ACCEL 0.15 // �߷°��ӵ�

typedef struct {
	POINT pos; // �� ��ǥ
	int z_pos;// z ��ǥ
	int stat; // �� ����
	int dir; // ����
	int speed; // �ӵ�
	float vec_y; // ���Ϻ���
}Pone; // ��

typedef enum {
	stand,move,jump,clmoving // ���ִ�,�����δ�,�����Ѵ�,Ŭ�����̵��Ѵ�
}Pone_Stat;

typedef enum {
left,right,down,up
}Direction;

	HINSTANCE hInst;
	LPCTSTR IpszClass = L"Window Class 5-5"; // �̰� �������� ������ �����ڵ� ���������� �׷���
											 // L"���ڿ�" ���ڿ� �տ� �빮�� L�� ���δ� �ƴϸ� �����ڵ忡�� ��Ƽ����Ʈ�� �ٲٴ���
	LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow) { // WinMain ��ҹ��� �ؼ��� ��!
		HWND hWnd;
		MSG Message;
		WNDCLASSEX WndClass; // EX �� �ٿ��� �ǰ� �Ⱥٿ��� �ȴ�.
		hInst = hInstance;

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

		static POINT mouse;

		static HDC hdc, memdc;// �׻� ù��° ���ڴ� hDC ��! 

		static HBITMAP Bit_Back;
		static HBITMAP Bit_move;
		static HBITMAP Bit_moveto;
		static HBITMAP Bit_stand;
		static HBRUSH brush_shadow;
		HBRUSH oldbrush;
		static RECT ponerect;
		static RECT rectView;
		static RECT rectPos;

		static Pone pone; // ��
		static bool moving; // Ű�� �������� �����̴°�?
		static bool jumping;
		static int movedist;

		static unsigned int mainframe;
		static int poneframe;

		//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

		switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
		case WM_CREATE:
			rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
			GetClientRect(hWnd, &rectView);

			Bit_Back = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
				MAKEINTRESOURCE(IDB_BACK));
			Bit_stand = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
				MAKEINTRESOURCE(IDB_STAND));
			Bit_move = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
				MAKEINTRESOURCE(IDB_MOVE));
			Bit_moveto = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
				MAKEINTRESOURCE(IDB_MOVETO));

			pone = {
				{rectView.right / 2,rectView.bottom / 2},0,Pone_Stat::stand,Direction::left,5,0
			}; // ��ǥ,z��,����,����,�ӵ�
			brush_shadow = (HBRUSH)GetStockObject(BLACK_BRUSH);
			moving = false;
			jumping = false;
			movedist =0;
			SetTimer(hWnd, WT_ANIMATION, 60, NULL);
			SetTimer(hWnd, WT_MOVE, 60, NULL);
			return 0;

		case WM_TIMER:
			switch (wParam) {
			case WT_ANIMATION:
				mainframe++;
				poneframe = mainframe % 4;
				break;
			case WT_MOVE:
				
				if (movedist <= 0) {
					if (moving == true) {
						switch (pone.dir) {
						case Direction::left:
							pone.pos.x -= pone.speed;
							break;
						case Direction::right:
							pone.pos.x += pone.speed;
							break;
						case Direction::up:
							pone.pos.y -= pone.speed;
							break;
						case Direction::down:
							pone.pos.y += pone.speed;
							break;
						}
					}
				}
				else {
					movedist--;
					switch (pone.dir) {
					case Direction::left:
						pone.pos.x -= pone.speed;
						break;
					case Direction::right:
						pone.pos.x += pone.speed;
						break;
					case Direction::up:
						pone.pos.y -= pone.speed;
						break;
					case Direction::down:
						pone.pos.y += pone.speed;
						break;
					}
					if (movedist <= 0) {
						pone.stat = Pone_Stat::stand;
					}
				}
				

				if (pone.vec_y >= 0) {
					pone.vec_y += GRAVITY_ACCEL;
				}
				else {
					pone.vec_y += GRAVITY_ACCEL + GRAVITY;
				}
				if (jumping == true) {
					pone.z_pos -= pone.vec_y;
				}
				
				if (jumping == true && pone.z_pos <= 0) {
					pone.stat = Pone_Stat::stand;
					jumping = false;
					pone.vec_y = 0;
					pone.z_pos = 0;
				}
					


				break;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case WM_KEYDOWN:
			if (movedist <= 0) {
				switch (wParam) {
				case VK_LEFT:
					moving = true;
					if (jumping == false) {
						pone.stat = Pone_Stat::move;
					}
					pone.dir = Direction::left;
					break;
				case VK_RIGHT:
					moving = true;
					if (jumping == false) {
						pone.stat = Pone_Stat::move;
					}
					pone.dir = Direction::right;
					break;
				case VK_UP:
					moving = true;
					if (jumping == false) {
						pone.stat = Pone_Stat::move;
					}
					pone.dir = Direction::up;
					break;
				case VK_DOWN:
					moving = true;
					if (jumping == false) {
						pone.stat = Pone_Stat::move;
					}

					pone.dir = Direction::down;
					break;
				case 'j':
				case 'J':
					pone.stat = Pone_Stat::jump;
					jumping = true;
					pone.vec_y = -4.5;
				}
			}
				
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case WM_KEYUP:
			moving = false;
			if (pone.z_pos == 0) {
				pone.stat = Pone_Stat::stand;
			}
			
			break;
		case WM_LBUTTONDOWN:
			ponerect = { pone.pos.x,pone.pos.y,
			pone.pos.x + 32,pone.pos.y + 64
			};
			mouse.x = LOWORD(lParam);
			mouse.y = HIWORD(lParam);
			if (PtInRect(&ponerect, mouse)) {
				pone.stat = Pone_Stat::clmoving;
				movedist = 10;
				pone.dir = rand() % 4;
			}
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case WM_PAINT: //������ �ٽ� �׷���� �� ��
			hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
			memdc = CreateCompatibleDC(hdc);

			HDC LayDC;
			LayDC = CreateCompatibleDC(hdc);
			HBITMAP Lay;
			HBRUSH block_brush;
			int block_color; // �� ���� �ٲٱ�� ����
			Lay = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
			SelectObject(LayDC, Lay);
			{

				SelectObject(memdc, Bit_Back);

				// mem1dc�� �ִ� ������ hdc�� �ѷ��ش�.
				BitBlt(LayDC, 0, 0, 800, 800
					, memdc, 0, 0, SRCCOPY); // ���� �׸��� // SRCCOPY : �������� �����ϰ� �׷���

				switch (pone.stat) {
				case Pone_Stat::stand:
					SelectObject(memdc, Bit_stand);
					break;
				case Pone_Stat::move:
					SelectObject(memdc, Bit_move);
					break;
				case Pone_Stat::jump:
					SelectObject(memdc, Bit_moveto);
					break;
				case Pone_Stat::clmoving:
					SelectObject(memdc, Bit_moveto);
					break;
				}
				oldbrush = (HBRUSH)SelectObject(LayDC,brush_shadow);
				Ellipse(LayDC, pone.pos.x, pone.pos.y + 58, pone.pos.x + 32, pone.pos.y + 68);
				TransparentBlt(LayDC,pone.pos.x,pone.pos.y-pone.z_pos,
					32,64,memdc,poneframe*32,0,32,64,RGB(255,255,0));
				

			BitBlt(hdc, 0, 0, 800, 800, LayDC, 0, 0, SRCCOPY);
			}
			DeleteObject(Lay);
			DeleteDC(LayDC);
			DeleteDC(memdc);
			EndPaint(hWnd, &ps);
			break;
		case WM_SIZE: // �����찡 �ٽ� �׷�����
			GetClientRect(hWnd, &rectView);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		} //ó���� �޽����� case���� ����
		return(DefWindowProc(hWnd, iMessage, wParam, lParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
	}

