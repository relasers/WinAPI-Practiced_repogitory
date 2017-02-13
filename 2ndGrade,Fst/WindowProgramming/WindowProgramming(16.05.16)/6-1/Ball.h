#pragma once
class CBall
{
private:
	RECT pos = {SIZE*2,SIZE * 2,SIZE * 3,SIZE * 3};
	bool ismove = false;
	int speed = 5;
	int xvec = 1;
	int yvec = 1;
	int shapetype = rec;
public:

	RECT getpos();
	bool getstate();
	int gettype();

	void setstate(bool);
	void getpos(POINT);
	void changevec(int x,int y);
	void movepos();
	void settype(int shape);
	CBall();
	~CBall();
};

