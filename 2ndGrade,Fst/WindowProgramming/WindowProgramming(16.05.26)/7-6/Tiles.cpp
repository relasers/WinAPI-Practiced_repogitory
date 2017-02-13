#include "stdafx.h"
#include "Tiles.h"


CTiles::CTiles()
{
}


CTiles::~CTiles()
{
}

void CTiles::setpos(POINT x, int xlen, int ylen)
{
	pos = {
		x.x,x.y,
		x.x + xlen,x.y + ylen
	};
}

void CTiles::draw(HDC hdc, HDC MemDC)
{
	if (isfilled) {

		StretchBlt(hdc, pos.left, pos.top, pos.right - pos.left, pos.bottom - pos.top
			, MemDC, 0, 0, 32, 32, SRCCOPY); // ���� �׸��� // SRCCOPY : �������� �����ϰ� �׷���

	}
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, pos.left, pos.top,
		pos.right, pos.bottom);
}
