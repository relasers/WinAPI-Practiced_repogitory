#pragma once
#include "Stdafx.h"
#include "Platform.h"
#include "Portal.h"
typedef enum {
	stand, walk
}PStance;

typedef enum {
	action,roped
}PMode;


class CPlayer
{
private:

	RECT pos = {0,0,32,42}; // �ʱ� ��ġ
	POINT StartLine;
	POINT EndLine;
	int xline = 0;

	int stance = PStance::stand;
	int act_mode = PMode::roped;
	int direction = Direction::left;
	int degree = 0; // ����
	float vec_y = 0; // �߷°��ӵ�
	bool isflying = true; // �����ִ°�?
	bool canjump = true; // �������ΰ�?
	bool iscollisionedP = true; // �÷����� �������� �ִ°�?
	bool isspinning = false;
/////////////<��������Ʈ ����>///////////////////////
	CSpriteImage* sprite_walk_left;
	CSpriteImage* sprite_walk_right;
	CSpriteImage* sprite_stand_left;
	CSpriteImage* sprite_stand_right;
	CSpriteImage* sprite_jump_left;
	CSpriteImage* sprite_jump_right;
	CSpriteImage* sprite_Ujump_left;
	CSpriteImage* sprite_Ujump_right;
	CSpriteImage* sprite_bash_left;
	CSpriteImage* sprite_bash_right;
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
	void setstline();
	void move(double);
	void collisioncheck(CPlatform,RECT);
	void portalcheck(CPortal,RECT);
	void setcollisioned(bool);
	void setflying(bool);
	void spincont();
	/////////////<Űó��>////////////////
	void ActonKey(bool); // Ű�� ���� ����
	void Updater(); // �÷��̾� ������Ʈ
	///////////////////////////////////////

	RECT getpos();
	int getstance();
	int getdir();
	bool getisspin();
	bool getcollisioned();
};

