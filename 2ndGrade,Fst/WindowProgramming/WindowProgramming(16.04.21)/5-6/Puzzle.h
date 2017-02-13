#pragma once
class CPuzzle
{
private:
	RECT pos;
	POINT imagepos; // �̹��� ǥ�úκ�

	bool viewed = true; // �̹����� ��ĭ�� �ƴ���?
	bool moving = false;

public:
	void SetPos(int i, int j, int screenmode,RECT m_rect);
	void CopyPos(RECT);
	
	void setimagepos(int i,int j);
	void setviewed(bool state);
	void setmoving(bool state);
	void moverect(int dir);

	RECT getPos();
	POINT getImagepos();
	bool getViewed();
	bool getMoving();

	CPuzzle();
	~CPuzzle();
};

