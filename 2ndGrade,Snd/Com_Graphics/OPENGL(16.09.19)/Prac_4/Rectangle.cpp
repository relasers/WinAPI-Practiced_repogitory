#include "Rectangle.h"



CRectangle::CRectangle()
{
}

CRectangle::CRectangle(POINT pt)
{
	point.x = pt.x;
	point.y = pt.y;
}


CRectangle::~CRectangle()
{
}

void CRectangle::Draw()
{
	glColor4f(R,G,B,1.0f);
	glBegin(GL_POLYGON);
		glVertex2i(point.x - width/2,			point.y + height - height / 2); //v1
		glVertex2i(point.x - width / 2,			point.y - height / 2); //v2
		glVertex2i(point.x - width / 2 + width, point.y - height / 2); //v3
		glVertex2i(point.x - width / 2 + width, point.y + height - height / 2); //v4
	glEnd();
}

void CRectangle::Update()
{
	tick++;

	if (tick == MaxTick)
	{
		tick = 0;
		SwapSize();
	}	
}

void CRectangle::SwapSize()
{
	srand((unsigned)time(nullptr));

	int temp = width;
	width = height;
	height = temp;

	R = rand() % 10 / 10.0;
	G = rand() % 10 / 10.0;
	B = rand() % 10 / 10.0;
}
