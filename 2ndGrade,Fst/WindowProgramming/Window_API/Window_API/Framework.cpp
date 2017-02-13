#include "Framework.h"
#include <string>

#include "SpriteImage.h"

using namespace std;

template <typename T>
T GetUserDataPtr(HWND hWnd) 
{
	return reinterpret_cast<T>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
}

void SetUserDataPtr(HWND hWnd, LPVOID ptr) 
{
	LONG_PTR result = ::SetWindowLongPtr(
		hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));

}

CFramework::CFramework()
{
}

CFramework::~CFramework()
{
	OnDestroy();
}

bool CFramework::OnCreate(HWND hWnd, const RECT & rc)
{
	m_hWnd = hWnd;
	m_rcClient = rc;

	m_rcClient.right -= m_rcClient.left;
	m_rcClient.bottom -= m_rcClient.top;
	m_rcClient.left = 0;
	m_rcClient.top = 0;

	CreatebackBuffer();

	::SetUserDataPtr(m_hWnd, this);
	::SetTimer(hWnd, WT_COUNTING, 1, NULL);

	m_SpriteImage = new CSpriteImage(TEXT("res\\image\\sprite\\Char_Archer_1.png"), 4, 4);

	return (m_hWnd != NULL);
}

void CFramework::CreatebackBuffer()
{
	if (m_hDC)
	{
		::SelectObject(m_hDC, NULL);
		::DeleteDC(m_hDC);
	}
	if (m_hBitmapBackBuffer) ::DeleteObject(m_hBitmapBackBuffer);

	HDC hdc = ::GetDC(m_hWnd);
	m_hDC = ::CreateCompatibleDC(hdc);
	m_hBitmapBackBuffer = ::CreateCompatibleBitmap(hdc, m_rcClient.right, m_rcClient.bottom);
	::SelectObject(m_hDC, m_hBitmapBackBuffer);

	SetBKColor(RGB(255, 255, 255));

	ClearBackgroundColor();

	::ReleaseDC(m_hWnd, hdc);
}

bool CFramework::OnDestroy()
{
	if (m_hbrBackground) ::DeleteObject(m_hbrBackground);
	
	::SelectObject(m_hDC, NULL);
	if (m_hBitmapBackBuffer) ::DeleteObject(m_hBitmapBackBuffer);
	if (m_hDC) ::DeleteDC(m_hDC);

	return false;
}

bool CFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			::wsprintf(m_strTest, TEXT("left"));
			break;
		case VK_UP:
			::wsprintf(m_strTest, TEXT("top"));
			break;
		case VK_RIGHT:
			::wsprintf(m_strTest, TEXT("right"));
			break;
		case VK_DOWN:
			::wsprintf(m_strTest, TEXT("bottom"));
			break;
		}

		::InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_KEYUP:
		break;
	}
	return false;
}

bool CFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONUP:
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
		break;
	}
	return false;
}

HRESULT CFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	default:
		return ::DefWindowProc(hWnd, nMessageID, wParam, lParam);

	}
	return 0;
}

void CFramework::Update(WPARAM wParam)
{
	switch (wParam)
	{
	case WT_COUNTING:

		m_SpriteImage->OnUpdate();

		::InvalidateRect(m_hWnd, NULL, FALSE);
		break;
	}
}

void CFramework::SetBKColor(COLORREF color)
{
	m_clrBackBuffer = color;
	if (m_hbrBackground) ::DeleteObject(m_hbrBackground);
	m_hbrBackground = ::CreateSolidBrush(m_clrBackBuffer);
}

void CFramework::ClearBackgroundColor()
{
	::FillRect(m_hDC, &m_rcClient, m_hbrBackground);
}

void CFramework::PreproccessingForDraw()
{
	ClearBackgroundColor();
	::SetBkMode(m_hDC, TRANSPARENT);
}

void CFramework::OnDraw(HDC hDC)
{
	PreproccessingForDraw();

	m_SpriteImage->Draw(m_hDC, 100, 100);

	::DrawText(m_hDC, m_strTest, -1, &m_rcClient, DT_CENTER | DT_VCENTER | DT_SINGLELINE);



	::BitBlt(hDC, m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom, m_hDC, 0, 0, SRCCOPY);
}

LRESULT CFramework::WndProc(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	CFramework* self = ::GetUserDataPtr<CFramework*>(hWnd);
	if (!self)
		return ::DefWindowProc(hWnd, nMessageID, wParam, lParam);

	switch (nMessageID)
	{

	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
		self->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_KEYUP:
		self->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;

	case WM_TIMER:
		self->Update(wParam);
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = ::BeginPaint(hWnd, &ps);
			
			self->OnDraw(hdc);

			::EndPaint(hWnd, &ps);
		}
		break;

	case WM_DESTROY:
		::SetUserDataPtr(hWnd, NULL);
		::KillTimer(hWnd, WT_COUNTING);
		::PostQuitMessage(0);
		break;

	default:
		return self->OnProcessingWindowMessage(hWnd, nMessageID, wParam, lParam);

	}
	return 0;
}
