#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include <math.h>
#include"resource.h"

#define CLIENT_WIDTH 800 // Ŭ���̾�Ʈ ����ũ��
#define CLIENT_HEIGHT 800 // Ŭ���̾�Ʈ ����ũ��
typedef enum {
	normal, mul1_2, mul1_4 // 3x3,4x4,5x5,��ü
}Mode;

typedef struct {
	int nXD;
	int nYD;
	int nW;
	int nH;
	int nXS;
	int nYS;
	int nWS;
	int nHS;
}CI; // copyimage

HINSTANCE hInst;
LPCTSTR IpszClass = L"Window Class 5-2"; // �̰� �������� ������ �����ڵ� ���������� �׷���
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
	static HBITMAP hBitmap;

	static RECT rectView;
	static RECT rectPos;
	static RECT m_glass; // ������ ���� ����ü
	static CI copy_image;
	static CI paste_image;

	static int screen_mode;

	static POINT start; //POINT�� ����
	static POINT old;

	static bool Drag;
	static bool isCopy;
	static float multiply;

	int endX, endY;
	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView);
		GetWindowRect(hWnd, &rectPos); //���� ��������  ��ġ 

		screen_mode = Mode::normal;
		multiply = 1;
		hBitmap = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
			MAKEINTRESOURCE(IDB_BITMAP1));
		start.x = old.x = 50;
		start.y = old.y = 50; // ���� ��ǥ
		Drag = false;
		isCopy = false;

		return 0;
	case WM_LBUTTONDOWN:
		Drag = true;
		
		m_glass.left = m_glass.right = LOWORD(lParam); 
		m_glass.top = m_glass.bottom = HIWORD(lParam); // ���� ��ǥ
		
		  InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_LBUTTONUP:
		
		if (Drag)
		{
			POINT local_ptstart;
			POINT local_ptend;

			local_ptstart = POINT{
				min(start.x, old.x),
				min(start.y, old.y)
			};
			local_ptend = POINT{
				max(start.x, old.x),
				max(start.y, old.y)
			};

			start = local_ptstart;
			old = local_ptend;
		}
		
		Drag = false;
		
		
		
		break;

	case WM_MOUSEMOVE:
		if (Drag == true)
		{ // �� ����
																// �� ���� XOR �� �� = ������ ��
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);

			m_glass.right = endX;
			m_glass.bottom = endY; // �� ������ �̠� �������� ����
		}
		  InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_CHAR:
		if (wParam == '0') {
			screen_mode = Mode::normal;
			multiply = 1;
		}
		else if (wParam == '1') {
			screen_mode = Mode::mul1_2;
			multiply = 0.8;
		}
		else if (wParam == '2') {
			screen_mode = Mode::mul1_4;
			multiply = 0.6;
		}
		else if (wParam == 'c' || wParam == 'C') {
			copy_image.nXD = 0;
			copy_image.nYD = 0;
			copy_image.nW = (m_glass.right - m_glass.left);
			copy_image.nH = (m_glass.bottom - m_glass.top);
			copy_image.nXS = 800 * m_glass.left / rectView.right;
			copy_image.nYS = 800 * m_glass.top / rectView.bottom;
			copy_image.nWS = 800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left)*multiply;
			copy_image.nHS = 800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top)*multiply;
			
		}
		else if (wParam == 'p' || wParam == 'P') {
			isCopy = true;
			if (isCopy == true) {
				paste_image = copy_image;
			}
		}

		if (isCopy == true) {
		
			paste_image.nXD = 0;
			paste_image.nYD = 0;
			paste_image.nW = (m_glass.right - m_glass.left);
			paste_image.nH = (m_glass.bottom - m_glass.top);
			paste_image.nXS = 800 * m_glass.left / rectView.right;
			paste_image.nYS = 800 * m_glass.top / rectView.bottom;
			paste_image.nWS = 800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left)*multiply;
			paste_image.nHS = 800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top)*multiply;
		
		}
		  InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_UP || wParam == VK_DOWN || wParam == VK_RIGHT || wParam == VK_LEFT) {
			switch (wParam) {
			case VK_UP:
				OffsetRect(&m_glass, 0, -5);
				break;
			case VK_DOWN:
				OffsetRect(&m_glass, 0, 5);
				break;
			case VK_RIGHT:
				OffsetRect(&m_glass, 5, 0);
				break;
			case VK_LEFT:
				OffsetRect(&m_glass, -5, 0);
				break;
			}
		}
		if (isCopy == true) {

			paste_image.nXD = 0;
			paste_image.nYD = 0;
			paste_image.nW = (m_glass.right - m_glass.left);
			paste_image.nH = (m_glass.bottom - m_glass.top);
			paste_image.nXS = 800 * m_glass.left / rectView.right;
			paste_image.nYS = 800 * m_glass.top / rectView.bottom;
			paste_image.nWS = 800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left)*multiply;
			paste_image.nHS = 800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top)*multiply;

		}
		  InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc);
		HBITMAP Lay;
		Lay = CreateCompatibleBitmap(hdc, 800, 800);
		SelectObject(LayDC, Lay);

		{

			memdc = CreateCompatibleDC(LayDC);
			SelectObject(memdc, hBitmap);

			StretchBlt(LayDC, 0, 0, rectView.right, rectView.bottom, memdc, 0, 0, 800, 800, SRCCOPY);
			// SRCCOPY : �������� �����ϰ� �׷���

			Rectangle(LayDC, m_glass.left - 1, m_glass.top - 1, m_glass.right + 1, m_glass.bottom + 1);



			switch (screen_mode) {
			case Mode::normal:
				StretchBlt(LayDC, m_glass.left, m_glass.top, (m_glass.right - m_glass.left), (m_glass.bottom - m_glass.top),
					memdc, 800 * m_glass.left / rectView.right, 800 * m_glass.top / rectView.bottom,
					800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left),
					800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top), SRCCOPY);
				break;
			case Mode::mul1_2:
			case Mode::mul1_4:
				StretchBlt(LayDC, m_glass.left, m_glass.top, (m_glass.right - m_glass.left), (m_glass.bottom - m_glass.top),
					memdc, 800 * m_glass.left / rectView.right, 800 * m_glass.top / rectView.bottom,
					800 * (m_glass.right - m_glass.left) / (rectView.right - rectView.left)*multiply,
					800 * (m_glass.bottom - m_glass.top) / (rectView.bottom - rectView.top)*multiply, SRCCOPY);
				break;
			}

			if (isCopy == true) {
				StretchBlt(LayDC, 0, 0, paste_image.nW, paste_image.nH,
					memdc, paste_image.nXS, paste_image.nYS,
					paste_image.nWS, paste_image.nHS, SRCCOPY);
			}

			if (Drag)
			{
				FrameRect(LayDC, &m_glass, (HBRUSH)GetStockObject(BLACK_BRUSH));
//				Rectangle(LayDC, m_glass.left, m_glass.top, endX, endY);
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

