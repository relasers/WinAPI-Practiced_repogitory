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
		if(winball.gettype() == Shape::rec)
		Rectangle(LayDC,winball.getpos().left,
			winball.getpos().top,
			winball.getpos().right,
			winball.getpos().bottom
			);
		else
			Ellipse(LayDC, winball.getpos().left,
				winball.getpos().top,
				winball.getpos().right,
				winball.getpos().bottom
			);

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

		if (winball.getstate()) {
			winball.movepos();
		}

		if (diaball.getstate()) {
			diaball.movepos();
		}

		if (winball.getpos().left <= 0) {
			winball.changevec(-1,1);
		}
		if (winball.getpos().top <= 0) {
			winball.changevec(1, -1);
		}
		if (winball.getpos().right >= m_rect.right) {
			winball.changevec(-1, 1);
		}
		if (winball.getpos().bottom >= m_rect.bottom) {
			winball.changevec(1, -1);
		}

		if (diaball.getpos().left <= 0) {
			diaball.changevec(-1, 1);
		}
		if (diaball.getpos().top <= 0) {
			diaball.changevec(1, -1);
		}
		if (diaball.getpos().right >= m_diarect.right) {
			diaball.changevec(-1, 1);
		}
		if (diaball.getpos().bottom >= m_diarect.bottom) {
			diaball.changevec(1, -1);
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
	switch (iMessage)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hwnd,IDC_RADIO_REC,IDC_RADIO_ELLIP,IDC_RADIO_REC);
		GetClientRect(hwnd, &m_diarect);
		SetTimer(hwnd,DT_UPDATE,10,NULL);
		return (BOOL)true;
	case WM_TIMER:
		switch (wParam) {
		case DT_UPDATE:
			InvalidateRect(hwnd, &m_diarect, FALSE);
			break;
		}
		break;
	case WM_PAINT:
		windc = BeginPaint(hwnd, &dia_ps); 
		HDC LayDC;

		LayDC = CreateCompatibleDC(windc); // hdc�� ȣȯ��Ų��.
		HBITMAP Lay; // ���̾� ����
		Lay = CreateCompatibleBitmap(windc, m_diarect.right, m_diarect.bottom); // �ٺ� ���۸� ,hdc�� ȣȯ��Ű��.
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &m_diarect, hbrBackground); // ȭ�� Ŭ����
			//MemDC = CreateCompatibleDC(LayDC); // �̰� ��Ʈ�� �Ѹ����

			SetBkMode(LayDC, TRANSPARENT);

			oldbr = (HBRUSH)SelectObject(LayDC,shapebr);
			if (diaball.gettype() == Shape::rec)
				Rectangle(LayDC, diaball.getpos().left,
					diaball.getpos().top,
					diaball.getpos().right,
					diaball.getpos().bottom
				);
			else
				Ellipse(LayDC, diaball.getpos().left,
					diaball.getpos().top,
					diaball.getpos().right,
					diaball.getpos().bottom
				);
			SelectObject(LayDC,shapebr);

			BitBlt(windc, 0, 0, m_diarect.right, m_diarect.bottom, LayDC, 0, 0, SRCCOPY);
		}
		DeleteObject(Lay);
		DeleteObject(windc);

		DeleteDC(LayDC);
		//DeleteDC(MemDC);
		DeleteDC(windc);

		EndPaint(hwnd, &dia_ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_DIA_MOVE:
			diaball.setstate(true);
			break;
		case IDC_DIA_STOP:
			diaball.setstate(false);
			break;
		case IDC_DIA_CLOSE:
			EndDialog(hwnd, 0);
			break;
		case IDC_WIN_START:
			winball.setstate(true);
			break;
		case IDC_WIN_STOP:
			winball.setstate(false);
			break;
		case IDC_WIN_CLOSE:
			Destroy();
			EndDialog(hwnd, 0);
			break;
		case IDC_RADIO_REC:
			Radio = 0; // 0�� 1 �߿��� 0����
			winball.settype(Shape::rec);
			diaball.settype(Shape::rec);
			break;
		case IDC_RADIO_ELLIP:
			Radio = 1;
			winball.settype(Shape::ellip);
			diaball.settype(Shape::ellip);
			break;
		}
		return (BOOL)true;
	}
	return (BOOL)false;
}
