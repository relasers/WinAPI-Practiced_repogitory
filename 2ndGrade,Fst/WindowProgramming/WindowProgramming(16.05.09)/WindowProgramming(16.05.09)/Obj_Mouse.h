#pragma once
class CObj_Mouse
{
private:
	RECT pos;
	int frame=0;
	bool exist = false;

public:
	CObj_Mouse();
	~CObj_Mouse();

	RECT Getpos();
	int Getframe();
	bool Getexist();

	void spriteframeinc();

	void setPos(POINT);

	void setexist(bool);
};

