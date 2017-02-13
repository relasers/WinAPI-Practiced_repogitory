#include "stdafx.h"
#include "SpriteImage.h"


CSpriteImage::CSpriteImage(LPCTSTR path, int w, int h)
{
	cimg.Load(path);
	m_width = w;
	m_height = h;
	m_widthlen = cimg.GetWidth()/m_width;
	m_heightlen = cimg.GetHeight() / m_height;

	HDC hdc = cimg.GetDC();
	m_transcolor = GetPixel( hdc , 0, 0);
	cimg.ReleaseDC();
}
CSpriteImage::~CSpriteImage(){

}

void CSpriteImage::Update(){
	++m_ptcurrent.x;
	if (m_ptcurrent.x == m_width) {
		m_ptcurrent.x = 0;
		++m_ptcurrent.y;
	}
	if (m_ptcurrent.y == m_height) {
		m_ptcurrent.y = 0;
	}

}

void CSpriteImage::Draw(HDC hdc,int x, int y)
{
	cimg.TransparentBlt(
	hdc,x,y,
	m_widthlen,
	m_heightlen,
	m_ptcurrent.x*m_widthlen, 
	m_ptcurrent.y*m_heightlen,
	m_widthlen,
	m_heightlen,
	m_transcolor
	);
}
