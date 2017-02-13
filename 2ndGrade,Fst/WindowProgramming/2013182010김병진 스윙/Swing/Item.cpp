#include "stdafx.h"
#include "Item.h"


CItem::CItem(POINT x, int inpt_id, int inplat_id)
{
	item_id = inpt_id;
	plat_id = inplat_id;

	
	sprite_coin = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Coin.png"), 2, 5);
	sprite_treasure = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Treasure.png"), 4, 3);
	sprite_ammobox = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\AmmoCreate.png"),5,1);

	next = nullptr;

	pos = { x.x - sprite_coin->getwidth() / 2,x.y,
		x.x + sprite_coin->getwidth() / 2
	,x.y + 32
	};
}

CItem::~CItem()
{
}

void CItem::draw(HDC hdc, RECT m_rect,RECT plat_rect)
{
	POINT pt{plat_rect.left+pos.left, plat_rect.top + pos.top};
	switch (item_id) {
	case ITEM_ID::ITM_COIN:
		sprite_coin->Draw(hdc, pt.x, pt.y, m_rect);
		break;
	case ITEM_ID::ITM_TREASURE:
		sprite_treasure->Draw(hdc, pt.x, pt.y, m_rect);
		break;
	case ITEM_ID::ITM_AMMO:
		sprite_ammobox->Draw(hdc, pt.x, pt.y, m_rect);
		break;
	
	}
	
}

void CItem::play_spr()
{
	sprite_coin->Update();
	sprite_ammobox->Update();
	sprite_treasure->Update();
}
int CItem::collisioncheck(CPlayer player, RECT m_rect, RECT plat_rect)
{
	RECT COLLISION_CHECK;
	RECT REAL_POS{ plat_rect.left + pos.left,
		plat_rect.top + pos.top,
		plat_rect.left + pos.left + 32,
		plat_rect.top + pos.top + 32 };
	int score = 0;

	if (IntersectRect(&COLLISION_CHECK, &player.getpos(), &REAL_POS)) {
		switch (item_id) {
		case ITEM_ID::ITM_COIN:
			hp = 0;
			score += 10;
			soundM.PlaySnd(SD_GETITEM);
			break;
		case ITEM_ID::ITM_AMMO:
			hp = 0;
			score += 50;
			soundM.PlaySnd(SD_GETITEM);
			break;
		case ITEM_ID::ITM_TREASURE:
			hp = 0;
			score += 100;
			soundM.PlaySnd(SD_GETITEM);
			break;
		}
	}
	return score;
}

int CItem::gethp()
{
	return hp;
}
