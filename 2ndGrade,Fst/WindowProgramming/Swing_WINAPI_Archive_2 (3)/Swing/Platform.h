#pragma once
class CPlatform
{
private:
	RECT pos;
public:
	CPlatform();
	~CPlatform();

	void setpos(RECT);
	void draw(HDC);
	///////////////////
	RECT getpos(); // rect ¹ÝÈ¯


};

