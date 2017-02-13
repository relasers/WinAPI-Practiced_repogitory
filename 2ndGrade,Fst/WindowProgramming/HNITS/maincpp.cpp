//  �����ڵ� ����Դϴ�.
#include "stdafx.h"
#include "resource.h"
#include <Windows.h>
#include <tchar.h>

#include "Framework.h"

//	LoadString : Ÿ��Ʋ �̸��� ������ Ŭ���� �̸� ����.
#define MAX_LOADSTRING 100

#define CLIENT_WIDTH 1200		// Ŭ���̾�Ʈ �ʺ�
#define CLIENT_HEIGHT 720		// Ŭ���̾�Ʈ ���� (��������������!!!!!!!)

#define WINTITLE	TEXT("Hunting Night in the Sanctuary")		//	Ŭ���̾�Ʈ Ÿ��Ʋ ���ڿ�
#define WINCLASSNAME	TEXT("winMain")			//	���� ������ Ŭ������

// ���� ����:
HINSTANCE hInst;							// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];				// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];		// �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
//LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

CFramework myFramework;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;

	wsprintf(szTitle, WINTITLE);
	wsprintf(szWindowClass, WINCLASSNAME);

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// �⺻ �޽��� �����Դϴ�.
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)	break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else myFramework.FrameAdvance();
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style =
		  CS_HREDRAW 	// Ŭ���̾�Ʈ�� �ʺ� �����ϸ�, ��ü �����츦 �ٽ� �׸��� �Ѵ�.
		| CS_VREDRAW	// Ŭ���̾�Ʈ�� ���̸� �����ϸ�, ��ü �����츦 �ٽ� �׸��� �Ѵ�.
	//	| CS_DBLCLKS	// �ش� �����쿡�� ����Ŭ���� ����ؾ� �Ѵٸ� �߰��ؾ� �Ѵ�.
		;
	wcex.lpfnWndProc = CFramework::WndProc;
//	wcex.lpfnWndProc = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) -> HRESULT
//	{return myFramework.OnProcessingWindowMessage(hWnd, message, wParam, lParam);};
//	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;	//	�ش� ���α׷��� �ν��Ͻ� �ڵ�.

//	MAKEINTERSOURCE : Make Inter Source. ���α׷� ���ο� �ִ� ���ҽ��� �ε����� ��ȯ�ϴ� ��ũ��.
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	//	���� ������ �ڵ�
	HWND hWnd;

	//	������ ��Ÿ��
	DWORD dwStyle =
		WS_OVERLAPPED 	// ����Ʈ ������. Ÿ��Ʋ �ٿ� ũ�� ������ �ȵǴ� ��輱�� ������. �ƹ��� ��Ÿ�ϵ� ���� ������ �� ��Ÿ���� ����ȴ�.
		| WS_CAPTION 		// Ÿ��Ʋ �ٸ� ���� �����츦 ����� WS_BORDER ��Ÿ���� �����Ѵ�.
		| WS_SYSMENU		// �ý��� �޴��� ���� �����츦 �����.
		| WS_MINIMIZEBOX	// �ּ�ȭ ��ư�� �����.
		| WS_BORDER			// �ܼ����� �� ��輱�� ����� ũ�� ������ �� �� ����.
//		| WS_THICKFRAME		// ũ�� ������ ������ �β��� ��輱�� ������. WS_BORDER�� ���� ����� �� ����.
		;					// �߰��� �ʿ��� ������ ��Ÿ���� http://www.soen.kr/lecture/win32api/reference/Function/CreateWindow.htm ����.

	//	�ν��Ͻ� �ڵ��� ���� ������ ����
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	//	����ũ�� ������ ������
	RECT getWinSize;
	GetWindowRect(GetDesktopWindow(), &getWinSize);

	//	Ŭ���̾�Ʈ ������
	RECT rc;
	rc.left = rc.top = 0;
	rc.right = CLIENT_WIDTH;
	rc.bottom = CLIENT_HEIGHT;
	//	������ ����� ������ �߰��Ǵ�(ĸ��, �ܰ��� ��) ũ�⸦ ����.
	AdjustWindowRect(&rc, dwStyle, FALSE);

	//	Ŭ���̾�Ʈ ������ǥ(left, top)
	//	����ũ���� �߾ӿ� Ŭ���̾�Ʈ�� ��ġ�ϵ��� ����
	POINT ptClientWorld;
	ptClientWorld.x = (getWinSize.right - CLIENT_WIDTH) / 2;
	ptClientWorld.y = (getWinSize.bottom - CLIENT_HEIGHT) / 2;

	//	������ ����
	hWnd = CreateWindow(
		szWindowClass			//	������ Ŭ���� ��
		, szTitle				//	ĸ�� ǥ�� ���ڿ�
		, dwStyle				//	������ ��Ÿ��
		, ptClientWorld.x		//	�θ� ������ ��� ������ ������ǥ : x
		, ptClientWorld.y		//	�θ� ������ ��� ������ ������ǥ : y
		, rc.right - rc.left	//	������ ������ : width
		, rc.bottom - rc.top	//	������ ������ : height
		, NULL					//	�θ� ������.
		, NULL					//	�޴� �ڵ�
		, hInstance				//	�ν��Ͻ� �ڵ�
		, NULL					//	�߰� �Ķ���� : NULL
		);

	//	���� ���н� ���α׷� ����
	//	Ȯ�� : WndProc�� default msg handler�� DefWindowProc �Լ��� ��ȯ�ϴ°�?
	if (!hWnd)	return FALSE;
	if (!myFramework.OnCreate(hWnd, rc)) return FALSE;
	//	������ ǥ��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//	���� ��ȯ
	return TRUE;
}
