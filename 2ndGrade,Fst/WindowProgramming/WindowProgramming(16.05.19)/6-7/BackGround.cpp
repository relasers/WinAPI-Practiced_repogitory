#include "stdafx.h"
#include "BackGround.h"


CBackGround::CBackGround()
{
}


CBackGround::~CBackGround()
{
}

void CBackGround::setpos(POINT x, int xlen, int ylen)
{
	pos = {
		x.x,x.y,
		x.x + xlen,x.y + ylen
	};

}

void CBackGround::draw(HDC hdc, HDC MemDC)
{

	if (isfilled) {
		StretchBlt(hdc, pos.left, pos.top, pos.right - pos.left, pos.bottom - pos.top
			, MemDC, 0, 0, 400, 400, SRCCOPY); // 산을 그린다 // SRCCOPY : 바탕색을 무시하고 그려라
		}
		
}

void CBackGround::setid(int set)
{
	id = set;
}
