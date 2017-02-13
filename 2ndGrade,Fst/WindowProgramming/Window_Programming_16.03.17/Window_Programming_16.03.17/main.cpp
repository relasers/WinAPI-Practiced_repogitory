#include<Windows.h>
//#include<Tchar.h> ����
HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name"; // �̰� �������� ������ �����ڵ� ���������� �׷���
// L"���ڿ�" ���ڿ� �տ� �빮�� L�� ���δ� �ƴϸ� �����ڵ忡�� ��Ƽ����Ʈ�� �ٲٴ���
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM IParam);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR IpszCmdParam,int nCmdShow){
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = IpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while(GetMessage(&Message,0,0,0)){
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT ps;
	HDC hDC;
	wchar_t temp[] = L"Hello World!!"; //�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�
	int x = 0, y = 0;

	switch (iMessage) {
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		TextOut(hDC, x, y, temp, wcslen(temp));
		// strlen(temp) �� ��Ƽ����Ʈ������ �����Ѵ�
		// �����ڵ忡�� �����ִ� �Լ��� wcslen �� �ִ�!!!


		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}