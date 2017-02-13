#pragma once
class CObj_Obstacle
{
	RECT pos;
	bool exist = false;
public:
	CObj_Obstacle();
	~CObj_Obstacle();

	RECT getPos();
	bool getexist();


	void setPos(POINT);
	void setexist(bool);
};

