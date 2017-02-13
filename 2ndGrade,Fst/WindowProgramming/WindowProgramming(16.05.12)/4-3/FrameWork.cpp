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
		HBRUSH shapecolor = NULL;
		HPEN shapepen = NULL;

		if (border) {
			shapepen = (HPEN)CreatePen(PS_SOLID, 5, (RGB(rand() % 255, rand() % 255, rand() % 255)));
		}
		else {
			shapepen = (HPEN)CreatePen(PS_SOLID, 1, (RGB(rand() % 255, rand() % 255, rand() % 255)));
		}

		switch (colortype) {
		case Color::Green:
			shapecolor = (HBRUSH)CreateSolidBrush(RGB(0,255,0));
			break;
		case Color::Red:
			shapecolor = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
			break;
		case Color::Yellow:
			shapecolor = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
			break;
		case Color::Random:
			shapecolor = (HBRUSH)CreateSolidBrush(RGB(rand()%255, rand() % 255, rand() % 255));
			break;
		}
		HBRUSH oldbrush;
		HPEN oldpen;

		//if(shapetype!=Shape::Line)
		ClearScreen(LayDC); // ȭ�� Ŭ����
		MemDC = CreateCompatibleDC(LayDC); // �̰� ��Ʈ�� �Ѹ����

		SetBkMode(LayDC, TRANSPARENT);
		//////<����� �׸���>//////////////////////////////////////////////////////////////////

		oldpen = (HPEN)SelectObject(LayDC, shapepen);
		oldbrush = (HBRUSH)SelectObject(LayDC,shapecolor);

		switch (shapetype) {
		case Shape::Rec:
			Rectangle(LayDC, shape.left, shape.top, shape.right, shape.bottom);
			break;
		case Shape::Ellip:
			Ellipse(LayDC, shape.left, shape.top, shape.right, shape.bottom);
			break;
		case Shape::Line:
			break;
		}
		
		if (info) {
			wsprintf(temp, TEXT("�� - �� - �� ?"));
			DrawText(LayDC,temp,-1,&m_rect,DT_CENTER);
		}

		SelectObject(LayDC, oldbrush);
		SelectObject(LayDC, oldpen);
		//////////////////////////////////////////////////////////////////////
		BitBlt(hdc, 0, 0, m_rect.right, m_rect.bottom, LayDC, 0, 0, SRCCOPY);
	


		SelectObject(LayDC, oldpen);
		SelectObject(LayDC,oldbrush);
		DeleteObject(shapecolor);
		DeleteObject(shapepen);
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
	if (shapetype != Shape::Line)
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::InputMouse(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_LBUTTONDOWN:
		drag = true;
		ptstart.x = LOWORD(lParam);
		ptstart.y = HIWORD(lParam);

		shape.left = ptstart.x;
		shape.top = ptstart.y;
		shape.right = ptstart.x;
		shape.bottom = ptstart.y;


		break;
	case WM_MOUSEMOVE:
		if(drag){
			ptend.x = LOWORD(lParam);
			ptend.y = HIWORD(lParam);
			shape.right = ptend.x;
			shape.bottom = ptend.y;

			if (shapetype == Shape::Line) {

				hdc = GetDC(m_hwnd);
				MoveToEx(hdc, ptstart.x, ptstart.y, NULL);
				ptstart.x = LOWORD(lParam);
				ptstart.y = HIWORD(lParam);
				LineTo(hdc, ptstart.x, ptstart.y);
				ReleaseDC(m_hwnd,hdc);
			}
		}
		break;
	case WM_LBUTTONUP:
		drag = false;
	}

	if(shapetype != Shape::Line)
	InvalidateRect(m_hwnd, &m_rect, FALSE);
	
}
void CFrameWork::InputKeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_KEYDOWN:
		
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
		case ID_COLOR_GREEN:
			colortype = Color::Green;
			break;
		case ID_COLOR_RED:
			colortype = Color::Red;
			break;
		case ID_COLOR_YELLOW:
			colortype = Color::Yellow;
			break;
		case ID_COLOR_RANDOM:
			colortype = Color::Random;
			break;
		case ID_SHAPE_RECTANGLE:
			shapetype = Shape::Rec;
			break;
		case ID_SHAPE_ELLIPSE:
			shapetype = Shape::Ellip;
			break;
		case ID_SHAPE_LINE:
			shapetype = Shape::Line;
			break;
		case ID_CHANGE_SHRINK:
			InflateRect(&shape, -10, -10);
			break;
		case ID_CHANGE_EXPAND:
			InflateRect(&shape, 10, 10);
			break;
		case ID_BORDER_ON:
			border = true;
			break;
		case ID_BORDER_OFF:
			border = false;
			break;
		case ID_HELP_INFO:
			if (info) {
				info = false;
				break;
			}
			if(info == false)
				info = true;
			break;
		case ID_HELP_EXIT:
			Destroy();
			break;
		}
		EndDialog(hwnd, LOWORD(wParam));
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}