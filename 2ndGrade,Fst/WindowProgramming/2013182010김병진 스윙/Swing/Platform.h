#pragma once

class CPlatform
{
private:
	RECT pos;
	int stance = PL_Status::holder;
	int direction = 1;
	int moved_distance = 50;

	
public:
	CPlatform();
	~CPlatform();
	//////////////////////
	
	void draw(HDC,RECT);
	///////////////////
	void setpos(RECT);
	void placpos(POINT);
	void initdir(int,int);
	void moving();
	RECT getpos(); // rect ¹ÝÈ¯
	int getdir();
	int getstance();

};

