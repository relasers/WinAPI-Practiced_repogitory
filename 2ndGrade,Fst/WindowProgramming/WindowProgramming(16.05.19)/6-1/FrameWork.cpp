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
		
		DialogBox(m_hInst, MAKEINTRESOURCE(IDD_DIALOG), m_hwnd, dialogFunc);
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
	HWND hButton;
	switch (iMessage)
	{
	case WM_INITDIALOG:
		hButton = GetDlgItem(hwnd, IDC_WIN_CLOSE);
		EnableWindow(hButton, true); // ���� ���� ��ư�� Ȱ��ȭ
		return (BOOL)true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_DIA_MOVE:
			MessageBox(hwnd, TEXT("move!"), TEXT("test"), MB_OK);
			break;
		case IDC_DIA_CLOSE:
			//hButton = GetDlgItem(hwnd, IDC_DIA_CLOSE);
			EndDialog(hwnd, 0);
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
