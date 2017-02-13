#include "stdafx.h"
#include "Puzzle.h"

CPuzzle::CPuzzle()
{
}


CPuzzle::~CPuzzle()
{
}

void CPuzzle::SetPos(int i, int j,int screenmode, RECT m_rect) {
	pos.left = j*m_rect.right/ screenmode;
	pos.top = i*m_rect.bottom / screenmode;
	pos.right = j*m_rect.right / screenmode + m_rect.right / screenmode;
	pos.bottom = i*m_rect.bottom / screenmode + m_rect.bottom / screenmode;
}
void CPuzzle::CopyPos(RECT rect) {
	pos = rect;
}

RECT CPuzzle::getPos() {
	return pos;
}

POINT CPuzzle::getImagepos() {
	return imagepos;
}

void CPuzzle::setimagepos(int i, int j){
	imagepos = {j,i};
}

void CPuzzle::setviewed(bool state) {
	viewed = state;
}

void CPuzzle::setmoving(bool state) {
	moving = state;
}



bool CPuzzle::getViewed() {
	return viewed;
}

bool CPuzzle::getMoving() {
	return moving;
}

void CPuzzle::moverect(int dir) {
	switch (dir) {
	case Direction::left:
			OffsetRect(&pos,-1,0);
			break;
	case Direction::right:
		OffsetRect(&pos, 1, 0);
		break;
	case Direction::up:
		OffsetRect(&pos, 0, -1);
		break;
	case Direction::down:
		OffsetRect(&pos, 0, 1);
		break;
	}
}