#pragma once
class CPortal
{
private:
	RECT pos;
	CSpriteImage* sprite;
public:
	CPortal();
	~CPortal();

	void init(POINT);
	void draw(HDC, RECT);
	void play_spr();

	RECT getpos();
};

