#include "stdafx.h"
#include "Obj_Mouse.h"


CObj_Mouse::CObj_Mouse()
{
}


CObj_Mouse::~CObj_Mouse()
{
}

RECT CObj_Mouse::Getpos() {
	return pos;
}
int CObj_Mouse::Getframe() {
	return frame;
}
bool CObj_Mouse::Getexist() {
	return exist;
}
void CObj_Mouse::spriteframeinc() {
	(++frame) %= 4;
}
void CObj_Mouse::setPos(POINT ptmouse) {
	pos = {
	ptmouse.x - 16,	
	ptmouse.y - 16,
	ptmouse.x + 16,
	ptmouse.y + 16,
	};
}
void CObj_Mouse::setexist(bool swit) {
	if (swit == true) {
		exist = true;
		return;
	}
	if (swit == false) {
		exist = false;
		return;
	}	
}