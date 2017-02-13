#include "stdafx.h"
#include "Portal.h"


CPortal::CPortal()
{
	sprite = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Gate.png"), 4, 3);
}


CPortal::~CPortal()
{
}

void CPortal::play_spr() {
	sprite->Update();
}

RECT CPortal::getpos()
{
	return pos;
}


void CPortal::init(POINT x)
{
	pos = {x.x,x.y,
		x.x+8,x.y+80};
}

void CPortal::draw(HDC hdc, RECT m_rect) {
	sprite->Draw(hdc, pos.left-32, pos.top, m_rect);
}