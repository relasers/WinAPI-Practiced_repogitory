#pragma once
class COBJ
{
public:
	RECT pos;
	TCHAR temp[20];
	int id = -1;
	bool isfilled = false;
	COBJ();
	~COBJ();
	void setpos(POINT, int, int);
	void draw(HDC, HDC);
};

