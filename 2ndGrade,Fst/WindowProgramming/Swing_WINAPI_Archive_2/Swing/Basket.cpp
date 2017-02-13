#include "stdafx.h"
#include "Basket.h"


void CBasket::init(POINT x)
{
	RECT setp;
	int calc;
	setp = { x.x,x.y,x.x + 16,x.y + 64 };
	plat[0].setpos(setp);
	setp = { x.x, x.y+32 , x.x + BASK_LENGTH , x.y + 64 };
	plat[1].setpos(setp);
	setp = { x.x + BASK_LENGTH - 16, x.y ,x.x + BASK_LENGTH , x.y + 64 };
	plat[2].setpos(setp);

	for (int i = 0; i < 3; ++i) {
		plat[i].initdir(PL_Status::slider,1);
	}
}

void CBasket::draw(HDC hdc,RECT m_rect)
{
	for (int i = 0; i < 3; ++i) {
		plat[i].draw(hdc, m_rect);
	}
}

void CBasket::updater()
{
	for (int i = 0; i < 3; ++i) {
	plat[i].moving();
	}
}

CPlatform CBasket::getplat(int x)
{
	return plat[x];
}

CBasket::CBasket()
{
}


CBasket::~CBasket()
{
}
