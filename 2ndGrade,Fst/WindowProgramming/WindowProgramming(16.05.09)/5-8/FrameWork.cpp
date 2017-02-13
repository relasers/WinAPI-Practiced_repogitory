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
		MAKEINTRESOURCE(IDB_BACKGROUND));
	bit_crossline = (HBITMAP)LoadBitmap(m_hInst,
		MAKEINTRESOURCE(IDB_CROSSLINE));
	bit_truck = (HBITMAP)LoadBitmap(m_hInst,
		MAKEINTRESOURCE(IDB_TRUCK));
	bit_rev_truck = (HBITMAP)LoadBitmap(m_hInst,
		MAKEINTRESOURCE(IDB_REVTRUCK));

	for (int i = 0; i < 8; ++i) {
		POINT temp_pos = {
			i*(50+rand()%100),
			100 + 50 * (i%4)
		};
		car[i].setspeed(2.0);
		car[i].setpos(temp_pos);
		if (i%4 < 2) {
			car[i].setdirection(Direction::to_left);
		}
		for (int x = 0; x < 8; ++x) {
			if (x != i) {
				if (IntersectRect(&col_check, &car[i].getpos(), &car[x].getpos())) {
					--i;
					break;
				}
			}
		}
	}

	for (int i = 0;i<3;++i) {
		POINT temp_pos = {
		m_rect.right - TRAFFICORBSIZE*(3) + TRAFFICORBSIZE*(i) ,0
		};
		light[i].setpos(temp_pos);
		light[i].setcolor(i);
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
		SelectObject(MemDC, bit_crossline);
		BitBlt(LayDC, crossline.left, crossline.top, 300, 200, MemDC, 0, 0, SRCCOPY);

		for (int i = 0; i < 8; ++i) {
			
			switch (car[i].getdir()) {
			case Direction::to_left:
				SelectObject(MemDC, bit_rev_truck);
				TransparentBlt(LayDC, car[i].getpos().left, car[i].getpos().top, 100, 50
					, MemDC, car[i].getframe() * 100, 0, 100, 50, RGB(255, 255, 255)); // ���� �׸���
				if (car[i].getpos().left < 0) {
					TransparentBlt(LayDC, m_rect.right + (car[i].getpos().left), car[i].getpos().top, 100, 50
						, MemDC, car[i].getframe() * 100, 0, 100, 50, RGB(255, 255, 255)); // ���� �׸���
				}
				break;
			case Direction::to_right:
				SelectObject(MemDC, bit_truck);
				TransparentBlt(LayDC, car[i].getpos().left, car[i].getpos().top, 100, 50
					, MemDC, car[i].getframe() * 100, 0, 100, 50, RGB(255, 255, 255)); // ���� �׸���
				if (car[i].getpos().right > m_rect.right) {
					TransparentBlt(LayDC, -100+(car[i].getpos().right-m_rect.right), car[i].getpos().top, 100, 50
						, MemDC, car[i].getframe() * 100 , 0, 100, 50, RGB(255, 255, 255)); // ���� �׸���
				}
				break;
			}
		}

		///��ȣ��////
		old_brush = (HBRUSH)GetStockObject(BLACK_BRUSH);
		SelectObject(LayDC,old_brush);
		Rectangle(LayDC,light[0].getpos().left,
		light[0].getpos().top,
			light[2].getpos().right,
			light[2].getpos().bottom
		);

		for (int i = 0; i < 3; ++i) {
			old_brush = (HBRUSH)GetStockObject(GRAY_BRUSH);
			SelectObject(LayDC, old_brush);
			switch (i) {
			case 0:
				if (red) {
					SelectObject(LayDC, old_brush);
					old_brush = (HBRUSH)SelectObject(LayDC, light[i].getcolor());
				}
				break;
			case 1:
				if (yellow) {
					SelectObject(LayDC, old_brush);
					old_brush = (HBRUSH)SelectObject(LayDC, light[i].getcolor());
				}
				break;
			case 2:
				if (green) {
					SelectObject(LayDC, old_brush);
					old_brush = (HBRUSH)SelectObject(LayDC, light[i].getcolor());
				}
				break;
			}
			Ellipse(LayDC, light[i].getpos().left,
				light[i].getpos().top,
				light[i].getpos().right,
				light[i].getpos().bottom
			);
			SelectObject(LayDC,old_brush);
		}
			
		if (counter != 0) {
			wsprintf(temp_str, TEXT("%d"),counter);
			DrawText(LayDC,temp_str,-1,&m_rect,DT_CENTER);
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
	case WT_UPDATER:
		for(int i=0;i<8;++i){
			car[i].imageframeinc();
			if (green || yellow) {
				car[i].moving(m_rect);
			}
			if (red) {
				switch (car[i].getdir()) {
				case Direction::to_left:
					if (crossline.right < car[i].getpos().left
						|| crossline.right > car[i].getpos().right
						|| !(IntersectRect(&col_check,&crossline,&car[i].getpos()))
						) {
						car[i].moving(m_rect);
					}
					break;
				case Direction::to_right:
					if (crossline.left > car[i].getpos().right
						|| crossline.left < car[i].getpos().left
						|| !(IntersectRect(&col_check, &crossline, &car[i].getpos()))
						) {
						car[i].moving(m_rect);
					}
					break;
				}
			
			}

			for (int x = 0; x < 8; ++x) {
				if (i != x) {
					if (IntersectRect(&col_check, &car[i].getpos(), &car[x].getpos())) {
						do { 
								car[i].movbak(m_rect);
						} while ((IntersectRect(&col_check, &car[i].getpos(), &car[x].getpos())));
						break;
					}
				}
			}
		}
		break;
	case WT_YTORCUNTR:
		counter--;
		if (counter == 0) {
			KillTimer(m_hwnd, WT_YTORCUNTR);
				green = false;
				yellow = false;
				red = true;
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

		for (int i = 0; i < 3; ++i) {
			if (PtInRect(&light[i].getpos(),ptmouse)) {
				switch (i) {
				case 0: //����
					KillTimer(m_hwnd, WT_YTORCUNTR);
					counter = 0;
					green = false;
					yellow = false;
					red = true;
					break;
				case 1: // ���
					green = false;
					yellow = true;
					red = false;
					counter = 3;
					KillTimer(m_hwnd, WT_YTORCUNTR);
					SetTimer(m_hwnd,WT_YTORCUNTR,1000,NULL);
					break;
				case 2: // �ʷ�
					KillTimer(m_hwnd, WT_YTORCUNTR);
					counter = 0;
					green = true;
					yellow = false;
					red = false;
					break;
				}
			}
		}
		InvalidateRect(m_hwnd, &m_rect, FALSE);
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