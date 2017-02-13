#pragma once
class CItem
{
private:
	RECT pos;
	int item_id;
	int plat_id;
	int hp = 1;
	CSpriteImage* sprite_coin;
	CSpriteImage* sprite_treasure;
	CSpriteImage* sprite_ammobox;

public:
	CItem(POINT, int ITEMID, int PlatID);
	CItem() = default;
	~CItem();

	void draw(HDC,RECT,RECT);
	void play_spr();

	int collisioncheck(CPlayer, RECT, RECT);
	int getPlatid() { return plat_id; }
	int gethp();
	CItem* next;
};

