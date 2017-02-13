#include "stdafx.h"
#include "Tile.h"


CTile::CTile()
{
}


CTile::~CTile()
{
}

void CTile::setpos(POINT x,int xlen,int ylen)
{
	pos = {
	x.x,x.y,
	x.x+xlen,x.y+ylen
	};
}

void CTile::draw(HDC hdc, HDC MemDC)
{
	Rectangle(hdc, pos.left, pos.top,
		pos.right, pos.bottom);


	if (isfilled) {
	
		StretchBlt(hdc, pos.left, pos.top, pos.right - pos.left, pos.bottom - pos.top
			, MemDC, 0, 0,32,32, SRCCOPY); // ���� �׸��� // SRCCOPY : �������� �����ϰ� �׷���
	
	}
}
