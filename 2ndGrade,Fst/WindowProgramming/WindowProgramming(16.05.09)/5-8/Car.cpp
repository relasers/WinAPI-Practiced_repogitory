#include "stdafx.h"
#include "Car.h"


CCar::CCar()
{
}


CCar::~CCar()
{
}

void CCar::imageframeinc() {
	(++frame) %= 4;
}

int CCar::getframe() {
	return frame;
}

int CCar::getdir() {
	return direction;
}

RECT CCar::getpos() {
	return pos;
}

void CCar::setspeed(double set_spd) {
	speed = set_spd;
}
void CCar::setpos(POINT pt) {
	pos = {
	pt.x,pt.y,pt.x+100,pt.y+50
	};
}

void CCar::setdirection(int dir) {
	direction = dir;
}
void CCar::moving(RECT m_rect) {
	switch(direction){
	case Direction::to_left:
		OffsetRect(&pos,-speed,0);
		if (pos.right < m_rect.left) {
			pos.left = m_rect.right - 100;
			pos.right = m_rect.right;
		}
		break;
	case Direction::to_right:
		OffsetRect(&pos, speed, 0);
		if (pos.left > m_rect.right) {
			pos.left = m_rect.left;
			pos.right = m_rect.left+100;
		}
		break;
	}
}

void CCar::movbak(RECT m_rect) {
	switch (direction) {
	case Direction::to_right:
		OffsetRect(&pos, -speed, 0);
		if (pos.right < m_rect.left) {
			pos.left = m_rect.right - 100;
			pos.right = m_rect.right;
		}
		break;
	case Direction::to_left:
		OffsetRect(&pos, speed, 0);
		if (pos.left > m_rect.right) {
			pos.left = m_rect.left;
			pos.right = m_rect.left+100;
		}
		break;
	}
}
