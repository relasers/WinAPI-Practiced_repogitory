#pragma once

class CTraffic_light
{
private:
	RECT pos;
	HBRUSH color;
	bool on;
public:
	CTraffic_light();
	~CTraffic_light();

	void setcolor(int color);
	void setpos(POINT);

	RECT getpos();
	HBRUSH getcolor();
	bool geton();
};

