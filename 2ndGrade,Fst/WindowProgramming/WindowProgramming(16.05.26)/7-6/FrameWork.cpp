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

	bitmap1 = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	bitmap2 = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	bitmap3 = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	bitmap4 = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	bitmap5 = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	bitmap6 = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP6));

	O_bitmap1 = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP8));
	O_bitmap2 = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP7));

	B_bitmap1 = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP9));
	B_bitmap2 = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP10));
	B_bitmap3 = LoadBitmap(m_hInst, MAKEINTRESOURCE(IDB_BITMAP11));
	
	Button[0] = CreateWindow(L"button", L"�����¿�",
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		800, 500, 50, 50, m_hwnd,
		(HMENU)IDC_Tile_1, m_hInst, NULL);
	SendMessage(Button[0], BM_SETIMAGE, 0, (LPARAM)bitmap1);
	Button[1] = CreateWindow(L"button", L"�����¿�",
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		850, 500, 50, 50, m_hwnd,
		(HMENU)IDC_Tile_2, m_hInst, NULL);
	SendMessage(Button[1], BM_SETIMAGE, 0, (LPARAM)bitmap2);
	Button[2] = CreateWindow(L"button", L"�����¿�",
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		900, 500, 50, 50, m_hwnd,
		(HMENU)IDC_Tile_3, m_hInst, NULL);
	SendMessage(Button[2], BM_SETIMAGE, 0, (LPARAM)bitmap3);
	Button[3] = CreateWindow(L"button", L"�����¿�",
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		800, 550, 50, 50, m_hwnd,
		(HMENU)IDC_Tile_5, m_hInst, NULL);
	SendMessage(Button[3], BM_SETIMAGE, 0, (LPARAM)bitmap4);
	Button[4] = CreateWindow(L"button", L"�����¿�",
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		850, 550, 50, 50, m_hwnd,
		(HMENU)IDC_Tile_6, m_hInst, NULL);
	SendMessage(Button[4], BM_SETIMAGE, 0, (LPARAM)bitmap5);
	Button[5] = CreateWindow(L"button", L"�����¿�",
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		900, 550, 50, 50, m_hwnd,
		(HMENU)IDC_Tile_7, m_hInst, NULL);
	SendMessage(Button[5], BM_SETIMAGE, 0, (LPARAM)bitmap6);
	Button[6] = CreateWindow(L"button", L"�����¿�",
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		800, 600, 50, 50, m_hwnd,
		(HMENU)IDC_OBJ_1, m_hInst, NULL);
	SendMessage(Button[6], BM_SETIMAGE, 0, (LPARAM)O_bitmap1);
	Button[7] = CreateWindow(L"button", L"�����¿�",
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		800, 650, 50, 50, m_hwnd,
		(HMENU)IDC_OBJ_2, m_hInst, NULL);

	SendMessage(Button[7], BM_SETIMAGE, 0, (LPARAM)O_bitmap2);

	Button_Mak = CreateWindow(L"button", L"�����",
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		800, 700, 50, 50, m_hwnd,
		(HMENU)IDC_BUTTON_CREATE, m_hInst, NULL);

	Button_Fil = CreateWindow(L"button", L"ä��",
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		850, 700, 50, 50, m_hwnd,
		(HMENU)IDC_BUTTON_FILL, m_hInst, NULL);

	Button_Ext = CreateWindow(L"button", L"����",
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		900, 700, 50, 50, m_hwnd,
		(HMENU)IDC_BUTTON1, m_hInst, NULL);


	TheList = CreateWindow(L"listbox", NULL,
		// ���j�� ������ Ŭ���� �̸��� ��button��
		WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
		// ���ϵ� �������̰� ������ ������ ���j ��Ÿ��
		800, 300, 200, 100, m_hwnd,
		(HMENU)IDC_LIST, m_hInst, NULL);

	for (int i = 0; i < 3; ++i) {
		wsprintf(str, TEXT("%d�� ���"), i);
		SendMessage(TheList, LB_ADDSTRING, 0, (LPARAM)str);
	}

	Edit[0] = CreateWindow(L"edit", L"����Ÿ�ϰ���", WS_CHILD | WS_VISIBLE | WS_BORDER,
		// ����Ʈ ������ Ŭ���� �̸��� ��edit��
		// ���ϵ� �������̰� ����Ʈ �ڽ� ������ �׵θ��� �ִ� ��Ÿ��
		800, 100, 200, 25, m_hwnd, (HMENU)IDC_EDIT_WN, m_hInst, NULL);
	Edit[1] = CreateWindow(L"edit", L"����ũ��", WS_CHILD | WS_VISIBLE | WS_BORDER,
		// ����Ʈ ������ Ŭ���� �̸��� ��edit��
		// ���ϵ� �������̰� ����Ʈ �ڽ� ������ �׵θ��� �ִ� ��Ÿ��
		800, 150, 200, 25, m_hwnd, (HMENU)IDC_EDIT_WS, m_hInst, NULL);
	Edit[2] = CreateWindow(L"edit", L"����Ÿ�ϰ���", WS_CHILD | WS_VISIBLE | WS_BORDER,
		// ����Ʈ ������ Ŭ���� �̸��� ��edit��
		// ���ϵ� �������̰� ����Ʈ �ڽ� ������ �׵θ��� �ִ� ��Ÿ��
		800, 125, 200, 25, m_hwnd, (HMENU)IDC_EDIT_HN, m_hInst, NULL);
	Edit[3] = CreateWindow(L"edit", L"����ũ��", WS_CHILD | WS_VISIBLE | WS_BORDER,
		// ����Ʈ ������ Ŭ���� �̸��� ��edit��
		// ���ϵ� �������̰� ����Ʈ �ڽ� ������ �׵θ��� �ִ� ��Ÿ��
		800, 175, 200, 25, m_hwnd, (HMENU)IDC_EDIT_HS, m_hInst, NULL);




	//SetTimer(m_hwnd, 1, 100, NULL);
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

		switch (back.id) {
		case 0:
			SelectObject(MemDC, B_bitmap1);
			break;
		case 1:
			SelectObject(MemDC, B_bitmap2);
			break;
		case 2:
			SelectObject(MemDC, B_bitmap3);
			break;
		}
		back.draw(LayDC,MemDC);

		wsprintf(temp,TEXT("%d, %d, %d"),selection,back.id,id);
		DrawText(LayDC,temp,-1,&m_rect,DT_RIGHT);

		for (int i = 0; i < tilenum.y; ++i) {
			for (int j = 0; j < tilenum.x; ++j) {

				switch (tile[i][j].id) {
				case 0:
					SelectObject(MemDC, bitmap1);
					break;
				case 1:
					SelectObject(MemDC, bitmap2);
					break;
				case 2:
					SelectObject(MemDC, bitmap3);
					break;
				case 3:
					SelectObject(MemDC, bitmap4);
					break;
				case 4:
					SelectObject(MemDC, bitmap5);
					break;
				case 5:
					SelectObject(MemDC, bitmap6);
					break;


				}

				tile[i][j].draw(LayDC, MemDC);
			}
		}

		for (int i = 0; i < tilenum.y; ++i) {
			for (int j = 0; j < tilenum.x; ++j) {

				switch (obj[i][j].id) {
				case 0:
					SelectObject(MemDC, O_bitmap1);
					break;
				case 1:
					SelectObject(MemDC, O_bitmap2);
					break;
				}
				obj[i][j].draw(LayDC, MemDC);
			}
		}
		
		
		Rectangle(LayDC, 0, 0, mapsize.x, mapsize.y);


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
		drag = true;
		ptmouse.x = LOWORD(lParam);
		ptmouse.y = HIWORD(lParam);
		switch (mode) {
		case Mode::Tiling: {
			for (int i = 0; i < tilenum.y; ++i) {
				for (int j = 0; j < tilenum.x; ++j) {
					if (PtInRect(&tile[i][j].pos, ptmouse)) {
						tile[i][j].isfilled = true;
						tile[i][j].id = id;
					}
				}
			}
		}
						   break;
		case Mode::Objecting: {
			for (int i = 0; i < tilenum.y; ++i) {
				for (int j = 0; j < tilenum.x; ++j) {
					if (PtInRect(&obj[i][j].pos, ptmouse)) {
							obj[i][j].isfilled = true;
							if (obj[i][j].id != 0)
							obj[i][j].id = id;
					}
				}
			}
		}
			break;
		}
		

		break;
	case WM_MOUSEMOVE:
		if (drag) {

			ptmouse.x = LOWORD(lParam);
			ptmouse.y = HIWORD(lParam);

			switch (mode) {
			case Mode::Tiling: {
				for (int i = 0; i < tilenum.y; ++i) {
					for (int j = 0; j < tilenum.x; ++j) {
						if (PtInRect(&tile[i][j].pos, ptmouse)) {
							tile[i][j].isfilled = true;
							tile[i][j].id = id;
						}
					}
				}
			}
							   break;
			case Mode::Objecting: {
				for (int i = 0; i < tilenum.y; ++i) {
					for (int j = 0; j < tilenum.x; ++j) {
						if (PtInRect(&obj[i][j].pos, ptmouse)) {
							 
								obj[i][j].isfilled = true;
								if (obj[i][j].id != 0)
								obj[i][j].id = id;
							
						}
					}
				}
			}
								  break;
			}


		}
		break;
	case WM_LBUTTONUP:
		drag = false;
		break;
	}
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}

void CFrameWork::InputKeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_KEYDOWN:
		DLGPROC dialogFunc = [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> INT_PTR { return framework.WindowDialogProc(hwnd, msg, wParam, lParam); };
		//hDlg = CreateDialog(m_hInst,MAKEINTRESOURCE(IDD_DIALOG),m_hwnd, dialogFunc);
		//ShowWindow(hDlg, SW_SHOW);
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
		case IDC_Tile_1:
			id = 0;
			mode = Mode::Tiling;
			break;
		case IDC_Tile_2:
			id = 1;
			mode = Mode::Tiling;
			break;
		case IDC_Tile_3:
			id = 2;
			mode = Mode::Tiling;
			break;
		case IDC_Tile_5:
			id = 3;
			mode = Mode::Tiling;
			break;
		case IDC_Tile_6:
			id = 4;
			mode = Mode::Tiling;
			break;
		case IDC_Tile_7:
			id = 5;
			mode = Mode::Tiling;
			break;
		case IDC_OBJ_1:
			id = 0;
			mode = Mode::Objecting;
			break;
		case IDC_OBJ_2:
			id = 1;
			mode = Mode::Objecting;
			break;
		case IDC_BUTTON_CREATE:
			tilenum.x = GetDlgItemInt(hwnd, IDC_EDIT_WN, NULL, FALSE);

			mapsize.x = GetDlgItemInt(hwnd, IDC_EDIT_WS, NULL, FALSE);

			tilenum.y = GetDlgItemInt(hwnd, IDC_EDIT_HN, NULL, FALSE);

			mapsize.y = GetDlgItemInt(hwnd, IDC_EDIT_HS, NULL, FALSE);

			if (tilenum.x > 30)
				tilenum.x = 30;
			if (tilenum.y > 30)
				tilenum.y = 30;
			for (int i = 0; i < tilenum.y; ++i) {
				for (int j = 0; j < tilenum.x; ++j) {
					POINT x = { j*(mapsize.x / tilenum.x) ,i*(mapsize.y / tilenum.y) };
					tile[i][j].setpos(x, (mapsize.x / tilenum.x), (mapsize.y / tilenum.y));
					obj[i][j].setpos(x, (mapsize.x / tilenum.x), (mapsize.y / tilenum.y));

				}
			}
			{
				POINT x = { 0,0 };
				back.setpos(x, mapsize.x, mapsize.y);
				InvalidateRect(m_hwnd, &m_rect, FALSE);
			}

			break;
		case IDC_LIST:
			switch (HIWORD(wParam)) {
			case LBN_SELCHANGE:
				selection = SendMessage(TheList, LB_GETCURSEL, 0, 0);
				break;
			}
			break;
		case IDC_BUTTON_FILL:
			back.id = selection;
			back.isfilled = true;
			break;
		case IDC_BUTTON1:
			Destroy();
			break;
		}
		return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}


LRESULT CALLBACK  CFrameWork::WindowDialogProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HWND hButton;
	switch (iMessage)
	{
	case WM_CREATE:
		
		
		return 0;
	
		//EndDialog(hwnd, LOWORD(wParam));
		return (BOOL)true;
	}
	return DefMDIChildProc(hwnd, iMessage, wParam, lParam);
}


LRESULT CALLBACK CFrameWork::ChildDrawProc(HWND hWnd, UINT iMessage,WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HBRUSH hbrBackground = NULL; // ���귯���ڵ�
	static RECT RectView;
	static HBRUSH transbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	static HBRUSH oldbrush;

	int ID;


	switch (iMessage) {
	case WM_CREATE:
		ID = 0;
		SetWindowLong(hWnd, 0, ID);
		GetClientRect(hWnd, &RectView);

		//if (hbrBackground) DeleteObject(hbrBackground);
		hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

		SetTimer(hWnd, 1, 10, NULL);
		InvalidateRect(hWnd, NULL, false); // WM_PAINT �޼��� ���� �߻���Ų��
		break;
	case WM_KEYDOWN:
		break;
	case WM_TIMER:

	{
		ID = GetWindowLong(hWnd, 0);
	}
	InvalidateRect(hWnd, NULL, false); // WM_PAINT �޼��� ���� �߻���Ų��
	break;
	case WM_PAINT: //������ �ٽ� �׷���� �� ��, ȭ���� �������� OS���� �޼��� ���� (ó�� ����, �ٸ� ������ �������ִٰ� �ٽ� ���� ��, â ũ�� �ٲ�InvalidateRect(), InvalidateRgn()�Լ��� ȣ���Ͽ� ������ ȭ���� ��ȿȭ��ų ��)
		hdc = BeginPaint(hWnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)

		HDC LayDC;
		LayDC = CreateCompatibleDC(hdc); // hdc�� ȣȯ��Ų��.
		HBITMAP Lay; // ���̾� ����
		Lay = CreateCompatibleBitmap(hdc, RectView.right, RectView.bottom); // �ٺ� ���۸� ,hdc�� ȣȯ��Ű��.
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &RectView, hbrBackground);
			SetBkMode(LayDC, TRANSPARENT);
			//////<����� �׸���>//////////////////////////////////////////////////////////////////
			oldbrush = (HBRUSH)SelectObject(LayDC, transbrush);

			ID = GetWindowLong(hWnd, 0);
			//////////////////////////////////////////////////////////////////////
			BitBlt(hdc, 0, 0, RectView.right, RectView.bottom, LayDC, 0, 0, SRCCOPY);
		}


		DeleteObject(Lay);
		DeleteObject(hdc);

		DeleteDC(LayDC);
		DeleteDC(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		switch (iMessage) {
		case WM_LBUTTONDOWN:
			drag = true;
			ptmouse.x = LOWORD(lParam);
			ptmouse.y = HIWORD(lParam);
			switch (mode) {
			case Mode::Tiling: {
				for (int i = 0; i < tilenum.y; ++i) {
					for (int j = 0; j < tilenum.x; ++j) {
						if (PtInRect(&tile[i][j].pos, ptmouse)) {
							tile[i][j].isfilled = true;
							tile[i][j].id = id;
						}
					}
				}
			}
							   break;
			case Mode::Objecting: {
				for (int i = 0; i < tilenum.y; ++i) {
					for (int j = 0; j < tilenum.x; ++j) {
						if (PtInRect(&obj[i][j].pos, ptmouse)) {
							obj[i][j].isfilled = true;
							if (obj[i][j].id != 0)
								obj[i][j].id = id;
						}
					}
				}
			}
								  break;
			}


			break;
		case WM_MOUSEMOVE:
			if (drag) {

				ptmouse.x = LOWORD(lParam);
				ptmouse.y = HIWORD(lParam);

				switch (mode) {
				case Mode::Tiling: {
					for (int i = 0; i < tilenum.y; ++i) {
						for (int j = 0; j < tilenum.x; ++j) {
							if (PtInRect(&tile[i][j].pos, ptmouse)) {
								tile[i][j].isfilled = true;
								tile[i][j].id = id;
							}
						}
					}
				}
								   break;
				case Mode::Objecting: {
					for (int i = 0; i < tilenum.y; ++i) {
						for (int j = 0; j < tilenum.x; ++j) {
							if (PtInRect(&obj[i][j].pos, ptmouse)) {

								obj[i][j].isfilled = true;
								if (obj[i][j].id != 0)
									obj[i][j].id = id;

							}
						}
					}
				}
									  break;
				}


			}
			break;
		case WM_LBUTTONUP:
			drag = false;
			break;
		}
		return 0;
	case WM_LBUTTONUP:
		return 0;
	case WM_ACTIVATE:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_SETFOCUS:
		break;
	case WM_KILLFOCUS:
		break;
	case WM_SIZE:
		break;
	case WM_DESTROY:
		return 0;
	}
	return DefMDIChildProc(hWnd, iMessage, wParam, lParam);
}