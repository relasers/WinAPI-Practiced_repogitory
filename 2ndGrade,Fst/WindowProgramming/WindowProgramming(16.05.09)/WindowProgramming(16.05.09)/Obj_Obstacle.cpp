#include "stdafx.h"
#include "Obj_Obstacle.h"


CObj_Obstacle::CObj_Obstacle()
{
}


CObj_Obstacle::~CObj_Obstacle()
{
}

RECT CObj_Obstacle::getPos() {
	return pos;
}
bool CObj_Obstacle::getexist() {
	return exist;
}

void CObj_Obstacle::setPos(POINT pt) {
	pos = {
	pt.x,pt.y,pt.x+MAX_OBSTACLE_SIZE,
	pt.y + MAX_OBSTACLE_SIZE
	};
}
void CObj_Obstacle::setexist(bool swit) {
	if (swit == true) {
		exist = true;
		return;
	}
	if (swit == false) {
		exist = false;
		return;
	}
}