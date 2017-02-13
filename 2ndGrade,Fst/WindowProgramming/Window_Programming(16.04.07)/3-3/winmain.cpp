//////////////////// �ְ�� ������� 3-2 �ڵ� ///////////////////////////////

#include<Windows.h>
#include<Tchar.h> 
#include<time.h>
#include<math.h> // ���� ���� ���� �����س���

#define T_LIGHT 50 // ��ȣ�� ������
#define T_LIGHT_POSIT 150 // ��ȣ�� ��ġ

#define CLIENT_WIDTH 800 // Ŭ���̾�Ʈ ����ũ��
#define CLIENT_HEIGHT 400 // Ŭ���̾�Ʈ ����ũ��

#define CAR_SIZE 200
#define CAR_H_SIZE 40
#define CAR_INTERVAL 70
#define S_OFF 0 // ����ġ ����
#define S_ON 1 // ����ġ ����

#define N_CAR 3 // �ڵ��� ��

HINSTANCE g_hInst;
LPCTSTR IpszClass = L"Window Class 3-3"; // �̰� �������� ������ �����ڵ� ���������� �׷���
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
	HBRUSH hBrush[5], oldBrush;

	static RECT rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) }; // â ũ�⸦ �����ϴ� RECT ����ü
	static RECT traffic_light[3];
	static RECT car[N_CAR];
	static bool red_on = false;
	static bool yellow_on = false;
	static bool green_on = true;
	static wchar_t temp[2];
	int i; // �ݺ��� ������
	static int counter=0;
	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��  
	case WM_CREATE:
		rectView = { 0,0,LOWORD(lParam),HIWORD(lParam) };
		GetClientRect(hWnd, &rectView); // ������ â ũ�⸦ ���س���.
		for (i = 0; i < 3; ++i) {
			traffic_light[i] = { rectView.right - (3-i) * T_LIGHT,0,rectView.right - (2-i) * T_LIGHT,T_LIGHT };
			car[i] = {(i+1)*CAR_INTERVAL,(i+1)*CAR_INTERVAL,(i + 1)*CAR_INTERVAL+CAR_SIZE,(i + 1)*CAR_INTERVAL + CAR_H_SIZE };
		}

		SetTimer(hWnd, 1, 50, NULL); // ��ũ��
		return 0;
		////////////////////////////////////////////////////////////////////////////////////
	case WM_TIMER:
		switch (wParam) {
		case 1:
			if (green_on == true||yellow_on == true) {
				OffsetRect(&car[0], 10, 0);
				OffsetRect(&car[1], -20, 0);
				OffsetRect(&car[2], 30, 0);
			}
			for (i = 0; i < N_CAR; ++i) {
				if (rectView.right <= car[i].left) {
					car[i].left = 0;
					car[i].right = CAR_SIZE;
				}
				if (i == 1 && car[i].left <= 0) {
					car[i].left = rectView.right;
					car[i].right = rectView.right+CAR_SIZE;
				}
			}
			break;
		case 2:
			counter--;
			MessageBeep(MB_OK);
			if (counter == 0) {
				KillTimer(hWnd, 2);
				red_on = true;
				yellow_on = false;
				green_on = false;
			}
			break;
		}
		
		InvalidateRect(hWnd, &rectView, TRUE);
		break;
		//////////////////////////////////////////////////////////////////////////////////////////
	case WM_KEYDOWN:
		hdc = GetDC(hWnd);
		if (wParam == 'B' || wParam == 'b') { // �Ķ���
			red_on = false;
			yellow_on = false;
			green_on = true;
		}
		else if (wParam == 'Y' || wParam == 'y') { // �����
			red_on = false;
			yellow_on = true;
			green_on = false;
			counter = 4;
			SetTimer(hWnd, 2, 1000, NULL);
			SendMessage(hWnd,WM_TIMER,2,NULL);
		}
		else if (wParam == 'R' || wParam == 'r') { // ������
			red_on = true;
			yellow_on = false;
			green_on = false;
		}

		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		hdc = GetDC(hWnd);
		ReleaseDC(hWnd, hdc);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
		hBrush[0] = (HBRUSH)GetStockObject(NULL_BRUSH);
		hBrush[1] = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		hBrush[2] = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
		hBrush[3] = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
		hBrush[4] = (HBRUSH)CreateSolidBrush(RGB(20, 150, 255));

		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, traffic_light[0].left, traffic_light[0].top, traffic_light[2].right, traffic_light[2].bottom);
		for (i = 0; i < 3; ++i) {
			SelectObject(hdc, oldBrush);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[0]);
			if (i == 0 && red_on == true) {
				SelectObject(hdc, oldBrush);
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush[i + 1]);
			}
			if (i == 1 && yellow_on == true) {
				SelectObject(hdc, oldBrush);
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush[i + 1]);
				if (0 < counter) {
					wsprintf(temp,TEXT("%d..."),counter);
					DrawText(hdc,temp,-1,&rectView,DT_VCENTER|DT_CENTER);
				}
			}
			if (i == 2 && green_on == true) {
				SelectObject(hdc, oldBrush);
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush[i + 1]);
			}
			Ellipse(hdc, traffic_light[i].left,traffic_light[i].top, traffic_light[i].right, traffic_light[i].bottom);
			SelectObject(hdc, oldBrush);
		}

		for (i = 0; i < 3; ++i) {
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush[4]);
			Rectangle(hdc, car[i].left, car[i].top, car[i].right, car[i].bottom);
			if (rectView.right <= car[i].right) {
				Rectangle(hdc, 0, car[i].top, car[i].right-rectView.right, car[i].bottom);
			}
			if (i == 1 && car[i].left <= 0) {
				Rectangle(hdc, car[i].right - rectView.right, car[i].top, rectView.right, car[i].bottom);
			}
			SelectObject(hdc, oldBrush);
		}

		///////////////////////////////////////////////������Ʈ���� �����////////////////////
		DeleteObject(hBrush[0]);
		DeleteObject(hBrush[1]);
		DeleteObject(hBrush[2]);
		DeleteObject(hBrush[3]);
		DeleteObject(hBrush[4]);
		EndPaint(hWnd, &ps);

		break;
	case WM_SIZE: // �����찡 �ٽ� �׷�����
		GetClientRect(hWnd, &rectView);
		for (i = 0; i < 3; ++i) {
			traffic_light[i] = { rectView.right - (3 - i) * T_LIGHT,0,rectView.right - (2 - i) * T_LIGHT,T_LIGHT };
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}

