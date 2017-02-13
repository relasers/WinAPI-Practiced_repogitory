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
// Ŭ���� �Լ������� ������� �ϴ°� �ƴϰ� cpp ���Ͽ� �Ѵ�.
bool CFrameWork::Initial(HWND h, RECT r,HINSTANCE inst) {
	// ������ �տ� �ڷ��� ���� �װ� ���������� �Ǿ������
	m_hwnd = h;
	m_rect = r;
	m_hInst = inst;

	for (int i = 0; i < Scene_State::Count; ++i) {
		m_ArrayScene[i] = nullptr;
	}
	m_currentScene = nullptr;

	lstrcpy(m_CaptionTitle,TEXT("�̸�"));
	lstrcat(m_CaptionTitle,TEXT(" ("));
	m_TitleLength = lstrlen(m_CaptionTitle);
	SetWindowText(m_hwnd,m_CaptionTitle);

	m_LastUpdate_time = chrono::system_clock::now();



	return m_hwnd != NULL; // ������ ���� �����ϸ� ������ �ڵ��� NULL ���� ����.
						   // �̰��� NULL���� ��� �����찡 ����� ��������� �ʾҴٴ°�, �ΰ��̸� �����츦 �׿���!
}
void CFrameWork::Destroy() { // ��ȯ���� ��� �������, ��¼�� �����״ϱ�, �޸� ���� ����
							 //�Ҹ��ڷ� �Ҹ��Ҷ� Destroy ȣ��, �Ҹ��ڴ� �Լ��� �׾�߸� ���´� , ���̰� �ٽ� �����ϰ� ������ ����
							 // �븦 �հ� �Ҷ� -> �׋��� ���� �Լ��� �̸� �� ���´�
	DestroyBackBuffer();
};

LRESULT CFrameWork::WindowMessage(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	switch (iMessage) {// �޽��� ��ȣ// case: �޽����� ���� ó��
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
	case WM_PAINT: //������ �ٽ� �׷���� �� ��
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps); // WM_PAINT �޼������� ��� , �� �ܿ��� ������ GetDC(),ReleaseDC() �� ����(��� ����Ҷ�)

		OnDraw(hdc); // hdc �� OnDraw �� �ѱ��.

		EndPaint(hwnd, &ps);
	}
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

	m_ArrayScene[Scene_State::Title] = new CTitleScene();
	m_ArrayScene[Scene_State::Title]->BuildObjects(this, m_hwnd,Scene_State::Title);

	m_ArrayScene[Scene_State::Lobby] = new CLobbyScene();
	m_ArrayScene[Scene_State::Lobby]->BuildObjects(this, m_hwnd, Scene_State::Lobby);

	m_currentScene = m_ArrayScene[Scene_State::Title]; // ������� Ÿ��Ʋ�� �ʱ�ȭ

	CreateBackBuffer();



}
void CFrameWork::OnDraw(HDC hdc) { //����� ��ο츦 ó���Ѵ�
		BitBlt(hdc, 0, 0, m_rect.right, m_rect.bottom, m_hdcBackGround, 0, 0, SRCCOPY);
}

void CFrameWork::PreprocessingDraw()
{
	ClearScreen(m_hdcBackGround); // ȭ�� Ŭ����
	SetBkMode(m_hdcBackGround, TRANSPARENT);
	//////<����� �׸���>///////////////////////////////////////////////////
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
	////////////////<ī��Ʈ��Ʈ>///////////////////////////////////
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
	if (m_ArrayScene[tag]) { // ���� nullptr�� �ƴ� ���
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