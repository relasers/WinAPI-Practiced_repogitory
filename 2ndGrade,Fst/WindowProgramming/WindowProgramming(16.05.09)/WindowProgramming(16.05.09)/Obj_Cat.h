#pragma once
class CObj_Cat
{
private:
	RECT pos;
	int frame = 0;
	bool lostpath = false;
	int lostpathtime = 0;
public:
	CObj_Cat();
	~CObj_Cat();

	RECT Getpos();
	int Getframe();
	bool Getlostpath();

	void spriteframeinc();
	void setPos(POINT);
	void catmove(int);
	void setlostpath(bool);
};

