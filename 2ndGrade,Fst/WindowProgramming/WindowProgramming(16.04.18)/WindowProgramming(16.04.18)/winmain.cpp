#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include <math.h>
#include"resource.h"

#define CLIENT_WIDTH 800 // Ŭ���̾�Ʈ ����ũ��
#define CLIENT_HEIGHT 800 // Ŭ���̾�Ʈ ����ũ��

typedef enum {
	by3,by4,by5,full // 3x3,4x4,5x5,��ü
}Mode;

HINSTANCE hInst;
LPCTSTR IpszClass = L"Window Class 5-1"; // �̰� �������� ������ �����ڵ� ���������� �׷���
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
	RECT temp; //�簢�� ����ü �浹 üũ��
	int i,j;
	static int screen_mode;
	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView);
		GetWindowRect(hWnd, &rectPos); //���� ��������  ��ġ 

		screen_mode = Mode::full;

		hBitmap = (HBITMAP)LoadBitmap(hInst, // hinstance �μ��� ������ ������ HINSTANCE ������..
			MAKEINTRESOURCE(IDB_BITMAP1));

		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd, &rectView, TRUE);
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hWnd);
		InvalidateRect(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		if (wParam == 'A' || wParam == 'a') {
			screen_mode = Mode::full;
		}
		else if (wParam == '3'){
			screen_mode = Mode::by3;
		}
		else if (wParam == '4') {
			screen_mode = Mode::by4;
		}
		else if (wParam == '5') {
			screen_mode = Mode::by5;
		}

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
		memdc = CreateCompatibleDC(hdc);
		SelectObject(memdc, hBitmap);
		switch (screen_mode) {
		case Mode::by3:
			for (i = 0;i<3;++i) {
				for (j = 0; j < 3; ++j) {
					StretchBlt(hdc, rectView.right / 3 * i, rectView.bottom / 3 * j, rectView.right / 3, rectView.bottom / 3, memdc,
						0,0,800,800, SRCCOPY);
				}
			}
			
			break;
		case Mode::by4:
			for (i = 0; i<4; ++i) {
				for (j = 0; j < 4; ++j) {
					StretchBlt(hdc, rectView.right / 4 * i, rectView.bottom / 4 * j, rectView.right / 4, rectView.bottom / 4, memdc,
						0, 0, 800, 800, SRCCOPY);
				}
			}
			break;
		case Mode::by5:
			for (i = 0; i<5; ++i) {
				for (j = 0; j < 5; ++j) {
					StretchBlt(hdc, rectView.right / 5 * i, rectView.bottom / 5 * j, rectView.right / 5, rectView.bottom / 5, memdc,
						0, 0, 800, 800, SRCCOPY);
				}
			}
			break;
		case Mode::full:
			StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, memdc, 0, 0, 800, 800, SRCCOPY);
			break;
		}
		// SRCCOPY : �������� �����ϰ� �׷���
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

