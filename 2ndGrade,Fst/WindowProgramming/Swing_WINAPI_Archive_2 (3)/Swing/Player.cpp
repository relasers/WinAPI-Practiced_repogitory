#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
	sprite_walk_left = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Player_Walk_left(32x42).png"), 1, 8);
	sprite_walk_right = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Player_Walk_right(32x42).png"), 1, 8);
	sprite_stand_left = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Player_Stand_left(32x42).png"), 1, 23);
	sprite_stand_right = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Player_Stand_right(32x42).png"), 1, 23);
	sprite_jump_left = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Player_Jump_left(32x48).png"), 1, 1);
	sprite_jump_right = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Player_Jump_right(32x48).png"), 1, 1);
	sprite_Ujump_left = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Player_UJump_left(32x48).png"), 1, 1);
	sprite_Ujump_right = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Player_UJump_right(32x48).png"), 1, 1);
}


CPlayer::~CPlayer()
{
}

void CPlayer::play_spr(){
	sprite_stand_left->Update();
	sprite_stand_right->Update();
	sprite_walk_left->Update();
	sprite_walk_right->Update();

	//(++degree) %= 360;

	// 스프라이트 각도 재설정
	sprite_stand_left->setdegree(degree);
	sprite_stand_right->setdegree(degree);
	sprite_walk_left->setdegree(degree);
	sprite_walk_right->setdegree(degree);
	sprite_jump_left->setdegree(degree);
	sprite_jump_right->setdegree(degree);
	sprite_Ujump_left->setdegree(degree);
	sprite_Ujump_right->setdegree(degree);
}

void CPlayer::reset_spr(){
	sprite_stand_left->ClearFramePos();
	sprite_stand_right->ClearFramePos();
	sprite_walk_left->ClearFramePos();
	sprite_walk_right->ClearFramePos();

}

void CPlayer::setpos(POINT x)
{
	pos = {x.x,x.y,x.x+PLAYER_WIDTH,x.y+PLAYER_HEIGHT};
}

void CPlayer::setstance(int st) {
	stance = st;
}

void CPlayer::setdir(int st) {
	direction = st;
}
void CPlayer::move(double dist) {
	switch (direction) {
	case Direction::left:
		OffsetRect(&pos,-dist,0);
		break;
	case Direction::right:
		OffsetRect(&pos, dist, 0);
		break;
	}
}

void CPlayer::collisioncheck(RECT rect,RECT platform)
{
	RECT COLLISION_CHECK;
	if (IntersectRect(&COLLISION_CHECK, &pos, &platform)) {
		vec_y = 0; // 가속벡터를 다시 0으로 초기화
		isflying = false; // 이제 날지 않아
		POINT setpt = {pos.left,platform.top-PLAYER_HEIGHT}; // 플레이어 위치 재세팅!
		setpos(setpt); // 위치 재조정한다/
		canjump = true; // 땅을 밟은자는 점프가 가능하다
	}
}

void CPlayer::ActonKey(bool iskeydown)
{//실시간으로 키를 딜레이없이 입력받는다
	if (iskeydown) {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			direction = Direction::left;
			stance = PStance::walk;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			direction = Direction::right;
			stance = PStance::walk;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (canjump) {
				vec_y = -10; // 점프벡터 가동!
				isflying = true; // 난다 날아
				canjump = false; // 이제 점프는 불가능!
			}
			
		}
	}
	
}

void CPlayer::Updater()
{
	(++degree)%=360;
	switch (stance) {
	case PStance::walk:
		move(PLAYERSPEED); // 플레이어 속도만큼 움직인다.
		break;
	}

	if(isflying){
		if (vec_y > 0) {
			vec_y += GRAVITY; // 음수라면 중력만 받는다
		}
		else
			vec_y += GRAVITY + GRAVITY_ACCEL; // 양수가 되면 가속도도 추가로 받는다
	}
	OffsetRect(&pos, 0, vec_y); // 가속도만큼 하강한다.




}

void CPlayer::draw(HDC hdc,RECT m_rect){

	if (!isflying) {
		switch (stance) {
		case PStance::stand:
			switch (direction) {
			case Direction::left:
				sprite_stand_left->Draw(hdc, pos.left, pos.top, m_rect);
				break;
			case Direction::right:
				sprite_stand_right->Draw(hdc, pos.left, pos.top, m_rect);
				break;
			}
			break;
		case PStance::walk:
			switch (direction) {
			case Direction::left:
				sprite_walk_left->Draw(hdc, pos.left, pos.top + 6, m_rect);
				break;
			case Direction::right:
				sprite_walk_right->Draw(hdc, pos.left, pos.top + 6, m_rect);
				break;
			}
			break;
		}
	}
	if(isflying) {
		switch (direction) {
		case Direction::left:
			if (vec_y < 0) {
				sprite_jump_left->Draw(hdc, pos.left, pos.top, m_rect);
			}
			else {
				sprite_Ujump_left->Draw(hdc, pos.left, pos.top, m_rect);
			}
			break;
		case Direction::right:
			if (vec_y < 0) {
				sprite_jump_right->Draw(hdc, pos.left, pos.top, m_rect);
			}
			else {
				sprite_Ujump_right->Draw(hdc, pos.left, pos.top, m_rect);
			}
			break;
		}
	}
	
}

RECT CPlayer::getpos() {
	return pos;
}
int CPlayer::getstance() {
	return stance;
}
int CPlayer::getdir() {
	return direction;
}