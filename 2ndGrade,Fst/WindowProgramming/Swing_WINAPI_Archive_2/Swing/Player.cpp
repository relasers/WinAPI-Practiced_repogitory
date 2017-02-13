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
	//sprite_walk_left = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Player_Walk_left(32x42).png"), 1, 8);
	//sprite_walk_right = new CSpriteImage(TEXT("RES\\IMG\\SPRITE\\Player_Walk_right(32x42).png"), 1, 8);
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
	xline = 0;
}

void CPlayer::setstance(int st) {
	stance = st;
}

void CPlayer::setdir(int st) {
	direction = st;
}
void CPlayer::setstline()
{
	StartLine = {pos.left + pos.right-pos.left,
	pos.bottom};
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

void CPlayer::collisioncheck(CPlatform platform,RECT m_rect)
{
	RECT COLLISION_CHECK;

	if (m_rect.right < pos.right) {
		pos.right = m_rect.right;
		pos.left = m_rect.right - PLAYER_WIDTH;
	}
	if (pos.left < 0) {
		pos.left = 0;
		pos.right = PLAYER_WIDTH;
	}
	if (m_rect.bottom < pos.top) {
		pos.top = m_rect.bottom - PLAYER_HEIGHT;
		pos.bottom = m_rect.bottom;
	}

	if (IntersectRect(&COLLISION_CHECK, &pos, &platform.getpos())) {
		vec_y = 0; // 가속벡터를 다시 0으로 초기화
		isflying = false; // 이제 날지 않아
		//POINT setpt = {pos.left,platform.getpos().top-PLAYER_HEIGHT}; // 플레이어 위치 재세팅!
		//setpos(setpt); // 위치 재조정한다/
		
		if (
			platform.getpos().right < pos.right &&
			platform.getpos().right > pos.left) {
			while (IntersectRect(&COLLISION_CHECK, &pos, &platform.getpos())) {
				pos.left = platform.getpos().right + 5;
				pos.right = platform.getpos().right+PLAYER_WIDTH + 5;
				//OffsetRect(&pos,5,0);
			}
		} // 플랫폼 오른쪽에 닿았을때
		if (
			platform.getpos().left > pos.left &&
			platform.getpos().left < pos.right) {
			while (IntersectRect(&COLLISION_CHECK, &pos, &platform.getpos())) {
				pos.left = platform.getpos().left - PLAYER_WIDTH - 5;
				pos.right = platform.getpos().left - 5;
				//OffsetRect(&pos, -5, 0);
			}
		}// 플랫폼 왼쪽에 닿았을때
		if (
			platform.getpos().top <  pos.bottom
			&& platform.getpos().top > pos.top) {
			while (IntersectRect(&COLLISION_CHECK, &pos, &platform.getpos())) {
				OffsetRect(&pos, 0, -PLAYERSPEED);
			}
		}
		if (platform.getpos().bottom > pos.top
			&& platform.getpos().bottom < pos.bottom) {
			while (IntersectRect(&COLLISION_CHECK, &pos, &platform.getpos())) {
				OffsetRect(&pos, 0, PLAYERSPEED);
			}
		}

		canjump = true; // 땅을 밟은자는 점프가 가능하다

	}

	RECT playerExtend = { pos.left,pos.top,pos.right,pos.bottom + PLAYERSPEED };
	if (IntersectRect(&COLLISION_CHECK, &playerExtend, &platform.getpos())) {
		switch (platform.getstance()) {
		case PL_Status::slider: {
			switch (platform.getdir()) {
			case PL_AC::minus:
				OffsetRect(&pos, -PLAYERSPEED, 0);
				break;
			case PL_AC::plus:
				OffsetRect(&pos, PLAYERSPEED, 0);
				break;
			}
		}
		break;
		case PL_Status::upsider: {
			switch (direction) {
			case PL_AC::minus:
				OffsetRect(&pos, 0, PLAYERSPEED);
				break;
			case PL_AC::plus:
				OffsetRect(&pos, 0, -PLAYERSPEED);
				break;
			}

		}
		 break;
		}
		iscollisionedP = true;
	}

}

void CPlayer::portalcheck(CPortal port,RECT m_rect)
{
	RECT COLLISION_CHECK;
	if (IntersectRect(&COLLISION_CHECK, &pos, &port.getpos())) {
		POINT settingpt = { m_rect.right / 2,120 };
		setpos(settingpt);
		soundM.PlaySnd(SD_PORTAL);
	}
}

void CPlayer::setcollisioned(bool x)
{
	iscollisionedP = x;
}

void CPlayer::setflying(bool x)
{
	isflying = x;
}

void CPlayer::spincont()
{
	switch (isspinning) {
	case true:
		degree = 0;
		xline = 0;
		isspinning = false;
		break;
	case false:
		if (xline != 0) {
			if (xline < 0)
				degree = 90;
			else
				degree = 270;
			isspinning = true;
		}
	
		break;
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
				vec_y = -PLAYER_JP_POWER; // 점프벡터 가동!
				isflying = true; // 난다 날아
				canjump = false; // 이제 점프는 불가능!
			}

		}
		if (GetAsyncKeyState('Z') || GetAsyncKeyState('z') & 0x8000) {
			if (-MX_LINE_LENGTH < xline && !isspinning) {
				--xline;
			}
		}
		if (GetAsyncKeyState('X') || GetAsyncKeyState('x') & 0x8000) {
			if (MX_LINE_LENGTH > xline && !isspinning) {
				++xline;
			}
		}

	}
}

void CPlayer::Updater()
{

	if (isspinning) {
		(--degree) %= 360;
		(--degree) %= 360;
		POINT x{};
		x.x = abs(xline)*sin(PI*degree / 180.0) + EndLine.x;
		x.y = abs(xline)*cos(PI*degree / 180.0) + EndLine.y;
		pos = { x.x,x.y,
			x.x + PLAYER_WIDTH,
			x.y + PLAYER_HEIGHT };

		

	}

	if (!isspinning) {
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

	StartLine = {pos.left+sprite_stand_left->getwidth()/2,
		pos.top + sprite_stand_left->getheight() / 2
	};
	EndLine = { pos.left + sprite_stand_left->getwidth() / 2 + xline,
		pos.top + sprite_stand_left->getheight() / 2
	};
	}

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

	if (xline != 0) {
		if (!isspinning) {
			MoveToEx(hdc, StartLine.x, StartLine.y, NULL);
			LineTo(hdc, EndLine.x, EndLine.y);
		}
		if (isspinning) {
			MoveToEx(hdc, EndLine.x, EndLine.y, NULL);
			POINT x{};
			x.x = abs(xline)*sin(PI*degree / 180.0) + EndLine.x + sprite_jump_left->getwidth()/2;
			x.y = abs(xline)*cos(PI*degree / 180.0) + EndLine.y + sprite_jump_left->getheight() / 2;;
			LineTo(hdc, x.x, x.y);
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

bool CPlayer::getisspin()
{
	return isspinning;
}

bool CPlayer::getcollisioned()
{
	return iscollisionedP;
}
