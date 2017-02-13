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
			, MemDC, 0, 0, 400, 400, SRCCOPY); // ���� �׸��� // SRCCOPY : �������� �����ϰ� �׷���
		}
		
}

void CBackGround::setid(int set)
{
	id = set;
}
