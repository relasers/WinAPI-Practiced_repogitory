#pragma once
class CPuzzle
{
private:
	RECT pos;
	POINT imagepos; // 이미지 표시부분

	bool viewed = true; // 이미지가 빈칸이 아닌지?
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

