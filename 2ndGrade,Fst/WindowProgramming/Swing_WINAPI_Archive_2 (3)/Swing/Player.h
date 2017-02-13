#pragma once
#include "Stdafx.h"

typedef enum {
	stand, walk
}PStance;


class CPlayer
{
private:

	RECT pos = {0,0,32,42}; // �ʱ� ��ġ

	int stance = PStance::stand;
	int direction = Direction::left;
	int degree = 0; // ����
	float vec_y = 0; // �߷°��ӵ�
	bool isflying = true; // �����ִ°�?
	bool canjump = true; // �������ΰ�?
/////////////<��������Ʈ ����>///////////////////////
	CSpriteImage* sprite_walk_left;
	CSpriteImage* sprite_walk_right;
	CSpriteImage* sprite_stand_left;
	CSpriteImage* sprite_stand_right;
	CSpriteImage* sprite_jump_left;
	CSpriteImage* sprite_jump_right;
	CSpriteImage* sprite_Ujump_left;
	CSpriteImage* sprite_Ujump_right;
////////////////////////////////////////////////
public:
	CPlayer();
	~CPlayer();
	//////////<��������Ʈ ��Ʈ��>////////////
	void draw(HDC,RECT);
	void play_spr();
	void reset_spr();
	void setpos(POINT);
	/////////<���� ��Ʈ��>////////////////////
	void setstance(int);
	void setdir(int);
	void move(double);
	void collisioncheck(RECT,RECT);
	/////////////<Űó��>////////////////
	void ActonKey(bool); // Ű�� ���� ����
	void Updater(); // �÷��̾� ������Ʈ
	///////////////////////////////////////

	RECT getpos();
	int getstance();
	int getdir();

};

