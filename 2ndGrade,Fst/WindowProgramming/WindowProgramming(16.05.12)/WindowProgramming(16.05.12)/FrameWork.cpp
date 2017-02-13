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
			WindowMenu(hwnd,iMessage,wParam,lParam);
		break;
	case WM_DESTROY:
		KillTimer(m_hwnd, 1);
		KillTimer(m_hwnd, 2);
		PostQuitMessage(0);
		return 0;
	} //ó���� �޽����� case���� ����
	return(DefWindowProc(hwnd, iMessage, wParam, lParam));// CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ���� 
}

void CFrameWork::OnCreate() { // ���߿� 3-1�б⋚ BuildObject �� ���� , �����޸� ������ ��
	GetClientRect(m_hwnd,&m_rect);




	for (int i = 0; i<N_BRICK_Y; ++i) {
		for (int j = 0; j < N_BRICK_X; ++j) {
			brick[i][j].brick.left = m_rect.right / N_BRICK_X*j;
			brick[i][j].brick.top = (i + 2) * BRICK_H_SIZE;
			brick[i][j].brick.right = m_rect.right / N_BRICK_X*(j + 1);
			brick[i][j].brick.bottom = (i + 3) * BRICK_H_SIZE;
			brick[i][j].exist = true;
			brick[i][j].hp = 2;
		}
	} // �󵹵� ������
	  //////////////////////////////////////////////////////////////////////
	ball = {
		{ m_rect.right / 2,m_rect.bottom / 2 ,m_rect.right / 2 + BALL_SIZE,m_rect.bottom / 2 + BALL_SIZE }, // ȭ�� �߾ӿ��� ���� �����ȴ�
		true,1,-1,8 };
	bar = { BAR_SIZE,m_rect.bottom - BAR_Y_POS - BAR_H_SIZE,BAR_SIZE * 2,m_rect.bottom - BAR_Y_POS }; // ���� �����/ 


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


		hBar_Brush = CreateSolidBrush(RGB(120, 130, 230));

		switch(colortype){
		case Color::red:
			hBall_Brush = CreateSolidBrush(RGB(255, 130, 120));
			break;
		case Color::blue:
			hBall_Brush = CreateSolidBrush(RGB(130, 130, 255));
			break;
		case Color::green:
			hBall_Brush = CreateSolidBrush(RGB(130, 255, 130));
			break;
		
		}
		hBrick_damaged_Brush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));
		hBrick_normal_Brush = CreateSolidBrush(RGB(255, 250, 250));


		if (grid) {
			for (int i = 0; i < GRIDNUM; ++i) {
				for (int j = 0; j < GRIDNUM; ++j) {
					Rectangle(LayDC,i*m_rect.right/GRIDNUM,
						j*m_rect.bottom / GRIDNUM,
						(i+1)*m_rect.right / GRIDNUM,
						(j+1)*m_rect.bottom / GRIDNUM
					);
				}
			}
		
		
		
		
		}


		oldBrush = (HBRUSH)SelectObject(LayDC, hBar_Brush);
		Rectangle(LayDC, bar.left, bar.top, bar.right, bar.bottom);
		SelectObject(LayDC, oldBrush);

		for (int i = 0; i<N_BRICK_Y; ++i) {
			for (int j = 0; j < N_BRICK_X; ++j) {
				if (brick[i][j].exist == true) {

					oldBrush = (HBRUSH)SelectObject(LayDC, hBrick_normal_Brush);

					if (brick[i][j].hp == 1) {
						SelectObject(LayDC, oldBrush);
						oldBrush = (HBRUSH)SelectObject(LayDC, hBrick_damaged_Brush);
					}
					Rectangle(LayDC, brick[i][j].brick.left, brick[i][j].brick.top, brick[i][j].brick.right, brick[i][j].brick.bottom);
					SelectObject(LayDC, oldBrush);
				}
			}
		}

		if (ball.exist == true) {
			oldBrush = (HBRUSH)SelectObject(LayDC, hBall_Brush);
			Ellipse(LayDC, ball.circle.left, ball.circle.top, ball.circle.right, ball.circle.bottom);
			SelectObject(LayDC, oldBrush);
		} // ���� �ִٸ� ���� �׸���

		if (ball.exist == false) {
			TextOut(LayDC, m_rect.right / 3, m_rect.bottom / 2, L"Yeah Ball is Out!! , Press R to restart", 39);
		} // ���� ������ ���� �����ٴ� �޼����� ��������


		wsprintf(temp, TEXT("damaged : %d, destroyed %d"), damaged, destroyed);
		DrawText(LayDC, temp, -1, &rect_temp, DT_VCENTER | DT_NOCLIP);

		if (game_end == true) {
			TextOut(LayDC, m_rect.right / 3, m_rect.bottom / 2, L"Game is Over, Game will be shutdown soon.....", 45);

		}
		



		

		//////////////////////////////////////////////////////////////////////
		BitBlt(hdc, 0, 0, m_rect.right, m_rect.bottom, LayDC, 0, 0, SRCCOPY);
	}
	
	SelectObject(LayDC, oldBrush);
	DeleteObject(hBall_Brush);
	DeleteObject(hBar_Brush);
	DeleteObject(hBrick_normal_Brush);
	DeleteObject(hBrick_damaged_Brush);

	DeleteObject(Lay);
	DeleteObject(hdc);

	DeleteDC(LayDC);
	DeleteDC(MemDC);
	DeleteDC(hdc);

}
void CFrameWork::OnTimer(UINT id) {
	switch (id) {
	case 1:
		if (game_end == false && game_moving == true) { // ������ �������϶� üũ

			OffsetRect(&ball.circle, ball.x_vec*ball.speed, ball.y_vec*ball.speed); // ���� �����δ�.
																					////////////////////////////////////////<�浹üũ>//////////////////////////////////////////////////////////////////////
			if (m_rect.right < ball.circle.right) { // ���� ���� , ������ �鿡 ������� 
				ball.x_vec = -1;
			}
			if (ball.circle.left < 0) {
				ball.x_vec = 1;
			}
			if (m_rect.bottom<ball.circle.top) { // ���� �ٴ����� ��������
				ball.exist = false;
				//ball.y_vec = -1;
			}
			if (ball.circle.top<0) { // ���� õ�忡 �΋H������
				ball.y_vec = 1;
			}

			for (int i = 0; i<N_BRICK_Y; ++i) {
				for (int j = 0; j < N_BRICK_X; ++j) {
					if (IntersectRect(&for_col_check, &brick[i][j].brick, &ball.circle)) {

						coll_check = Collision_Rec_Ell(ball.circle.left + BALL_SIZE / 2, ball.circle.top + BALL_SIZE / 2
							, BALL_SIZE / 2, brick[i][j].brick);
						if (0 < brick[i][j].hp) {
							switch (coll_check) {
							case Collision_Check::Point:
								ball.y_vec *= -1;
								ball.x_vec *= -1;
								OffsetRect(&ball.circle, ball.x_vec*COLLISION_REFLECT, ball.y_vec*COLLISION_REFLECT);
								brick[i][j].hp--;
								if (brick[i][j].hp <= 0) {
									brick[i][j].exist = false;
									damaged--;
									destroyed++;
								}
								else
									damaged++;
								break;
							case Collision_Check::Side:
								ball.x_vec *= -1;
								OffsetRect(&ball.circle, ball.x_vec*COLLISION_REFLECT, 0);
								brick[i][j].hp--;
								if (brick[i][j].hp <= 0) {
									brick[i][j].exist = false;
									damaged--;
									destroyed++;
								}
								else
									damaged++;
								break;
							case Collision_Check::Updown:
								ball.y_vec *= -1;
								OffsetRect(&ball.circle, 0, ball.y_vec*COLLISION_REFLECT);
								brick[i][j].hp--;
								if (brick[i][j].hp <= 0) {
									brick[i][j].exist = false;
									damaged--;
									destroyed++;
								}
								else
									damaged++;
								break;
							}
						}

					}

				}
			} // ��������� �浹�� üũ�Ѵ�

			if (IntersectRect(&for_col_check, &bar, &ball.circle)) {
				coll_check = Collision_Rec_Ell(ball.circle.left + BALL_SIZE / 2, ball.circle.top + BALL_SIZE / 2
					, BALL_SIZE / 2, bar);
				switch (coll_check) {
				case Collision_Check::Point:
					ball.y_vec *= -1;
					ball.x_vec *= -1;
					OffsetRect(&ball.circle, ball.x_vec*COLLISION_REFLECT * 2, ball.y_vec*COLLISION_REFLECT * 2);
					break;
				case Collision_Check::Side:
					ball.x_vec *= -1;
					OffsetRect(&ball.circle, ball.x_vec*COLLISION_REFLECT * 2, 0);
					break;
				case Collision_Check::Updown:
					ball.y_vec *= -1;
					OffsetRect(&ball.circle, 0, -COLLISION_REFLECT); // ���뿡 ������ ������ �� �������� Ƥ��
					break;
				}
			}// ����� �浹�� üũ�Ѵ�



		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (destroyed == N_BRICK_X*N_BRICK_Y) {
			game_end = true;
			KillTimer(m_hwnd, 1);
			SetTimer(m_hwnd, 2, 3000, NULL); // ������ �״� Ÿ�̸�
		};
		break;
		////////////////////////////////////////////////////////////////////
	case 2:
		KillTimer(m_hwnd, 1);
		KillTimer(m_hwnd, 2);
		PostQuitMessage(0);
		break;
	}
	//////////////////////////////////////////////////////////////////////////////////////////
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::InputMouse(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_LBUTTONDOWN:
		drag = true;
		break;
	case WM_LBUTTONUP:
		drag = false;
		break;
	case WM_MOUSEMOVE:
		if (drag == true) {
			mx = LOWORD(lParam);
			if (0<mx - BAR_SIZE / 2 && mx + BAR_SIZE / 2 < m_rect.right) {
				bar.left = mx - BAR_SIZE / 2;
				bar.right = mx + BAR_SIZE / 2;
			}
		}
		break;
	}
	InvalidateRect(m_hwnd, &m_rect, FALSE);
}
void CFrameWork::InputKeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_KEYDOWN:
		if (wParam == 'R' || wParam == 'r' && ball.exist == false) {
			ball.exist = true;
			ball.circle = { m_rect.right / 2, m_rect.bottom / 2, m_rect.right / 2 + BALL_SIZE, m_rect.bottom / 2 + BALL_SIZE };
			// 
		}// ���� �ٽ� �����Ѵ�
		else if (wParam == '+') {
			if (ball.speed < MX_SPEED) {
				ball.speed++;
			}
		}
		else if (wParam == '-') {
			if (MN_SPEED<ball.speed) {
				ball.speed--;
			}
		}
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

INT_PTR CFrameWork::WindowMenu(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (iMessage)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDM_G_START:
			game_moving = true;
			break;
		case IDM_G_END:
			game_moving = false;
			break;
		case IDM_SPD_FAST:
			ball.speed = 7;
			break;
		case IDM_SPD_MEDIUM:
			ball.speed = 5;
			break;
		case IDM_SPD_SLOW:
			ball.speed = 3;
			break;
		case IDM_BSIZE_BIG:
			InflateRect(&ball.circle, +3, +3);
			break;
		case IDM_BSIZE_SMALL:
			InflateRect(&ball.circle, -3, -3);
			break;
		case IDM_COLOR_BLUE:
			colortype = Color::blue;
			break;
		case IDM_COLOR_GREEN:
			colortype = Color::green;
			break;
		case IDM_COLOR_RED:
			colortype = Color::red;
			break;
		case IDM_GRID_ON:
			grid = true;
			break;
		case IDM_GRID_OFF:
			grid = false;
			break;
		}
		EndDialog(hwnd, LOWORD(wParam));
		InvalidateRect(m_hwnd, &m_rect, FALSE);
		return (INT_PTR)TRUE;
		break;
	}
	return (INT_PTR)FALSE;
}



float CFrameWork::LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}

BOOL CFrameWork::InCircle(int x, int y, int rad, int px, int py)
{
	if (LengthPts(x, y, px, py) < rad)
		return TRUE;
	else
		return FALSE;
}
int CFrameWork::Collision_Rec_Ell(int c_x, int c_y, int c_rad, RECT rec_check) {
	if ((rec_check.left <= c_x && c_x <= rec_check.right) ||
		(rec_check.top <= c_y && c_y <= rec_check.bottom)) {
		RECT rec_chk = {
			rec_check.left - c_rad,
			rec_check.top - c_rad,
			rec_check.right + c_rad,
			rec_check.bottom + c_rad,
		};
		if ((rec_chk.left < c_x && c_x < rec_chk.right)) {
			return Collision_Check::Updown;
		}
		else if (rec_chk.top < c_y && c_y < rec_chk.bottom) {
			return Collision_Check::Side;
		}
	}
	else {
		if (InCircle(c_x, c_y, c_rad, rec_check.left, rec_check.top))return Collision_Check::Point;
		if (InCircle(c_x, c_y, c_rad, rec_check.left, rec_check.bottom))return Collision_Check::Point;
		if (InCircle(c_x, c_y, c_rad, rec_check.right, rec_check.top))return Collision_Check::Point;
		if (InCircle(c_x, c_y, c_rad, rec_check.right, rec_check.bottom))return Collision_Check::Point;
	}
}