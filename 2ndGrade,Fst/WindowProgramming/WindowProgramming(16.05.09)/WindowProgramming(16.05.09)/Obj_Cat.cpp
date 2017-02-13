#include "stdafx.h"
#include "Obj_Cat.h"


CObj_Cat::CObj_Cat()
{
}

CObj_Cat::~CObj_Cat()
{
}
RECT CObj_Cat::Getpos() {
	return pos;
}
int CObj_Cat::Getframe() {
	return frame;
}
bool CObj_Cat::Getlostpath() {
	return lostpath;
}
void CObj_Cat::spriteframeinc() {
	(++frame) %= 4;
	if (lostpathtime != 0)
		lostpathtime--;
	if (lostpathtime == 0) {
		lostpath = false;
	}
}
void CObj_Cat::setPos(POINT pt) {
	pos = {
	pt.x,pt.y,pt.x + 32,pt.y + 32
	};
}
void CObj_Cat::catmove(int direction){
	switch (direction) {
	case Direction::left:
		OffsetRect(&pos,-3,0);
		break;
	case Direction::right:
		OffsetRect(&pos, 3, 0);
		break;
	case Direction::up:
		OffsetRect(&pos, 0, -3);
		break;
	case Direction::down:
		OffsetRect(&pos, 0, 3);
		break;
	}
}
void CObj_Cat::setlostpath(bool swit) {
	if (swit == true) {
		lostpath = true;
		lostpathtime = 2;
		return;
	}
	if (swit == false) {
		lostpath = false;
		lostpathtime = 10;
		return;
	}
}