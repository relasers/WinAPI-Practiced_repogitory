#include "stdafx.h"
#include "FrameWork.h"


CFrameWork::CFrameWork()
{
	m_current_time = chrono::system_clock::now();
	m_fps = 0;
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

	for (int i = 0; i < Scene_State::Count; ++i) {
		m_ArrayScene[i] = nullptr;
	}
	m_currentScene = nullptr;

	lstrcpy(m_CaptionTitle,TEXT("이름"));
	lstrcat(m_CaptionTitle,TEXT(" ("));
	m_TitleLength = lstrlen(m_CaptionTitle);
	SetWindowText(m_hwnd,m_CaptionTitle);

	m_LastUpdate_time = chrono::system_clock::now();



	return m_hwnd != NULL; // 윈도우 생성 실패하면 윈도우 핸들이 NULL 값이 들어간다.
						   // 이값이 NULL값일 경우 윈도우가 제대로 만들어지지 않았다는것, 널값이면 윈도우를 죽여라!
}
void CFrameWork::Destroy() { // 반환값은 없어도 상관없다, 어쩌피 죽을테니까, 메모리 누수 방지
							 //소멸자로 소멸할때 Destroy 호출, 소멸자는 함수가 죽어야만 나온다 , 죽이고 다시 생성하고 싶을때 쓰자
							 // 대를 잇게 할때 -> 그떄를 위해 함수를 미리 빼 놓는다
	DestroyBackBuffer();
};

LRESULT CFrameWork::WindowMessage(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	switch (iMessage) {// 메시지 번호// case: 메시지에 따라 처리
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEMOVE:
		if(m_currentScene->InputMouse(iMessage, wParam, lParam)) // 
		InputMouse(iMessage, wParam, lParam);
		break;
		/////////////////////////////////////////
	case WM_CHAR:
	case WM_KEYDOWN:
	case WM_KEYUP:
		if (m_currentScene->InputKeyBoard(iMessage, wParam, lParam)) //
		InputKeyBoard(iMessage, wParam, lParam);
		break;
		///////////////////////////////////////////
	case WM_PAINT: //윈도우 다시 그려줘야 할 때
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps); // WM_PAINT 메세지에서 사용 , 이 외에서 쓸떄는 GetDC(),ReleaseDC() 를 쓴다(잠시 출력할때)

		OnDraw(hdc); // hdc 를 OnDraw 로 넘긴다.

		EndPaint(hwnd, &ps);
	}
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

	m_ArrayScene[Scene_State::Title] = new CTitleScene();
	m_ArrayScene[Scene_State::Title]->BuildObjects(this, m_hwnd,Scene_State::Title);

	m_ArrayScene[Scene_State::Lobby] = new CLobbyScene();
	m_ArrayScene[Scene_State::Lobby]->BuildObjects(this, m_hwnd, Scene_State::Lobby);

	m_currentScene = m_ArrayScene[Scene_State::Title]; // 현재신은 타이틀로 초기화

	CreateBackBuffer();



}
void CFrameWork::OnDraw(HDC hdc) { //여기다 드로우를 처리한다
		BitBlt(hdc, 0, 0, m_rect.right, m_rect.bottom, m_hdcBackGround, 0, 0, SRCCOPY);
}

void CFrameWork::PreprocessingDraw()
{
	ClearScreen(m_hdcBackGround); // 화면 클리어
	SetBkMode(m_hdcBackGround, TRANSPARENT);
	//////<여기다 그린다>///////////////////////////////////////////////////
	m_currentScene->Draw(m_hdcBackGround);
	//////////////////////////////////////////////////////////////////////
	
}


void CFrameWork::CreateBackBuffer()
{

	HDC hdc = GetDC(m_hwnd);
	if (m_hdcBackGround) {
		SelectObject(m_hdcBackGround,(HBITMAP)NULL);
		DeleteDC(m_hdcBackGround);
	}
	if (m_BackGroundBitmap) {
		DeleteObject(m_BackGroundBitmap);
	}
	m_hdcBackGround = CreateCompatibleDC(hdc);
	m_BackGroundBitmap = CreateCompatibleBitmap(hdc,m_rect.right,m_rect.bottom);
	SelectObject(m_hdcBackGround,m_BackGroundBitmap);



	ReleaseDC(m_hwnd,hdc);
}

void CFrameWork::DestroyBackBuffer()
{
	if (m_hdcBackGround) {
		SelectObject(m_hdcBackGround, (HBITMAP)NULL);
		DeleteDC(m_hdcBackGround);
		m_hdcBackGround = nullptr;
	}
	if (m_BackGroundBitmap) {
		DeleteObject(m_BackGroundBitmap);
		m_BackGroundBitmap = nullptr;
	}

}

void CFrameWork::OnTimer(float fTimeElapsed) {
		m_currentScene->Update(fTimeElapsed);
}

void CFrameWork::InputMouse(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_LBUTTONDOWN:

		break;
	}
}
void CFrameWork::InputKeyBoard(UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_KEYDOWN:
		
		break;
	}
}
void CFrameWork::CreateBkBrush(COLORREF color) {
	if (hbrBackground) DeleteObject(hbrBackground);
	hbrBackground = (HBRUSH)CreateSolidBrush(color);
}
void CFrameWork::ClearScreen(HDC hdc) {
	FillRect(hdc,&m_rect,hbrBackground);
}

void CFrameWork::FrameAdvance()
{
	////////////////<카운트세트>///////////////////////////////////
	m_timeElapsed = chrono::system_clock::now() - m_current_time;
	if (m_timeElapsed.count() > 1.0 / 60.0) {
		m_current_time = chrono::system_clock::now();
		if (m_timeElapsed.count() > 0.0) {
			m_fps = 1.0 / m_timeElapsed.count();
		}
	}
	else return;
	////////////////////////////////////////////////////
	OnTimer(m_timeElapsed.count());
	PreprocessingDraw();
	InvalidateRect(m_hwnd, &m_rect, FALSE);

	m_UpdateElapsed = chrono::system_clock::now() - m_LastUpdate_time;
	if (m_UpdateElapsed.count() > 1.0 / 3.0) {
		m_LastUpdate_time = chrono::system_clock::now();
	}
	else return;
	_itow_s(m_fps + 0.1f, m_CaptionTitle + m_TitleLength, TITLE_MX_LENGTH - m_TitleLength, 10);
	wcscat_s(m_CaptionTitle+m_TitleLength, TITLE_MX_LENGTH -m_TitleLength,TEXT(" fps)"));
	SetWindowText(m_hwnd,m_CaptionTitle);
}

void CFrameWork::ChangeScene(int tag, bool bDestroy)
{
	if (bDestroy) {
		int d_tag = m_currentScene->GetMyTag();
		delete m_currentScene;
		m_currentScene = nullptr;
		m_ArrayScene[d_tag] = nullptr;
	}
	if (m_ArrayScene[tag]) { // 만약 nullptr가 아닐 경우
		m_currentScene = m_ArrayScene[tag];
	}
	else {
		switch (tag) {
		case Scene_State::Title:
			m_ArrayScene[Scene_State::Title] = new CTitleScene();
			m_ArrayScene[Scene_State::Title]->BuildObjects(this, m_hwnd, Scene_State::Title);
			break;
		case Scene_State::Lobby:
			m_ArrayScene[Scene_State::Lobby] = new CLobbyScene();
			m_ArrayScene[Scene_State::Lobby]->BuildObjects(this, m_hwnd, Scene_State::Lobby);
			break;
		}
		m_currentScene = m_ArrayScene[tag];
	}
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