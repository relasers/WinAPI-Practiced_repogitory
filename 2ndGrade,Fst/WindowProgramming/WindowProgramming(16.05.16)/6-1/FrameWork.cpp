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

		LayDC = CreateCompatibleDC(windc); // hdc와 호환시킨다.
		HBITMAP Lay; // 레이어 생성
		Lay = CreateCompatibleBitmap(windc, m_diarect.right, m_diarect.bottom); // 다블 버퍼링 ,hdc와 호환시키자.
		SelectObject(LayDC, Lay);
		{
			FillRect(LayDC, &m_diarect, hbrBackground); // 화면 클리어
			//MemDC = CreateCompatibleDC(LayDC); // 이건 비트맵 뿌리기용

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
			Radio = 0; // 0과 1 중에서 0선택
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
