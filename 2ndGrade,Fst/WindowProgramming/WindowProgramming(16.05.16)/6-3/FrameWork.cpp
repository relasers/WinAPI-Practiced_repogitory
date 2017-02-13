#include "stdafx.h"
#include "FrameWork.h"


CFrameWork::CFrameWork()
{

}

CFrameWork::~CFrameWork()
{
	Destroy();
}
// 클래스 함수선언은 헤더에서 하는게 아니고 cpp 파일에 한다.
bool CFrameWork::Initial(HWND h, RECT r,HINSTANCE inst) {
	// 변수명 앞에 자료형 쓰면 그건 지역변수가 되어버린다
	m_hwnd = h;
	m_rect = r;
	m_hInst = inst;
	return m_hwnd != NULL; // 윈도우 생성 실패하면 윈도우 핸들이 NULL 값이 들어간다.
						   // 이값이 NULL값일 경우 윈도우가 제대로 만들어지지 않았다는것, 널값이면 윈도우를 죽여라!
}
void CFrameWork::Destroy() { // 반환값은 없어도 상관없다, 어쩌피 죽을테니까, 메모리 누수 방지
							 //소멸자로 소멸할때 Destroy 호출, 소멸자는 함수가 죽어야만 나온다 , 죽이고 다시 생성하고 싶을때 쓰자
							 // 대를 잇게 할때 -> 그떄를 위해 함수를 미리 빼 놓는다
	PostQuitMessage(0);
};

LRESULT CFrameWork::WindowMessage(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리
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
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
		hdc = BeginPaint(hwnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)
		
		OnDraw(hdc); // hdc 를 OnDraw 로 넘긴다.

		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		WindowMenu(hwnd, iMessage, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	} //처리할 메시지만 case문에 나열
	return(DefWindowProc(hwnd, iMessage, wParam, lParam));// CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달 
}

void CFrameWork::OnCreate() { // 나중에 3-1학기떄 BuildObject 로 쓴다 , 동적메모리 릴리즈 용
	GetClientRect(m_hwnd,&m_rect);
	SetTimer(m_hwnd,1,1,NULL);
}
void CFrameWork::OnDraw(HDC hdc) { //여기다 드로우를 처리한다
	
	HDC LayDC;
	LayDC = CreateCompatibleDC(hdc); // hdc와 호환시킨다.
	HBITMAP Lay; // 레이어 생성
	Lay = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom); // 다블 버퍼링 ,hdc와 호환시키자.
	SelectObject(LayDC, Lay);
	{
		ClearScreen(LayDC); // 화면 클리어
		MemDC = CreateCompatibleDC(LayDC); // 이건 비트맵 뿌리기용

		SetBkMode(LayDC, TRANSPARENT);
		//////<여기다 그린다>//////////////////////////////////////////////////////////////////

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
