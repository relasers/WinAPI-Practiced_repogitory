#pragma once
#include <Windows.h>
#include <atlimage.h>

class CSpriteImage
{
protected:
	int m_width;
	int m_height;
	CImage cimg;
	POINT m_ptcurrent{0,0};
	int m_widthlen;
	int m_heightlen;
	COLORREF m_transcolor;
public:
	CSpriteImage(LPCTSTR path,int w,int h);
	~CSpriteImage();

	void Update();
	void Draw(HDC hdc,int x,int y); //lt ±‚¡ÿ
};

