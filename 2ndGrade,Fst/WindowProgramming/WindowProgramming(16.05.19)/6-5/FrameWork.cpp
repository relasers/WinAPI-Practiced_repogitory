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
bool CFrameWork::Initial(HWND h, RECT r, HINSTANCE inst) {
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
	GetClientRect(m_hwnd, &m_rect);
	SetTimer(m_hwnd, 1, 1, NULL);
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
			MAKEINTRESOURCE(IDD_DIALOG),
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
	FillRect(hdc, &m_rect, hbrBackground);
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
		hCombo = GetDlgItem(hwnd, IDC_COMBO_YEAR);
		hList = GetDlgItem(hwnd, IDC_LIST);
		CheckRadioButton(hwnd,
			IDC_RADIO_MAN, IDC_RADIO_WOMAN, IDC_RADIO_MAN);
		
		for (int i = 1900; i < 2016; ++i) {
			_itow_s(i,Temp,10);
			SendMessage(hCombo,CB_ADDSTRING,0,(LPARAM)Temp);
		}

		return (BOOL)true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RADIO_WOMAN:
			radio = 1;
			break;
		case IDC_RADIO_MAN:
			radio = 0;
			break;
		case IDC_SORT:

			for (int i = 0; i < 50; ++i) {
				for (int j = 0; j < 256; ++j) {
					Forsort[i][j] = '\0';
				}
			}

			for (int i = 0; i < index; ++i) {
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)Forsort[i]);
			}
			for (int i = index; 0 < i; --i) {
				for (int j = 0; j < i; ++j) {
					if(Forsort[j + 1][0] != '\0')
					if (wcscmp(Forsort[j], Forsort[j+1]) < 0) { //�������� ��
						for (int x = 0; x < 256; ++x) {
							Temp[x] = Forsort[j][x];
						}
						for (int x = 0; x < 256; ++x) {
							Forsort[j][x] = Forsort[j+1][x];
						}
						for (int x = 0; x < 256; ++x) {
							Forsort[j + 1][x] = Temp[x];
						}
					}

				}
			}
			for (int i = 0; i < index; ++i) {
				SendMessage(hList, LB_DELETESTRING, 0, 0);
			}
			for (int i = 0; i < index; ++i) {
				SendMessage(hList, LB_INSERTSTRING, 0, (LPARAM)Forsort[i]);
			}

			break;
		case IDC_NEW:
			SetDlgItemText(hwnd, IDC_EDIT_NAME, L"");
			SetDlgItemText(hwnd, IDC_EDIT_NUMBER, L"");
			SetDlgItemText(hwnd, IDC_COMBO_YEAR, L"");
			break;
		case IDC_JOIN:
			GetDlgItemText(hwnd, IDC_EDIT_NAME, member.name, sizeof(member.name));
			GetDlgItemText(hwnd, IDC_EDIT_NUMBER, member.number, sizeof(member.number));
			member.sex = radio;
			member.year = selection+1900;
			switch (member.sex) {
			case 0:
				wsprintf(Temp, TEXT("����"));
				break;
			case 1:
				wsprintf(Temp, TEXT("����"));
				break;
			}
			wsprintf(Buffer, TEXT("�̸� : %s, ���� : %s, ���� : %s, ����⵵ : %d")
				,member.name,
				member.number,Temp,member.year);
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Buffer);
			index++;
			break;
		case IDC_BAN:
			SendMessage(hList, LB_DELETESTRING, listselection, 0);
			if(index!=0)
			index--;
			break;
		case IDC_COMBO_YEAR: // �޺��ڽ��� ������
			if (HIWORD(wParam) == CBN_SELCHANGE) // �ϳ��� ���õ�(���� ����)
				selection = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			break;

		case IDC_LIST: // �޺��ڽ��� ������
			if (HIWORD(wParam) == LBN_SELCHANGE)
				listselection = SendMessage(hList, LB_GETCURSEL, 0, 0);
			break;
		case IDC_WIN_CLOSE:
			Destroy();
			break;
		}

		//EndDialog(hwnd, LOWORD(wParam));
		return (BOOL)true;
	}
	return (BOOL)false;
}