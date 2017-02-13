#pragma once
#include "stdafx.h"
class CBasket
{
private:
	CPlatform plat[3];
public:
	void init(POINT);
	void draw(HDC,RECT);
	void updater();

	CPlatform getplat(int);
	CBasket();
	~CBasket();
};

