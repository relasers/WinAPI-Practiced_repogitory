#include<Windows.h>
#include<Tchar.h> 
#include<time.h>

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
		800, //������ ����ũ��
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

	srand((unsigned)time(NULL));
	PAINTSTRUCT ps;
	HDC hDC; // �׻� ù��° ���ڴ� hDC ��! 
	RECT rect[20][20];

	wchar_t temp[40] = { 0 };
	int i, j;
	int number = rand() % 6; // ������ ��
	int seed = 0; // �̰� �� �����Ǽ� �� �������� �ٽ� 0���� �ʱ�ȭ�ȴ�
	int change = 0; // �� ���� 2�� ���� ��ĭ�� ��ĭ ���� �ƴ� ��ǥ���� �����Ѵ�
	for (i = 0; i < 20; ++i) {
		for (j = 0; j < 20; ++j) {
			rect[i][j] = {
			j*40, // Left
			i*20, // Top
			40+j*40, // Right
			20+i*20, // Bottom
			};
		}
	}
	//�����ڵ带 ����� ���� char ��� wchar_t �� ���� ���ڿ� �տ� L�� ���δ�

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hDC = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
		
		for (i = 0; i < 20; ++i) {
			for (j = 0; j < 20; ++j) {

				if (change % 2 == 0) {
					if (j % 2 == 0 || number == 0) {
						wsprintf(temp, TEXT("(%d,%d)"), j + 1, i + 1);
						SetTextColor(hDC, RGB(rand() % 220, rand() % 220, rand() % 220));
						DrawText(hDC, temp, -1, &rect[i][j], DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOCLIP);
					}
				}
				else {
					if (j % 2 == 1 || number == 0) {
						wsprintf(temp, TEXT("(%d,%d)"), j + 1, i + 1);
						SetTextColor(hDC, RGB(rand() % 220, rand() % 220, rand() % 220));
						DrawText(hDC, temp, -1, &rect[i][j], DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOCLIP);
					}
				}
			}
			seed++;
			if (seed == number) {
				change++;
				seed = 0;
			}
		}
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