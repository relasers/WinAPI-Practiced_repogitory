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

	RECT pos = {0,0,32,42}; // 초기 위치
	POINT StartLine;
	POINT EndLine;
	int xline = 0;

	int stance = PStance::stand;
	int act_mode = PMode::roped;
	int direction = Direction::left;
	int degree = 0; // 각도
	float vec_y = 0; // 중력가속도
	bool isflying = true; // 날고있는가?
	bool canjump = true; // 점프중인가?
	bool iscollisionedP = true; // 플랫폼과 접촉한적 있는가?
	bool isspinning = false;
/////////////<스프라이트 모음>///////////////////////
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
	//////////<스프라이트 컨트롤>////////////
	void draw(HDC,RECT);
	void play_spr();
	void reset_spr();
	void setpos(POINT);
	/////////<변수 컨트롤>////////////////////
	void setstance(int);
	void setdir(int);
	void setstline();
	void move(double);
	void collisioncheck(CPlatform,RECT);
	void portalcheck(CPortal,RECT);
	void setcollisioned(bool);
	void setflying(bool);
	void spincont();
	/////////////<키처리>////////////////
	void ActonKey(bool); // 키에 따른 동작
	void Updater(); // 플레이어 업데이트
	///////////////////////////////////////

	RECT getpos();
	int getstance();
	int getdir();
	bool getisspin();
	bool getcollisioned();
};

