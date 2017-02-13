#include "stdafx.h"
#include "OBJ.h"


COBJ::COBJ()
{
}


COBJ::~COBJ()
{
}
void COBJ::setpos(POINT x, int xlen, int ylen)
{
	pos = {
		x.x,x.y,
		x.x + xlen,x.y + ylen
	};
}

void COBJ::draw(HDC hdc, HDC MemDC)
{


	if (isfilled) {

		TransparentBlt(hdc, pos.left, pos.top, pos.right - pos.left, pos.bottom - pos.top
			, MemDC, 0, 0, 32, 32, RGB(255,255,255)); // 산을 그린다 // SRCCOPY : 바탕색을 무시하고 그려라
		SetTextColor(hdc,RGB(150,150,150));
		wsprintf(temp,TEXT("%d"),id);
		DrawText(hdc,temp,-1,&pos, DT_VCENTER|DT_CENTER);
	}
}