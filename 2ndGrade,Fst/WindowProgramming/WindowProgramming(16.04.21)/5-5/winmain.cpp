#include <Windows.h>
#include <Tchar.h> 
#include <time.h>
#include <math.h>
#include"resource.h"

#define CLIENT_WIDTH 800 // Ŭ���̾�Ʈ ����ũ��
#define CLIENT_HEIGHT 800 // Ŭ���̾�Ʈ ����ũ��

#define WT_ANIMATION 1
#define WT_UPDATE 2
#define WT_BACKGROUND 3

#define GRAVITY 0.5
#define GRAVITY_ACCEL 0.15

//bool keydown[255] = { 0, };

typedef struct {
	RECT pos;
	bool moving;
	int dir;
	double vec_y;
}Player;

typedef struct {
	RECT pos;
	bool exist;
}Explode;

typedef enum {
	left,right
}player_dir;

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
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, //������ ��Ÿ��
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

	static HDC hdc, memdc;
	static HBITMAP Bit_Back1;
	static HBITMAP Bit_Back2;
	static HBITMAP Bit_Explosion;
	static HBITMAP Bit_Obstacle;
	static HBITMAP Bit_Player;

	static RECT rectView;
	static RECT rectPos;

	static RECT back_1;
	static RECT back_2;
	static RECT platform;
	static RECT obstacle;
	static Explode explode;

	static Player player;

	static unsigned int mainframe;
	static int playerframe;
	static int obstacleframe;
	static int explosionframe;
	int randomposobs;
	static RECT temp; //�簢�� ����ü �浹 üũ��

	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView);
		GetWindowRect(hWnd, &rectPos); //���� ��������  ��ġ 

		back_1 = { 0,0,800,800 };
		back_2 = { 0,400,800,800 };
		platform = { 0,700,800,800 };


		randomposobs = 620 + rand() % 30;
		obstacle = { 0,randomposobs,64,randomposobs+64 };

		player = { {500,500,532,548},false,player_dir::left,0 };

		explode = { {0,0,64,64}, false };

		Bit_Back1 = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
			MAKEINTRESOURCE(IDB_BITMAP1));
		Bit_Back2 = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
			MAKEINTRESOURCE(IDB_BITMAP2));
		Bit_Explosion = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
			MAKEINTRESOURCE(IDB_BITMAP3));
		Bit_Obstacle = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
			MAKEINTRESOURCE(IDB_BITMAP4));
		Bit_Player = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
			MAKEINTRESOURCE(IDB_BITMAP5));

		mainframe = 0;
		playerframe = 0;
		explosionframe = 0;

		SetTimer(hWnd, WT_BACKGROUND, 10, NULL);
		SetTimer(hWnd, WT_ANIMATION, 60, NULL);
		SetTimer(hWnd, WT_UPDATE, 10, NULL);
		return 0;

	case WM_TIMER:
		randomposobs = 620 + rand() % 30;
		switch (wParam) {
		case WT_BACKGROUND:
			OffsetRect(&back_1, 2, 0);

			OffsetRect(&back_2, 5, 0);
			if (rectView.right < back_1.left) {
				back_1 = { 0,0,800,800 };
			}
			if (rectView.right < back_2.left) {
				back_2 = { 0,400,800,800 };
			}
			break;
		case WT_ANIMATION:
			(++mainframe) %= 21000;
			playerframe = mainframe % 10;
			obstacleframe = mainframe % 4;

			if (explode.exist == true) {
				explosionframe++;
				if (explosionframe > 6) {
					explode.exist = false;
					explosionframe = 0;
				}
			}

			break;
		case WT_UPDATE:

			if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
				player.dir = player_dir::left;
				player.moving = true;
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
				player.dir = player_dir::right;
				player.moving = true;
			}
			if (GetAsyncKeyState(VK_UP) & 0x8000) {
				player.vec_y = -10;
			}
			// ����! �̷����ϸ� Ű �浹�� ����!

			OffsetRect(&obstacle, 5, 0);
			if (rectView.right < obstacle.left) {
				obstacle = { -64,randomposobs,0,randomposobs+64 };
			}


			if (player.vec_y > 0) {
				player.vec_y += GRAVITY;
			}
			else
				player.vec_y += GRAVITY+GRAVITY_ACCEL;


			OffsetRect(&player.pos, 0, player.vec_y);

			if (IntersectRect(&temp, &platform, &player.pos)) {
				player.pos.top = platform.top - 49;
				player.pos.bottom = platform.top - 1;
				player.vec_y = 0;
			}

			if (IntersectRect(&temp, &obstacle, &player.pos)) {

				explode.pos = {
					player.pos.left,
					player.pos.top,
					player.pos.left + 64,
					player.pos.top + 64,
				};

				explode.exist = true;
				explosionframe = 0;
			}

			if (player.moving) {
				switch (player.dir) {
				case player_dir::left:
					OffsetRect(&player.pos, -5, 0);
					break;
				case player_dir::right:
					OffsetRect(&player.pos, 5, 0);
					break;
				}
			}

			

			break;
		}
	
		InvalidateRgn(hWnd, NULL, false);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		break;
	case WM_KEYDOWN:
		
		//key[wParam] = true;
		switch (wParam) {
		case VK_LEFT:
			player.dir = player_dir::left;
			player.moving = true;
			break;
		case VK_RIGHT:
			player.dir = player_dir::right;
			player.moving = true;
			break;
		case VK_UP:
			player.vec_y = -10;
			break;
		}
		
		
		InvalidateRect(hWnd,NULL,false);
		break;
	case WM_KEYUP:
		if(player.moving)
		player.moving = false;
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
		memdc = CreateCompatibleDC(hdc);

		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc);
		HBITMAP Lay;
		Lay = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom);
		SelectObject(LayDC, Lay);
		{

			SelectObject(memdc, Bit_Back1);

			BitBlt(LayDC, back_1.left, back_1.top, back_1.right - back_1.left, back_1.bottom - back_1.top
				, memdc, 0, 0, SRCCOPY); // ���� �׸��� // SRCCOPY : �������� �����ϰ� �׷���
			if (rectView.right < back_1.right) {
				BitBlt(LayDC, 0, back_1.top, back_1.left, back_1.bottom - back_1.top
					, memdc, 800 - back_1.left, 0, SRCCOPY); // ���� �׸��� // SRCCOPY : �������� �����ϰ� �׷���
			}
			SelectObject(memdc, Bit_Back2);

			TransparentBlt(LayDC, back_2.left, back_2.top, back_2.right - back_2.left, back_2.bottom - back_2.top
				, memdc, 0, 0,800,200, RGB(255,255,255)); // ���� �׸���
			if (rectView.right < back_2.right) {

				TransparentBlt(LayDC, 0, back_2.top, back_2.left, back_2.bottom - back_2.top
					, memdc, 800 - back_2.left, 0, back_2.left ,200, RGB(255, 255, 255)); // ���� �׸���

			}

			SelectObject(memdc, Bit_Obstacle);
			TransparentBlt(LayDC, obstacle.left, obstacle.top, 64, 64
				, memdc, obstacleframe*64, 0, 64, 64, RGB(255, 255, 255)); // ��ֹ��� �׸���

			SelectObject(memdc, Bit_Player);
			TransparentBlt(LayDC, player.pos.left, player.pos.top, 32, 48
				, memdc, playerframe * 32, 0, 32, 48, RGB(255, 255, 255)); // �÷��̾ �׸���

			if (explode.exist == true) {
				SelectObject(memdc, Bit_Explosion);
				TransparentBlt(LayDC, explode.pos.left, explode.pos.top, 64, 64
					, memdc, explosionframe * 64, 0, 64, 64, RGB(255, 255, 255)); // ��8�� �׸���
			}
			

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

