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

void CPlatform::draw(HDC hdc)
{
	Rectangle(hdc,pos.left,pos.top,pos.right,pos.bottom);
}

RECT CPlatform::getpos()
{
	return pos;
}
