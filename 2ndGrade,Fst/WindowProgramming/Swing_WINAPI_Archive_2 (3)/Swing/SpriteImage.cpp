#include "stdafx.h"
#include "SpriteImage.h"

CSpriteImage::CSpriteImage(LPCTSTR path, int w, int h)
{
	cimg.Load(path);
	m_width = w;
	m_height = h;
	m_widthlen = cimg.GetWidth() / m_width;
	m_heightlen = cimg.GetHeight() / m_height;
	degree = 0;
	HDC hdc = cimg.GetDC();
	m_transcolor = GetPixel(hdc, 0 , 0);
	m_backcolor = (HBRUSH)CreateSolidBrush(m_transcolor);
	cimg.ReleaseDC();
}
CSpriteImage::~CSpriteImage() {

}

void CSpriteImage::Update() {
	++m_ptcurrent.x;
	if (m_ptcurrent.x == m_width) {
		m_ptcurrent.x = 0;
		++m_ptcurrent.y;
	}
	if (m_ptcurrent.y == m_height) {
		m_ptcurrent.y = 0;
	}

}

void CSpriteImage::ClearFramePos(){
	m_ptcurrent = {0,0}; // 0,0으로 초기화
}

void CSpriteImage::Draw(HDC hdc, int x, int y,RECT m_rect)
{
	HDC RotateDC;
	RotateDC = CreateCompatibleDC(hdc); // hdc와 호환시킨다.
	HBITMAP Rotate; // 레이어 생성
	Rotate = CreateCompatibleBitmap(hdc, m_rect.right, m_rect.bottom); // 다블 버퍼링 ,hdc와 호환시키자.
	SelectObject(RotateDC, Rotate);
	{
		FillRect(RotateDC, &m_rect, m_backcolor);
		XFORM xForm = { 1,0,0,1,0,0 };
		SetGraphicsMode(RotateDC, GM_ADVANCED);
		xForm.eM11 = (float)cos(degree*PI / 180);
		xForm.eM12 = (float)sin(degree*PI / 180);
		xForm.eM21 = (float)-sin(degree*PI / 180);
		xForm.eM22 = (float)cos(degree*PI / 180);
		xForm.eDx = x + (float)m_widthlen / 2.0;												// 3행 1열 성분 설정 (X축 이동 성분)
		xForm.eDy = y + (float)m_heightlen / 2.0;
		SetWorldTransform(RotateDC, &xForm);
		SetBkMode(RotateDC, TRANSPARENT);
		
		cimg.TransparentBlt(
			RotateDC,
			-(m_widthlen / 2.0),
			-(m_heightlen / 2.0),
			m_widthlen,
			m_heightlen,
			m_ptcurrent.x*m_widthlen,
			m_ptcurrent.y*m_heightlen,
			m_widthlen,
			m_heightlen,
			m_transcolor
		);

		xForm = { 1,0,0,1,0,0 };
		SetWorldTransform(RotateDC, &xForm);

		TransparentBlt(hdc, 0, 0, m_rect.right, m_rect.bottom, RotateDC,
			0, 0,m_rect.right,m_rect.bottom, m_transcolor);
	}
	DeleteObject(Rotate);
	DeleteDC(RotateDC);
		
}

void CSpriteImage::setdegree(float deg)
{
	degree = deg;
}
