#pragma once
#include "Stdafx.h"

typedef enum {
	stand, walk
}PStance;


class CPlayer
{
private:

	RECT pos = {0,0,32,42}; // 초기 위치

	int stance = PStance::stand;
	int direction = Direction::left;
	int degree = 0; // 각도
	float vec_y = 0; // 중력가속도
	bool isflying = true; // 날고있는가?
	bool canjump = true; // 점프중인가?
/////////////<스프라이트 모음>///////////////////////
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
	//////////<스프라이트 컨트롤>////////////
	void draw(HDC,RECT);
	void play_spr();
	void reset_spr();
	void setpos(POINT);
	/////////<변수 컨트롤>////////////////////
	void setstance(int);
	void setdir(int);
	void move(double);
	void collisioncheck(RECT,RECT);
	/////////////<키처리>////////////////
	void ActonKey(bool); // 키에 따른 동작
	void Updater(); // 플레이어 업데이트
	///////////////////////////////////////

	RECT getpos();
	int getstance();
	int getdir();

};

