#include "stdafx.h"
#include "Platform.h"


CPlatform::CPlatform()
{
	
}


CPlatform::~CPlatform()
{
	
}

void CPlatform::setpos(RECT siz)
{
	pos = siz;
}

void CPlatform::placpos(POINT x)
{
	pos = { x.x,x.y,x.x + PLAT_WIDTH,x.y + PLAT_HEIGHT };
}

void CPlatform::initdir(int x,int mode)
{
	if (mode == 0) {
		stance = 1 + x % 2;
		if (6 < x)
			stance = 2;
			direction = PL_AC::plus;
			moved_distance = 0;
		}
	else {
		stance = x;
		
		direction = PL_AC::plus;
		moved_distance = 0;
	}
		
}

void CPlatform::moving()
{
	switch (stance) {
	case PL_Status::upsider: {
		moved_distance++;
		switch (direction) {
		case PL_AC::minus:
			OffsetRect(&pos, 0, PLAYERSPEED);
			break;
		case PL_AC::plus:
			OffsetRect(&pos, 0, -PLAYERSPEED);
			break;
		}
		break;
	}
	case PL_Status::slider: {
		moved_distance++;
		switch (direction) {
		case PL_AC::minus:
			OffsetRect(&pos, -PLAYERSPEED,0 );
			break;
		case PL_AC::plus:
			OffsetRect(&pos, PLAYERSPEED, 0);
			break;
		}
		break;
	}
	}

	if (moved_distance == MX_DIST) {
		moved_distance = 0;
		switch (direction) {
		case PL_AC::minus:
			direction = PL_AC::plus;
			break;
		case PL_AC::plus:
			direction = PL_AC::minus;
			break;
		}
	}
}

void CPlatform::draw(HDC hdc,RECT m_rect)
{
	
	brick.StretchBlt(hdc, pos.left, pos.top,
	 pos.right - pos.left, pos.bottom - pos.top);
	
}

RECT CPlatform::getpos()
{
	return pos;
}

int CPlatform::getdir()
{
	return direction;
}

int CPlatform::getstance()
{
	return stance;
}
