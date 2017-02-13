#include "stdafx.h"
#include "Traffic_light.h"


CTraffic_light::CTraffic_light()
{
}


CTraffic_light::~CTraffic_light()
{
}

void CTraffic_light::setcolor(int in_color) {
	switch (in_color) {
	case Color_RED: //ª°
		color = (HBRUSH)CreateSolidBrush(RGB(255,0,0));
		break;
	case Color_YELLOW: //≥Î
		color = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
		break;
	case Color_GREEN: //√ 
		color = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
		break;
	}
}
void CTraffic_light::setpos(POINT pt) {
	pos = {
	pt.x,pt.y,pt.x+TRAFFICORBSIZE,pt.y+TRAFFICORBSIZE
	};
}
RECT CTraffic_light::getpos() {
	return pos;
}
HBRUSH CTraffic_light::getcolor() {
	return color;
}
bool CTraffic_light::geton() {
	return on;
}