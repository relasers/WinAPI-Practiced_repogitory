#include "Ractangle.h"



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
	switch (shape) {
	case 0:
		{
			glColor4f(R, G, B, 1.0f);
			glBegin(GL_POLYGON);
			glVertex2i(point.x - width / 2, point.y + height - height / 2); //v1
			glVertex2i(point.x - width / 2, point.y - height / 2); //v2
			glVertex2i(point.x - width / 2 + width, point.y - height / 2); //v3
			glVertex2i(point.x - width / 2 + width, point.y + height - height / 2); //v4
			glEnd();
			break;
		}
	case 1:
		{
			glColor4f(R, G, B, 1.0f);
			glBegin(GL_POLYGON);
			for (int i = 0; i < 360; ++i) {
				glVertex2i(point.x + Width*cos(i*PI / 180.0),
							point.y + Width*sin(i*PI / 180.0)); //v1
			}
			glEnd();
			break;
		}
	
	}
	
}

void CRectangle::Update(int w,int h)
{
	tick++;

	if (tick == MaxTick)
	{
		tick = 0;
		SwapSize();
	}

	point.x += X_vec*speed;
	point.y += Y_vec*speed;

	if (point.x <= 0)
	{
		point.x = 0;
		X_vec *= -1;
	}
	if (point.y <= 0)
	{
		point.y = 0;
		Y_vec *= -1;
	}

	if (point.x >= w)
	{
		point.x = w;
		X_vec *= -1;
	}
	if (point.y >= h)
	{
		point.y = h;
		Y_vec *= -1;
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

void CRectangle::ChangeShape(int s)
{
	shape = s;
}

void CRectangle::IncreaseSpd()
{
	speed++;
	if (speed >= MX_Speed) {
		speed = MX_Speed;
	}
}

void CRectangle::DecreaseSpd()
{
	speed--;
	if (speed <= MN_Speed) {
		speed = MN_Speed;
	}
}
