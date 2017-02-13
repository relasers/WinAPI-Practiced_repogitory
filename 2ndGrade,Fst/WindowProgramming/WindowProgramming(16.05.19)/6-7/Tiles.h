#pragma once
class CTiles
{
public:
	RECT pos;
	int id;
	bool isfilled = false;
	CTiles();
	~CTiles();
	void setpos(POINT, int, int);
	void draw(HDC, HDC);
};

