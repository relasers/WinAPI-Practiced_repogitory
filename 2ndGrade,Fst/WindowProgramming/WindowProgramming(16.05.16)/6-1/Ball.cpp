#include "stdafx.h"
#include "Ball.h"


RECT CBall::getpos()
{
	return pos;
}

bool CBall::getstate()
{
	return ismove;
}

int CBall::gettype()
{
	return shapetype;
}

void CBall::setstate(bool stat)
{
	ismove = stat;
}

void CBall::getpos(POINT pt)
{
	pos = {
	pt.x,pt.y,pt.x+SIZE,pt.y+SIZE
	
	};
}

void CBall::changevec(int x, int y)
{
	xvec *= x;
	yvec *= y;
}

void CBall::movepos()
{
	if(ismove)
	OffsetRect(&pos,speed*xvec,speed*yvec);
}

void CBall::settype(int shape)
{
	shapetype = shape;
}

CBall::CBall()
{

}


CBall::~CBall()
{
}
