#pragma once

#include <windows.h>
#include <atlImage.h>

class CSpriteImage
{

protected:

	CImage cimg;

	int width;
	int height;

	int widthLen;
	int heightLen;

	POINT ptCurrent{ 0,0 };

	COLORREF Backcolor;

public:
	CSpriteImage(LPCTSTR path, int w, int h);
	~CSpriteImage();
	
	void OnUpdate();

	void Draw(HDC hDC, int x, int y);
};

