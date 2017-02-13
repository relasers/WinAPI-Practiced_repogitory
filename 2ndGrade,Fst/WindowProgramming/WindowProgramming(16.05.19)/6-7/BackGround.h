#pragma once
class CBackGround
{
public:
	RECT pos;
	int id = 0;
	bool isfilled = false;
	CBackGround();
	~CBackGround();
	void setpos(POINT, int xlen, int ylen);
	void draw(HDC,HDC);
	void setid(int);
};

