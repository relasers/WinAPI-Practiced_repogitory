#include "stdafx.h"
#include "FrameWork.h"


CFrameWork::CFrameWork()
{

}

CFrameWork::~CFrameWork()
{
	Destroy();
}
// Ŭ���� �Լ������� ������� �ϴ°� �ƴϰ� cpp ���Ͽ� �Ѵ�.
bool CFrameWork::Initial(HWND h, RECT r,HINSTANCE inst) {
	// ������ �տ� �ڷ��� ���� �װ� ���������� �Ǿ������
	m_hwnd = h;
	m_rect = r;
	m_hInst = inst;
	return m_hwnd != NULL; // ������ ���� �����ϸ� ������ �ڵ��� NULL ���� ����.
						   // �̰��� NULL���� ��� �����찡 ����� ��������� �ʾҴٴ°�, �ΰ��̸� �����츦 �׿���!
}
void CFrameWork::Destroy() { // ��ȯ���� ��� �������, ��¼�� �����״ϱ�, �޸� ���� ����
							 //�Ҹ��ڷ� �Ҹ��Ҷ� Destroy ȣ��, �Ҹ��ڴ� �Լ��� �׾�߸� ���´� , ���̰� �ٽ� �����ϰ� ������ ����
							 // �븦 �հ� �Ҷ� -> �׋��� ���� �Լ��� �̸� �� ���´�
	PostQuitMessage(0);
};

LRESULT CFrameWork::WindowMessage(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��
	case WM_TIMER:
		OnTimer(wParam);
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEMOVE:
		InputMouse(iMessage, wParam, lParam);
		break;
		/////////////////////////////////////////
	case WM_CHAR:
	case WM_KEYDOWN:
	case WM_KEYUP:
		InputKeyBoard(iMessage, wParam, lParam);
		break;
		///////////////////////////////////////////
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
		hdc = BeginPaint(hwnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)
		
		OnDraw(hdc); // hdc �� OnDraw �� �ѱ��.

		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		WindowMenu(hwnd, iMessage, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hwnd, iMessage, wParam, lParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}

void CFrameWork::OnCreate() { // ���߿� 3-1�б⋚ BuildObject �� ���� , �����޸� ������ ��
	GetClientRect(m_hwnd,&m_rect);
	SetTimer(m_hwnd,1,1,NULL);
}
void CFrameWork::OnDraw(HDC hdc) { //����� ��ο츦 ó���Ѵ�
	
	HDC LayDC;
	LayDC = CreateCompatibleDC(hdc); // hdc�� ȣȯ��Ų��.
	HBITMAP Lay; // ���̾� ����
	Lay = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom); // �ٺ� ���۸� ,hdc�� ȣȯ��Ű��.
	SelectObject(LayDC, Lay);
	{
		ClearScreen(LayDC); // ȭ�� Ŭ����
		MemDC = CreateCompatibleDC(LayDC); // �̰� ��Ʈ�� �Ѹ����

		SetBkMode(LayDC, TRANSPARENT);
		//////<����� �׸���>//////////////////////////////////////////////////////////////////

		MoveToEx(LayDC,0,m_rect.bottom/2,NULL);
		LineTo(LayDC, m_rect.right, m_rect.bottom/2);

		MoveToEx(LayDC, m_rect.right/2, 0, NULL);
		LineTo(LayDC,m_rect.right/2,m_rect.bottom);
		
		switch (Radiostat) {
		case TriFun::sa:
			for (f = -500; f < 700; ++f) {
				y = (double)(sin(f*3.14 / 180)*h);
				
				for (int i = -1; i < 1; ++i) {
					for (int j = -1; j < 1; ++j) {
						SetPixel(LayDC, j + m_rect.right / 2 + xpos + (double)f,
							i + m_rect.bottom / 2 + y,
							RGB(Checkstat[Col::Re] * 255, Checkstat[Col::Gr] * 255, Checkstat[Col::Bl] * 255));
						if (Checkstat[0] == 1 && Checkstat[1] == 1 && Checkstat[2] == 1)
							SetPixel(LayDC, j + m_rect.right / 2 + xpos + (double)f,
								i + m_rect.bottom / 2 + y,
								RGB(rand() % 255, rand() % 255, rand() % 255));
					}
				}
			}
			break;
		case TriFun::co:
			for (f = -500; f < 700; ++f) {
				y = (double)(cos(f*3.14 / 180)*h);
				for (int i = -1; i < 1; ++i) {
					for (int j = -1; j < 1; ++j) {
						SetPixel(LayDC, j+m_rect.right / 2 + xpos + (double)f,
							i+m_rect.bottom / 2 + y,
							RGB(Checkstat[Col::Re] * 255, Checkstat[Col::Gr] * 255, Checkstat[Col::Bl] * 255));
						if (Checkstat[0] == 1 && Checkstat[1] == 1 && Checkstat[2] == 1)
							SetPixel(LayDC, j+m_rect.right / 2 + xpos + (double)f,
								i+m_rect.bottom / 2 + y,
								RGB(rand() % 255, rand() % 255, rand() % 255));
					}
				}
				
			}
			break;
		case TriFun::ta:
			for (f = -500; f < 700; ++f) {
				y = (double)(tan(f*3.14 / 180)*h);
				for (int i = -1; i < 1; ++i) {
					for (int j = -1; j < 1; ++j) {
						SetPixel(LayDC, j + m_rect.right / 2 + xpos + (double)f,
							i + m_rect.bottom / 2 + y,
							RGB(Checkstat[Col::Re] * 255, Checkstat[Col::Gr] * 255, Checkstat[Col::Bl] * 255));
						if (Checkstat[0] == 1 && Checkstat[1] == 1 && Checkstat[2] == 1)
							SetPixel(LayDC, j + m_rect.right / 2 + xpos + (double)f,
								i + m_rect.bottom / 2 + y,
								RGB(rand() % 255, rand() % 255, rand() % 255));
					}
				}
			}
			break;
		}
		
		//////////////////////////////////////////////////////////////////////
		BitBlt(hdc, 0, 0, m_rect.right, m_rect.bottom, LayDC, 0, 0, SRCCOPY);
	}
	

	DeleteObject(Lay);
	DeleteObject(hdc);

	DeleteDC(LayDC);
	DeleteDC(MemDC);
	DeleteDC(hdc);

}
void CFrameWork::OnTimer(UINT id) {
	switch (id) {
	case WT_COUNTING:
		if (movupdown) {
			if (udstat == CTSTAT::Inc) {
				++h;
				if (MX_UD <= h) {
					udstat = CTSTAT::Dec;
					break;
				}
			}
			else {
				--h;
				if (MN_UD >= h) {
					udstat = CTSTAT::Inc;
					break;
				}
			}
		}
			
		if (movleft) {
			xpos-=1;
			if (-360 >= xpos)
				xpos = 0;
		}
			

		break;
	}
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::InputMouse(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_LBUTTONDOWN:
		InvalidateRect(m_hwnd, &m_rect, FALSE);
		break;
	}
}

void CFrameWork::InputKeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_KEYDOWN:

		DLGPROC dialogFunc = [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> INT_PTR { return framework.WindowDialogProc(hwnd, msg, wParam, lParam); };
		
		DialogBox(m_hInst, MAKEINTRESOURCE(IDD_DIALOG1), m_hwnd, dialogFunc);
		break;
	}
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::CreateBkBrush(COLORREF color) {
	if (hbrBackground) DeleteObject(hbrBackground);
	hbrBackground = (HBRUSH)CreateSolidBrush(color);
}
void CFrameWork::ClearScreen(HDC hdc) {
	FillRect(hdc,&m_rect,hbrBackground);
}

LRESULT CFrameWork::WindowMenu(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (iMessage)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		
		}
		EndDialog(hwnd, LOWORD(wParam));
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}

BOOL CFrameWork::WindowDialogProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	switch (iMessage)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hwnd,
			IDC_RADIO_SIN, IDC_RADIO_TAN, IDC_RADIO_SIN);
		return (BOOL)true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_CHECK_RED:
			Checkstat[Col::Re] = 1 - Checkstat[Col::Re];
			break;
		case IDC_CHECK_GREEN:
			Checkstat[Col::Gr] = 1 - Checkstat[Col::Gr];
			break;
		case IDC_CHECK_BLUE:
			Checkstat[Col::Bl] = 1 - Checkstat[Col::Bl];
			break;
		case IDC_RADIO_SIN:
			Radiostat = TriFun::sa;
			break;
		case IDC_RADIO_COS:
			Radiostat = TriFun::co;
			break;
		case IDC_RADIO_TAN:
			Radiostat = TriFun::ta;
			break;
		case IDC_BUTTON_MTLEFT:
			if (movleft) {
				movleft = false;
				break;
			}
			movleft = true;
			break;
		case IDC_BUTTON_MTUD:
			if (movupdown) {
				movupdown = false;
				break;
			}
			movupdown = true;
			break;
		case IDC_BUTTON_STOP:
			movleft = false;
			movupdown = false;
			break;
		case IDC_BUTTON_RESET:
			h = 50;
			xpos = 0;
			break;
		case IDC_BUTTON_EXIT:
			Destroy();
			EndDialog(hwnd, 0);
			break;
		}
		return (BOOL)true;
	}
	return (BOOL)false;
}
