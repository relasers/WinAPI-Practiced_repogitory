#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include <math.h>
#include"resource.h"

#define CLIENT_WIDTH 800 // Ŭ���̾�Ʈ ����ũ��
#define CLIENT_HEIGHT 800 // Ŭ���̾�Ʈ ����ũ��

typedef enum {
	jayu,full,by2,by3,by4,by5
}Screen;

typedef struct {
	RECT posit;
	bool select;
}Board;

typedef struct {
	int nXD;
	int nYD;
	int nW;
	int nH;
	int nXS;
	int nYS;
	int nWS;
	int nHS;
	int selX;
	int selY;
	bool copied;
}CI; // copyimage

bool isPointinRect(RECT rc,int x,int y) {
	if ((rc.left <= x&&x <= rc.right) && (rc.top <= y && y <= rc.bottom)) {
		return true;
	}
	return false;
} // ���� �簢���� �浹�n


HINSTANCE hInst;
LPCTSTR IpszClass = L"Window Class 5-3"; // �̰� �������� ������ �����ڵ� ���������� �׷���
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

	HDC hdc, memdc;; // �׻� ù��° ���ڴ� hDC ��! 
	HBRUSH nullBrush,oldBrush;
	HPEN selectPen,normalPen, oldPen;
	static HBITMAP hBitmap;

	static RECT rectView;
	static RECT m_glass; // ������ ���� ����ü

	static CI paste_image[5][5];

	static Board board[3][3];
	static int sel_X=-1; //���ð���
	static int sel_Y=-1; //���ü���

	static float screen_mode;

	static int startX, startY, oldX, oldY;
	static int mx = 0, my = 0; // ���콺
	static bool Drag;
	static bool isCopy;
	static float multiply;
	int i, j;
	int endX, endY;
	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView);

		multiply = 1;
		hBitmap = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
			MAKEINTRESOURCE(IDB_BITMAP2));
		startX = oldX = 50; startY = oldY = 50; // ���� ��ǥ
		Drag = false;
		isCopy = false;

		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; ++j) {
				board[i][j].posit = { i*rectView.right / 6, j*rectView.bottom / 3,
					(i + 1)*rectView.right / 6, (j + 1)*rectView.bottom / 3 };
				board[i][j].select = false;
			}
		} // ���� �׸���
		for (i = 0; i < 5; ++i) {
			for (j = 0; j < 5; ++j) {
				paste_image[i][j].copied = false;
			}
		}
		return 0;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);

		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; ++j) {
				if (0 <= mx&&mx <= rectView.right / 2) {
					board[i][j].select = false;
					if (isPointinRect(board[i][j].posit, mx, my)) {
						board[i][j].select = true;
						sel_X = i;
						sel_Y = j;
					}
				}
			}
		}
		if (sel_X != -1 && sel_Y != -1) {
			if (screen_mode == Screen::jayu) {
				if (rectView.right / 2 <= mx&&mx <= rectView.right) {
					Drag = true;
					m_glass.left = m_glass.right = LOWORD(lParam); m_glass.top = m_glass.bottom = HIWORD(lParam); // ���� ��ǥ
					ReleaseDC(hWnd, hdc);
					InvalidateRect(hWnd, NULL, FALSE);
				}
			}
			else {
				for (i = 0; i < screen_mode; ++i) {
					for (j = 0; j < screen_mode; ++j) {
						if ((rectView.right / 2 + rectView.right / 2 / screen_mode*j
							<= mx&&mx <= rectView.right / 2 + rectView.right / 2 / screen_mode*(j + 1)) &&
							(rectView.bottom / screen_mode*i <= my && my <= rectView.bottom / screen_mode*(i + 1))) {
							paste_image[i][j].nXD = rectView.right / 2 + rectView.right / 2 / screen_mode*j;
							paste_image[i][j].nYD = (rectView.bottom / screen_mode)*i;
							paste_image[i][j].nW = rectView.right / 2 / screen_mode;
							paste_image[i][j].nH = rectView.bottom / screen_mode;
							paste_image[i][j].selX = sel_X;
							paste_image[i][j].selY = sel_Y;
							paste_image[i][j].copied = true;
						}
					}
				}
			}
		}
		

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		Drag = false;
		if (screen_mode == Screen::jayu) {
			paste_image[0][0].nXD = m_glass.left;
			paste_image[0][0].nYD = m_glass.top;
			paste_image[0][0].nW = (m_glass.right - m_glass.left);
			paste_image[0][0].nH = (m_glass.bottom - m_glass.top);
			paste_image[0][0].nXS = 800 * m_glass.left / rectView.right;
			paste_image[0][0].nYS = 800 * m_glass.top / rectView.bottom;
			paste_image[0][0].nWS = 800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left)*multiply;
			paste_image[0][0].nHS = 800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top)*multiply;
			paste_image[0][0].selX = sel_X;
			paste_image[0][0].selY = sel_Y;
			paste_image[0][0].copied = true;
		}
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hWnd);
		if (Drag == true)
		{ // �� ����
			SetROP2(hdc, R2_XORPEN); // ���� XOR ����
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN)); // �� ��
																// �� ���� XOR �� �� = ������ ��
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);
			Rectangle(hdc, m_glass.left, m_glass.top, m_glass.right, m_glass.bottom);
			Rectangle(hdc, m_glass.left, m_glass.top, endX, endY);
			m_glass.right = endX; m_glass.bottom = endY; // �� ������ �̠� �������� ����
		}
		InvalidateRect(hWnd, NULL, FALSE);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		if (wParam == '0') {
			screen_mode = Screen::jayu;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		else if (wParam == '1') {
			screen_mode = Screen::full;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		else if (wParam == '2') {
			screen_mode = Screen::by2;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		else if (wParam == '3') {
			screen_mode = Screen::by3;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		else if (wParam == '4') {
			screen_mode = Screen::by4;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		else if (wParam == '5') {
			screen_mode = Screen::by5;
			for (i = 0; i < 5; ++i) {
				for (j = 0; j < 5; ++j) {
					paste_image[i][j].copied = false;
				}
			}
		}
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
		memdc = CreateCompatibleDC(hdc);
		nullBrush = (HBRUSH)GetStockObject(NULL_BRUSH); // ��귯��
		selectPen = (HPEN)CreatePen(PS_SOLID,2,RGB(255,0,0)); // ���� ��
		normalPen = (HPEN)CreatePen(PS_DASH, 1, RGB(255, 255, 0)); // ���� ��

		SelectObject(memdc, hBitmap);

		StretchBlt(hdc, 0, 0, rectView.right/2, rectView.bottom, memdc, 0, 0, 400, 800, SRCCOPY);
		
		// SRCCOPY : �������� �����ϰ� �׷���
		
		
		if (screen_mode == Screen::jayu) {
			Rectangle(hdc, m_glass.left - 1, m_glass.top - 1, m_glass.right + 1, m_glass.bottom + 1);
			if (paste_image[0][0].copied == true) {
				StretchBlt(hdc, paste_image[0][0].nXD, paste_image[0][0].nYD,
					paste_image[0][0].nW, paste_image[0][0].nH,
					memdc, paste_image[0][0].selX*(400 / 3), paste_image[0][0].selY*(800 / 3),
					400 / 3, 800 / 3, SRCCOPY); // ����� �׸��� �׸���
			}
			
		}

		else {
			for (i = 0; i < screen_mode; ++i) {
				for (j = 0; j < screen_mode; ++j) {
					Rectangle(hdc, rectView.right/2+rectView.right/2/(screen_mode)*j
						, rectView.bottom/screen_mode*i,
						rectView.right / 2 + rectView.right / 2 / (screen_mode)*(j+1),
						rectView.bottom / screen_mode*(i+1));
					if (paste_image[i][j].copied == true) {
						StretchBlt(hdc, paste_image[i][j].nXD, paste_image[i][j].nYD,
							paste_image[i][j].nW, paste_image[i][j].nH,
							memdc, paste_image[i][j].selX*(400 / 3), paste_image[i][j].selY*(800 / 3),
							400 / 3, 800 / 3, SRCCOPY);
					}
				}
			}
		}


		oldBrush = (HBRUSH)SelectObject(hdc, nullBrush);
		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; ++j) {
				oldPen = (HPEN)SelectObject(hdc,normalPen);
				if (board[i][j].select == true) {
					SelectObject(hdc, oldPen);
					oldPen = (HPEN)SelectObject(hdc, selectPen);
				}
				Rectangle(hdc, board[i][j].posit.left, board[i][j].posit.top,
					board[i][j].posit.right, board[i][j].posit.bottom);
				SelectObject(hdc, oldPen);
			}
		} // ���� �׸��� // ĭ�� ������
		SelectObject(hdc, oldBrush);

		DeleteDC(memdc);
		DeleteObject(selectPen);
		DeleteObject(normalPen);
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE: // �����찡 �ٽ� �׷�����
		GetClientRect(hWnd, &rectView);

		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; ++j) {
				board[i][j].posit = { i*rectView.right / 6, j*rectView.bottom / 3,
					(i + 1)*rectView.right / 6, (j + 1)*rectView.bottom / 3 };
				board[i][j].select = false;
			}
		} // ���� �׸���
		for (i = 0; i < screen_mode; ++i) {
			for (j = 0; j < screen_mode; ++j) {
				paste_image[i][j].nXD = rectView.right / 2 + rectView.right / 2 / screen_mode*j;
				paste_image[i][j].nYD = (rectView.bottom / screen_mode)*i;
				paste_image[i][j].nW = rectView.right / 2 / screen_mode;
				paste_image[i][j].nH = rectView.bottom / screen_mode;
			}
		}
		
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}

