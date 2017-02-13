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
		hDlg = CreateDialog(m_hInst,
			MAKEINTRESOURCE(IDD_CALCULATOR),
			m_hwnd, dialogFunc);
		ShowWindow(hDlg, SW_SHOW);
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
		return (BOOL)true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_0:
			Operand = 0;
			Display(Operand);
			break;
		case IDC_BUTTON_1:
			Operand = 1;
			Display(Operand);
			break;
		case IDC_BUTTON_2:
			Operand = 2;
			Display(Operand);
			break;
		case IDC_BUTTON_3:
			Operand = 3;
			Display(Operand);
			break;
		case IDC_BUTTON_4:
			Operand = 4;
			Display(Operand);
			break;
		case IDC_BUTTON_5:
			Operand = 5;
			Display(Operand);
			break;
		case IDC_BUTTON_6:
			Operand = 6;
			Display(Operand);
			break;
		case IDC_BUTTON_7:
			Operand = 7;
			Display(Operand);
			break;
		case IDC_BUTTON_8:
			Operand = 8;
			Display(Operand);
			break;
		case IDC_BUTTON_9:
			Operand = 9;
			Display(Operand);
			break;
		case IDC_BUTTON_BINARY:
			bin = true;
			for (int i = 0; i < 128; ++i) {
				Show[i] = '\0';
			}
			tep = _wtof(Buffer);
			if (bin == true)
				_ltow_s(tep, Show, 2);
			if (bin == false) {
				_ltow_s(tep, Show, 10);
			}
			SetDlgItemText(hDlg, IDC_EDIT, Show);
			break;
		case IDC_BUTTON_DECIMAL:
			bin = false;
			for (int i = 0; i < 128; ++i) {
				Show[i] = '\0';
			}
			tep = _wtof(Buffer);
			if (bin == true)
				_ltow_s(tep, Show, 2);
			if (bin == false) {
				_ltow_s(tep, Show, 10);
			}
			SetDlgItemText(hDlg, IDC_EDIT, Show);
			break;
		case IDC_BUTTON_DOT:
			if (Buffer[lstrlen(Buffer) - 1] != '.') {
				lstrcat(Buffer, TEXT("."));
				for (int i = 0; i < 128; ++i) {
					Show[i] = '\0';
				}
				tep = _wtof(Buffer);
				if (bin == true)
					_ltow_s(tep, Show, 2);
				if (bin == false) {
					_ltow_s(tep, Show, 10);
				}
				SetDlgItemText(hDlg, IDC_EDIT, Show);
			}
			break;
		case IDC_BUTTON_EQUAL:
			Equal();
			Buffer[0] = 0;
			Display(Result);
			Buffer[0] = 0;
			afterresult = true;
			break;
		case IDC_BUTTON_MULTIPLY:
			Operator = Yunsan::Ymulti;
			Operation();
			break;
		case IDC_BUTTON_SUBTRACT:
			Operator = Yunsan::Ysubtract;
			Operation();
			break;
		case IDC_PLUS:
			Operator = Yunsan::Yplus;
			Operation();
			break;
		case IDC_BUTTON_DEVIDE:
			Operator = Yunsan::Ydevide;
			Operation();
			break;
		case IDC_BUTTON_REST:
			while (Buffer[wcslen(Buffer) - 1] != '\0')
			if (Buffer != NULL && Buffer[0] != '0') {
				Buffer[wcslen(Buffer) - 1] = '\0';

				for (int i = 0; i < 128; ++i) {
					Show[i] = '\0';
				}
				tep = _wtof(Buffer);
				if (bin == true)
					_ltow_s(tep, Show, 2);
				if (bin == false) {
					_ltow_s(tep, Show, 10);
				}
				SetDlgItemText(hDlg, IDC_EDIT, Show);
			}
			Result = 0;
			break;
		case IDC_BUTTON_DELONE:
			if (Buffer != NULL && Buffer[0] != '0') {
				Buffer[wcslen(Buffer) - 1] = '\0';

				for (int i = 0; i < 128; ++i) {
					Show[i] = '\0';
				}
				tep = _wtof(Buffer);
				if (bin == true)
					_ltow_s(tep, Show, 2);
				if (bin == false) {
					_ltow_s(tep, Show, 10);
				}
				SetDlgItemText(hDlg, IDC_EDIT, Show);
			}
			break;
		case IDC_BUTTON_REVERSE:
			x = 0;
			temp = '\0';
			for (int i = 0; Buffer[i] != '\0' ; ++i) {
				x++;
			}
			max = x; // �迭 ũ��(�߰����� ����ϱ�����)
			for (int i = 0; i <= (max / 2); ++i) { // �� �հ� �� �ڸ� �ٲٰ� ���� 2��°, ������ �տ��� �ٲٰ� ,,,,,
				temp = Buffer[i];
				Buffer[i] = Buffer[(int)max-(int)i-1];
				Buffer[(int)max - (int)i - 1] = temp;
			}
			if ((int)max % 2 == 0) {
				temp = Buffer[(int)max/2];
				Buffer[(int)max / 2] = Buffer[(int)max / 2 - 1];
				Buffer[(int)max / 2 - 1] = temp;
			}

			for (int i = 0; i < 128; ++i) {
				Show[i] = '\0';
			}
			tep = _wtof(Buffer);
			if (bin == true)
				_ltow_s(tep, Show, 2);
			if (bin == false) {
				_ltow_s(tep, Show, 10);
			}
			SetDlgItemText(hDlg, IDC_EDIT, Show);
			break;
		case IDC_BUTTON_CLOSE:
			Destroy();
			break;
		}
		
		//EndDialog(hwnd, LOWORD(wParam));
		return (BOOL)true;
	}
	return (BOOL)false;
}

void CFrameWork::Operation()
{
	if (Result == 0) {
		Result = _wtof(Buffer);
		Buffer[0] = 0;
	}
	else {
		Operand = _wtof(Buffer);
		switch (Operator) {
		case Yunsan::Yplus:
			Result += Operand;
			break;
		case Yunsan::Ysubtract:
			Result -= Operand;
			break;
		case Yunsan::Ymulti:
			Result *= Operand;
			break;
		case Yunsan::Ydevide:
			Result /= Operand;
			break;
		}
		Buffer[0] = 0;
		Display(Result);
		Buffer[0] = 0;
	}
	return;
}

void CFrameWork::Equal()
{
	Operand = _wtof(Buffer);
	switch (Operator) {
	case Yunsan::Yplus:
		Result += Operand;
		break;
	case Yunsan::Ysubtract:
		Result -= Operand;
		break;
	case Yunsan::Ymulti:
		Result *= Operand;
		break;
	case Yunsan::Ydevide:
		Result /= Operand;
		break;
	}
	return;
}
void CFrameWork::Display(double Result)
{
	TCHAR cTemp[128] = { 0 };
	double ff = _wtof(Buffer);
	if (ff == 0 && Buffer[0] != '.' && Buffer[1] != '.') {
		Buffer[0] = 0;
	}
	swprintf(cTemp, sizeof(cTemp), TEXT("%g"), Result);
	lstrcat(Buffer, cTemp);

	for (int i = 0; i < 128; ++i) {
		Show[i] = '\0';
	}
	tep = _wtof(Buffer);
	if(bin == true)
		_ltow_s(tep, Show, 2);
	if (bin == false) {
		_ltow_s(tep, Show, 10);
	}
	afterresult = false;
	SetDlgItemText(hDlg, IDC_EDIT, Show);
	return;
}
