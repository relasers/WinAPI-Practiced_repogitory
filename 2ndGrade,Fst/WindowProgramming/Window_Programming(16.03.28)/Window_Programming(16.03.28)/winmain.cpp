#include<Windows.h>
#include<Tchar.h> 
HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class Name"; // �̰� �������� ������ �����ڵ� ���������� �׷���
										  // L"���ڿ�" ���ڿ� �տ� �빮�� L�� ���δ� �ƴϸ� �����ڵ忡�� ��Ƽ����Ʈ�� �ٲٴ���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);

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
		800, // ������ ����ũ��
		600, //������ ����ũ��
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam) {
	PAINTSTRUCT ps;
	HDC hDC; // �׻� ù��° ���ڴ� hDC ��! 
	RECT rect; // �簢�� ����ü ����
	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_PAINT: //������ �ٽ� �׷���� �� ��, ȭ���� �������� OS���� �޼��� ���� (ó�� ����, �ٸ� ������ �������ִٰ� �ٽ� ���� ��, â ũ�� �ٲ�InvalidateRect(), InvalidateRgn()�Լ��� ȣ���Ͽ� ������ ȭ���� ��ȿȭ��ų ��)
		hDC = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
		rect.left = 0; // �簢�� ����
		rect.top = 0;
		rect.right = 780;  // �� �ٿ��� -> ���ڿ� ��ϱ� �߸�
		rect.bottom = 560; // �� �ٿ��� -> ������ ������ ũ�Ⱑ Ÿ��Ʋ�� �����̶� �̰� �����̸� �߷�
		SetTextColor(hDC, RGB(77, 255, 240));
		SetBkColor(hDC, RGB(178, 0, 15));
		DrawText(hDC, L"LeftTop (0, 0)", -1, &rect, DT_SINGLELINE | DT_TOP | DT_LEFT); // 3��° ���� -1 : NULL ���� ���ö������� ���̸� ���Ѵٴ°�
		SetTextColor(hDC, RGB(0, 255, 104));
		SetBkColor(hDC, RGB(255, 0, 151));
		DrawText(hDC, L"RightTop (800, 0)", -1, &rect, DT_SINGLELINE | DT_TOP | DT_RIGHT );
		SetTextColor(hDC, RGB(0, 0, 255));
		SetBkColor(hDC, RGB(255, 255, 0));
		DrawText(hDC, L"Center (300, 400)", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		SetTextColor(hDC, RGB(255, 85, 0));
		SetBkColor(hDC, RGB(0, 175, 255));
		DrawText(hDC, L"LeftBottom (0, 800)", -1, &rect, DT_SINGLELINE | DT_BOTTOM | DT_LEFT);
		SetTextColor(hDC, RGB(0,0,178));
		SetBkColor(hDC, RGB(255, 255, 77));
		DrawText(hDC, L"RightBottom (600, 800)", -1, &rect, DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);
		// strlen(temp) �� ��Ƽ����Ʈ������ �����Ѵ�
		// �����ڵ忡�� �����ִ� �Լ��� wcslen �� �ִ�!!!
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}