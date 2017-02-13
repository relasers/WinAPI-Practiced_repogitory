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
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hwnd, iMessage, wParam, lParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}

void CFrameWork::OnCreate() { // ���߿� 3-1�б⋚ BuildObject �� ���� , �����޸� ������ ��
	GetClientRect(m_hwnd,&m_rect);

	srand((unsigned)time(NULL));

	bit_back = (HBITMAP)LoadBitmap(m_hInst,
		MAKEINTRESOURCE(IDB_DESK));
	bit_cat = (HBITMAP)LoadBitmap(m_hInst,
		MAKEINTRESOURCE(IDB_CAT));
	bit_mouse = (HBITMAP)LoadBitmap(m_hInst,
		MAKEINTRESOURCE(IDB_MOUSE));
	POINT cat_temp_pt = { rand() % m_rect.right - 32,rand() % m_rect.bottom - 32 };
	cat.setPos( cat_temp_pt );

	int max_creating = 3 + rand() % (MAX_OBSTACLE-3);
	bool iscol = false;
	for (int i = 0; i < max_creating; ++i) {
		do {
			POINT temp_pos = { rand() % m_rect.right - MAX_OBSTACLE_SIZE,
				rand() % m_rect.bottom - MAX_OBSTACLE_SIZE };
			obstacle[i].setPos(temp_pos);
			iscol = false;
			for (int j = 0; j < max_creating; ++j) {
				if (i != j) {
					if (IntersectRect(&col_check, &obstacle[j].getPos(), &obstacle[i].getPos()))
						iscol = true;
				}
				
			}
		} while (IntersectRect(&col_check,&cat.Getpos(),&obstacle[i].getPos()) || iscol == true);
		obstacle[i].setexist(true);
	}
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

		SelectObject(MemDC, bit_back);
		BitBlt(LayDC, 0, 0, m_rect.right, m_rect.bottom, MemDC, 0, 0, SRCCOPY);
		
		for (int i = 0; i < MAX_OBSTACLE; ++i) {
			if (obstacle[i].getexist())
				Rectangle(LayDC, obstacle[i].getPos().left,
					obstacle[i].getPos().top,
					obstacle[i].getPos().right,
					obstacle[i].getPos().bottom
				);
		}
		
		
		if (mouse.Getexist()) {
			SelectObject(MemDC, bit_mouse);
			TransparentBlt(LayDC, mouse.Getpos().left, mouse.Getpos().top, 32, 32
				, MemDC, mouse.Getframe() * 32, 0, 32, 32, RGB(255, 255, 255)); // ���� �׸���
		}
		SelectObject(MemDC, bit_cat);
		TransparentBlt(LayDC, cat.Getpos().left, cat.Getpos().top, 32, 32
			, MemDC, cat.Getframe() * 32, 0, 32, 32, RGB(255, 255, 255)); // ���� �׸���

		
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
	POINT temp_pos;
	switch (id) {
	case WT_COUNTING:
		mouse.spriteframeinc();
		cat.spriteframeinc();

		if (mouse.Getexist()) {
			if (mouse.Getpos().left < cat.Getpos().left) {
				if(!cat.Getlostpath())
					cat.catmove(Direction::left);
				if (cat.Getlostpath())
					cat.catmove(Direction::right);
			}
			else if (mouse.Getpos().left > cat.Getpos().left) {
				if (!cat.Getlostpath())
					cat.catmove(Direction::right);
				if (cat.Getlostpath())
					cat.catmove(Direction::left);
			}
			if (mouse.Getpos().top < cat.Getpos().top) {
				if (!cat.Getlostpath())
					cat.catmove(Direction::up);
				if (cat.Getlostpath())
					cat.catmove(Direction::down);
			}
			else if (mouse.Getpos().top > cat.Getpos().top) {
				if (!cat.Getlostpath())
					cat.catmove(Direction::down);
				if (cat.Getlostpath())
					cat.catmove(Direction::up);
			}

			for (int i = 0; i < MAX_OBSTACLE; ++i) {
				if (obstacle[i].getexist()) {
					if (IntersectRect(&col_check, &cat.Getpos(), &obstacle[i].getPos())) {
						if (obstacle[i].getPos().left < cat.Getpos().right
							&& obstacle[i].getPos().left > cat.Getpos().left
							//&&(obstacle[i].getPos().top <= cat.Getpos().top && cat.Getpos().bottom <= obstacle[i].getPos().bottom)
							) {
							while (
								IntersectRect(&col_check, &cat.Getpos(), &obstacle[i].getPos())
								) {
								cat.catmove(Direction::left);
							}
							cat.setlostpath(true);
						}
						if (obstacle[i].getPos().right > cat.Getpos().left
							&& obstacle[i].getPos().right < cat.Getpos().right
							//&& (obstacle[i].getPos().top <= cat.Getpos().top && cat.Getpos().bottom <= obstacle[i].getPos().bottom)
							) {
							while (
								IntersectRect(&col_check, &cat.Getpos(), &obstacle[i].getPos())
								) {
								cat.catmove(Direction::right);
							}
							cat.setlostpath(true);
						}
						if (obstacle[i].getPos().top < cat.Getpos().bottom
							&& obstacle[i].getPos().top > cat.Getpos().top
							//&& (obstacle[i].getPos().left <= cat.Getpos().left && cat.Getpos().right <= obstacle[i].getPos().right)
							) {
							while (
								IntersectRect(&col_check, &cat.Getpos(), &obstacle[i].getPos())
								) {
								cat.catmove(Direction::up);
							}
							cat.setlostpath(true);
						}
						if (obstacle[i].getPos().bottom > cat.Getpos().top
							&& obstacle[i].getPos().bottom < cat.Getpos().bottom
							) {
							while (
								IntersectRect(&col_check, &cat.Getpos(), &obstacle[i].getPos())
								) {
								cat.catmove(Direction::down);
							}
							cat.setlostpath(true);
						}
					}
				}
			}

		}
		




		break;
	}
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::InputMouse(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_LBUTTONDOWN:

		ptmouse.x = LOWORD(lParam);
		ptmouse.y = HIWORD(lParam);

		drag = true;

		mouse.setPos(ptmouse);
		mouse.setexist(true);

		InvalidateRect(m_hwnd, &m_rect, FALSE);
		break;
	case WM_MOUSEMOVE:
		if (drag) {
			ptmouse.x = LOWORD(lParam);
			ptmouse.y = HIWORD(lParam);
			mouse.setPos(ptmouse);
		}
		break;
	case WM_LBUTTONUP:
		if (drag) {
			mouse.setexist(false);
			drag = false;
		}
		break;
	}
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