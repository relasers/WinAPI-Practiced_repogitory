#pragma once
class CTile
{
public:
	RECT pos;
	int id;
	bool isfilled = false;
	CTile();
	~CTile();
	void setpos(POINT,int,int);
	void draw(HDC,HDC);
};

